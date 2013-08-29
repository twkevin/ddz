#include "CtrlImage.h"


#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"
#include "PublicFunc.h"

USING_NS_CC;

CCtrlImage::CCtrlImage()
	: m_strImg("")
{

}

CCtrlImage::~CCtrlImage()
{

}

bool CCtrlImage::init()
{
    if ( !CCSprite::init() )
    {
        return false;
	}

    return true;
}

GLint CCtrlImage::readNode()
{
	GLint nRet = CCMyWndObject::readNode();

	if (0 != nRet)
	{
		return -1;
	}
	
	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());
	if (!pAni)
	{
		return -1;
	}

	const char *pszValue = pAni->GetString(m_strAniSection.c_str(), "Frame0");
	if (pszValue)
	{
		m_strImg = pszValue;
	}

	if (m_strImg.empty())
	{
		return -1;
	}

	if (!this->initWithFile(m_strImg.c_str()))
	{
		return -1;
	}

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CHECKF(pEGLView);

	float fScaleX = pEGLView->getScaleX();
	float fScaleY = pEGLView->getScaleY();
	this->setScaleX(fScaleX);
	this->setScaleY(fScaleY);

	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));

	return 0;
}

GLint CCtrlImage::initGUI()
{
	GLint nRet = this->readNode();

	return nRet;
}

bool CCtrlImage::isTouchInside(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

CCMyWndObject* CCtrlImage::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isVisible())
	{
		return NULL;
	}

	return this;
}
