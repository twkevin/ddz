#include "CtrlListCell.h"
#include "CtrlList.h"

#include "IniMgr.h"
#include "MyGlobal.h"
#include "PublicFunc.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCtrlListCell::CCtrlListCell()
{
}

CCtrlListCell::~CCtrlListCell()
{

}

void CCtrlListCell::Create( int nWndID, CCMyWndObject *pParent)
{
	CHECK(pParent);
	CCDialogBase::Create(nWndID, pParent);
	this->init();
}

bool CCtrlListCell::init()
{
	initGUI();
	DoDataExchange((void *)m_nWndID);
	BindEvent();

	// 从父控件list获取其他信息:
	CCMyWndObject* pParent = GetUIParent();
	CHECKF(pParent);
	CCtrlList* pList = dynamic_cast<CCtrlList*>(pParent);
	CHECKF(pList);


    return true;
}

GLint CCtrlListCell::initGUI()
{
	GLint nRet = this->readNode();
	if (0 != nRet)
	{
		return nRet;
	}

	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));

	return nRet;
}

GLint CCtrlListCell::readNode()
{
	GLint nRet = CCDialogBase::readNode();

	if (0 != nRet)
	{
		return -1;
	}

	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());
	if (!pAni)
	{
		return -1;
	}

	std::string strFrame0 = "";
	const char *pszValue = pAni->GetString(m_strAniSection.c_str(), "Frame0");
	if (pszValue)
	{
		strFrame0 = pszValue;
	}

	if (strFrame0.empty())
	{
		return 0;
	}

	CCRect rc(m_nX, m_nY, m_nWidth, m_nHeight);
	//CCSprite* pSprite = CCSprite::create(strFrame0.c_str(), rc);
	CCSprite* pSprite = CCSprite::create(strFrame0.c_str());
	CHECKF(pSprite);

	pSprite->setTextureRect(rc);

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CHECKF(pEGLView);

	float fScaleX = pEGLView->getScaleX();
	float fScaleY = pEGLView->getScaleY();
	pSprite->setScaleX(fScaleX);
	pSprite->setScaleY(fScaleY);

	//pSprite->setAnchorPoint(CCPointZero);
	pSprite->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	pSprite->setPosition(ccp(m_nX, m_nY + m_nHeight));
	this->addChild(pSprite, 0);

	return 0;
}

int CCtrlListCell::GetType()const
{
	return CTRL_LIST_CELL;
}

void CCtrlListCell::draw()
{
	CCTableViewCell::draw();
#if 0
	// draw bounding box
	CCRect rect = boundingBox();
	CCPoint vertices[4]={
		ccp(rect.getMinX(),rect.getMinY()),
		ccp(rect.getMinX(),rect.getMaxY()),
		ccp(rect.getMaxX(),rect.getMaxY()),
		ccp(rect.getMaxX(),rect.getMinY()),
	};
	ccDrawPoly(vertices, 4, true);
#endif
}

bool CCtrlListCell::isTouchInside(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	CCNode* pParent = getParent();
	if (NULL == pParent)
	{
		return false;
	}
	
	touchLocation = pParent->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

CCMyWndObject* CCtrlListCell::GetPointObject(cocos2d::CCTouch* pTouch)
{
	CHECKF(pTouch);
	CCMyWndObject* pWndObj = NULL;

	if (!isVisible() || !isTouchInside(pTouch))
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

	if (NULL == pWndObj)
	{
		pWndObj = this;
	}

	return pWndObj;
}

