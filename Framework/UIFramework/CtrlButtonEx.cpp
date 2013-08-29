
#include "MyDialog.h"
#include "CtrlButtonEx.h"

#include "MyGlobal.h"
#include "IniMgr.h"
#include "StringFormat.h"
#include "StringManager.h"
#include "UIManager.h"
#include "PublicFunc.h"


enum
{
	enumBtnZoomActionTag = 0xCCCB0002,
};

CCtrlButtonEx::CCtrlButtonEx()
: m_nFontSize(0)
, m_nFontColor(0)
, m_strFontName(FONT_NAME)
, m_strText("")
, m_titleLabel(NULL)
, m_backgroundSprite(NULL)
, m_backgroundSpriteDispatchTable(NULL)
, m_nAniStretch(CTRLBUTTONANISTRETCH_NORMAL)
, m_isPushed(false)
, m_zoomOnTouchDown(false)
{
}

CCtrlButtonEx::~CCtrlButtonEx()
{
	CC_SAFE_RELEASE(m_titleLabel);
	CC_SAFE_RELEASE(m_backgroundSpriteDispatchTable);
	CC_SAFE_RELEASE(m_backgroundSprite);
}

const char* CCtrlButtonEx::GetBgAni()
{
	return m_strAniSection.c_str();
}

void CCtrlButtonEx::SetBgAni(const char* pszAni)
{
	if (NULL == pszAni)
	{
		return;
	}

	clearBackgroundSprite();

	m_strAniSection = std::string(pszAni);

	if (m_strAniSection.empty())
	{
		return;
	}

	// Normal
	CCScale9Sprite *backgroundNormal = createBackgroundSprite(CCControlStateNormal);
	setBackgroundSpriteForState(backgroundNormal, CCControlStateNormal);
	// Highlighted
	CCScale9Sprite *backgroundHighlighted = createBackgroundSprite(CCControlStateHighlighted);
	setBackgroundSpriteForState(backgroundHighlighted, CCControlStateHighlighted);
	// Disabled
	CCScale9Sprite *backgroundDisable = createBackgroundSprite(CCControlStateDisabled);
	setBackgroundSpriteForState(backgroundDisable, CCControlStateDisabled);
	// Selected
	CCScale9Sprite *backgroundSelected = createBackgroundSprite(CCControlStateSelected);
	setBackgroundSpriteForState(backgroundSelected, CCControlStateSelected);
}

void CCtrlButtonEx::setEnabled(bool enabled)
{
	CCControl::setEnabled(enabled);
	needsLayout();
}

void CCtrlButtonEx::setSelected(bool enabled)
{
	if (!m_bEnabled)
	{
		return;
	}

	m_bSelected = enabled;
	if(m_bSelected)
	{
		m_eState = CCControlStateSelected;
	}
	else
	{
		m_eState = CCControlStateNormal;
	}
	needsLayout();
}

void CCtrlButtonEx::setHighlighted(bool enabled)
{
	if (!m_bEnabled)
	{
		return;
	}

	m_bHighlighted = enabled;
	if(m_bHighlighted)
	{
		m_eState = CCControlStateHighlighted;
	}
	else
	{
		m_eState = CCControlStateNormal;
	}
	needsLayout();

	CCAction *action =getActionByTag(enumBtnZoomActionTag);
	if (action)
	{
		stopAction(action);        
	}

	if( m_zoomOnTouchDown )
	{
		float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 1.1f : 1.0f;
		CCAction *zoomAction =CCScaleTo::create(0.05f, scaleValue);
		zoomAction->setTag(enumBtnZoomActionTag);
		runAction(zoomAction);
	}
}

bool CCtrlButtonEx::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return false;
	}

	if (GetHandle() != g_objUIMgr.GetTouchHandleObj())
	{
		return false;
	}

	m_eState=CCControlStateHighlighted;
	m_isPushed=true;
	this->setHighlighted(true);
	sendActionsForControlEvents(CCControlEventTouchDown);
	return true;
}

void CCtrlButtonEx::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{    
	if (!isEnabled() || isSelected())
	{
		if (isHighlighted())
		{
			setHighlighted(false);
		}
		return;
	}

	bool isTouchMoveInside = isTouchInside(pTouch);
	if (isTouchMoveInside && !isHighlighted())
	{
		m_eState = CCControlStateHighlighted;
		setHighlighted(true);
		sendActionsForControlEvents(CCControlEventTouchDragEnter);
	}
	else if (isTouchMoveInside && isHighlighted())
	{
		sendActionsForControlEvents(CCControlEventTouchDragInside);
	}
	else if (!isTouchMoveInside && isHighlighted())
	{
		m_eState = CCControlStateNormal;
		setHighlighted(false);

		sendActionsForControlEvents(CCControlEventTouchDragExit);        
	}
	else if (!isTouchMoveInside && !isHighlighted())
	{
		sendActionsForControlEvents(CCControlEventTouchDragOutside);        
	}
}
void CCtrlButtonEx::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	m_eState = CCControlStateNormal;
	m_isPushed = false;
	setHighlighted(false);

	if (isTouchInside(pTouch))
	{
		if (GetHandle() == g_objUIMgr.GetTouchHandleObj())
		{
			sendActionsForControlEvents(CCControlEventTouchUpInside);
		}
	}
	else
	{
		sendActionsForControlEvents(CCControlEventTouchUpOutside);        
	}
}

void CCtrlButtonEx::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	m_eState = CCControlStateNormal;
	m_isPushed = false;
	setHighlighted(false);
	sendActionsForControlEvents(CCControlEventTouchCancel);
}

CCScale9Sprite* CCtrlButtonEx::createBackgroundSprite(CCControlState state)
{
	CCAssert(!(CCControlStateNormal != state && CCControlStateHighlighted != state && CCControlStateDisabled != state && CCControlStateSelected != state),
		"CCtrlButtonEx support CCControlStateNormal CCControlStateHighlighted CCControlStateDisabled CCControlStateSelected only!");

	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());

	if (!pAni)
	{
		return NULL;
	}

	int nFrame = 0;

	if (CCControlStateHighlighted == state)
	{
		nFrame = 1;
	}
	else if (CCControlStateDisabled == state)
	{
		nFrame = 2;
	}
	else if (CCControlStateSelected == state)
	{
		nFrame = 3;
	}

	std::string strFrame = FORMAT("Frame%d")<<nFrame;

	const char *pszValue = pAni->GetString(m_strAniSection.c_str(), strFrame.c_str());

	if (NULL == pszValue)
	{
		return NULL;
	}	

	CCScale9Sprite *backgroundSprite = CCScale9Sprite::create(pszValue);

	if (!backgroundSprite)
	{
		return NULL;
	}

 	// 不为9宫格方式
	if (CTRLBUTTONANISTRETCH_NORMAL == m_nAniStretch || CTRLBUTTONANISTRETCH_STRETCH == m_nAniStretch)
	{
		CCRect rectCapInsets = CCRectMake(0, 0, backgroundSprite->getContentSize().width, backgroundSprite->getContentSize().height);
		backgroundSprite->removeAllChildren();
		CCScale9Sprite *backgroundSpriteResize =  backgroundSprite->resizableSpriteWithCapInsets(rectCapInsets);
		return backgroundSpriteResize;
	}

	return backgroundSprite;
}

void CCtrlButtonEx::setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state)
{
	CCAssert(!(CCControlStateNormal != state && CCControlStateHighlighted != state && CCControlStateDisabled != state && CCControlStateSelected != state),
		"CCtrlButtonEx support CCControlStateNormal CCControlStateHighlighted CCControlStateDisabled CCControlStateSelected only!");
	
	if (NULL == sprite)
	{
		return;
	}

	CCScale9Sprite* previousBackgroundSprite = (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);

	if (previousBackgroundSprite)
	{
		removeChild(previousBackgroundSprite, true);
		m_backgroundSpriteDispatchTable->removeObjectForKey(state);
	}

	m_backgroundSpriteDispatchTable->setObject(sprite, state);
	sprite->setVisible(false);
	sprite->setAnchorPoint(ccp(0.5f, 0.5f));
	addChild(sprite);

	if (CTRLBUTTONANISTRETCH_NORMAL != m_nAniStretch)
	{
		sprite->setPreferredSize(CCSizeMake(m_nWidth, m_nHeight));
	}

	// If the current state if equal to the given state we update the layout
	if (getState() == state)
	{
		needsLayout();
	}
}

CCScale9Sprite* CCtrlButtonEx::getBackgroundSpriteForState(CCControlState state)
{
	if (!m_backgroundSpriteDispatchTable)
	{
		return NULL;
	}

	CCScale9Sprite* backgroundSprite=(CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);    
	if (backgroundSprite)
	{
		return backgroundSprite;
	}
	return (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(CCControlStateNormal);
}

void CCtrlButtonEx::clearBackgroundSprite()
{
	CCDictElement * item = NULL;

	CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
	{
		CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();

		if (NULL == sprite)
		{
			continue;
		}

		removeChild(sprite, true);
	}

	m_backgroundSpriteDispatchTable->removeAllObjects();
}

void CCtrlButtonEx::setAniStretch(GLint nAniStretch)
{
	if (m_nAniStretch == nAniStretch)
	{
		return;
	}

	m_nAniStretch = nAniStretch;

	SetBgAni(m_strAniSection.c_str());
}

GLint CCtrlButtonEx::getAniStretch()
{
	return m_nAniStretch;
}

void CCtrlButtonEx::setZoomOnTouchDown(bool zoomOnTouchDown)
{
	m_zoomOnTouchDown = zoomOnTouchDown;
}

bool CCtrlButtonEx::getZoomOnTouchDown()
{
	return m_zoomOnTouchDown;
}

void CCtrlButtonEx::needsLayout()
{
	// Hide the background
	if (m_backgroundSprite) {
		m_backgroundSprite->setVisible(false);
	}

	// Update the background sprite
	this->setBackgroundSprite(this->getBackgroundSpriteForState(m_eState));

	if (m_titleLabel != NULL)
	{
		m_titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
		m_titleLabel->setVisible(true);
	}

	if (m_backgroundSprite != NULL)
	{
		m_backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
		m_backgroundSprite->setVisible(true);   
	}   
}

// on "init" you need to initialize your instance
bool CCtrlButtonEx::init()
{
	if (!CCControl::init())
	{
		return false;
	}

	// Set the default anchor point
	ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));
	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));
	setTouchPriority(g_nControlTouchPri);

	setTouchEnabled(true);
	m_isPushed = false;

	this->setBackgroundSpriteDispatchTable(CCDictionary::create());

	SetBgAni(m_strAniSection.c_str());

	CCLabelTTF *titleText = CCLabelTTF::create(m_strText.c_str(), m_strFontName.c_str(), m_nFontSize);
	titleText->setColor(ccGetColor3B(m_nFontColor));
	titleText->setOpacity(ccGetOpacity(m_nFontColor));
	setTitleLabelInButton(titleText);

	return true;
}

GLint CCtrlButtonEx::readNode()
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

	m_nAniStretch = pIni->GetValue(strIndex.c_str(), "AniStretch", CTRLBUTTONANISTRETCH_STRETCH);

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

	return 0;
}

void CCtrlButtonEx::setTitleLabelInButton(CCNode* titleLabel)
{
	if (m_titleLabel)
	{
		removeChild(m_titleLabel, true);
	}

	titleLabel->setVisible(false);
	titleLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	addChild(titleLabel, 1);
	setTitleLabel(titleLabel);
	needsLayout();
}

GLint CCtrlButtonEx::initGUI()
{
	GLint nRet = this->readNode();

	if (!init())
	{
		return -1;
	}

	return nRet;
}

CCMyWndObject* CCtrlButtonEx::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return NULL;
	}

	return this;
}
