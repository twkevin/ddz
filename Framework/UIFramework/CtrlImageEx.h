#ifndef __UI_CTRLIMAGEEX_H__
#define __UI_CTRLIMAGEEX_H__

#include "cocos-ext.h"
#include "MyWndObject.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCMyDialog;

enum
{
	CTRLIMAGEANISTRETCH_NORMAL					= 0,
	CTRLIMAGEANISTRETCH_STRETCH					= 1,
	CTRLIMAGEANISTRETCH_STRETCHNINESIGNAL		= 2,
};

// 目前支持AniStretch拉伸方式为 不拉伸、普通拉伸、九宫格拉伸
// 不拉伸 默认方式 图片显示在控件中间
// 普通拉伸 拉伸至控件大小
// 九宫格拉伸 目前仅支持为单张纹理资源为三等分进行拉伸
// 目前支持图片两态 依次正常态、灰态在Ani中配置对应两张资源
class CCtrlImageEx : public cocos2d::extension::CCControl, public CCMyWndObject
{
	/** The current background sprite. */
	CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m_backgroundSprite, BackgroundSprite);
	// <CCControlState, CCScale9Sprite*>
	CC_SYNTHESIZE_RETAIN(CCDictionary*, m_backgroundSpriteDispatchTable, BackgroundSpriteDispatchTable);
	/** The Ani Stretch Mode of the Image*/
	CC_PROPERTY(GLint, m_nAniStretch, AniStretch);

public:
	const char* GetBgAni();
	void SetBgAni(const char* pszAni);
	//events
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

protected:
	virtual CCScale9Sprite* createBackgroundSprite(CCControlState state);
	virtual void setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state);
	virtual CCScale9Sprite* getBackgroundSpriteForState(CCControlState state);
	virtual void clearBackgroundSprite();
	virtual void needsLayout(void);

public:
	CCtrlImageEx();
	~CCtrlImageEx();

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_CTRL(CCtrlImageEx);
	virtual bool init();
	virtual GLint initGUI();
	virtual GLint readNode();	
};

#endif
