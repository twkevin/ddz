#ifndef __UI_CTRLSTATIC_H__
#define __UI_CTRLSTATIC_H__

#include "MyWndObject.h"

class CCtrlStatic : public cocos2d::CCLabelTTF, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_MY_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_MY_SYNTHESIZE(std::string, m_strFontName, FontName);
	CC_MY_SYNTHESIZE(std::string, m_strText, Text);
	CC_MY_SYNTHESIZE(GLint, m_nVerticalTextAlignment, VerticalTextAlignment);
	CC_MY_SYNTHESIZE(GLint, m_nTextAlignment, TextAlignment);

public:	
	CCtrlStatic();
	~CCtrlStatic();

	bool isTouchInside(cocos2d::CCTouch * touch);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();
	//static CCtrlStatic* create(int nWndID, CCMyDialog *pParent);
	CREATE_CTRL(CCtrlStatic);
};

#endif
