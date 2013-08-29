#ifndef __UI_CTRLLIST_H__
#define __UI_CTRLLIST_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MyWndObject.h"

class CCtrlList;

class ICtrlListEventHandle
{
public:
	virtual void tableCellTouched(cocos2d::extension::CCTableView* pTable,
		cocos2d::extension::CCTableViewCell* pCell) = 0;
};

//////////////////////////////////////////////////////////////////////////
// 设置ViewDelegate为自己，处理view事件后发往父窗口

class CCtrlList : public cocos2d::extension::CCTableView,
	public cocos2d::extension::CCTableViewDelegate,
	public CCMyWndObject
{
public:
	CCtrlList();
	~CCtrlList();

	// 获取配置的cell大小
	cocos2d::CCSize cellSizeForTable(void);

	const char* GetSelBgAni(void) const;

	void scrollToCell(int nRow, bool animated = false);

	//设置窗口的拖动，如果内容小于整个范围，不能拖。
	void SetFixedInView(bool bFixedInView);

	//设置窗口的拖动，如果内容小于整个范围，不能拖。
	bool IsFixedInView() const;

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 

    virtual void tableCellTouched(cocos2d::extension::CCTableView* table,
		cocos2d::extension::CCTableViewCell* cell);

    virtual void tableCellHighlight(cocos2d::extension::CCTableView* table,
		cocos2d::extension::CCTableViewCell* cell);

    virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table,
		cocos2d::extension::CCTableViewCell* cell);
    
    virtual void tableCellWillRecycle(cocos2d::extension::CCTableView* table,
		cocos2d::extension::CCTableViewCell* cell);

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);

	bool isTouchInside(cocos2d::CCTouch * touch);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);	

//	CREATE_FUNC(CCtrlList);
public:
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

protected:
	const char* m_pszSelBkImgAni;
	CC_MY_SYNTHESIZE(GLint, m_nColWidth, ColWidth)
	CC_MY_SYNTHESIZE(GLint, m_nLineHeight, LineHeight)
	bool m_bFixedInView;

protected:
	ICtrlListEventHandle* m_pEventDelegate;
	cocos2d::CCPoint m_touchPoint;
	cocos2d::extension::CCTableViewCell *m_pRecordTouchedCell;
};

#endif
