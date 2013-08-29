#include "MyDialog.h"
#include "CtrlImageEx.h"

#include "MyGlobal.h"
#include "IniMgr.h"
#include "StringFormat.h"
#include "StringManager.h"
#include "PublicFunc.h"
#include "UIManager.h"

CCtrlImageEx::CCtrlImageEx()
: m_backgroundSprite(NULL)
, m_backgroundSpriteDispatchTable(NULL)
, m_nAniStretch(CTRLIMAGEANISTRETCH_STRETCH)
{
}

CCtrlImageEx::~CCtrlImageEx()
{
	CC_SAFE_RELEASE(m_backgroundSpriteDispatchTable);
	CC_SAFE_RELEASE(m_backgroundSprite);
}


bool CCtrlImageEx::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
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
	this->setHighlighted(true);
	sendActionsForControlEvents(CCControlEventTouchDown);
	return true;
}

void CCtrlImageEx::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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
void CCtrlImageEx::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	m_eState = CCControlStateNormal;
	setHighlighted(false);

	if (isTouchInside(pTouch))
	{
		//if (GetHandle() == g_objUIMgr.GetTouchHandleObj())
		{
			sendActionsForControlEvents(CCControlEventTouchUpInside);
		}
	}
	else
	{
		sendActionsForControlEvents(CCControlEventTouchUpOutside);        
	}
}

void CCtrlImageEx::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	m_eState = CCControlStateNormal;
	setHighlighted(false);
	sendActionsForControlEvents(CCControlEventTouchCancel);
}

const char* CCtrlImageEx::GetBgAni()
{
	return m_strAniSection.c_str();
}

void CCtrlImageEx::SetBgAni(const char* pszAni)
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
	// Disabled
	CCScale9Sprite *backgroundDisable = createBackgroundSprite(CCControlStateDisabled);
	setBackgroundSpriteForState(backgroundDisable, CCControlStateDisabled);
}

CCScale9Sprite* CCtrlImageEx::createBackgroundSprite(CCControlState state)
{
	CCAssert(!(CCControlStateNormal != state && CCControlStateDisabled != state),
		"CCtrlImageEx support CCControlStateNormal and CCControlStateDisabled only!");

	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());

	if (!pAni)
	{
		return NULL;
	}

	int nFrame = 0;

	if (CCControlStateDisabled == state)
	{
		nFrame = 1;
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
	if (CTRLIMAGEANISTRETCH_NORMAL == m_nAniStretch || CTRLIMAGEANISTRETCH_STRETCH == m_nAniStretch)
	{
		CCRect rectCapInsets = CCRectMake(0, 0, backgroundSprite->getContentSize().width, backgroundSprite->getContentSize().height);
		backgroundSprite->removeAllChildren();
		CCScale9Sprite *backgroundSpriteResize =  backgroundSprite->resizableSpriteWithCapInsets(rectCapInsets);
		return backgroundSpriteResize;
	}

	return backgroundSprite;
}

void CCtrlImageEx::setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state)
{
	CCAssert(!(CCControlStateNormal != state && CCControlStateDisabled != state),
		"CCtrlImageEx support CCControlStateNormal and CCControlStateDisabled only!");

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

	if (CTRLIMAGEANISTRETCH_NORMAL != m_nAniStretch)
	{
		sprite->setPreferredSize(CCSizeMake(m_nWidth, m_nHeight));
	}

	// If the current state if equal to the given state we update the layout
	if (getState() == state)
	{
		needsLayout();
	}
}

CCScale9Sprite* CCtrlImageEx::getBackgroundSpriteForState(CCControlState state)
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

void CCtrlImageEx::clearBackgroundSprite()
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

void CCtrlImageEx::setAniStretch(GLint nAniStretch)
{
	if (m_nAniStretch == nAniStretch)
	{
		return;
	}

	m_nAniStretch = nAniStretch;

	SetBgAni(m_strAniSection.c_str());
}

GLint CCtrlImageEx::getAniStretch()
{
	return m_nAniStretch;
}

void CCtrlImageEx::needsLayout()
{
	// Hide the background
	if (m_backgroundSprite) {
		m_backgroundSprite->setVisible(false);
	}

	// Update the background sprite
	this->setBackgroundSprite(this->getBackgroundSpriteForState(m_eState));

	if (m_backgroundSprite != NULL)
	{
		m_backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
	}

	//TODO: should this also have margins if one of the preferred sizes is relaxed?
	if (m_backgroundSprite != NULL)
	{
		CCSize preferredSize = m_backgroundSprite->getPreferredSize();

		if (preferredSize.width > 0 && preferredSize.height > 0)
		{
			m_backgroundSprite->setContentSize(preferredSize);
		}
	}

	if (m_backgroundSprite != NULL)
	{
		m_backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
		m_backgroundSprite->setVisible(true);   
	}   
}

// on "init" you need to initialize your instance
bool CCtrlImageEx::init()
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
	
	setTouchEnabled(false);

	this->setBackgroundSpriteDispatchTable(CCDictionary::create());

	SetBgAni(m_strAniSection.c_str());

	return true;
}

GLint CCtrlImageEx::readNode()
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

	int nAniStretch = pIni->GetValue(strIndex.c_str(), "AniStretch", CTRLIMAGEANISTRETCH_STRETCH);

	if (CTRLIMAGEANISTRETCH_NORMAL == nAniStretch || CTRLIMAGEANISTRETCH_STRETCH == nAniStretch
		|| CTRLIMAGEANISTRETCH_STRETCHNINESIGNAL == nAniStretch)
	{
		m_nAniStretch = nAniStretch;
	}

	return 0;
}

GLint CCtrlImageEx::initGUI()
{
	GLint nRet = this->readNode();

	if (!init())
	{
		return -1;
	}

	return nRet;
}

CCMyWndObject* CCtrlImageEx::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || IsMsgThrough())
	{
		return NULL;
	}

	return this;
}
