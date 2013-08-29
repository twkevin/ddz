#ifndef _GUI_MANAGER_H
#define _GUI_MANAGER_H
#include <vector>
#include <map>
#include "MyGlobal.h"
#include "MyWndObject.h"
#include "cocos2d.h"
#include "AppWnd.h"

class CCMyDialog;

//通过此处创建的窗口，只会有一个实例。 且在程序结束时最后通过Destroy进行销毁。
//如果需创建多个相同类型的窗口，则需要new CCMyDialog. 后调用Create(templateID,...)
class CUIManager : public cocos2d::CCObject
{
public:
	virtual ~CUIManager();
	static CUIManager& sharedInstance();
	static CUIManager* sharedInstancePtr(); // for lua

	//销毁
	void Destroy();

	void AddDlg(CCMyDialog *pDlg);

	//创建新的对话框,返回句柄
	DLG_HANDLE CreateDlg(DLG_IDD nDialogIDD, bool bShow = true, DLG_HANDLE hdlParent = NULL);

	//设置显示(找到对话框句柄并显示;如果找不到,则返回false)
	bool ShowDialog(DLG_HANDLE nDlgHandle/*句柄*/, bool bShow = true/*是否显示*/, bool bFront = false/*置顶*/);

	//是否可见
	bool IsVisible(DLG_HANDLE nDlgHandle);

	//对话框是否可见
	bool IsDlgVisible(DLG_IDD nDialogIDD);

	//发送对话框消息，同步方式，本接口只能在UI主线程中调用。
	DWORD SendMessage( DLG_HANDLE hDlg, UINT Msg, WPARAM wParam, LPARAM lParam );

	//通过句柄返回对应的CCMyWndObject
	CCMyWndObject* GetWndObj(DLG_HANDLE nWndObjHandle);

	//通过句柄返回对应的对话框
	CCMyDialog* GetDlg(DLG_HANDLE nDlgHandle/*对话框的句柄*/);

	//显示对话框，且设置为模态对话框(该窗口未关闭时,鼠标点击窗口以外的地方无反应)
	void ShowModalDlg(DLG_HANDLE nDlgHandle/*窗口句柄*/);

	//通过对话框句柄号设置自动关闭
	void SetAutoCloseDialog(DLG_HANDLE handle,bool bAutoClose=true);

	//对话框置顶
	void BindToFront(DLG_HANDLE hDlg);

	//取消置顶对话框
	void BindToBack(DLG_HANDLE hDlg);

	//置顶的对话框
	DLG_HANDLE GetFrontDlg(void);

	//获取鼠标事件处理的对话框
	DLG_HANDLE OnTouchBegan(cocos2d::CCTouch* pTouch);

	//清除上次鼠标事件处理状态
	void DoTouchOver(void);

	//获取鼠标事件处理的对话框
	DLG_HANDLE GetTouchHandleDlg(void) const;

	//获取鼠标事件点击到的控件
	DLG_HANDLE GetTouchHandleObj(void) const;

	// 清除鼠标事件点击到的控件，通常用于拖拽后控件不响应
	void CleanTouchHandleObj(void);

	//关闭所有对话框
	bool CloseAllDialog();

	//释放所有对话框
	bool ReleaseAllDialog();

	//获取顶级窗口
	CCMyWndObject* GetAppWnd(void);

	void OnNetPackage(void* pDataPkg);

	void AddSceneHoldDlg(DLG_HANDLE hDlg, CCMyDialog* pDlg);

	// 同步特殊不随Scene切换隐藏的界面到新的Scene
	void SynOnSceneEnter(cocos2d::CCNode* pScene);

	// 可析构Scene退出时必须同步关闭其子Dialog
	void SynOnSceneExit(cocos2d::CCNode* pScene);

	void EnableAutoDelDialog(bool bEnableAutoDelDialog);//内部调用，外部不要调

protected:
	//检查模态对话框状态(退出模态对话框时,清除模态对话框状态)
	void ChkModalDlgStatus();

protected:	
	CUIManager();

	//返回创建的对话框(如果该对话框已创建,则直接返回)
	CCMyDialog* CreateNewDialog(int nIDD,CCMyDialog* lpParentDlg);

	// 界面分层管理系统
	// Zorder=0(普通),Zorder=1(Front)的界面会由ShowDialog函数统一调整
	// Zorder为其他值的界面不受控制，由设置者管理
	// Zorder为cocos2d-x属性，越大的显示在越前
	bool IsDialogTop(CCMyDialog* pDlg);

	CAppWnd m_rootWnd;//最顶极的窗口
	typedef std::map<int, CCMyDialog*> MAP_DIALOG;//map映射(对话框的Handle,对话框指针)
	MAP_DIALOG m_MapDialog;//所有已创建的对话框
	DLG_HANDLE m_hwndModal;//对话框句柄
	bool m_bEnableAutoDelDialog;

	cocos2d::CCTouch* m_pDealTouch;
	DLG_HANDLE m_hDlgTouchHandle;		// 点击响应的界面
	DLG_HANDLE m_hObjTouchHandle;		// 点击到的控件

	MAP_DIALOG m_mapHoldDialog;			// Scene切换后跟随显示的对话框
};

#define g_objUIMgr CUIManager::sharedInstance()

#endif
