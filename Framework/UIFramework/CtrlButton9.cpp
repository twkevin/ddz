#include "CtrlButton9.h"

#include "MyGlobal.h"
#include "IniMgr.h"
#include "StringFormat.h"
#include "StringManager.h"
#include "PublicFunc.h"

USING_NS_CC;
USING_NS_CC_EXT;


CCtrlButton9::CCtrlButton9()
	: m_nFontSize(0)
	, m_nFontColor(0)
	, m_strFontName(FONT_NAME)
	, m_strText("")
{

}

CCtrlButton9::~CCtrlButton9()
{

}
// on "init" you need to initialize your instance
bool CCtrlButton9::init()
{
	return CCControl::init();
}

GLint CCtrlButton9::readNode()
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
	
	CMyIniPtr pAni = g_objIniMgr.GetMyIniPtr(m_strAniPath.c_str());
	if (!pAni)
	{
		return -1;
	}

	m_mapFrame.clear();
	int nFrameAmount = pAni->GetData(m_strAniSection.c_str(), "FrameAmount");

	for (int i=0; i< nFrameAmount; ++i)
	{
		std::string strFrame = "";
		const char *pszValue = pAni->GetString(m_strAniSection.c_str(), "Frame0");
		if (pszValue)
		{
			strFrame = pszValue;
		}

		m_mapFrame[i] = strFrame;
	}

	std::string strFrame0 = this->GetFrame(0);
	if (strFrame0.empty())
	{
		return -1;
	}

	CCScale9Sprite *backgroundButton = CCScale9Sprite::create(strFrame0.c_str());
	if (NULL == backgroundButton)
	{
		return -1;
	}

	CCLabelTTF *titleButton = CCLabelTTF::create(m_strText.c_str(), m_strFontName.c_str(), m_nFontSize);
	titleButton->setColor(ccGetColor3B(m_nFontColor));
	titleButton->setOpacity(ccGetOpacity(m_nFontColor));

	this->initWithLabelAndBackgroundSprite(titleButton, backgroundButton);

	std::string strFrame1 = this->GetFrame(1);
	if (!strFrame1.empty())
	{
		CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create(strFrame1.c_str());
		if (NULL != backgroundHighlightedButton)
		{
			this->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
		}
	}

	this->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
	this->setAnchorPoint(ccp(m_fArchorPointX, m_fArchorPointY));
	this->setPosition(ccp(m_fRealX, m_fRealY));	

	return 0;
}

GLint CCtrlButton9::initGUI()
{
	if (!init())
	{
		return 0;
	}

	GLint nRet = this->readNode();

	return nRet;
}

int CCtrlButton9::GetFrameAmount() const
{
	return static_cast<int>(m_mapFrame.size());
}

std::string CCtrlButton9::GetFrame(int nFrame) const
{
	std::map<int, std::string>::const_iterator iter = m_mapFrame.find(nFrame);

	if (m_mapFrame.end() == iter)
	{
		return std::string("");
	}

	return iter->second;
}

CCMyWndObject* CCtrlButton9::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return NULL;
	}

	return this;
}
