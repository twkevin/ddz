#ifndef __UI_CTRLIBUTTONEX_H__
#define __UI_CTRLIBUTTONEX_H__

#include "cocos-ext.h"
#include "MyWndObject.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum
{
	CTRLBUTTONANISTRETCH_NORMAL					= 0,
	CTRLBUTTONANISTRETCH_STRETCH				= 1,
	CTRLBUTTONANISTRETCH_STRETCHNINESIGNAL		= 2,
};

// 目前支持AniStretch拉伸方式为 不拉伸、普通拉伸、九宫格拉伸
// 不拉伸 默认方式 图片显示在控件中间
// 普通拉伸 拉伸至控件大小
// 九宫格拉伸 目前仅支持为单张纹理资源为三等分进行拉伸
// 目前支持图片四态 依次是正常态、高亮态、灰态、选中在Ani中配置对应四张资源
class CCtrlButtonEx: public cocos2d::extension::CCControl, public CCMyWndObject
{
	CC_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_SYNTHESIZE(std::string, m_strFontName, FontName);
	CC_SYNTHESIZE(std::string, m_strText, Text);

	/** The current title label. */
	CC_SYNTHESIZE_RETAIN(CCNode*, m_titleLabel, TitleLabel);
	/** The current background sprite. */
	CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m_backgroundSprite, BackgroundSprite);
	// <CCControlState, CCScale9Sprite*>
	CC_SYNTHESIZE_RETAIN(CCDictionary*, m_backgroundSpriteDispatchTable, BackgroundSpriteDispatchTable);
	/** The Ani Stretch Mode of the Image*/
	CC_PROPERTY(GLint, m_nAniStretch, AniStretch);

	/** Adjust the button zooming on touchdown. Default value is NO. */
	CC_PROPERTY(bool, m_zoomOnTouchDown, ZoomOnTouchDown);

public:
	const char* GetBgAni();
	void SetBgAni(const char* pszAni);

public:
	virtual void setTitleLabelInButton(CCNode* titleLabel);
	virtual CCScale9Sprite* createBackgroundSprite(CCControlState state);
	virtual void setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state);
	virtual CCScale9Sprite* getBackgroundSpriteForState(CCControlState state);
	virtual void clearBackgroundSprite();
	virtual void needsLayout(void);
	virtual void setEnabled(bool enabled);
	virtual void setSelected(bool enabled);
	virtual void setHighlighted(bool enabled);

	//events
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	bool m_isPushed;

public:
	CCtrlButtonEx();
	~CCtrlButtonEx();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_CTRL(CCtrlButtonEx);
	virtual bool init();
	virtual GLint initGUI();
	virtual GLint readNode();

};

#define ON_BNEX_TOUCH_DOWN(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDown); \
}\
}\
}

#define ON_BNEX_DRAG_INSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragInside); \
}\
}\
}

#define ON_BNEX_DRAG_OUTSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragOutside); \
}\
}\
}

#define ON_BNEX_DRAG_ENTER(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragEnter); \
}\
}\
}

#define ON_BNEX_DRAG_EXIT(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragExit); \
}\
}\
}

#define ON_BNEX_TOUCH_UP_INSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchUpInside); \
}\
}\
}

#define ON_BNEX_TOUCH_UP_OUTSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchUpOutside); \
}\
}\
}

#define ON_BNEX_TOUCH_CANCEL(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButtonEx* pCtrl =(CCtrlButtonEx*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchCancel); \
}\
}\
}

#endif
