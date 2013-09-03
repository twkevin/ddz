#ifndef __UI_CTRLPROGRESS_H__
#define __UI_CTRLPROGRESS_H__

#include "cocos-ext.h"
#include "MyWndObject.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCtrlProgress : public cocos2d::extension::CCControl, public CCMyWndObject
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

    // maybe this should be read-only
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_progressSprite, ProgressSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_backgroundSprite, BackgroundSprite);
	
	/** 
    * Initializes a slider with a background sprite, a progress bar
    * item.
    *
    * @param backgroundSprite  CCSprite, that is used as a background.
    * @param progressSprite    CCSprite, that is used as a progress bar.
    */
    virtual bool initWithSprites(CCSprite * backgroundSprite, CCSprite* progressSprite);

    virtual void needsLayout();

public:
	CCtrlProgress();
	~CCtrlProgress();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_CTRL(CCtrlProgress);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

public:
	int GetFrameAmount() const;
	std::string GetFrame(int nFrame) const;

private:
	std::map<int, std::string> m_mapFrame;
};

#define ON_PROGRESS_VALUE_CHANGED(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlProgress* pCtrl =(CCtrlProgress*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventValueChanged); \
}\
}\
}

#endif
