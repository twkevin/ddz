#ifndef __UI_CTRLSLIDER_H__
#define __UI_CTRLSLIDER_H__

#include "cocos-ext.h"
#include "MyWndObject.h"
#include "touch_dispatcher/CCTouch.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCtrlSlider : public cocos2d::extension::CCControl, public CCMyWndObject
{
	//maunally put in the setters
    /** Contains the receiver’s current value. */
    CC_SYNTHESIZE_READONLY(float, m_value, Value);
    virtual void setValue(float val);
    /** Contains the minimum value of the receiver. 
    * The default value of this property is 0.0. */
    CC_SYNTHESIZE_READONLY(float, m_minimumValue, MinimumValue);
    virtual void setMinimumValue(float val);
    /** Contains the maximum value of the receiver. 
    * The default value of this property is 1.0. */
    CC_SYNTHESIZE_READONLY(float, m_maximumValue, MaximumValue);
    virtual void setMaximumValue(float val);
    virtual void setEnabled(bool enabled);
    virtual bool isTouchInside(CCTouch * touch);
    CCPoint locationFromTouch(CCTouch* touch);

    CC_SYNTHESIZE(float, m_minimumAllowedValue, MinimumAllowedValue);
    CC_SYNTHESIZE(float, m_maximumAllowedValue, MaximumAllowedValue);

    // maybe this should be read-only
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_progressSprite, ProgressSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_backgroundSprite, BackgroundSprite);

public:
	CCtrlSlider();
	~CCtrlSlider();

	/** 
    * Initializes a slider with a background sprite, a progress bar and a thumb
    * item.
    *
    * @param backgroundSprite  CCSprite, that is used as a background.
    * @param progressSprite    CCSprite, that is used as a progress bar.
    * @param thumbItem         CCSprite, that is used as a thumb.
    */
    virtual bool initWithSprites(CCSprite * backgroundSprite, CCSprite* progressSprite, CCSprite* thumbSprite);

    virtual void needsLayout();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

protected:
    void sliderBegan(CCPoint location);
    void sliderMoved(CCPoint location);
    void sliderEnded(CCPoint location);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

/** Returns the value for the given location. */
    float valueForLocation(CCPoint location);

public:
	CREATE_CTRL(CCtrlSlider);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

public:
	int GetFrameAmount() const;
	std::string GetFrame(int nFrame) const;

private:
	std::map<int, std::string> m_mapFrame;
};

#define ON_SLIDER_VALUE_CHANGED(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlSlider* pCtrl =(CCtrlSlider*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventValueChanged); \
}\
}\
}

#endif
