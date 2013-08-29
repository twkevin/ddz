#include "MyDialog.h"
#include "CtrlStatic.h"

#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"


USING_NS_CC;

CCtrlStatic::CCtrlStatic()
	: m_nFontSize(0)
	, m_nFontColor(0)
	, m_strFontName(FONT_NAME)
	, m_strText("")
	, m_nTextAlignment(0)
	, m_nVerticalTextAlignment(0)
{

}

CCtrlStatic::~CCtrlStatic()
{

}
/*
CCtrlStatic* CCtrlStatic::create(int nWndID, CCMyDialog *pParent)
{
	if (NULL == pParent)
	{
		return NULL;
	}

	CCtrlStatic *pRet = new CCtrlStatic();
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
}*/
bool CCtrlStatic::init()
{
    if ( !CCLabelTTF::init() )
    {
        return false;
	}

    return true;
}

GLint CCtrlStatic::readNode()
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
	m_nTextAlignment = pIni->GetValue(strIndex.c_str(), "herAlign", g_nDefaultTextAlignment);
	m_nVerticalTextAlignment = pIni->GetValue(strIndex.c_str(), "verAlign", g_nDefaultVerticalTextAlignment);

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

	this->initWithString(m_strText.c_str(), m_strFontName.c_str(), m_nFontSize, CCSize(m_nWidth, 0), 
		(CCTextAlignment)m_nTextAlignment, (CCVerticalTextAlignment)m_nVerticalTextAlignment);

	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));
	this->setColor(ccGetColor3B(m_nFontColor));
	this->setOpacity(ccGetOpacity(m_nFontColor));
	this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));

	return 0;
}

GLint CCtrlStatic::initGUI()
{
	GLint nRet = this->readNode();

	return nRet;
}

bool CCtrlStatic::isTouchInside(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

CCMyWndObject* CCtrlStatic::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isVisible() || IsMsgThrough())
	{
		return NULL;
	}

	return this;
}
