#ifndef __UI_BASEDIALOG_H__
#define __UI_BASEDIALOG_H__


#include "MyWndObject.h"
#include "DialogImpl.h"

#ifdef DDX_Control
#undef DDX_Control
#endif

#define DDX_Control(pDX, nIDC, rControl) \
{ \
	DDX_Control_Imp(pDX, nIDC, rControl);\
	rControl.setPosition(ccp(rControl.getRealX(), rControl.getRealY()));\
	addChild(&rControl, 0, rControl.GetHandle()); \
}

class CCDialogBase : public CDialogImpl
{
public:
	CCDialogBase();
	~CCDialogBase();

	virtual void Create(int nWndID, CCMyWndObject *pParent = NULL);
	virtual void BindEvent();

public:
	//获取控件的类型CTRL_WNDOBJ
	virtual int GetType()const;	

	virtual GLint initGUI();
	virtual GLint readNode();

protected:
	// 自动绑定控件ID和控件名字
	virtual void DoDataExchange(void* pDX);
	
};

//对话框管理的基类
class CCDialogBaseBuilder {
public:

#if ( TQ_TARGET_PLATFORM == TQ_PLATFORM_WIN32)
#ifdef CreateDialog
#undef CreateDialog
#endif
#endif
	//创建对话框,不会重复创建;若已创建,则直接返回对应的对话框
	virtual CCDialogBase* CreateDialog(CCDialogBase* lpParent=NULL, const char* sLuaScpritName=NULL) = 0;
	virtual const char* GetDialogClassName()=0;
	virtual void  ResetDlg()=0;
	// 	virtual CCDialogBase *GetSingeDialog();
};

using std::map;

typedef int DIALOG_IDD;
typedef map<DIALOG_IDD, CCDialogBaseBuilder*> DLGBUILDER_MAP;//通过ID号找到对话框管理者

inline DLGBUILDER_MAP& g_DialogBuilderMap(){static DLGBUILDER_MAP s_mapDlgBuilderMap;return s_mapDlgBuilderMap;}
#define get_DlgBuilderMap g_DialogBuilderMap()

//管理创建的对话框,s_mapDlgBuilderMap里保存了所有还没创建的对话框的ID
#define DIALOG_BUILDER(Dialog_ClassName) \
class CRegistDlgClass_##Dialog_ClassName: public CCDialogBaseBuilder \
{\
public:\
	CRegistDlgClass_##Dialog_ClassName()\
{\
	get_DlgBuilderMap[Dialog_ClassName::getDialogIDD()] = this;\
}\
	~CRegistDlgClass_##Dialog_ClassName()\
{\
	s_SingleDlg = NULL;\
}\
	virtual CCDialogBase* CreateDialog(CCDialogBase* lpParent=NULL, const char* sLuaScpritName=NULL){ if (!s_SingleDlg) { s_SingleDlg = new Dialog_ClassName(); \
	if(s_SingleDlg!=NULL) { s_SingleDlg->Create(Dialog_ClassName::getDialogIDD(),lpParent); } } return s_SingleDlg;}\
	virtual const char* GetDialogClassName(){return #Dialog_ClassName;}\
	virtual void  ResetDlg(){s_SingleDlg = NULL;}\
private:\
	static CCDialogBase* s_SingleDlg;\
};\
	CCDialogBase* CRegistDlgClass_##Dialog_ClassName::s_SingleDlg=NULL;\
	CRegistDlgClass_##Dialog_ClassName regMe_##Dialog_ClassName;

#endif // __HELLOWORLD_SCENE_H__
