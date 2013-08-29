#include "CtrlList.h"

#include "BaseFunc.h"
#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"


USING_NS_CC;
USING_NS_CC_EXT;

namespace
{
	const int C_NTABLEVIEW_TAG = 100;
}

CCtrlList::CCtrlList()
	: m_nColWidth(0)
	, m_nLineHeight(0)
	, m_pEventDelegate(NULL)
	, m_pszSelBkImgAni(NULL)
	, m_bFixedInView(false)
	, m_pRecordTouchedCell(NULL)
{

}

CCtrlList::~CCtrlList()
{

}

bool CCtrlList::init()
{
	CCMyWndObject* lpParent = GetUIParent();
	CHECKF(lpParent);
	CCTableViewDataSource* pData = dynamic_cast<CCTableViewDataSource*>(lpParent);
	CHECKF(pData);
	ICtrlListEventHandle* pView = dynamic_cast<ICtrlListEventHandle*>(lpParent);
	CHECKF(pView);
	m_pEventDelegate = pView;

	ignoreAnchorPointForPosition(false);
	// 由于tableview的裁剪，必须锚点为0,0
	m_fRealX -= m_nWidth * m_fArchorPointX;
	m_fRealY -= m_nHeight * m_fArchorPointY;
	m_fArchorPointX = 0.0f;
	m_fArchorPointY = 0.0f;
	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));
	setTouchPriority(g_nListTouchPri);

	this->initWithViewSize(CCSizeMake(m_nWidth, m_nHeight));
	this->setDataSource(pData);
	this->setDelegate(this);
	this->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->_updateContentSize();
	this->setDirection(kCCScrollViewDirectionVertical);

	this->reloadData();
    return true;
}

void CCtrlList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CHECK(table == this && NULL != cell && m_pEventDelegate);

	m_pEventDelegate->tableCellTouched(table, cell);
}

void CCtrlList::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	CHECK(table == this && NULL != cell && m_pEventDelegate);
}

void CCtrlList::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	CHECK(table == this && NULL != cell && m_pEventDelegate);
}

void CCtrlList::tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell)
{
	CHECK(table == this && NULL != cell && m_pEventDelegate);
}

void CCtrlList::scrollViewDidScroll(CCScrollView* view)
{
	// 照抄原实现，去掉继续调用发消息给ViewDelegate，因ViewDelegate是自己
	unsigned int uCountOfItems = m_pDataSource->numberOfCellsInTableView(this);
	if (0 == uCountOfItems)
	{
		return;
	}

	unsigned int startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
	CCPoint offset = ccpMult(this->getContentOffset(), -1);
	maxIdx = MAX(uCountOfItems-1, 0);
	const CCSize cellSize = m_pDataSource->cellSizeForTable(this);

	if (m_eVordering == kCCTableViewFillTopDown)
	{
		offset.y = offset.y + m_tViewSize.height/this->getContainer()->getScaleY() - cellSize.height;
	}
	startIdx = this->_indexFromOffset(offset);

	if (m_eVordering == kCCTableViewFillTopDown)
	{
		offset.y -= m_tViewSize.height/this->getContainer()->getScaleY();
	}
	else 
	{
		offset.y += m_tViewSize.height/this->getContainer()->getScaleY();
	}
	offset.x += m_tViewSize.width/this->getContainer()->getScaleX();

	endIdx   = this->_indexFromOffset(offset);   

#if 0 // For Testing.
	CCObject* pObj;
	int i = 0;
	CCARRAY_FOREACH(m_pCellsUsed, pObj)
	{
		CCTableViewCell* pCell = (CCTableViewCell*)pObj;
		CCLog("cells Used index %d, value = %d", i, pCell->getIdx());
		i++;
	}
	CCLog("---------------------------------------");
	i = 0;
	CCARRAY_FOREACH(m_pCellsFreed, pObj)
	{
		CCTableViewCell* pCell = (CCTableViewCell*)pObj;
		CCLog("cells freed index %d, value = %d", i, pCell->getIdx());
		i++;
	}
	CCLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif

	if (m_pCellsUsed->count() > 0)
	{
		CCTableViewCell* cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(0);

		idx = cell->getIdx();
		while(idx <startIdx)
		{
			this->_moveCellOutOfSight(cell);
			if (m_pCellsUsed->count() > 0)
			{
				cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(0);
				idx = cell->getIdx();    
			}
			else
			{
				break;
			}
		}
	}
	if (m_pCellsUsed->count() > 0)
	{
		CCTableViewCell *cell = (CCTableViewCell*)m_pCellsUsed->lastObject();
		idx = cell->getIdx();

		while(idx <= maxIdx && idx > endIdx)
		{
			this->_moveCellOutOfSight(cell);
			if (m_pCellsUsed->count() > 0)
			{
				cell = (CCTableViewCell*)m_pCellsUsed->lastObject();
				idx = cell->getIdx();

			}
			else
			{
				break;
			}
		}
	}

	for (unsigned int i=startIdx; i <= endIdx; i++)
	{
		//if ([m_pIndices containsIndex:i])
		if (m_pIndices->find(i) != m_pIndices->end())
		{
			continue;
		}
		this->updateCellAtIndex(i);
	}
}

void CCtrlList::scrollViewDidZoom(CCScrollView* view)
{
	CHECK(NULL != view && m_pEventDelegate);
}

CCSize CCtrlList::cellSizeForTable(void)
{
    return CCSizeMake(m_nColWidth, m_nLineHeight);
}

const char* CCtrlList::GetSelBgAni(void) const
{
	return m_pszSelBkImgAni;
}

void CCtrlList::SetFixedInView(bool bFixedInView)
{
	m_bFixedInView = bFixedInView;
}

bool CCtrlList::IsFixedInView() const
{
	return m_bFixedInView;
}

GLint CCtrlList::readNode()
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

	m_nColWidth = pIni->GetValue(strIndex.c_str(), "ColWidth", 100);
	m_nLineHeight = pIni->GetValue(strIndex.c_str(), "ListCtrlLineHeight", 100);
	m_pszSelBkImgAni = pIni->GetValue(strIndex.c_str(), "ListCtrlSelBkImg", "");
	if (m_pszSelBkImgAni && 0 == strlen(m_pszSelBkImgAni))
	{
		m_pszSelBkImgAni = NULL;
	}

	return 0;
}

GLint CCtrlList::initGUI()
{
	GLint nRet = this->readNode();

	if (!this->init())
	{
		return -1;
	}

	return nRet;
}

void CCtrlList::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

void CCtrlList::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bFixedInView)
	{
		CCSize cellSize  = m_pDataSource->cellSizeForTable(this);
		unsigned int cellCount = m_pDataSource->numberOfCellsInTableView(this);

		if (cellSize.height * cellCount <= m_tViewSize.height)
		{
			return;
		}
	}

	CCTableView::ccTouchMoved(pTouch, pEvent);
}

void CCtrlList::scrollToCell( int nRow, bool animated/* = false*/ )
{
	int nCellCount = m_pDataSource->numberOfCellsInTableView(this);
	CHECK(nRow >= 0 && nRow < nCellCount);
	CCSize cellSize  = m_pDataSource->cellSizeForTable(this);

	int offset = 0;
	int intTableTotalHeight = cellSize.height * nCellCount;

	offset = getHeight() - intTableTotalHeight + (nRow * getLineHeight());

	setContentOffset(ccp(0, offset), animated);
}

bool CCtrlList::isTouchInside( cocos2d::CCTouch * touch )
{
	CCRect frame;
	CCNode* pParent = this->getParent();
	if (NULL == pParent)
	{
		return false;
	}

	CCPoint frameOriginal = pParent->convertToWorldSpace(this->getPosition());
	frame = CCRectMake(frameOriginal.x, frameOriginal.y, m_tViewSize.width, m_tViewSize.height);
	if (NULL == m_pContainer)
	{
		return false;
	}

	//dispatcher does not know about clipping. reject touches outside visible bounds.
	return frame.containsPoint(m_pContainer->convertToWorldSpace(m_pContainer->convertTouchToNodeSpace(touch)));
}

CCMyWndObject* CCtrlList::GetPointObject( cocos2d::CCTouch* pTouch )
{
	CHECKF(pTouch);
	CCMyWndObject* pWndObj = NULL;

	if (!isVisible() || !isTouchInside(pTouch))
	{
		return pWndObj;
	}

	// 由于list的coco2d-x父子结构不同于框架的逻辑结构，不能遍历list的CCNode children
	LIST_CTRL& lstChildren = this->GetChild();
	LIST_CTRL::iterator iter = lstChildren.begin();
	LIST_CTRL::iterator enditer = lstChildren.end();

	for (; iter != enditer; ++iter)
	{
		CCMyWndObject* pChild = *iter;
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

	if (NULL == pWndObj)
	{
		pWndObj = this;
	}
	
	return pWndObj;
}

bool CCtrlList::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (!isVisible() || !isTouchInside(pTouch))
	{
		m_touchPoint = CCPointZero;
		return false;
	}

	bool bRet = CCTableView::ccTouchBegan(pTouch, pEvent); 
	m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

	m_pRecordTouchedCell = m_pTouchedCell;	

	return bRet;
}

void CCtrlList::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (!this->isVisible()) {
		return;
	}

	if (NULL != m_pRecordTouchedCell)
	{
		CCPoint touchLocation = pTouch->getLocation();
		touchLocation = m_pRecordTouchedCell->convertToNodeSpace(touchLocation);
		CCRect bBox= m_pRecordTouchedCell->boundingBox();
		bool bIsClick = bBox.containsPoint(touchLocation);

		if (!bIsClick)
		{
			m_pTouchedCell = NULL;
			m_pRecordTouchedCell = NULL;
			CCTableView::ccTouchEnded(pTouch, pEvent);
			return;
		}

		CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		float distance = endPoint.y - m_touchPoint.y;

		if(fabs(distance) < 25)
		{
			if(m_pTableViewDelegate != NULL) {
				m_pTableViewDelegate->tableCellUnhighlight(this, m_pRecordTouchedCell);
				m_pTableViewDelegate->tableCellTouched(this, m_pRecordTouchedCell);
			}

			 m_pTouchedCell = NULL;
		}
	}

	m_pRecordTouchedCell = NULL;

	CCTableView::ccTouchEnded(pTouch, pEvent);
}

void CCtrlList::ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (NULL != m_pRecordTouchedCell)
	{
		CCPoint touchLocation = pTouch->getLocation();
		touchLocation = m_pRecordTouchedCell->convertToNodeSpace(touchLocation);
		CCRect bBox= m_pRecordTouchedCell->boundingBox();
		bool bIsClick = bBox.containsPoint(touchLocation);
		if (!bIsClick)
		{
			m_pTouchedCell = NULL;
			m_pRecordTouchedCell = NULL;
			CCTableView::ccTouchCancelled(pTouch, pEvent);
			return;
		}

		CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		float distance = endPoint.x - m_touchPoint.x;

		if(fabs(distance) < 25)
		{
			if(m_pTableViewDelegate != NULL) {
				m_pTableViewDelegate->tableCellUnhighlight(this, m_pRecordTouchedCell);
			}

			m_pTouchedCell = NULL;
		}
	}

	m_pRecordTouchedCell = NULL;

	CCTableView::ccTouchCancelled(pTouch, pEvent);
}
