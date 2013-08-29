#include "CtrlSlider.h"

#include "MyGlobal.h"
#include "IniMgr.h"
#include "StringFormat.h"
#include "StringManager.h"
#include "UIManager.h"
#include "PublicFunc.h"

CCtrlSlider::CCtrlSlider()
: m_value(0.0f)
, m_minimumValue(0.0f)
, m_maximumValue(0.0f)
, m_minimumAllowedValue(0.0f)
, m_maximumAllowedValue(0.0f)
, m_thumbSprite(NULL)
, m_progressSprite(NULL)
, m_backgroundSprite(NULL)
{
}

CCtrlSlider::~CCtrlSlider()
{
	CC_SAFE_RELEASE(m_thumbSprite);
	CC_SAFE_RELEASE(m_progressSprite);
	CC_SAFE_RELEASE(m_backgroundSprite);
}

bool CCtrlSlider::initWithSprites(CCSprite * backgroundSprite, CCSprite* progressSprite, CCSprite* thumbSprite)
{
	CCAssert(backgroundSprite,  "Background sprite must be not nil");
	CCAssert(progressSprite,    "Progress sprite must be not nil");
	CCAssert(thumbSprite,       "Thumb sprite must be not nil");

	this->setBackgroundSprite(backgroundSprite);
	this->setProgressSprite(progressSprite);
	this->setThumbSprite(thumbSprite);

	// Add the slider background
	m_backgroundSprite->setAnchorPoint(ccp(0.0f, 0.5f));
	m_backgroundSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
	addChild(m_backgroundSprite);

	// Add the progress bar
	m_progressSprite->setAnchorPoint(ccp(0.0f, 0.5f));
	m_progressSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
	addChild(m_progressSprite);

	// Add the slider thumb  
	m_thumbSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
	addChild(m_thumbSprite);

	// Init default values
	m_minimumValue                   = 0.0f;
	m_maximumValue                   = 1.0f;

	setValue(m_minimumValue);
	return true;
}


void CCtrlSlider::setEnabled(bool enabled)
{
	CCControl::setEnabled(enabled);
	if (m_thumbSprite != NULL) 
	{
		m_thumbSprite->setOpacity((enabled) ? 255 : 128);
	}
}

void CCtrlSlider::setValue(float value)
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

void CCtrlSlider::setMinimumValue(float minimumValue)
{
	m_minimumValue=minimumValue;
	m_minimumAllowedValue = minimumValue;
	if (m_minimumValue >= m_maximumValue)    
	{
		m_maximumValue   = m_minimumValue + 1.0f;
	}
	setValue(m_value);
}

void CCtrlSlider::setMaximumValue(float maximumValue)
{
	m_maximumValue=maximumValue;
	m_maximumAllowedValue = maximumValue;
	if (m_maximumValue <= m_minimumValue)   
	{
		m_minimumValue   = m_maximumValue - 1.0f;
	}
	setValue(m_value);
}

bool CCtrlSlider::isTouchInside(CCTouch * touch)
{
	CCPoint touchLocation   = touch->getLocation();
	touchLocation           = this->getParent()->convertToNodeSpace(touchLocation);

	CCRect rect             = this->boundingBox();
	rect.size.width         += m_thumbSprite->boundingBox().size.width;
	rect.origin.x           -= m_thumbSprite->boundingBox().size.width / 2;

	return rect.containsPoint(touchLocation);
}

CCPoint CCtrlSlider::locationFromTouch(CCTouch* touch)
{
	CCPoint touchLocation   = touch->getLocation();                      // Get the touch position
	touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class

	if (touchLocation.x < 0)
	{
		touchLocation.x     = 0;
	} else if (touchLocation.x > m_backgroundSprite->boundingBox().size.width)
	{
		touchLocation.x     = m_backgroundSprite->boundingBox().size.width;
	}

	return touchLocation;
}


bool CCtrlSlider::ccTouchBegan(CCTouch* touch, CCEvent* pEvent)
{
	if (!isTouchInside(touch) || !isEnabled() || !isVisible())
	{
		return false;
	}

	if (GetHandle() != g_objUIMgr.GetTouchHandleObj())
	{
		return false;
	}

	CCPoint location = locationFromTouch(touch);
	sliderBegan(location);
	return true;
}

void CCtrlSlider::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint location = locationFromTouch(pTouch);
	sliderMoved(location);
}

void CCtrlSlider::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	sliderEnded(CCPointZero);
}

void CCtrlSlider::needsLayout()
{
	if (NULL == m_thumbSprite || NULL == m_backgroundSprite || NULL == m_progressSprite)
	{
		return;
	}
	// Update thumb position for new value
	float percent               = (m_value - m_minimumValue) / (m_maximumValue - m_minimumValue);

	CCPoint pos                 = m_thumbSprite->getPosition();
	pos.x                       = percent * m_backgroundSprite->boundingBox().size.width;
	m_thumbSprite->setPosition(pos);

	// Stretches content proportional to newLevel
	CCRect textureRect          = m_progressSprite->getTextureRect();
	textureRect                 = CCRectMake(textureRect.origin.x, textureRect.origin.y,
		percent * m_backgroundSprite->getContentSize().width, textureRect.size.height);
	m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
}

void CCtrlSlider::sliderBegan(CCPoint location)
{
	this->setSelected(true);
	this->getThumbSprite()->setColor(ccGRAY);
	setValue(valueForLocation(location));
}

void CCtrlSlider::sliderMoved(CCPoint location)
{
	setValue(valueForLocation(location));
}

void CCtrlSlider::sliderEnded(CCPoint location)
{
	if (this->isSelected())
	{
		setValue(valueForLocation(m_thumbSprite->getPosition()));
	}
	this->getThumbSprite()->setColor(ccWHITE);
	this->setSelected(false);
}

float CCtrlSlider::valueForLocation(CCPoint location)
{
	float percent = location.x/ m_backgroundSprite->boundingBox().size.width;
	return MAX(MIN(m_minimumValue + percent * (m_maximumValue - m_minimumValue), m_maximumAllowedValue), m_minimumAllowedValue);
}

// on "init" you need to initialize your instance
bool CCtrlSlider::init()
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
	setTouchEnabled(true);

	std::string strFrame0 = this->GetFrame(0);
	std::string strFrame1 = this->GetFrame(1);
	std::string strFrame2 = this->GetFrame(2);

	if (strFrame0.empty() || strFrame1.empty() || strFrame2.empty())
	{
		return false;
	}

	CCSprite *backgroundSprite	= CCSprite::create(strFrame0.c_str());
	CCSprite *progressSprite	= CCSprite::create(strFrame1.c_str());
	CCSprite *thumbSprite		= CCSprite::create(strFrame2.c_str());

	backgroundSprite->setScaleX(this->getContentSize().width / backgroundSprite->getContentSize().width);
	backgroundSprite->setScaleY(this->getContentSize().height / backgroundSprite->getContentSize().height);
	progressSprite->setScaleX(this->getContentSize().width / progressSprite->getContentSize().width);
	progressSprite->setScaleY(this->getContentSize().height / progressSprite->getContentSize().height);
	thumbSprite->setScaleX(this->getContentSize().width / backgroundSprite->getContentSize().width);
	thumbSprite->setScaleY(this->getContentSize().height / backgroundSprite->getContentSize().height);

	if (!initWithSprites(backgroundSprite, progressSprite, thumbSprite))
	{
		return false;
	}

	setMinimumAllowedValue(0.0f);
	setMaximumAllowedValue(1.0f);

	return true;
}

GLint CCtrlSlider::readNode()
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

GLint CCtrlSlider::initGUI()
{
	GLint nRet = this->readNode();

	return nRet;
}

int CCtrlSlider::GetFrameAmount() const
{
	return static_cast<int>(m_mapFrame.size());
}

std::string CCtrlSlider::GetFrame(int nFrame) const
{
	std::map<int, std::string>::const_iterator iter = m_mapFrame.find(nFrame);

	if (m_mapFrame.end() == iter)
	{
		return std::string("");
	}

	return iter->second;
}

CCMyWndObject* CCtrlSlider::GetPointObject( cocos2d::CCTouch* pTouch )
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
	{
		return NULL;
	}

	return this;
}
