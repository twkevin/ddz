#ifndef __UI_CTRLBMFONTSTATIC_H__
#define __UI_CTRLBMFONTSTATIC_H__

#include "MyWndObject.h"

// ����CCLabelBMFont
// ��ΪGuiEdit���ܱ���fontname���ã�����Ani���ñ�ʾʹ���ĸ������ļ�

class CCtrlBMFontStatic : public cocos2d::CCLabelBMFont, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_MY_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_MY_SYNTHESIZE(std::string, m_strFontName, FontName);
	CC_MY_SYNTHESIZE(std::string, m_strFontFntFile, FontFntFile);
	CC_MY_SYNTHESIZE(std::string, m_strText, Text);
	CC_MY_SYNTHESIZE(GLint, m_nVerticalTextAlignment, VerticalTextAlignment);
	CC_MY_SYNTHESIZE(GLint, m_nTextAlignment, TextAlignment);

public:	
	CCtrlBMFontStatic();
	~CCtrlBMFontStatic();

	bool isTouchInside(cocos2d::CCTouch * touch);

	//��ȡ�������ڵĿؼ�
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public:
	CREATE_CTRL(CCtrlBMFontStatic);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();

};

#endif
