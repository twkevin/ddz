#ifndef __UI_CTRLBUTTON9_H__
#define __UI_CTRLBUTTON9_H__

#include "cocos-ext.h"
#include "MyWndObject.h"


class CCtrlButton9 : public cocos2d::extension::CCControlButton, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_MY_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_MY_SYNTHESIZE(std::string, m_strFontName, FontName);
	CC_MY_SYNTHESIZE(std::string, m_strText, Text);

public:
	CCtrlButton9();
	~CCtrlButton9();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_FUNC(CCtrlButton9);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

public:
	int GetFrameAmount() const;
	std::string GetFrame(int nFrame) const;

private:
	std::map<int, std::string> m_mapFrame;
};


#define ON_BN9_TOUCH_DOWN(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDown); \
}\
}\
}

#define ON_BN9_DRAG_INSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragInside); \
}\
}\
}

#define ON_BN9_DRAG_OUTSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragOutside); \
}\
}\
}

#define ON_BN9_DRAG_ENTER(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragEnter); \
}\
}\
}

#define ON_BN9_DRAG_EXIT(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchDragExit); \
}\
}\
}

#define ON_BN9_TOUCH_UP_INSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchUpInside); \
}\
}\
}

#define ON_BN9_TOUCH_UP_OUTSIDE(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchUpOutside); \
}\
}\
}

#define ON_BN9_TOUCH_CANCEL(id,fun) \
{ \
	CCMyWndObject* pItem = GetDlgItem(id); \
	if (pItem) \
{ \
	CCtrlButton9* pCtrl =(CCtrlButton9*)pItem; \
	if (pCtrl) \
{\
	pCtrl->addTargetWithActionForControlEvents(this, cccontrol_selector(MY_GUI_CLASS_NAME::fun), CCControlEventTouchCancel); \
}\
}\
}

#endif
