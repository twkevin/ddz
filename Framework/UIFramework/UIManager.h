#ifndef _GUI_MANAGER_H
#define _GUI_MANAGER_H
#include <vector>
#include <map>
#include "MyGlobal.h"
#include "MyWndObject.h"
#include "cocos2d.h"
#include "AppWnd.h"

class CCMyDialog;

//ͨ���˴������Ĵ��ڣ�ֻ����һ��ʵ���� ���ڳ������ʱ���ͨ��Destroy�������١�
//����贴�������ͬ���͵Ĵ��ڣ�����Ҫnew CCMyDialog. �����Create(templateID,...)
class CUIManager : public cocos2d::CCObject
{
public:
	virtual ~CUIManager();
	static CUIManager& sharedInstance();
	static CUIManager* sharedInstancePtr(); // for lua

	//����
	void Destroy();

	int GetHandleByIDD(int nIDD);
	void AddDlg(CCMyDialog *pDlg);

	//�����µĶԻ���,���ؾ��
	DLG_HANDLE CreateDlg(DLG_IDD nDialogIDD, bool bShow = true, DLG_HANDLE hdlParent = NULL);

	//������ʾ(�ҵ��Ի���������ʾ;����Ҳ���,�򷵻�false)
	bool ShowDialog(DLG_HANDLE nDlgHandle/*���*/, bool bShow = true/*�Ƿ���ʾ*/, bool bFront = false/*�ö�*/);

	//�Ƿ�ɼ�
	bool IsVisible(DLG_HANDLE nDlgHandle);

	//�Ի����Ƿ�ɼ�
	bool IsDlgVisible(DLG_IDD nDialogIDD);

	//���ͶԻ�����Ϣ��ͬ����ʽ�����ӿ�ֻ����UI���߳��е��á�
	DWORD SendMessage( DLG_HANDLE hDlg, UINT Msg, WPARAM wParam, LPARAM lParam );

	//ͨ��������ض�Ӧ��CCMyWndObject
	CCMyWndObject* GetWndObj(DLG_HANDLE nWndObjHandle);

	//ͨ��������ض�Ӧ�ĶԻ���
	CCMyDialog* GetDlg(DLG_HANDLE nDlgHandle/*�Ի���ľ��*/);

	//��ʾ�Ի���������Ϊģ̬�Ի���(�ô���δ�ر�ʱ,�������������ĵط��޷�Ӧ)
	void ShowModalDlg(DLG_HANDLE nDlgHandle/*���ھ��*/);

	//ͨ���Ի������������Զ��ر�
	void SetAutoCloseDialog(DLG_HANDLE handle,bool bAutoClose=true);

	//�Ի����ö�
	void BindToFront(DLG_HANDLE hDlg);

	//ȡ���ö��Ի���
	void BindToBack(DLG_HANDLE hDlg);

	//�ö��ĶԻ���
	DLG_HANDLE GetFrontDlg(void);

	//��ȡ����¼�����ĶԻ���
	DLG_HANDLE OnTouchBegan(cocos2d::CCTouch* pTouch);

	//����ϴ�����¼�����״̬
	void DoTouchOver(void);

	//��ȡ����¼�����ĶԻ���
	DLG_HANDLE GetTouchHandleDlg(void) const;

	//��ȡ����¼�������Ŀؼ�
	DLG_HANDLE GetTouchHandleObj(void) const;

	// �������¼�������Ŀؼ���ͨ��������ק��ؼ�����Ӧ
	void CleanTouchHandleObj(void);

	//�ر����жԻ���
	bool CloseAllDialog();

	//�ͷ����жԻ���
	bool ReleaseAllDialog();

	//��ȡ��������
	CCMyWndObject* GetAppWnd(void);

	void OnNetPackage(void* pDataPkg);

	void AddSceneHoldDlg(DLG_HANDLE hDlg, CCMyDialog* pDlg);

	// ͬ�����ⲻ��Scene�л����صĽ��浽�µ�Scene
	void SynOnSceneEnter(cocos2d::CCNode* pScene);

	// ������Scene�˳�ʱ����ͬ���ر�����Dialog
	void SynOnSceneExit(cocos2d::CCNode* pScene);

	void EnableAutoDelDialog(bool bEnableAutoDelDialog);//�ڲ����ã��ⲿ��Ҫ��	

protected:
	//���ģ̬�Ի���״̬(�˳�ģ̬�Ի���ʱ,���ģ̬�Ի���״̬)
	void ChkModalDlgStatus();

protected:	
	CUIManager();

	//���ش����ĶԻ���(����öԻ����Ѵ���,��ֱ�ӷ���)
	CCMyDialog* CreateNewDialog(int nIDD,CCMyDialog* lpParentDlg);

	// ����ֲ����ϵͳ
	// Zorder=0(��ͨ),Zorder=1(Front)�Ľ������ShowDialog����ͳһ����
	// ZorderΪ����ֵ�Ľ��治�ܿ��ƣ��������߹���
	// ZorderΪcocos2d-x���ԣ�Խ�����ʾ��Խǰ
	bool IsDialogTop(CCMyDialog* pDlg);

	CAppWnd m_rootWnd;//����Ĵ���
	typedef std::map<int, CCMyDialog*> MAP_DIALOG;//mapӳ��(�Ի����Handle,�Ի���ָ��)
	MAP_DIALOG m_MapDialog;//�����Ѵ����ĶԻ���
	DLG_HANDLE m_hwndModal;//�Ի�����
	bool m_bEnableAutoDelDialog;

	cocos2d::CCTouch* m_pDealTouch;
	DLG_HANDLE m_hDlgTouchHandle;		// �����Ӧ�Ľ���
	DLG_HANDLE m_hObjTouchHandle;		// ������Ŀؼ�

	MAP_DIALOG m_mapHoldDialog;			// Scene�л��������ʾ�ĶԻ���
	std::map<int,int> m_mapIDDHandle;
};

#define g_objUIMgr CUIManager::sharedInstance()

#endif
