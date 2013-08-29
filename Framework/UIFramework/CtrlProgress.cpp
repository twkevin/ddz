#include "CtrlProgress.h"

#include "MyGlobal.h"
#include "IniMgr.h"
#include "StringFormat.h"
#include "StringManager.h"
#include "PublicFunc.h"

CCtrlProgress::CCtrlProgress()
: m_value(0.0f)
, m_minimumValue(0.0f)
, m_maximumValue(0.0f)
, m_progressSprite(NULL)
, m_backgroundSprite(NULL)
{
}

CCtrlProgress::~CCtrlProgress()
{
	CC_SAFE_RELEASE(m_progressSprite);
	CC_SAFE_RELEASE(m_backgroundSprite);
}


bool CCtrlProgress::initWithSprites(CCSprite * backgroundSprite, CCSprite* progressSprite)
{
	CCAssert(backgroundSprite,  "Background sprite must be not nil");
	CCAssert(progressSprite,    "Progress sprite must be not nil");

	this->setBackgroundSprite(backgroundSprite);
	this->setProgressSprite(progressSprite);

	// Add the slider background
	m_backgroundSprite->setAnchorPoint(ccp(0.0f, 0.5f));
	m_backgroundSprite->setPosition(ccp(0, m_backgroundSprite->getContentSize().height / 2));
	m_backgroundSprite->setScaleX(this->getContentSize().width / m_backgroundSprite->getContentSize().width);
	m_backgroundSprite->setScaleY(this->getContentSize().height / m_backgroundSprite->getContentSize().height);
	addChild(m_backgroundSprite);

	// Add the progress bar
	m_progressSprite->setAnchorPoint(ccp(0.0f, 0.5f));
	m_progressSprite->setPosition(ccp(0.0f, m_progressSprite->getContentSize().height / 2));
	m_progressSprite->setScaleX(this->getContentSize().width / m_progressSprite->getContentSize().width);
	m_progressSprite->setScaleY(this->getContentSize().height / m_progressSprite->getContentSize().height);
	addChild(m_progressSprite);

	// Init default values
	m_minimumValue                   = 0.0f;
	m_maximumValue                   = 1.0f;

	setValue(m_minimumValue);

	return true;
}

void CCtrlProgress::setValue(float value)
{
	// set new value with sentinel
	if (value < m_minimumValue)
	{
		value = m_minimumValue;
	}

	if (value > m_maximumValue) 
	{
		value = m_maximumValue;
	}

	m_value = value;

	this->needsLayout();

	this->sendActionsForControlEvents(CCControlEventValueChanged);
}

void CCtrlProgress::setMinimumValue(float minimumValue)
{
	m_minimumValue=minimumValue;
	if (m_minimumValue >= m_maximumValue)    
	{
		m_maximumValue   = m_minimumValue + 1.0f;
	}
	setValue(m_value);
}

void CCtrlProgress::setMaximumValue(float maximumValue)
{
	m_maximumValue=maximumValue;
	if (m_maximumValue <= m_minimumValue)   
	{
		m_minimumValue   = m_maximumValue - 1.0f;
	}
	setValue(m_value);
}

void CCtrlProgress::needsLayout()
{
	if (NULL == m_backgroundSprite || NULL == m_progressSprite)
	{
		return;
	}

	// Update thumb position for new value
	float percent               = (m_value - m_minimumValue) / (m_maximumValue - m_minimumValue);

	// Stretches content proportional to newLevel
	CCRect textureRect          = m_progressSprite->getTextureRect();
	textureRect                 = CCRectMake(textureRect.origin.x, textureRect.origin.y,
		percent * m_backgroundSprite->getContentSize().width, textureRect.size.height);
	m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
}

// on "init" you need to initialize your instance
bool CCtrlProgress::init()
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

	std::string strFrame0 = this->GetFrame(0);
	std::string strFrame1 = this->GetFrame(1);

	if (strFrame0.empty() || strFrame1.empty())
	{
		return false;
	}

	CCSprite *backgroundSprite = CCSprite::create(strFrame0.c_str());
	CCSprite *progressSprite = CCSprite::create(strFrame1.c_str());

	if (!initWithSprites(backgroundSprite, progressSprite))
	{
		return false;
	}

	return true;
}

GLint CCtrlProgress::readNode()
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

	m_mapFrame.clear();

	int nFrameAmount = pAni->GetData(m_strAniSection.c_str(), "FrameAmount");

	for (int i=0; i< nFrameAmount; ++i)
	{
		std::string strFrame = FORMAT("Frame%d")<<i;

		const char *pszValue = pAni->GetString(m_strAniSection.c_str(), strFrame.c_str());

		if (pszValue)
		{
			strFrame = pszValue;
		}

		m_mapFrame[i] = strFrame;
	}

	if (!init())
	{
		return -1;
	}

	return 0;
}

GLint CCtrlProgress::initGUI()
{
	GLint nRet = this->readNode();

	return nRet;
}

int CCtrlProgress::GetFrameAmount() const
{
	return static_cast<int>(m_mapFrame.size());
}

std::string CCtrlProgress::GetFrame(int nFrame) const
{
	std::map<int, std::string>::const_iterator iter = m_mapFrame.find(nFrame);

	if (m_mapFrame.end() == iter)
	{
		return std::string("");
	}

	return iter->second;
}

CCMyWndObject* CCtrlProgress::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return NULL;
	}

	return this;
}
