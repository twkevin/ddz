#include "CtrlBMFontStatic.h"


#include "StringManager.h"
#include "IniMgr.h"
#include "MyGlobal.h"
#include "StringFormat.h"

USING_NS_CC;

CCtrlBMFontStatic::CCtrlBMFontStatic()
	: m_nFontSize(0)
	, m_nFontColor(0)
	, m_strFontName("")
	, m_strFontFntFile("")
	, m_strText("")
	, m_nTextAlignment(0)
	, m_nVerticalTextAlignment(0)
{

}

CCtrlBMFontStatic::~CCtrlBMFontStatic()
{

}

bool CCtrlBMFontStatic::init()
{
	// 需要配置ani字段
	if (m_strFontFntFile.empty())
	{
		if (CCLabelBMFont::init())
		{
			CCLabelBMFont::setWidth(m_nWidth);
			CCLabelBMFont::setAlignment((CCTextAlignment)m_nTextAlignment);
		}
		else
		{
			return false;
		}
	}
	else if (!CCLabelBMFont::initWithString(m_strText.c_str(), m_strFontFntFile.c_str(), m_nWidth, (CCTextAlignment)m_nTextAlignment))
	{
		return false;
	}

	ignoreAnchorPointForPosition(false);
	// 已经锚点为0.5f,0.5f
	// CCLabelBMFont可能依赖于中心锚点,Position和m_fwidth来算对齐后显示的位置，设置ContentSize没有用
	CCPoint pntAnchor = getAnchorPoint();
	m_fRealX -= m_nWidth * (m_fArchorPointX - pntAnchor.x);
	m_fRealY -= m_nHeight * (m_fArchorPointY - pntAnchor.y);
	m_fArchorPointX = pntAnchor.x;
	m_fArchorPointY = pntAnchor.y;
	this->setPosition(ccp(m_fRealX, m_fRealY));

    return true;
}

GLint CCtrlBMFontStatic::readNode()
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
	m_nTextAlignment = pIni->GetValue(strIndex.c_str(), "herAlign", kCCTextAlignmentCenter);
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

	m_strFontName = m_strAniSection;

	if (!m_strFontName.empty())
	{
		CMyIni* pIni = g_objIniMgr.GetMyIniPtr(FRAMEWORK_CCDATA_INI);

		if (NULL == pIni)
		{
			return -1;
		}

		const char *pszFile = pIni->GetString(m_strFontName.c_str(), "filepath");
		if (NULL != pszFile)
		{
			m_strFontFntFile = pszFile;
		}
	}

	return 0;
}

GLint CCtrlBMFontStatic::initGUI()
{
	GLint nRet = this->readNode();

	if (!this->init())
	{
		return -1;
	}

	return nRet;
}

bool CCtrlBMFontStatic::isTouchInside(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox=boundingBox();
	return bBox.containsPoint(touchLocation);
}

CCMyWndObject* CCtrlBMFontStatic::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isVisible() || IsMsgThrough())
	{
		return NULL;
	}

	return this;
}
