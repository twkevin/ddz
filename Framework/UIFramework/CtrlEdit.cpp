#include "MyDialog.h"
#include "CtrlEdit.h"

#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"
#include "UIManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace
{
	static bool g_sbIsKeyboradShow = false;
}

static int _calcCharCount(const char * pszText)
{
	int n = 0;
	char ch = 0;
	while ((ch = *pszText))
	{
		CC_BREAK_IF(! ch);

		if (0x80 != (0xC0 & ch))
		{
			++n;
		}
		++pszText;
	}
	return n;
}

CCtrlTextFieldTTF::CCtrlTextFieldTTF()
	: m_nInputType(EditInputFlagAll)
	, m_strText("")
	, EventChanged(NULL)
{

}

CCtrlTextFieldTTF::~CCtrlTextFieldTTF()
{

}

CCtrlTextFieldTTF * CCtrlTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{        
	CCtrlTextFieldTTF *pRet = new CCtrlTextFieldTTF();
	if(pRet && pRet->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
	{
		pRet->autorelease();
		if (placeholder)
		{
			pRet->setPlaceHolder(placeholder);
		}
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CCtrlTextFieldTTF::SetInputFlag(EditInputFlag nInputFlag)
{
	m_nInputType = nInputFlag;
}

EditInputFlag CCtrlTextFieldTTF::GetInputFlag() const
{
	return m_nInputType;
}

std::string CCtrlTextFieldTTF::GetText() const
{
	return m_strText;
}

void CCtrlTextFieldTTF::SetText(const char *pszText)
{
    if (pszText)
    {
        m_strText = pszText;
    }
    else
    {
        m_strText = "";
    }
}

void CCtrlTextFieldTTF::insertText(const char * text, int len)
{
	std::string sInsert(text, len);

	// insert \n means input end
	int nPos = sInsert.find('\n');
	if ((int)sInsert.npos != nPos)
	{
		len = nPos;
		sInsert.erase(nPos);
	}

	if (len > 0)
	{
		if (EditInputFlagAll == m_nInputType)
		{
			if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, sInsert.c_str(), len))
			{
				// delegate doesn't want to insert text
				return;
			}

			m_strText.append(sInsert);
			m_nCharCount += _calcCharCount(sInsert.c_str());
			std::string sText(*m_pInputText);
			sText.append(sInsert);
			setString(sText.c_str());
		}
		else if (EditInputFlagPassword == m_nInputType)
		{
			int nInsertSize = _calcCharCount(sInsert.c_str());
			std::string strInsert = "";
			for (int i=0; i<nInsertSize; ++i)
			{
				strInsert.append("*");
			}

			if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, strInsert.c_str(), nInsertSize))
			{
				// delegate doesn't want to insert text
				return;
			}

			m_strText.append(sInsert);
			m_nCharCount += nInsertSize;
			std::string sText(*m_pInputText);
			sText.append(strInsert);			

			setString(sText.c_str());
		}

		if (EventChanged)
		{
			EventChanged();
		}
	}

	if ((int)sInsert.npos == nPos) {
		return;
	}

	// '\n' inserted, let delegate process first
	if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, "\n", 1))
	{
		return;
	}

	// if delegate hasn't processed, detach from IME by default
	detachWithIME();
}

void CCtrlTextFieldTTF::deleteBackward()
{
	int nStrLen = m_pInputText->length();
	if (! nStrLen)
	{
		// there is no string
		return;
	}

	// get the delete byte number
	int nDeleteLen = 1;    // default, erase 1 byte

	while(0x80 == (0xC0 & m_pInputText->at(nStrLen - nDeleteLen)))
	{
		++nDeleteLen;
	}

	if (m_pDelegate && m_pDelegate->onTextFieldDeleteBackward(this, m_pInputText->c_str() + nStrLen - nDeleteLen, nDeleteLen))
	{
		// delegate doesn't wan't to delete backwards
		return;
	}

	// if all text deleted, show placeholder string
	if (nStrLen <= nDeleteLen)
	{
		CC_SAFE_DELETE(m_pInputText);
		m_pInputText = new std::string;
		m_nCharCount = 0;
		CCLabelTTF::setString(m_pPlaceHolder->c_str());
		m_strText = "";

		if (EventChanged)
		{
			EventChanged();
		}
		return;
	}

	// set new input text
	std::string strText(m_strText.c_str(), nStrLen - nDeleteLen);
	m_strText = strText;

	std::string sText(m_pInputText->c_str(), nStrLen - nDeleteLen);
	setString(sText.c_str());

	if (EventChanged)
	{
		EventChanged();
	}
}

KeyboardNotificationLayer::KeyboardNotificationLayer()
	: m_pTrackNode(0)
	, m_pWnd(0)
{
	setTouchEnabled(true);
}

void KeyboardNotificationLayer::SetWndObject(CCtrlEdit* pWnd)
{
	m_pWnd = pWnd;
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, g_nHandleEditPri, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
	if (! m_pTrackNode)
	{
		return;
	}

	CCRect rectTracked = ccGetRect(m_pTrackNode);
	// if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
	if (! rectTracked.intersectsRect(info.end))
	{
		return;
	}

	// assume keyboard at the bottom of screen, calculate the vertical adjustment.
	float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
	CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

	// move all the children node of KeyboardNotificationLayer
	/*CCArray * children = getChildren();
	CCNode * node = 0;
	int count = children->count();
	CCPoint pos;
	for (int i = 0; i < count; ++i)
	{
		node = (CCNode*)children->objectAtIndex(i);
		pos = node->getPosition();
		pos.y += adjustVert;
		node->setPosition(pos);
	}*/
}

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_beginPos = pTouch->getLocation();    
	return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (! m_pTrackNode)
	{
		return;
	}

	CHECK(m_pWnd);

	CCPoint endPos = pTouch->getLocation();    

	float delta = 5.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	// decide the trackNode is clicked.
	if (m_pWnd)
	{
		CCPoint touchLocation = pTouch->getLocation();
		touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
		CCRect bBox= m_pWnd->boundingBox();
		bool bIsClick = bBox.containsPoint(touchLocation);
		this->onClickTrackNode(bIsClick);
	}	
}

CCtrlEdit::CCtrlEdit()
	: m_nFontSize(0)
	, m_nFontColor(0)
	, m_strFontName(FONT_NAME)
	, m_strText("")
	, m_pTextField(NULL)
	, EventChanged(0)
	, EventInputEnd(0)
	, m_nCharLimit(1024)
    , m_RecordPos(0.0f,0.0f)
	, m_pCursorSprite(NULL)
{
	m_infoIMEKeyboardNotification.duration = 0.25f;
	m_infoIMEKeyboardNotification.begin = CCRect(0, 0, 0, 0);
	m_infoIMEKeyboardNotification.end = CCRect(0, 0, 0, 0);

	this->SetWndObject(this);
}

CCtrlEdit::~CCtrlEdit()
{
	CC_SAFE_RELEASE(m_pCursorAction);
}

bool CCtrlEdit::init()
{
	setKeypadEnabled(true);
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));
	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));

	m_pTextField = CCtrlTextFieldTTF::textFieldWithPlaceHolder(m_strText.c_str(), CCSize(m_nWidth, m_nHeight), (CCTextAlignment)kCCTextAlignmentLeft,  m_strFontName.c_str(), m_nFontSize);

	CHECKF(m_pTextField);
	m_pTextField->setColorSpaceHolder(ccGetColor3B(m_nFontColor));
	m_pTextField->setContentSize(CCSizeMake(m_nWidth, m_nHeight));	
    m_pTextField->setAnchorPoint(ccp(0, 0));
	m_pTextField->setPosition(ccp(0, 0));
	m_pTextField->setDelegate(this);
	m_pTextField->EventChanged.bind(this, &CCtrlEdit::textChange);
	

    addChild(m_pTextField);
	
	m_pTrackNode = m_pTextField;
	int nHeight = static_cast<int>(m_nFontSize * CC_CONTENT_SCALE_FACTOR() * 1.33f);
	initCursorSprite(nHeight);
    return true;
}

GLint CCtrlEdit::readNode()
{
	GLint nRet = CCMyWndObject::readNode();

	if (0 != nRet)
	{
		return -1;
	}

	CMyIni* pIni = g_objIniMgr.GetMyIniPtr(m_strGuiPath.c_str());

	if (NULL == pIni)
	{
		return -1;
	}

	std::string strIndex = FORMAT("%d-%d") << m_nParentWndID << m_nWndID;

	m_nFontSize = pIni->GetValue(strIndex.c_str(), "fontSize", g_nDefualtFontSize);
	m_nFontColor = pIni->GetValue(strIndex.c_str(), "fontColor", g_nDefualtFontColor);

	const char *pszValue = pIni->GetString(strIndex.c_str(), "text");
	if (pszValue)
	{
		 const char* pszStr= g_objStrMgr.GetStr(pszValue);
		 if (pszStr)
		 {
			 m_strText = pszStr;
		 }
		 else
		 {
			 m_strText = "";
		 }
	}
	else
	{
		m_strText = "";
	}
    
    int nPwd = pIni->GetValue(strIndex.c_str(), "pwd", 0);
    if (1 == nPwd)
    {
        this->SetInputFlag(EditInputFlagPassword);
    }

	return 0;
}

GLint CCtrlEdit::initGUI()
{
	GLint nRet = this->readNode();

	init();

	return nRet;
}

std::string CCtrlEdit::subtitle()
{
	return "CCtrlEdit with Cursor";
}

void CCtrlEdit::onClickTrackNode(bool bClicked)
{
	CCtrlTextFieldTTF * pTextField = (CCtrlTextFieldTTF*)m_pTrackNode;
	if (bClicked)
	{
		if (!g_sbIsKeyboradShow)
		{
			pTextField->attachWithIME();
			g_sbIsKeyboradShow = true;
		}
	}
	else
	{
		if (g_sbIsKeyboradShow)
		{
			pTextField->detachWithIME();
			g_sbIsKeyboradShow = false;
		}	
	}
}

void CCtrlEdit::onEnter()
{
	KeyboardNotificationLayer::onEnter();

	m_pCursorAction = CCRepeatForever::create(
		CCSequence::create(
		CCFadeOut::create(0.25),
		CCFadeIn::create(0.25),
		0
		));
	m_pCursorAction->retain();
}

void CCtrlEdit::initCursorSprite(int nHeight)
{
	// 初始化光标
	const int column = 4;
	m_pCursorSprite = CCScale9Sprite::create("data/extensions/cursor.png");
	m_pCursorSprite->setPreferredSize(CCSizeMake(column, nHeight));
	
	CCRect bBox= this->boundingBox();
	m_pCursorSprite->setAnchorPoint(ccp(0.0f, 0.5f));
	m_pCursorSprite->setPosition(ccp(0, bBox.size.height / 2 + 4));

	this->addChild(m_pCursorSprite);

	m_pCursorSprite->setVisible(false);
}

void CCtrlEdit::onExit()
{
	KeyboardNotificationLayer::onExit();

	CC_SAFE_RELEASE(m_pCursorAction);
}

// CCTextFieldDelegate protocol
bool CCtrlEdit::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
	showKeyboard();

	return false;
}

bool CCtrlEdit::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
	hideKeyboard();

	return false;
}

CCSize CCtrlEdit::GetTextSize(const char * text)
{
	CCSize textSize(0.0f,0.0f);

	if (NULL == text)
	{
		return textSize;
	}

	do
	{
		CCTexture2D *tex = new CCTexture2D();
		CC_BREAK_IF(!tex);

		float fContentScaleFactor= CCDirector::sharedDirector()->getContentScaleFactor();
		bool bRet = tex->initWithString( text,
			m_strFontName.c_str(),
			m_nFontSize * fContentScaleFactor,
			CCSizeZero,
			m_pTextField->getHorizontalAlignment(),
			m_pTextField->getVerticalAlignment());

		if (bRet)
		{
			float fOffsetX = tex->getPixelsWide();
			fOffsetX /= fContentScaleFactor;
			textSize.width += fOffsetX;

			float fOffsetY = tex->getPixelsHigh();
			fOffsetY /= fContentScaleFactor;
			textSize.height += fOffsetY;
		}

		tex->release();
	}while(false);

	return textSize;
}

bool CCtrlEdit::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen)
{
	if (NULL == pSender)
	{
		return false;
	}

	// if insert enter, treat as default to detach with ime
	if ('\n' == *text)
	{
		return false;
	}

	// if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
	if (pSender->getCharCount() >= m_nCharLimit)
	{
		return true;
	}

	
	CCSize testSize1 = GetTextSize(pSender->getString());
	float fPosX = testSize1.width;
	CCSize testSize = GetTextSize(text);

	fPosX += testSize.width;

	if (fPosX > m_nWidth)
	{
		return true;
	}

	if (EventChanged)
	{
		EventChanged();
	}

	return false;
}

bool CCtrlEdit::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
	m_pCursorSprite->setPositionX(m_posCursor.x);

	if (EventChanged)
	{
		EventChanged();
	}

	return false;
}

bool CCtrlEdit::onDraw(CCTextFieldTTF * pSender)
{
	return false;
}

void CCtrlEdit::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
	this->removeChild(pNode, true);
}

void CCtrlEdit::SetInputFlag(EditInputFlag nInputFlag)
{
	if (m_pTextField)
	{
		m_pTextField->SetInputFlag(nInputFlag);
	}
}

EditInputFlag CCtrlEdit::GetInputFlag() const
{
	if (m_pTextField)
	{
		return m_pTextField->GetInputFlag();
	}

	return EditInputFlagErr;
}

std::string CCtrlEdit::getString()
{
	if (m_pTextField)
	{
		return m_pTextField->GetText();
	}

	return std::string("");
}

void CCtrlEdit::setString(const char* pszText)
{
	if (NULL == pszText)
	{
		return;
	}

	if (m_pTextField)
	{
		CCSize testSize = GetTextSize(pszText);
		m_posCursor.x = testSize.width;
		m_pCursorSprite->setPositionX(m_posCursor.x);

		m_pTextField->setString(pszText);
        m_pTextField->SetText(pszText);
	}
}

std::string CCtrlEdit::getPlaceHolder()
{
	if (m_pTextField)
	{
        const char* pszText = m_pTextField->getPlaceHolder();
        if (pszText)
        {
            return std::string(pszText);
        }
	}

	return std::string("");
}

bool CCtrlEdit::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isVisible())
	{
		return false;
	}
    
	if (GetHandle() != g_objUIMgr.GetTouchHandleObj())
	{
		hideKeyboard();

		return false;
	}
    
	m_beginPos = pTouch->getLocation();    
	return true;
}

CCMyWndObject* CCtrlEdit::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (NULL == m_pWnd)
	{
		return NULL;
	}

	CCPoint touchLocation = pTouch->getLocation();
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox= m_pWnd->boundingBox();
	bool bIsClick = bBox.containsPoint(touchLocation);
	if (bIsClick)
	{
		return this;
	}

	return NULL;
}

void CCtrlEdit::keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info)
{
    if (!isVisible())
	{
		return;
	}
    
	if (GetHandle() != g_objUIMgr.GetTouchHandleObj())
	{
		return;
	}

	m_infoIMEKeyboardNotification.duration = info.duration;
	m_infoIMEKeyboardNotification.begin = info.begin;
	m_infoIMEKeyboardNotification.end = info.end;

}

void CCtrlEdit::keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info)
{
}

void CCtrlEdit::keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info)
{
    if (!isVisible())
	{
		return;
	}
    
	m_infoIMEKeyboardNotification.duration = info.duration;
	m_infoIMEKeyboardNotification.begin = info.begin;
	m_infoIMEKeyboardNotification.end = info.end;
}

void CCtrlEdit::keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info)
{
    
}

void CCtrlEdit::textChange()
{
	if (m_pTextField)
	{
		const char* pszText = m_pTextField->getString();
		if (pszText)
		{
			CCSize sizeText = GetTextSize(pszText);
			if (m_pCursorSprite)
			{
				std::string strTmp = pszText;
				if (!strTmp.empty())
				{
					m_pCursorSprite->setPositionX(sizeText.width);
				}
				else
				{
					m_pCursorSprite->setPositionX(0);
				}
			}
		}
		else
		{
			if (m_pCursorSprite)
			{
				m_pCursorSprite->setPositionX(0);
			}
		}
	}
}

void CCtrlEdit::setOnFocus(bool bIsOnFocus)
{
	if (NULL == m_pCursorSprite)
	{
		return;
	}

	if (bIsOnFocus)
	{
		m_pCursorSprite->setVisible(true);
		m_pCursorSprite->runAction(m_pCursorAction);	
	}
	else
	{
		m_pCursorSprite->setVisible(false);
		m_pCursorSprite->stopAction(m_pCursorAction);
	}	
}

bool CCtrlEdit::isOnFocus() const
{
	if (NULL == m_pCursorSprite)
	{
		return false;
	}

	if (m_pCursorSprite->isVisible())
	{
		return true;
	}

	return false;
}

void CCtrlEdit::doKeyboardShowDelayAction()
{
	CCActionInterval *delay = CCDelayTime::create(0.3f);
	this->runAction(CCSequence::create(delay,CCCallFunc::create(this, callfunc_selector(CCtrlEdit::doKeyboardShowAction)),NULL));
}

void CCtrlEdit::doKeyboardShowAction()
{
	if (!isVisible())
	{
		return;
	}

	DLG_HANDLE hHandleDlg = GetTopParent();
	CCMyWndObject* pWndObject = g_objUIMgr.GetWndObj(hHandleDlg);
	if (NULL == pWndObject)
	{
		return;
	}

	CCNode *pHandleNode = dynamic_cast<CCNode*>(pWndObject);
	if (NULL == pHandleNode)
	{
		return;
	}

	CCPoint destPos = getPosition();
	CCRect bgRect(destPos.x, destPos.y, m_nWidth, m_nHeight);

	if (bgRect.origin.y - m_nHeight < m_infoIMEKeyboardNotification.end.origin.y + m_infoIMEKeyboardNotification.end.size.height)
	{
        m_RecordPos.y = pHandleNode->getPositionY();
        m_RecordPos.x = 0;
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        
        destPos.x = 0;
        destPos.y = m_infoIMEKeyboardNotification.end.size.height+ visibleSize.height;        


		CCMoveTo* moveTo = CCMoveTo::create(m_infoIMEKeyboardNotification.duration, destPos);		

		pHandleNode->runAction(moveTo);
	}
}

void CCtrlEdit::doKeyboardHideAction()
{
	if (!isVisible())
	{
		return;
	}

	CCPoint destPos = getPosition();

	if (fabs(m_infoIMEKeyboardNotification.end.size.height) < (destPos.y - m_nHeight))
	{
		return;
	}
	
	DLG_HANDLE hHandleDlg = GetTopParent();
	CCMyWndObject* pWndObject = g_objUIMgr.GetWndObj(hHandleDlg);
	if (NULL == pWndObject)
	{
		return;
	}
    
	CCNode *pHandleNode = dynamic_cast<CCNode*>(pWndObject);
	if (NULL == pHandleNode)
	{
		return;
	}

	CCMoveTo* moveTo = CCMoveTo::create(m_infoIMEKeyboardNotification.duration, m_RecordPos);
	pHandleNode->runAction(moveTo);
}

void CCtrlEdit::showKeyboard()
{
	if (!isOnFocus())
	{
		setOnFocus(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID        || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		float fContentScaleFactor= CCDirector::sharedDirector()->getContentScaleFactor();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		m_infoIMEKeyboardNotification.duration = 0.25f;
		m_infoIMEKeyboardNotification.end.origin.y = 0;
		m_infoIMEKeyboardNotification.end.size.height = (visibleSize.height / 2 - 100)* fContentScaleFactor;
        
        doKeyboardShowDelayAction();
#endif
	}
}

void CCtrlEdit::hideKeyboard()
{
	if (isOnFocus())
	{	
		setOnFocus(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID        || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		m_infoIMEKeyboardNotification.duration = 0.25f;
        doKeyboardHideAction();

		CCtrlTextFieldTTF * pTextField = (CCtrlTextFieldTTF*)m_pTrackNode;
		if (pTextField)
		{
			if (g_sbIsKeyboradShow)
			{
				pTextField->detachWithIME();				
			}
		}

		if (EventInputEnd)
		{
			EventInputEnd();
		}
#endif
		g_sbIsKeyboradShow = false;
	}	
}

void CCtrlEdit::keyBackClicked()
{
	CCLOG("CCtrlEdit::keyBackClicked()");
	if (!isVisible())
	{
		return;
	}

	if (g_sbIsKeyboradShow)
	{
		CCLOG("CCtrlEdit::keyBackClicked() IsKeyboradShow");
		setOnFocus(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID        || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		m_infoIMEKeyboardNotification.duration = 0.25f;
		doKeyboardHideAction();

		CCtrlTextFieldTTF * pTextField = (CCtrlTextFieldTTF*)m_pTrackNode;
		if (pTextField)
		{
			pTextField->detachWithIME();
		}

		if (EventInputEnd)
		{
			EventInputEnd();
		}
#endif
		g_sbIsKeyboradShow = false;
	}
	

	KeyboardNotificationLayer::keyBackClicked();	
}

void CCtrlEdit::keyMenuClicked()
{
	CCLOG("CCtrlEdit::keyMenuClicked()");
	KeyboardNotificationLayer::keyMenuClicked();
}

