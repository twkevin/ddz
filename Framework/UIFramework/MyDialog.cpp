#include "MyDialog.h"
#include "UIManager.h"
#include "StringFormat.h"

#include "IniMgr.h"
#include "MyGlobal.h"
#include "PublicFunc.h"
#include "CtrlList.h"
#include "CtrlPage.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCMyDialog::CCMyDialog()
	: m_isInit(false)
	, m_backgroundSprite(NULL)
	, m_nAniStretch(enumUISTRETCH_STRETCH)
{
}

CCMyDialog::~CCMyDialog()
{
	CC_SAFE_RELEASE(m_backgroundSprite);
}


CCMyDialog* CCMyDialog::createEx(int nWndID, CCMyDialog *pParent)
{
	CCMyDialog *pRet = new CCMyDialog();
	if (pRet)
	{
		pRet->Create(nWndID, pParent);
		g_objUIMgr.AddDlg(pRet);	
		return pRet; 
	}

	return NULL;
}

CCMyDialog* CCMyDialog::create(int nWndID)
{
	return  CCMyDialog::createEx(nWndID, NULL);
}

CCMyDialog* CCMyDialog::newDlg(int nWndID)
{
	CCMyDialog *pRet = new CCMyDialog();
	if (pRet)
	{
		pRet->setWndID(nWndID);
		return pRet; 
	}

	return NULL;
}

bool CCMyDialog::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	initGUI();
	DoDataExchange((void *)m_nWndID);
	BindEvent();

    return true;
}

GLint CCMyDialog::readNode()
{
	GLint nRet = CCDialogBase::readNode();

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

	int nAniStretch = pIni->GetValue(strIndex.c_str(), "AniStretch", enumUISTRETCH_STRETCH);
	setAniStretch(nAniStretch);

	ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));
	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));

	setTouchPriority(g_nDialogTouchPri);
	setTouchEnabled(true);

	CCLOG("strIndex = %s",strIndex.c_str());
	CCLOG("m_nWidth = %d, m_nHeight = %d",m_nWidth, m_nHeight);
	CCLOG("m_strAniSection = %s",m_strAniSection.c_str());
	SetBgAni(m_strAniSection.c_str());

	return 0;
}

int CCMyDialog::GetType() const
{
	return CTRL_DIALOG;
}

void CCMyDialog::Create( int nWndID, CCMyWndObject *pParent /*= NULL*/ )
{
	if (m_isInit)
	{
		return;
	}
	
	m_isInit = true;
	CCDialogBase::Create(nWndID, pParent);
	this->init();
	setVisible(false);
}

void CCMyDialog::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool CCMyDialog::isTouchInside(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

bool CCMyDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !isVisible())
	{
		return false;
	}

	DLG_HANDLE hDlgTouch = g_objUIMgr.OnTouchBegan(pTouch);

	// 如果支持拖拽就return true，吃掉touch事件
	return false;
}

void CCMyDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CCMyDialog::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CCMyDialog::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CCMyDialog::OnNetPackage(void* pDataPkg)
{
	LIST_CTRL& clds = GetChild();
	CCMyWndObject* lpItem = NULL;
	CCMyDialog* lpDlg = NULL;
	LIST_CTRL::iterator itr = clds.begin();
	LIST_CTRL::iterator enditr = clds.end();
	for(; itr != enditr; ++itr)
	{
		lpItem = *itr;
		if(CTRL_DIALOG == lpItem->GetType())
		{
			lpDlg = static_cast<CCMyDialog*> (lpItem);
			if (lpDlg)
			{
				lpDlg->OnNetPackage(pDataPkg);
			}
		}
	}
}

void CCMyDialog::setVisible(bool visible)
{
	bool bOldVisible = IsShow();
	CCNode::setVisible(visible);

	if (visible == bOldVisible)
	{
		return;
	}

	if (!visible)
	{
		g_objUIMgr.BindToBack(GetHandle());
	}

	CCMyWndObject* pParent = GetUIParent();

	if (NULL != pParent && CTRL_DIALOG == pParent->GetType())
	{
		CCMyDialog* pParentDlg = static_cast<CCMyDialog*>(pParent);
		if (pParentDlg && visible)
		{
			pParentDlg->addChild(this, getZOrder(), GetHandle());
		}
		else if (pParentDlg && !visible)
		{
			pParentDlg->removeChildByTag(GetHandle());
		}
	}
	else if (IsRoot(pParent))
	{
		if (visible)
		{
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			if (pScene)
			{
				pScene->addChild(this, getZOrder(), GetHandle());
			}
		}
		else
		{
			CCNode* pParentNode = this->getParent();
			if (pParentNode)
			{
				pParentNode->removeChildByTag(GetHandle());
			}
		}
	}
}

bool CCMyDialog::isVisible(void)
{
	bool bVisible = IsShow();
	CCMyDialog* pDlg = this;

	while(pDlg && bVisible)
	{
		bVisible = pDlg->IsShow();

		CCMyWndObject* pParentObj = pDlg->GetUIParent();
		if (pParentObj && CTRL_DIALOG != pParentObj->GetType())
		{
			break;
		}
		else if (pParentObj && IsRoot(pParentObj))
		{
			break;
		}

		pDlg = static_cast<CCMyDialog*>(pParentObj);
	}

	return bVisible;
}

void CCMyDialog::SetShow(bool visible)
{
	CCNode::setVisible(visible);
}

bool CCMyDialog::IsShow(void)
{
	return CCNode::isVisible();
}

void CCMyDialog::setAniStretch(GLint nAniStretch)
{
	if (m_nAniStretch == nAniStretch)
	{
		return;
	}

	m_nAniStretch = nAniStretch;

	SetBgAni(m_strAniSection.c_str());
}

GLint CCMyDialog::getAniStretch()
{
	return m_nAniStretch;
}

const char* CCMyDialog::GetBgAni(void)
{
	return m_strAniSection.c_str();
}

void CCMyDialog::clearBackgroundSprite(void)
{
	if (m_backgroundSprite)
	{
		removeChild(m_backgroundSprite, true);
	}

	CC_SAFE_RELEASE_NULL(m_backgroundSprite);
}

void CCMyDialog::SetBgAni(const char* pszAni)
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

	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());

	if (!pAni)
	{
		return;
	}

	int nFrame = 0;
	std::string strFrame = FORMAT("Frame%d")<<nFrame;
	const char *pszValue = pAni->GetString(m_strAniSection.c_str(), strFrame.c_str());

	if (NULL == pszValue)
	{
		return;
	}

	CCScale9Sprite *backgroundSprite = CCScale9Sprite::create(pszValue);

	if (!backgroundSprite)
	{
		return;
	};

	// 不为9宫格方式
	if (enumUISTRETCH_NORMAL == m_nAniStretch)
	{
		CCRect rectCapInsets = CCRectMake(0, 0, backgroundSprite->getContentSize().width, backgroundSprite->getContentSize().height);
		backgroundSprite->removeAllChildren();
		CCScale9Sprite *backgroundSpriteResize =  backgroundSprite->resizableSpriteWithCapInsets(rectCapInsets);
		CHECK(backgroundSpriteResize);
		setBackgroundSprite(backgroundSpriteResize);
	}
	else if (enumUISTRETCH_STRETCH == m_nAniStretch)
	{
		float fOrgWidth = backgroundSprite->getContentSize().width;
		float fOrgHeight = backgroundSprite->getContentSize().height;
		CCRect rectCapInsets = CCRectMake(0, 0, fOrgWidth, fOrgHeight);
		backgroundSprite->removeAllChildren();
		CCScale9Sprite *backgroundSpriteResize =  backgroundSprite->resizableSpriteWithCapInsets(rectCapInsets);
		CHECK(backgroundSpriteResize);
		float fScaleX = 1.0f;
		float fScaleY = 1.0f;

		if (0.0f != fOrgWidth && 0.0f != fOrgHeight)
		{
			fScaleX = (float)m_nWidth / fOrgWidth;
			fScaleY = (float)m_nHeight / fOrgHeight;
		}

		backgroundSpriteResize->setScaleX(fScaleX);
		backgroundSpriteResize->setScaleY(fScaleY);
		setBackgroundSprite(backgroundSpriteResize);
	}
	else
	{
		setBackgroundSprite(backgroundSprite);
	}

	CHECK(m_backgroundSprite);
	m_backgroundSprite->setAnchorPoint(ccp(0, 0));
	m_backgroundSprite->setPosition(ccp(0, 0));
	this->addChild(m_backgroundSprite, 0);
}

CCMyWndObject* CCMyDialog::GetPointObject(cocos2d::CCTouch* pTouch)
{
	CHECKF(pTouch);
	CCMyWndObject* pWndObj = NULL;

	if (!IsShow() || !isTouchInside(pTouch))
	{
		return pWndObj;
	}

	CCNode* pNode = NULL;
	CCObject* pObj = NULL;
	CCArray* pChildren = this->getChildren();
	if (NULL == pChildren || 0 == pChildren->count())
	{
		return pWndObj;
	}

	CCARRAY_FOREACH_REVERSE(pChildren, pObj)
	{
		pNode = (CCNode*)pObj;
		if (NULL == pNode)
		{
			continue;
		}

		CCMyWndObject* pChild = GetWndObjWithHandle(pNode->getTag());
		if (NULL == pChild)
		{
			continue;
		}

		pWndObj = pChild->GetPointObject(pTouch);
		if (NULL != pWndObj)
		{
			break;
		}
	}

	if (NULL == pWndObj && !IsMsgThrough())
	{
		pWndObj = this;
	}

	return pWndObj;
}

void CCMyDialog::SetHoldScene( void )
{
	g_objUIMgr.AddSceneHoldDlg(GetHandle(), this);
}

