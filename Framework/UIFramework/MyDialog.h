#ifndef __UI_MYDIALOG_H__
#define __UI_MYDIALOG_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DialogBase.h"

class CCMyDialog : public cocos2d::CCLayer , public CCDialogBase
{
public:
	CCMyDialog();
	~CCMyDialog();

	virtual void Create(int nWndID, CCMyWndObject *pParent = NULL);
	virtual void OnNetPackage(void* pDataPkg);

	// 设置界面是否恢复到Active Scene
	void SetHoldScene(void);

	virtual void setVisible(bool visible);
	//本窗口和所有父窗口都可见时返回真(所有父窗口都是m_isVisible为真)
	virtual bool isVisible();

	//设置m_isVisible，不添加父子关系
	void SetShow(bool visible);

	//是否可见(和函数IsVisible()一样,返回m_isVisible)
	bool IsShow(void);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

	//获取控件的类型CTRL_WNDOBJ
	virtual int GetType()const;	

	virtual bool init(); 
	virtual GLint readNode();

	static CCMyDialog* createEx(int nWndID, CCMyDialog *pParent);
	static CCMyDialog* create(int nWndID);

public:
	const char* GetBgAni(void);
	void SetBgAni(const char* pszAni);

public:
	/**
    * Returns a boolean value that indicates whether a touch is inside the bounds
    * of the receiver. The given touch must be relative to the world.
    *
    * @param touch A CCTouch object that represents a touch.
    *
    * @return YES whether a touch is inside the receiver’s rect.
    */
    bool isTouchInside(cocos2d::CCTouch * touch);

	virtual void registerWithTouchDispatcher();

	//events
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	/** The current background sprite. */
	CC_SYNTHESIZE_RETAIN(cocos2d::extension::CCScale9Sprite*, m_backgroundSprite, BackgroundSprite);
	/** The Ani Stretch Mode of the Image*/
	CC_PROPERTY(GLint, m_nAniStretch, AniStretch);

protected:
	void clearBackgroundSprite(void);

private:
	bool m_isInit;//对话框是否已创建
};

#endif
