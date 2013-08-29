#ifndef __UI_CTRLLISTCELL_H__
#define __UI_CTRLLISTCELL_H__

#include "cocos-ext.h"
#include "DialogBase.h"

class CCtrlListCell : public cocos2d::extension::CCTableViewCell , public CCDialogBase
{
public:
	CCtrlListCell();
	~CCtrlListCell();

	virtual void Create(int nWndID, CCMyWndObject *pParent);

	bool isTouchInside(cocos2d::CCTouch * touch);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

	virtual int GetType()const;	

	virtual void draw();
};

#endif
