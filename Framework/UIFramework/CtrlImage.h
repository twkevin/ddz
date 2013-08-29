#ifndef __UI_CTRLIMAGE_H__
#define __UI_CTRLIMAGE_H__

#include "MyWndObject.h"


class CCtrlImage : public cocos2d::CCSprite, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(std::string, m_strImg, Img);

public:	
	CCtrlImage();
	~CCtrlImage();

	bool isTouchInside(cocos2d::CCTouch * touch);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_FUNC(CCtrlImage);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

};

#endif
