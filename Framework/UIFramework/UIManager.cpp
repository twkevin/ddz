#pragma warning(disable: 4786) 

#include "MyDialog.h"
#include "BaseFunc.h"
#include "StringFormat.h"
#include "UIManager.h"

namespace
{
	const int c_nDefaultDlgOrder = 0;
	const int c_nFrontDlgOrder	 = 1;
};

USING_NS_CC;
using namespace std;

CUIManager::CUIManager()
	: m_pDealTouch(NULL)
	, m_hDlgTouchHandle(0)
	, m_hObjTouchHandle(0)
{
	m_hwndModal = NULL;
	m_bEnableAutoDelDialog=false;
}

CUIManager::~CUIManager()
{
	//Destroy();	
}

CCMyDialog* CUIManager::CreateNewDialog(int nIDD,CCMyDialog*  lpParentDlg)
{
	DLGBUILDER_MAP::iterator it = get_DlgBuilderMap.find(nIDD);
	if (it == get_DlgBuilderMap.end()) 
	{
	//	TQLOG(1, "CUIManager::CreateNewDialog 未发现窗口[%d]配置信息\n", nIDD);
		return NULL;
	}

	CCMyDialog* dlg =static_cast<CCMyDialog*>(it->second->CreateDialog(lpParentDlg));
	return dlg;
}


void CUIManager::AddDlg(CCMyDialog *pDlg)
{
	if (NULL == pDlg)
	{
		return;
	}

	m_MapDialog[pDlg->GetHandle()] = pDlg;
	m_mapIDDHandle[pDlg->getWndID()] = pDlg->GetHandle();
}

int CUIManager::GetHandleByIDD(int nIDD)
{
	std::map<int,int>::iterator it = m_mapIDDHandle.find(nIDD);
	if (it == m_mapIDDHandle.end()) 
	{
		return 0;
	}

	return it->second;
}

DLG_HANDLE CUIManager::CreateDlg(DLG_IDD nDialogIDD, bool bShow,DLG_HANDLE hdlParent/*=NULL*/)
{
	CCMyDialog* lpParent=NULL;
	if(hdlParent!=0)//for android warning
	{
		lpParent=GetDlg(hdlParent);
		if(lpParent==NULL)
		{
			return 0;
		}
	}

	CCMyDialog* pDlg = CreateNewDialog(nDialogIDD,lpParent);	
	if (pDlg)
	{		
		m_MapDialog[pDlg->GetHandle()] = pDlg;
		pDlg->setVisible(bShow);
		return pDlg->GetHandle();
	}

	return 0;
}

CUIManager& CUIManager::sharedInstance()
{
	static CUIManager s_UI;
	return s_UI;
}

CUIManager* CUIManager::sharedInstancePtr()
{
	return &CUIManager::sharedInstance();
}

bool CUIManager::ShowDialog(DLG_HANDLE nDlgHandle, bool bShow, bool bFront)
{
	CCMyDialog* pDlg = GetDlg(nDlgHandle);
	if(pDlg)
	{
		pDlg->setVisible(bShow);

		if (bFront)
		{
			pDlg->BindToFront();
		}
		else if (!bShow)
		{
			this->BindToBack(nDlgHandle);
		}

		return true;
	}
	return false;
}

bool CUIManager::IsVisible(DLG_HANDLE nDlgHandle)
{
	CCMyDialog* pDlg = GetDlg(nDlgHandle);
	if(pDlg)
	{
		return pDlg->isVisible();
	}
	return false;
}

void CUIManager::Destroy()
{
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter = m_MapDialog.begin();
	for(iter; iter != m_MapDialog.end(); ++iter)
	{
		pDlg = iter->second;
		if(pDlg)
		{
//			pDlg->DestroyWindow();
			delete pDlg;
			pDlg = NULL;
		}	
	}	
	m_MapDialog.clear();
}

bool CUIManager::CloseAllDialog()
{
	CCMyDialog* pDlg = NULL;
	for(MAP_DIALOG::iterator iter = m_MapDialog.begin(); iter != m_MapDialog.end(); ++iter)
	{
		pDlg = iter->second;
		if(pDlg)
		{
			pDlg->setVisible(false);
		}
	}	

	return true;
}

bool CUIManager::ReleaseAllDialog()
{
	CCMyDialog* pDlg = NULL;	MAP_DIALOG::iterator iter;
	for(iter = m_MapDialog.begin(); iter != m_MapDialog.end(); ++iter)
	{
		pDlg = iter->second;
		if(pDlg)
		{
			pDlg->SetUIParent(NULL);
		}
	}	
	for(iter = m_MapDialog.begin(); iter != m_MapDialog.end(); ++iter)
	{
		pDlg = iter->second;
		if(pDlg)
		{
//			pDlg->DestroyWindow();
			delete pDlg;
			iter->second=NULL;
		}
	}
	m_MapDialog.clear();
	return true;
}

void CUIManager::ShowModalDlg(DLG_HANDLE nDlgHandle)
{
	CCMyDialog* pDlg = NULL;

	if(nDlgHandle)
	{
		MAP_DIALOG::iterator it = m_MapDialog.find(nDlgHandle);
		if(it!=m_MapDialog.end())
		{
			m_hwndModal = nDlgHandle;
			ShowDialog(m_hwndModal, true);
			pDlg = GetDlg(nDlgHandle);
			if(pDlg)
			{
				pDlg->setVisible(true);
//				CWndApp::sharedInstance()->SetModalWnd(pDlg);
//				pDlg->BindToTop(true);
			}
		}
	}

	if(pDlg==NULL)
		m_hwndModal = NULL;
}

bool CUIManager::IsDlgVisible(DLG_IDD nDialogIDD)
{
	bool bVisible = false;
	for(MAP_DIALOG::iterator it = m_MapDialog.begin(); it!=m_MapDialog.end(); ++it)
	{
		CCMyDialog* pDlg = it->second;
		if(pDlg)
		{
			if(pDlg->getWndID() == nDialogIDD)
			{
				bVisible = pDlg->isVisible();
				break;
			}			
		}
	}
	return bVisible;
}

void CUIManager::EnableAutoDelDialog(bool bEnableAutoDelDialog)
{
	m_bEnableAutoDelDialog=bEnableAutoDelDialog;
}

void CUIManager::SetAutoCloseDialog(int handle,bool bAutoClose)
{
}

bool CUIManager::IsDialogTop(CCMyDialog* pDlg)
{
	if (NULL == pDlg)
	{
		return false;
	}

	return pDlg->getZOrder() != c_nDefaultDlgOrder &&
		pDlg->getZOrder() != c_nFrontDlgOrder;
}

void CUIManager::BindToFront( DLG_HANDLE hDlg )
{
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter = m_MapDialog.begin();
	MAP_DIALOG::iterator enditer = m_MapDialog.end();

	for(; iter != enditer; ++iter)
	{
		pDlg = iter->second;

		if(pDlg && pDlg->isVisible() && pDlg->GetHandle() == hDlg)
		{
			if (!IsDialogTop(pDlg))
			{
				pDlg->setZOrder(c_nFrontDlgOrder);
			}
		}
		else if (pDlg)
		{
			if (!IsDialogTop(pDlg))
			{
				pDlg->setZOrder(c_nDefaultDlgOrder);
			}
		}
	}	
}

void CUIManager::BindToBack(DLG_HANDLE hDlg)
{
	MAP_DIALOG::iterator findIter = m_MapDialog.find(hDlg);
	if (findIter == m_MapDialog.end() ||
		NULL == findIter->second ||
		c_nFrontDlgOrder != findIter->second->getZOrder())
	{
		return;
	}

	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
	CHECK(pScene);
	CCArray* pChildren = pScene->getChildren();
	if (NULL == pChildren || 0 == pChildren->count())
	{
		return;
	}

	CCNode* pNode = NULL;
	CCObject* pObj = NULL;
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter;
	MAP_DIALOG::iterator enditer = m_MapDialog.end();

	CCARRAY_FOREACH_REVERSE(pChildren, pObj)
	{
		pNode = (CCNode*)pObj;
		if (NULL == pNode)
		{
			continue;
		}

		pDlg = NULL;
		iter = m_MapDialog.begin();
		for (; iter != enditer; ++iter)
		{
			pDlg = iter->second;
			if (NULL == pDlg)
			{
				continue;
			}

			if (pNode->getTag() == pDlg->getWndID() &&
				pDlg->GetHandle() != hDlg &&
				pNode->isVisible())
			{
				break;
			}
		}

		if (iter == enditer || NULL == pDlg)
		{
			continue;
		}

		BindToFront(pDlg->GetHandle());
		break;
	}
}

DLG_HANDLE CUIManager::GetFrontDlg(void)
{
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter = m_MapDialog.begin();
	MAP_DIALOG::iterator enditer = m_MapDialog.end();
	for(; iter != enditer; ++iter)
	{
		pDlg = iter->second;
		if(pDlg && pDlg->isVisible() && c_nFrontDlgOrder == pDlg->getZOrder())
		{
			return pDlg->GetHandle();
		}
	}

	return 0;
}

CCMyWndObject* CUIManager::GetAppWnd( void )
{
	return &m_rootWnd;
}

DLG_HANDLE CUIManager::OnTouchBegan( cocos2d::CCTouch* pTouch )
{
	if (pTouch && m_pDealTouch &&
		m_pDealTouch->m_uID == pTouch->m_uID && 0 != m_hDlgTouchHandle)
	{
		return m_hDlgTouchHandle;
	}

	m_pDealTouch = pTouch;
	m_hDlgTouchHandle = 0;
	m_hObjTouchHandle = 0;
	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
	CHECKF(pScene);
	CCArray* pChildren = pScene->getChildren();
	CHECKF(pChildren && pChildren->count() > 0);
	CCNode* pNode = NULL;
	CCObject* pObj = NULL;
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter;
	MAP_DIALOG::iterator enditer = m_MapDialog.end();

	CCARRAY_FOREACH_REVERSE(pChildren, pObj)
	{
		pNode = (CCNode*)pObj;
		if (NULL == pNode)
		{
			continue;
		}

		pDlg = NULL;
		iter = m_MapDialog.begin();
		for (; iter != enditer; ++iter)
		{
			pDlg = iter->second;
			if (NULL == pDlg)
			{
				continue;
			}

			if (pNode->getTag() == pDlg->GetHandle() &&
				pNode->isVisible())
			{
				break;
			}
		}
		
		if (iter == enditer || NULL == pDlg)
		{
			continue;
		}

		if (pDlg->isTouchEnabled() && pDlg->isTouchInside(pTouch))
		{
			m_hDlgTouchHandle = pDlg->GetHandle();
			break;
		}
	}

	if (0 != m_hDlgTouchHandle)
	{
		BindToFront(m_hDlgTouchHandle);
	}

	if (pDlg)
	{
		CCMyWndObject* pRealDealChild = pDlg->GetPointObject(m_pDealTouch);
		if (NULL != pRealDealChild)
		{
			m_hObjTouchHandle = pRealDealChild->GetHandle();
		}
	}

	if (0 == m_hObjTouchHandle)
	{
		m_hObjTouchHandle = m_hDlgTouchHandle;
	}

	return m_hDlgTouchHandle;
}

void CUIManager::DoTouchOver(void)
{
	m_pDealTouch = NULL;
	m_hDlgTouchHandle = 0;
	m_hObjTouchHandle = 0;
}

DLG_HANDLE CUIManager::GetTouchHandleDlg(void) const
{
	return m_hDlgTouchHandle;
}

DLG_HANDLE CUIManager::GetTouchHandleObj(void) const
{
	return m_hObjTouchHandle;
}

void CUIManager::CleanTouchHandleObj(void)
{
	m_hObjTouchHandle = ID_NONE;
}

void CUIManager::ChkModalDlgStatus()
{
	CCMyDialog* pDlg = NULL;
	if(m_hwndModal)
	{
		MAP_DIALOG::iterator it = m_MapDialog.find(m_hwndModal);
		if(it!=m_MapDialog.end())
		{
			pDlg = it->second;
			if(pDlg)
			{
				if(pDlg->isVisible()==false)
					ShowModalDlg(NULL);
			}
		}
		else 
		{
			ShowModalDlg(NULL);
		}
	}
}

CCMyWndObject* CUIManager::GetWndObj(DLG_HANDLE nWndObj)
{
	CHECKF(ID_NONE != nWndObj);
	return m_rootWnd.GetWndObjWithHandle(nWndObj);
}

//通过句柄返回对应的对话框
CCMyDialog* CUIManager::GetDlg(DLG_HANDLE nDlgHandle)
{
	CHECKF(ID_NONE != nDlgHandle);
	CCMyWndObject* pDlg = this->GetWndObj(nDlgHandle);
	if (NULL == pDlg || CTRL_DIALOG != pDlg->GetType())
	{
		return NULL;
	}

	return static_cast<CCMyDialog*>(pDlg);
}

DWORD CUIManager::SendMessage( DLG_HANDLE hDlg, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	CCMyDialog* pDlg = GetDlg(hDlg);
	if (NULL == pDlg)
	{
		return 0;
	}

	return pDlg->SendMessage(Msg, wParam, lParam);
}

void CUIManager::OnNetPackage(void* pDataPkg)
{
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter = m_MapDialog.begin();
	MAP_DIALOG::iterator enditer = m_MapDialog.end();
	for(; iter != enditer; ++iter)
	{
		pDlg = iter->second;
		if(pDlg && pDlg->isVisible())
		{
			pDlg->OnNetPackage(pDataPkg);
		}
	}
}

void CUIManager::AddSceneHoldDlg(DLG_HANDLE hDlg, CCMyDialog* pDlg)
{
	if (0 == hDlg || NULL == pDlg)
	{
		return;
	}

	MAP_DIALOG::iterator findIter = m_mapHoldDialog.find(hDlg);
	if (findIter != m_mapHoldDialog.end())
	{
		return;
	}

	m_mapHoldDialog.insert(std::make_pair(hDlg, pDlg));
}

void CUIManager::SynOnSceneEnter( CCNode* pScene )
{
	CHECK(pScene);

	MAP_DIALOG::iterator iter = m_mapHoldDialog.begin();
	MAP_DIALOG::iterator endIter = m_mapHoldDialog.end();

	for (; iter != endIter; ++iter)
	{
		CCMyDialog* pDlg = iter->second;

		if (pDlg && pDlg->IsShow())
		{
			// ReplaceScene的OnEnter比OnExit先进
			pDlg->setVisible(false);
			pDlg->SetShow(true);
			pScene->addChild(pDlg, pDlg->getZOrder(), pDlg->GetHandle());
		}
	}
}

void CUIManager::SynOnSceneExit( CCNode* pScene )
{
	CHECK(pScene);

	CCArray* pChildren = pScene->getChildren();
	if (NULL == pChildren || 0 >= pChildren->count())
	{
		return;
	}

	CCNode* pNode = NULL;
	CCObject* pObj = NULL;
	CCMyDialog* pDlg = NULL;
	MAP_DIALOG::iterator iter;
	MAP_DIALOG::iterator enditer = m_MapDialog.end();

	CCARRAY_FOREACH(pChildren, pObj)
	{
		pNode = (CCNode*)pObj;
		if (NULL == pNode)
		{
			continue;
		}

		pDlg = NULL;
		iter = m_MapDialog.begin();

		for (; iter != enditer; ++iter)
		{
			pDlg = iter->second;
			if (NULL == pDlg)
			{
				continue;
			}

			if (pNode->getTag() == pDlg->GetHandle())
			{
				pDlg->setVisible(false);
				break;
			}
		}
	}
}
