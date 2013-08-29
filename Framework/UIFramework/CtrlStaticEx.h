#ifndef __UI_CTRLSTATICEX_H__
#define __UI_CTRLSTATICEX_H__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "MyWndObject.h"

USING_NS_CC;
USING_NS_CC_EXT;


#define POINTER_OPERATION( pointer, operation ) \
	do\
{\
	if( pointer )\
{\
	operation;\
}\
}while( 0 )

//the anchor point of CCtrlStaticEx is the left-bottom corner.
class CCtrlStaticEx : public CCNode, public CCScrollViewDelegate, public CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nFontSize, FontSize);
	CC_MY_SYNTHESIZE(GLint, m_nFontColor, FontColor);
	CC_MY_SYNTHESIZE(std::string, m_strFontName, FontName);
	CC_MY_SYNTHESIZE(std::string, m_strText, Text);
	CC_MY_SYNTHESIZE(GLint, m_nVerticalTextAlignment, VerticalTextAlignment);
	CC_MY_SYNTHESIZE(GLint, m_nTextAlignment, TextAlignment);

public://static functions
	static CCtrlStaticEx* create( const char* pszText, const char *fontName, float fontSize, CCTextAlignment hAlignment, CCSize ScrollViewSize );

public:
	CCtrlStaticEx();
	~CCtrlStaticEx();
	bool init( const char* pszText, const char *fontName, float fontSize, CCTextAlignment hAlignment, CCSize& ScrollViewSize );

	void setTextColor(const ccColor3B& color3)
	{ POINTER_OPERATION( m_pLabel, m_pLabel->setColor( color3 ) ); }


public:

	void setString(const char* pszText);
	virtual bool init(); 
	virtual GLint initGUI();
	virtual GLint readNode();
	bool isTouchInside(cocos2d::CCTouch * touch);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

public://scroll view delegate
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

private:
	CCScrollView* m_pScrollView;
	CCLabelTTF* m_pLabel;
};

#endif /* defined(__COG__CGScrollLabel__) */
