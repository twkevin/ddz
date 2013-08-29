#ifndef __UI_CTRLCHECKBOX_H__
#define __UI_CTRLCHECKBOX_H__

#include "cocos-ext.h"
#include "MyWndObject.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCtrlCheckBox : public cocos2d::extension::CCControl, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nLeftOffset, LeftOffset);
	CC_MY_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_MY_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_MY_SYNTHESIZE(std::string, m_strText, Text);
	CC_MY_SYNTHESIZE(std::string, m_strFontName, FontName);

	/** Adjust the button zooming on touchdown. Default value is YES. */
	CC_PROPERTY(bool, m_zoomOnTouchDown, ZoomOnTouchDown);
public:	
	CCtrlCheckBox();
	~CCtrlCheckBox();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_FUNC(CCtrlCheckBox);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();
public:
	bool getChecked();

	virtual void setHighlighted(bool enabled);
	void setChecked(bool Checked);

	//events
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m_pSpriteUnchecked, SpriteUnchecked);
	CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m_pSpriteChecked, SpriteChecked);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_pLabelText, LabelText);

	bool m_bChecked;
};


#define ON_CHKBOX_TOUCH_UP_INSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlCheckBox* pCtrl =(CCtrlCheckBox*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchUpInside); \
}\
}\
}

#endif
