#ifndef __MYWNDOBJECT_H__
#define __MYWNDOBJECT_H__

#include "cocos2d.h"
#include <list>
#include "CQGlobal.h"


using namespace std;
class CCMyWndObject;
typedef list<CCMyWndObject*> LIST_CTRL;

 /*定义控件类型,由控件的GetType()固定返回(ini里的"type"是代码生成器和界面编辑器约定的,不同,ini里的type配置:1:CDialog,2:CtrlStatic,3:CtrlButton,4:CCtrlImage,5:CtrlList,6:CtrlComboBox,7:CtrlProgress,8:CtrlSlider,9:CCtrlCheckBox,10:CtrlEdit,
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
	CTRL_DLG_INNER,//12    CCtrlComboBoxList(comboBox弹出的选项对话框)
	CTRL_DIALOG,//13 	 //CDialog
	CTRL_PAGE,//		 CCtrlPage		
	CTRL_CIRCLEPROGRESS,//		 CCtrlCircleProgress	
	//以下只在lua中  CLuaDialog::GetCtrlByID才有效:
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

	//是否是最顶层的窗口CWndApp::m_rootWnd
	static bool IsRoot(CCMyWndObject* lpWnd);

	//返回获取控件的句柄号
	int GetHandle(void) const;

	//获取父窗口
	CCMyWndObject* GetUIParent();

	//设置父窗口
	void SetUIParent(CCMyWndObject* lpParent);

	//删除一个子窗口,lpChild为要查找的子窗口
	void RemoveCld(CCMyWndObject* lpChild);

	//删除全部子窗口
	void RemoveAllCld();

	//增加一个子窗口
	void AddCld(CCMyWndObject* lpChild);

	//获得子窗口链表
	LIST_CTRL& GetChild();

	//根据资源号找到子窗口下的控件
	CCMyWndObject* GetDlgItem(int iTemplateID,bool bChildDlg=false/*子窗口是否为必须为对话框,用于子窗口和子控件ID相同*/);

	//在子窗口列表里通过句柄找到对应的控件或对话框
	CCMyWndObject* GetWndObjWithHandle(int iHandle/*句柄*/);

	//是否消息透明
	bool IsMsgTransparent()const;

	//设置消息透明,透明是对底下窗口也接收不到,由后面的场景接收到(暂不支持)
	void SetMsgTransparent(bool isTransparent=true);	

	//是否消息穿透
	bool IsMsgThrough() const;

	//设置消息穿透,消息穿透对底下窗口是可接收到
	void SetMsgThrough(bool isMsgThrough);

	//前置窗口(将窗口前置显示出来(所有子窗口不被遮挡))
	void BindToFront(void);

	//最顶层父窗口
	int GetTopParent(void);

	//发送消息
	DWORD SendMessage(UINT message,WPARAM wParam, LPARAM lParam);

	//处理本窗口和子窗口事件(SendMessage后处理的事件;自定义事件消息名的值不能取1-1000的系统事件,要取MSG_USEREVENT以上的事件;注意:不能将pObj=NULL设置)
	virtual DWORD WndProc(CCMyWndObject* pObj/*触发消息的控件*/, UINT nMessage/*事件消息名*/, WPARAM wParam/*若是系统事件则为坐标*/, LPARAM lParam);

	//获取坐标所在的控件
	virtual CCMyWndObject* GetPointObject(cocos2d::CCTouch* pTouch);

	//获取控件的类型CTRL_WNDOBJ
	virtual int GetType()const;	

	//////////////////////////////////////////////////////////////////////////
	// 读取配置ini数据
	virtual GLint initGUI() = 0; 
	virtual GLint readNode();
	bool containsPoint(cocos2d::CCPoint point) const;
	void setAnchorPointType(int nType);

private:
	CCMyWndObject* m_lpParent;
	//子窗口链表(只是存储数据，不负责显示的顺序)
	LIST_CTRL m_lstChld;
	bool m_bMsgThrough;		//消息穿透
	bool m_bMsgTransparent;	//消息透明
	int m_handle;			//句柄(每个控件都拥有唯一的一个句柄号)
};

#endif // __HELLOWORLD_SCENE_H__
