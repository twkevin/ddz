#ifndef __MYGLOBAL_H__
#define __MYGLOBAL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DESIGN_RESOLUTION_ANCHOR_POINT_LEFT_TOP  0
#define DESIGN_RESOLUTION_ANCHOR_POINT_CENTER	 1


#define DESIGN_RESOLUTION_ANCHOR_POINT  DESIGN_RESOLUTION_ANCHOR_POINT_LEFT_TOP

enum
{
	enumUISTRETCH_NORMAL				= 0,
	enumUISTRETCH_STRETCH				= 1,
	enumUISTRETCH_STRETCHNINESIGNAL		= 2,
};

const char GUI_INI[] = { "ini/gui.ini" };
const char FRAMEWORK_CCDATA_INI[] = { "ini/ccdata.ini" };
const char GUI_ANI[] = { "ani/ui.ani" };
//const char FONT_NAME[] = { "font" };
const char FONT_NAME[] = { "微软雅黑" };	// #hy:pc版本字体临时解决方案

const int g_nDefualtFontSize = 24;
const int g_nDefualtFontColor = 0xffffffff;
const int g_nDefaultVerticalTextAlignment = 1;
const int g_nDefaultTextAlignment = 0;

typedef int DLG_HANDLE;  //对话框句柄
typedef int DLG_IDD;	//对话框ID 

// Touch响应优先级(越低的越先响应)
const int g_nObjDefaultPri = 0;
const int g_nControlTouchPri = -1;
const int g_nHandleControlPri = -2;
const int g_nHandleEditPri = -3;
const int g_nListTouchPri	= -4;
const int g_nDialogTouchPri	= -5;

#endif
