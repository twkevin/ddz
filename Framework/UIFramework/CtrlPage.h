/*
 *  CtrlPage.h
 *
 *  Created by ndtq on 12-5-7.
 *  Copyright 2011 TQ Digital Entertainment. All rights reserved.
 *
 */

#ifndef __CTRL_PAGE_H__
#define __CTRL_PAGE_H__

#include <vector>
#include "DelegateEvent.h"
#include "MyWndObject.h"
#include "cocos2d.h"
#include "cocos-ext.h"

//
// ����һ��Image�ؼ�����ͼ������CtrlPage�ĵ�ͼ
// ��ʱֻ֧��CCMyDialog��������
//

//��ҳ��ͼ�ؼ�������
typedef struct tagPageCommAtt
{
	bool bPageHeadVisable;//�Ƿ���ҳü Ĭ��false
	int nPageHeadHeight;//ҳü�߶� Ĭ��16
	bool bPageFootVisable;//�Ƿ���ҳ�� Ĭ��false
	int nPageFootHeight;//ҳ�Ÿ߶�  Ĭ��16
	int nPageSpace;//ҳ���
	char* m_lpValueBg;//����ͼƬ  Ĭ��0
	tagPageCommAtt();
}PageCommAtt,*LPPageCommAtt;

class CCMyDialog;

//ҳ����
typedef struct tagPageItemAtt//  
{
	CCMyDialog *pObj;
	bool bAutoDestory;
	int	 nWidth;
	int  nHeight;
	DWORD	m_dwData;
	tagPageItemAtt();
}PageItemAtt,*LPPageItemAtt;

typedef std::vector<LPPageItemAtt>  VECPAGES;

class CCtrlPage : public cocos2d::CCLayer,
	public cocos2d::extension::CCScrollViewDelegate,
	public CCMyWndObject
{
public:
	CCtrlPage();
	virtual ~CCtrlPage();

	//��ҳ�б������һҳ���ɹ��������б��е�λ�ã�ʧ�ܷ���-1
	int AddPageItem(CCMyDialog* lpDlg/*���ڶ���*/, bool bAutoDestory = false/*Clear��ʱ���delete��*/);

	//���ҳ�б�ҳ��
    int GetPageCount() const;

	//���ҳ�б�ĳҳ��ҳ����
	LPPageItemAtt GetPageItem(int nIndex);

	//��ҳ�б���ɾ��ĳҳҳ����
	void RemovePageItem(int nIndex);

	//���ҳ�б�����bAutoDestory�����������ָ��
	void ClearPages();

	//���õ�ǰҳ
	void SetCurPageIndex(int nPageIndex, bool animated = false);
	int GetCurPageIndex() const;

	const char* GetBgAni(void);
	void SetBgAni(const char* pszAni);

	CommonEvent m_pageChangeEvent;

public:
	virtual bool init(void); 
	virtual GLint initGUI(void);
	virtual GLint readNode(void);

	//�õ��ؼ�����:CTRL_PAGE
	virtual int GetType(void) const;

	bool isTouchInside(cocos2d::CCTouch * touch);

	//��ȡ�������ڵĿؼ�
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	//scrollview������ʱ������
	void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {}
	//scrollview���ŵ�ʱ������
	void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 

protected:
	//�������ں��Ӵ����¼�(SendMessage������¼�)
	virtual DWORD WndProc(CCMyWndObject* pObj/*������Ϣ�Ĵ���*/, UINT message,WPARAM wParam, LPARAM lParam);

	void DoPageChange(int nPageIndex);

	//����ҳ
	void ResetPagePos();

	void clearBackgroundSprite(void);

	void adjustScrollView(void);

	unsigned int _indexFromOffset(cocos2d::CCPoint offset);

protected:
	PageCommAtt m_pageCommAtt;
	VECPAGES m_vecPageItem;
	int m_nPageIndex;
	cocos2d::CCPoint m_touchPoint;

	/** The current background sprite. */
	CC_SYNTHESIZE_RETAIN(cocos2d::extension::CCScale9Sprite*, m_backgroundSprite, BackgroundSprite);
	/** The Ani Stretch Mode of the Image*/
	CC_PROPERTY(GLint, m_nAniStretch, AniStretch);
	//ҳ��ͼ
	CC_SYNTHESIZE_RETAIN(cocos2d::extension::CCScrollView*, m_pScrollView, ScrollView);
};

#endif
