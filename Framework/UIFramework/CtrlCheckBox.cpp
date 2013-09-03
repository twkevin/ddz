#include "MyDialog.h"
#include "CtrlCheckBox.h"

#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"
#include "UIManager.h"
#include "PublicFunc.h"

enum
{
	kZoomActionTag = 0xCCCB0001,
};

CCtrlCheckBox::CCtrlCheckBox()
	: m_bChecked(false)
	, m_pSpriteUnchecked(NULL)
	, m_pSpriteChecked(NULL)
	, m_pLabelText(NULL)
	, m_nLeftOffset(0)
	, m_nFontSize(0)
	, m_nFontColor(0)
	, m_strText("")
	, m_strFontName(FONT_NAME)
	, m_zoomOnTouchDown(false)
{

}

CCtrlCheckBox::~CCtrlCheckBox()
{
	CC_SAFE_RELEASE(m_pSpriteUnchecked);
	CC_SAFE_RELEASE(m_pSpriteChecked);
	CC_SAFE_RELEASE(m_pLabelText);
}

bool CCtrlCheckBox::init()
{
	if ( !CCControl::init())
	{
		return false;
	}

	return true;
}

GLint CCtrlCheckBox::readNode()
{
	GLint nRet = CCMyWndObject::readNode();

	if (0 != nRet)
	{
		return -1;
	}

	this->ignoreAnchorPointForPosition(false);
	this->setTouchEnabled(true);
	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));
	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));
	this->setEnabled(true);

	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());
	if (!pAni)
	{
		return -1;
	}

	const char *pszValue = pAni->GetString(m_strAniSection.c_str(), "Frame0");
	if (NULL == pszValue)
	{
		return -1;
	}

	CCScale9Sprite* pUncheckedSprite = CCScale9Sprite::create(pszValue);
	if (NULL == pUncheckedSprite)
	{
		return -1;
	}
	
	setZoomOnTouchDown(true);
	setSpriteUnchecked(pUncheckedSprite);
	this->addChild(getSpriteUnchecked());
	pUncheckedSprite->setPosition(pUncheckedSprite->getContentSize().width/2,this->getContentSize().height/2);

	const char *pszValueCheck = pAni->GetString(m_strAniSection.c_str(), "Frame1");
	if (NULL == pszValueCheck)
	{
		return -1;
	}

	CCScale9Sprite* pCheckedSprite = CCScale9Sprite::create(pszValueCheck);
	if (NULL == pCheckedSprite)
	{
		return -1;
	}

	setSpriteChecked(pCheckedSprite);
	addChild(getSpriteChecked());
	pCheckedSprite->setPosition(pCheckedSprite->getContentSize().width/2,this->getContentSize().height/2);
	getSpriteChecked()->setVisible(false);

	CMyIni* pIni = g_objIniMgr.GetMyIniPtr(m_strGuiPath.c_str());

	if (NULL == pIni)
	{
		return -1;
	}

	std::string strIndex = FORMAT("%d-%d") << m_nParentWndID << m_nWndID;

	m_nFontSize = pIni->GetValue(strIndex.c_str(), "fontSize", g_nDefualtFontSize);
	m_nFontColor = pIni->GetValue(strIndex.c_str(), "fontColor", g_nDefualtFontColor);
	m_nLeftOffset = pIni->GetValue(strIndex.c_str(), "leftOffset", 0);

	const char *pszTextValue = pIni->GetString(strIndex.c_str(), "text");
	if (pszTextValue)
	{
		const char* pszStr= g_objStrMgr.GetStr(pszTextValue);
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

	m_pLabelText = CCLabelTTF::create(m_strText.c_str(), m_strFontName.c_str(), m_nFontSize, CCSizeZero, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	if (m_pLabelText)
	{
		this->addChild(m_pLabelText);
		m_pLabelText->setColor(ccGetColor3B(m_nFontColor));
		int nWidth = getSpriteUnchecked()->getContentSize().width;
		m_pLabelText->setPosition(ccp(m_pLabelText->getContentSize().width/2 + (nWidth + m_nLeftOffset), this->getContentSize().height/2));
	}

	return 0;
}

GLint CCtrlCheckBox::initGUI()
{
	if (!init())
	{
		return 0;
	}

	GLint nRet = this->readNode();

	return nRet;
}

void CCtrlCheckBox::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	setHighlighted(false);
	if (isTouchInside(pTouch))
	{
		getSpriteChecked()->setVisible(!m_bChecked);
		getSpriteUnchecked()->setVisible(m_bChecked);
		m_bChecked = !m_bChecked;
		sendActionsForControlEvents(CCControlEventTouchUpInside);        
	}
	else
	{
		sendActionsForControlEvents(CCControlEventTouchUpOutside);        
	}
}

bool CCtrlCheckBox::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return false;
	}

	if (GetHandle() != g_objUIMgr.GetTouchHandleObj())
	{
		return false;
	}

	this->setHighlighted(true);
	sendActionsForControlEvents(CCControlEventTouchDown);
	return true;
}

void CCtrlCheckBox::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
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

void CCtrlCheckBox::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	setHighlighted(false);
	sendActionsForControlEvents(CCControlEventTouchCancel);
}

void CCtrlCheckBox::setZoomOnTouchDown(bool zoomOnTouchDown)
{
	m_zoomOnTouchDown = zoomOnTouchDown;
}

bool CCtrlCheckBox::getZoomOnTouchDown()
{
	return m_zoomOnTouchDown;
}

void CCtrlCheckBox::setHighlighted( bool enabled )
{
	CCControl::setHighlighted(enabled);

	CCAction *action =getActionByTag(kZoomActionTag);
	if (action)
	{
		stopAction(action);        
	}
	needsLayout();
	if( m_zoomOnTouchDown )
	{
		float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 1.1f : 1.0f;
		CCAction *zoomAction =CCScaleTo::create(0.05f, scaleValue);
		zoomAction->setTag(kZoomActionTag);
		runAction(zoomAction);
	}
}

bool CCtrlCheckBox::getChecked()
{
	return m_bChecked;
}

void CCtrlCheckBox::setChecked( bool Checked )
{
	if (m_bChecked != Checked)
	{
		getSpriteChecked()->setVisible(!m_bChecked);
		getSpriteUnchecked()->setVisible(m_bChecked);
		m_bChecked = Checked;
	}
}

CCMyWndObject* CCtrlCheckBox::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return NULL;
	}

	return this;
}



