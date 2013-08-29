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

// Ŀǰ֧��AniStretch���췽ʽΪ �����졢��ͨ���졢�Ź�������
// ������ Ĭ�Ϸ�ʽ ͼƬ��ʾ�ڿؼ��м�
// ��ͨ���� �������ؼ���С
// �Ź������� Ŀǰ��֧��Ϊ����������ԴΪ���ȷֽ�������
// Ŀǰ֧��ͼƬ��̬ ��������̬����̬��Ani�����ö�Ӧ������Դ
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

	//��ȡ�������ڵĿؼ�
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_CTRL(CCtrlImageEx);
	virtual bool init();
	virtual GLint initGUI();
	virtual GLint readNode();	
};

#endif
