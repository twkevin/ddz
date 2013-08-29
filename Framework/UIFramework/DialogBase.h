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
	//��ȡ�ؼ�������CTRL_WNDOBJ
	virtual int GetType()const;	

	virtual GLint initGUI();
	virtual GLint readNode();

protected:
	// �Զ��󶨿ؼ�ID�Ϳؼ�����
	virtual void DoDataExchange(void* pDX);
	
};

//�Ի������Ļ���
class CCDialogBaseBuilder {
public:

#if ( TQ_TARGET_PLATFORM == TQ_PLATFORM_WIN32)
#ifdef CreateDialog
#undef CreateDialog
#endif
#endif
	//�����Ի���,�����ظ�����;���Ѵ���,��ֱ�ӷ��ض�Ӧ�ĶԻ���
	virtual CCDialogBase* CreateDialog(CCDialogBase* lpParent=NULL, const char* sLuaScpritName=NULL) = 0;
	virtual const char* GetDialogClassName()=0;
	virtual void  ResetDlg()=0;
	// 	virtual CCDialogBase *GetSingeDialog();
};

using std::map;

typedef int DIALOG_IDD;
typedef map<DIALOG_IDD, CCDialogBaseBuilder*> DLGBUILDER_MAP;//ͨ��ID���ҵ��Ի��������

inline DLGBUILDER_MAP& g_DialogBuilderMap(){static DLGBUILDER_MAP s_mapDlgBuilderMap;return s_mapDlgBuilderMap;}
#define get_DlgBuilderMap g_DialogBuilderMap()

//�������ĶԻ���,s_mapDlgBuilderMap�ﱣ�������л�û�����ĶԻ����ID
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
