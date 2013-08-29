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
// 配置一个Image控件，底图会用作CtrlPage的底图
// 暂时只支持CCMyDialog往里面塞
//

//翻页视图控件的属性
typedef struct tagPageCommAtt
{
	bool bPageHeadVisable;//是否有页眉 默认false
	int nPageHeadHeight;//页眉高度 默认16
	bool bPageFootVisable;//是否有页脚 默认false
	int nPageFootHeight;//页脚高度  默认16
	int nPageSpace;//页间隔
	char* m_lpValueBg;//背景图片  默认0
	tagPageCommAtt();
}PageCommAtt,*LPPageCommAtt;

class CCMyDialog;

//页内容
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

	//往页列表中添加一页，成功返回在列表中的位置，失败返回-1
	int AddPageItem(CCMyDialog* lpDlg/*窗口对象*/, bool bAutoDestory = false/*Clear的时候会delete掉*/);

	//获得页列表页数
    int GetPageCount() const;

	//获得页列表某页的页内容
	LPPageItemAtt GetPageItem(int nIndex);

	//从页列表中删除某页页内容
	void RemovePageItem(int nIndex);

	//清空页列表，根据bAutoDestory的设置来清除指针
	void ClearPages();

	//设置当前页
	void SetCurPageIndex(int nPageIndex, bool animated = false);
	int GetCurPageIndex() const;

	const char* GetBgAni(void);
	void SetBgAni(const char* pszAni);

	CommonEvent m_pageChangeEvent;

public:
	virtual bool init(void); 
	virtual GLint initGUI(void);
	virtual GLint readNode(void);

	//得到控件类型:CTRL_PAGE
	virtual int GetType(void) const;

	bool isTouchInside(cocos2d::CCTouch * touch);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	//scrollview滚动的时候会调用
	void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {}
	//scrollview缩放的时候会调用
	void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 

protected:
	//处理本窗口和子窗口事件(SendMessage后处理的事件)
	virtual DWORD WndProc(CCMyWndObject* pObj/*触发消息的窗口*/, UINT message,WPARAM wParam, LPARAM lParam);

	void DoPageChange(int nPageIndex);

	//重置页
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
	//页视图
	CC_SYNTHESIZE_RETAIN(cocos2d::extension::CCScrollView*, m_pScrollView, ScrollView);
};

#endif
