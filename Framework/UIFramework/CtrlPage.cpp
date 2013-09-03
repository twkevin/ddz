#include "CtrlPage.h"

#include "UIManager.h"
#include "StringFormat.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "PublicFunc.h"
#include "MyDialog.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace
{
	const int c_nRemoveHandle = 50;
};

tagPageCommAtt::tagPageCommAtt()
	: bPageHeadVisable(false)	//是否有页眉 默认false
	, nPageHeadHeight(16)		//页眉高度 默认16
	, bPageFootVisable(false)	//是否有页脚 默认false
	, nPageFootHeight(16)		//页脚高度  默认16
	, m_lpValueBg(NULL)			//背景图片
	, nPageSpace(0)
{
}

tagPageItemAtt::tagPageItemAtt()
	: pObj(NULL)
	, bAutoDestory(true)
	, m_dwData(0)
	, nWidth(0)
	, nHeight(0)
{
}

//CCtrlPage
////////////////////////
CCtrlPage::CCtrlPage()
	: m_nPageIndex(-1)
	, m_backgroundSprite(NULL)
	, m_pScrollView(NULL)
	, m_nAniStretch(enumUISTRETCH_STRETCH)
	, m_pageChangeEvent(NULL)
{
}

CCtrlPage::~CCtrlPage()
{
	CC_SAFE_RELEASE_NULL(m_backgroundSprite);
	CC_SAFE_RELEASE_NULL(m_pScrollView);

	ClearPages();
}

CCtrlPage* CCtrlPage::create(int nWndID, CCMyDialog *pParent)
{
	if (NULL == pParent)
	{
		return NULL;
	}

	CCtrlPage *pRet = new CCtrlPage();
	if (pRet)
	{ 
		int nParentWndID = pParent->getWndID();
		pRet->setParentWndID(nParentWndID);
		pRet->setWndID(nWndID);
		pRet->SetUIParent(pParent);
		pRet->initGUI();
		pParent->addChild(pRet, 0, pRet->GetHandle());

		return pRet; 
	}

	return NULL;
}

int CCtrlPage::GetType() const
{
	return CTRL_PAGE;
}                        

int CCtrlPage::AddPageItem(CCMyDialog* lpObj, bool bAutoDestory)
{
	if (NULL == lpObj)
	{
		return -1;
	}

	lpObj->Create(lpObj->getWndID(), this);
	lpObj->setVisible(true);

	LPPageItemAtt pPageItem = new PageItemAtt;
	pPageItem->pObj = lpObj;
	pPageItem->bAutoDestory = bAutoDestory;
	pPageItem->m_dwData = NULL;
	pPageItem->nWidth = getWidth();
	pPageItem->nHeight = getHeight();
	m_vecPageItem.push_back(pPageItem);

	if (m_pScrollView)
	{
		m_pScrollView->addChild(lpObj, 0, lpObj->GetHandle());
	}

	ResetPagePos();
	return m_vecPageItem.size() - 1;
}

int CCtrlPage::GetPageCount() const
{
	return static_cast<int>(m_vecPageItem.size());
}

LPPageItemAtt CCtrlPage::GetPageItem(int nIndex)
{
	if (m_vecPageItem.size()<=(unsigned int)nIndex)
	{
		return NULL;
	}

	return m_vecPageItem[nIndex];
}

//#hy: 会崩溃，暂时不要调用
void CCtrlPage::RemovePageItem(int nIndex)
{
	if (static_cast<int>(m_vecPageItem.size()) <= nIndex || 0 > nIndex)
	{
		return ;
	}

	VECPAGES::iterator it = m_vecPageItem.begin();
	std::advance(it, nIndex);
	LPPageItemAtt pItem = *it;

	if (NULL != pItem && NULL != pItem->pObj)
	{
		if (m_pScrollView)
		{
			CCNode* pContainer = m_pScrollView->getContainer();
			if (pContainer)
			{
				pContainer->removeChild(pItem->pObj, true);
			}
		}

		if (pItem->bAutoDestory)
		{
			CC_SAFE_RELEASE(pItem->pObj);
		}
	}

	CC_SAFE_DELETE(pItem);
	m_vecPageItem.erase(it);

	if (0 == m_vecPageItem.size())
	{
		m_nPageIndex = -1;
	}

	ResetPagePos();
}

//#hy: 会崩溃，暂时不要调用
void CCtrlPage::ClearPages()
{
	VECPAGES::iterator it = m_vecPageItem.begin();
	VECPAGES::iterator endit = m_vecPageItem.end();

	for (; it != endit; ++it)
	{
		LPPageItemAtt pItem = *it;

		if (NULL != pItem && NULL != pItem->pObj)
		{
			if (m_pScrollView)
			{
				CCNode* pContainer = m_pScrollView->getContainer();
				if (pContainer)
				{
					pContainer->removeChild(pItem->pObj, true);
				}
			}

			if (pItem->bAutoDestory)
			{
				CC_SAFE_RELEASE(pItem->pObj);
			}
		}

		CC_SAFE_DELETE(pItem);
	}

	m_vecPageItem.clear();
}

DWORD CCtrlPage::WndProc(CCMyWndObject* pObj, UINT message, WPARAM wParam, LPARAM lParam)
{
	return CCMyWndObject::WndProc(pObj/*触发消息的窗口*/, message,wParam,  lParam);
}

void CCtrlPage::DoPageChange(int nPageIndex)
{
	int nPageNum = GetPageCount();

	if (NULL != m_pageChangeEvent)
	{
		m_pageChangeEvent(nPageIndex,nPageNum);
	}
}

void CCtrlPage::ResetPagePos()
{
	int nPageCnt = 0;
	int nRight = 0;
	int nPageNum = static_cast<int>(m_vecPageItem.size());

	for (nPageCnt = 0; nPageCnt < nPageNum; ++nPageCnt)
	{
		LPPageItemAtt pItem = m_vecPageItem[nPageCnt];
		if (NULL != pItem && NULL != pItem->pObj)
		{
			int nWidth = pItem->nWidth;
			pItem->pObj->setAnchorPoint(ccp(0.0f, 0.0f));
			pItem->pObj->setPosition(nRight, 0);
			nRight += pItem->nWidth + m_pageCommAtt.nPageSpace;
		}
	}
}

void CCtrlPage::SetCurPageIndex(int nPageIndex, bool animated)
{
	if (0 > nPageIndex || nPageIndex >= GetPageCount())
	{
		return;
	}

	if (animated && m_pScrollView)
	{
		int offset = -nPageIndex * getWidth();

		CCNode* pContainer = m_pScrollView->getContainer();
		if (pContainer)
		{
			pContainer->stopAllActions();
		}

		m_pScrollView->setContentOffset(ccp(offset, 0), animated);
	}

	if (m_nPageIndex == nPageIndex)
	{
		return;
	}

	m_nPageIndex = nPageIndex;
	this->DoPageChange(nPageIndex);
}

int CCtrlPage::GetCurPageIndex() const
{
	return m_nPageIndex;
}

bool CCtrlPage::init( void )
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_nPageIndex = -1;

		ignoreAnchorPointForPosition(false);
		this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
		this->setPosition(ccp(m_fRealX, m_fRealY));
		this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));
		setTouchPriority(g_nListTouchPri);
		setTouchEnabled(true);

		CCSize sizeView = CCSizeMake(getWidth(), getHeight());
		CCScrollView* pView = CCScrollView::create(sizeView);
		CC_BREAK_IF(NULL == pView);
		setScrollView(pView);
		m_pScrollView->setContentOffset(CCPointZero);
		m_pScrollView->setTouchEnabled(true);
		m_pScrollView->setDelegate(this);
		m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal); 
		this->addChild(m_pScrollView);

		bRet = true;
	} while (0);

	return bRet;
}

GLint CCtrlPage::initGUI( void )
{
	GLint nRet = this->readNode();

	if (!this->init())
	{
		return -1;
	}

	return nRet;
}

GLint CCtrlPage::readNode( void )
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
	int nAniStretch = pIni->GetValue(strIndex.c_str(), "AniStretch", enumUISTRETCH_STRETCH);

	if (m_nAniStretch == nAniStretch)
	{
		SetBgAni(m_strAniSection.c_str());
	}
	else
	{
		setAniStretch(nAniStretch);
	}

	return 0;
}

bool CCtrlPage::isTouchInside( cocos2d::CCTouch * touch )
{
	CCNode* pParent = this->getParent();
	if (NULL == pParent)
	{
		return false;
	}

	CHECKF(touch);
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = pParent->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

CCMyWndObject* CCtrlPage::GetPointObject( cocos2d::CCTouch* pTouch )
{
	CHECKF(pTouch);
	CCMyWndObject* pWndObj = NULL;

	if (!isVisible() || !isTouchInside(pTouch))
	{
		return pWndObj;
	}

	VECPAGES::iterator it = m_vecPageItem.begin();
	VECPAGES::iterator endit = m_vecPageItem.end();

	for (; it != endit; ++it)
	{
		LPPageItemAtt pItem = *it;

		if (NULL == pItem || NULL == pItem->pObj)
		{
			continue;
		}

		pWndObj = pItem->pObj->GetPointObject(pTouch);
		if (NULL != pWndObj)
		{
			break;
		}
	}

	if (NULL == pWndObj)
	{
		pWndObj = this;
	}

	return pWndObj;
}

void CCtrlPage::onEnter( void )
{
	CCLayer::onEnter();
	
	CCDirector* pDirector = CCDirector::sharedDirector();
	if (NULL == pDirector)
	{
		return;
	}

	// 强行修改ScrollView的touch Priority=CtrlPage，后加入的CtrlPage会先响应才能吃掉TouchEnd
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	if (m_pScrollView && pDispatcher)
	{
		// 系统bug，setPriority不会寻找等待加入的Touch Handle
		// pDispatcher->setPriority(getTouchPriority(), m_pScrollView);
		pDispatcher->removeDelegate(m_pScrollView);
		pDispatcher->addTargetedDelegate(m_pScrollView, getTouchPriority(), false);
	}

	pDispatcher->removeDelegate(this);
	pDispatcher->addTargetedDelegate(this, getTouchPriority(), false);
}

void CCtrlPage::onExit( void )
{
	CCLayer::onExit();
}

bool CCtrlPage::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (!isVisible() || !isTouchInside(pTouch))
	{
		m_touchPoint = CCPointZero;
		return false;
	}

	m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	return true; 
}

void CCtrlPage::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void CCtrlPage::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_touchPoint.equals(CCPointZero))
	{
		return;
	}

	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;

	if(c_nRemoveHandle * CC_CONTENT_SCALE_FACTOR() <= fabs(distance))
	{
		g_objUIMgr.CleanTouchHandleObj();
	}

	adjustScrollView();

	// 必须要吃掉ScrollView的pTouch，否则ScrollView会自己调整
	if (m_pScrollView)
	{
		m_pScrollView->ccTouchCancelled(pTouch, pEvent);
	}
}

void CCtrlPage::ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;

	if(50 <= fabs(distance))
	{
		g_objUIMgr.CleanTouchHandleObj();
	}

	adjustScrollView();
	// 必须要吃掉ScrollView的pTouch，否则ScrollView会自己调整
	if (m_pScrollView)
	{
		m_pScrollView->ccTouchCancelled(pTouch, pEvent);
	}
}

void CCtrlPage::adjustScrollView(void)
{
	if (NULL == m_pScrollView)
	{
		return;
	}

	CCPoint offset = m_pScrollView->getContentOffset();
	unsigned int nIndex = _indexFromOffset(offset);
	SetCurPageIndex(nIndex, true);
}

unsigned int CCtrlPage::_indexFromOffset(CCPoint offset)
{
	if (0 == getWidth())
	{
		return 0;
	}

	int index = 0;

	if (0 > offset.x)
	{
		int nOffsetX = abs(static_cast<int>(offset.x));
		index = nOffsetX / getWidth();
		if ((nOffsetX % getWidth()) > (getWidth() / 2))
		{
			++index;
		}
	}

	const int maxIdx = static_cast<int>(m_vecPageItem.size()) - 1;
	index = MAX(0, index);
	index = MIN(index, maxIdx);

	return index;
}

void CCtrlPage::setAniStretch(GLint nAniStretch)
{
	if (m_nAniStretch == nAniStretch)
	{
		return;
	}

	m_nAniStretch = nAniStretch;

	SetBgAni(m_strAniSection.c_str());
}

GLint CCtrlPage::getAniStretch()
{
	return m_nAniStretch;
}

const char* CCtrlPage::GetBgAni(void)
{
	return m_strAniSection.c_str();
}

void CCtrlPage::clearBackgroundSprite(void)
{
	if (m_backgroundSprite)
	{
		removeChild(m_backgroundSprite, true);
	}

	CC_SAFE_RELEASE_NULL(m_backgroundSprite);
}

void CCtrlPage::SetBgAni(const char* pszAni)
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

