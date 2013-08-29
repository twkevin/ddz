#ifndef __MYWNDOBJECT_H__
#define __MYWNDOBJECT_H__

#include "cocos2d.h"
#include <list>
#include "CQGlobal.h"


using namespace std;
class CCMyWndObject;
typedef list<CCMyWndObject*> LIST_CTRL;

 /*����ؼ�����,�ɿؼ���GetType()�̶�����(ini���"type"�Ǵ����������ͽ���༭��Լ����,��ͬ,ini���type����:1:CDialog,2:CtrlStatic,3:CtrlButton,4:CCtrlImage,5:CtrlList,6:CtrlComboBox,7:CtrlProgress,8:CtrlSlider,9:CCtrlCheckBox,10:CtrlEdit,
 )*/
enum 
{
	CTRL_WNDOBJ,//0		  CWndObject	
	CTRL_STATIC,//1		//CCtrlStatic
	CTRL_IMG,    //2	  CCtrlImage
	CTRL_BUTTON,		//CCtrlButton
	CTRL_SLIDER,//4		  CCtrlSlider
	CTRL_CHECKBOX,		//CCtrlCheckBox
	CTRL_PROGRESS,//6     CCtrlProgress
	CTRL_LIST,			//CCtrlList
	CTRL_DLG,//8		//CCtrlDlg	
	CTRL_EDIT,			//CCtrlEdit
	CTRL_COMBOBOX,//10    CCtrlComboBox
	CTRL_LINK,			//CCtrlLink
	CTRL_DLG_INNER,//12    CCtrlComboBoxList(comboBox������ѡ��Ի���)
	CTRL_DIALOG,//13 	 //CDialog
	CTRL_PAGE,//		 CCtrlPage		
	CTRL_CIRCLEPROGRESS,//		 CCtrlCircleProgress	
	//����ֻ��lua��  CLuaDialog::GetCtrlByID����Ч:
    CTRL_BUTTON_TAB,//CTabCtrlBtn
	CTRL_EFF_CONTAINER, //CCtrlEffContainer
	CTRL_LIST_EX,	//CCtrlListEx
	CTRL_SCROLL,	//CCtrlScroll
	CTRL_LIST_CELL,	//CCtrlListCell
};


#define ccGetColorA(nColor) (GLubyte)((0xff000000 & nColor) >> 24)
#define ccGetColorR(nColor) (GLubyte)((0x00ff0000 & nColor) >> 16)
#define ccGetColorG(nColor) (GLubyte)((0x0000ff00 & nColor) >> 8)
#define ccGetColorB(nColor) (GLubyte)(0x000000ff & m_nFontColor)
#define ccGetColor3B(nColor) ccc3(ccGetColorR(nColor), ccGetColorG(nColor), ccGetColorB(nColor))
#define ccGetOpacity(nColor) ccGetColorA(nColor)

cocos2d::CCRect ccGetRect(cocos2d::CCNode * pNode);

#ifdef CC_MY_SYNTHESIZE
#undef CC_MY_SYNTHESIZE
#endif

#define CREATE_CTRL(__TYPE__) \
	static __TYPE__* create(int nWndID, CCMyDialog *pParent) \
{ \
	if (NULL == pParent)\
{\
	return NULL;\
}\
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet) \
{ \
	int nParentWndID = pParent->getWndID();\
	pRet->setParentWndID(nParentWndID);\
	pRet->setWndID(nWndID);\
	pRet->SetUIParent(pParent);\
	pRet->initGUI();\
	pParent->addChild(pRet, 0, pRet->GetHandle());\
	return pRet; \
} \
return NULL;\
}

#define CC_MY_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void) const { return varName; }\
public: inline void set##funName(varType var){ varName = var; }

class CCMyWndObject
{
	CC_MY_SYNTHESIZE(GLint, m_nParentWndID, ParentWndID);
	CC_MY_SYNTHESIZE(GLint, m_nWndID, WndID);
	CC_MY_SYNTHESIZE(GLint, m_nX, X);
	CC_MY_SYNTHESIZE(GLint, m_nY, Y);
	CC_MY_SYNTHESIZE(GLint, m_nWidth, Width);
	CC_MY_SYNTHESIZE(GLint, m_nHeight, Height);	
	CC_MY_SYNTHESIZE(GLfloat, m_fRealX, RealX);
	CC_MY_SYNTHESIZE(GLfloat, m_fRealY, RealY);
	CC_MY_SYNTHESIZE(GLfloat, m_fArchorPointX, ArchorPointX);
	CC_MY_SYNTHESIZE(GLfloat, m_fArchorPointY, ArchorPointY);
	CC_MY_SYNTHESIZE(std::string, m_strAniSection, AniSection);
	CC_MY_SYNTHESIZE(std::string, m_strAniPath, AniPath);
	CC_MY_SYNTHESIZE(std::string, m_strGuiPath, GuiPath);

public:
	CCMyWndObject();
	~CCMyWndObject();

	//�Ƿ������Ĵ���CWndApp::m_rootWnd
	static bool IsRoot(CCMyWndObject* lpWnd);

	//���ػ�ȡ�ؼ��ľ����
	int GetHandle(void) const;

	//��ȡ������
	CCMyWndObject* GetUIParent();

	//���ø�����
	void SetUIParent(CCMyWndObject* lpParent);

	//ɾ��һ���Ӵ���,lpChildΪҪ���ҵ��Ӵ���
	void RemoveCld(CCMyWndObject* lpChild);

	//ɾ��ȫ���Ӵ���
	void RemoveAllCld();

	//����һ���Ӵ���
	void AddCld(CCMyWndObject* lpChild);

	//����Ӵ�������
	LIST_CTRL& GetChild();

	//������Դ���ҵ��Ӵ����µĿؼ�
	CCMyWndObject* GetDlgItem(int iTemplateID,bool bChildDlg=false/*�Ӵ����Ƿ�Ϊ����Ϊ�Ի���,�����Ӵ��ں��ӿؼ�ID��ͬ*/);

	//���Ӵ����б���ͨ������ҵ���Ӧ�Ŀؼ���Ի���
	CCMyWndObject* GetWndObjWithHandle(int iHandle/*���*/);

	//�Ƿ���Ϣ͸��
	bool IsMsgTransparent()const;

	//������Ϣ͸��,͸���ǶԵ��´���Ҳ���ղ���,�ɺ���ĳ������յ�(�ݲ�֧��)
	void SetMsgTransparent(bool isTransparent=true);	

	//�Ƿ���Ϣ��͸
	bool IsMsgThrough() const;

	//������Ϣ��͸,��Ϣ��͸�Ե��´����ǿɽ��յ�
	void SetMsgThrough(bool isMsgThrough);

	//ǰ�ô���(������ǰ����ʾ����(�����Ӵ��ڲ����ڵ�))
	void BindToFront(void);

	//��㸸����
	int GetTopParent(void);

	//������Ϣ
	DWORD SendMessage(UINT message,WPARAM wParam, LPARAM lParam);

	//�������ں��Ӵ����¼�(SendMessage������¼�;�Զ����¼���Ϣ����ֵ����ȡ1-1000��ϵͳ�¼�,ҪȡMSG_USEREVENT���ϵ��¼�;ע��:���ܽ�pObj=NULL����)
	virtual DWORD WndProc(CCMyWndObject* pObj/*������Ϣ�Ŀؼ�*/, UINT nMessage/*�¼���Ϣ��*/, WPARAM wParam/*����ϵͳ�¼���Ϊ����*/, LPARAM lParam);

	//��ȡ�������ڵĿؼ�
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

	//��ȡ�ؼ�������CTRL_WNDOBJ
	virtual int GetType()const;	

	//////////////////////////////////////////////////////////////////////////
	// ��ȡ����ini����
	virtual GLint initGUI() = 0; 
	virtual GLint readNode();
	bool containsPoint(cocos2d::CCPoint point) const;
	void setAnchorPointType(int nType);

private:
	CCMyWndObject* m_lpParent;
	//�Ӵ�������(ֻ�Ǵ洢���ݣ���������ʾ��˳��)
	LIST_CTRL m_lstChld;
	bool m_bMsgThrough;		//��Ϣ��͸
	bool m_bMsgTransparent;	//��Ϣ͸��
	int m_handle;			//���(ÿ���ؼ���ӵ��Ψһ��һ�������)
};

#endif // __HELLOWORLD_SCENE_H__
