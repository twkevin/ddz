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

	// ���ý����Ƿ�ָ���Active Scene
	void SetHoldScene(void);

	virtual void setVisible(bool visible);
	//�����ں����и����ڶ��ɼ�ʱ������(���и����ڶ���m_isVisibleΪ��)
	virtual bool isVisible();

	//����m_isVisible������Ӹ��ӹ�ϵ
	void SetShow(bool visible);

	//�Ƿ�ɼ�(�ͺ���IsVisible()һ��,����m_isVisible)
	bool IsShow(void);

	//��ȡ�������ڵĿؼ�
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

	//��ȡ�ؼ�������CTRL_WNDOBJ
	virtual int GetType()const;	

	virtual bool init(); 
	virtual GLint readNode();

	static CCMyDialog* createEx(int nWndID, CCMyDialog *pParent);
	static CCMyDialog* create(int nWndID);
	static CCMyDialog* newDlg(int nWndID);

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
    * @return YES whether a touch is inside the receiver��s rect.
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
	bool m_isInit;//�Ի����Ƿ��Ѵ���
};

#endif
