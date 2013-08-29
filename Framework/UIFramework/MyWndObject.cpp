#include "MyWndObject.h"
#include <algorithm>

#include "platform/CCPlatformMacros.h"
#include "MyGlobal.h"
#include "StringFormat.h"
#include "IniMgr.h"
#include "UIManager.h"

USING_NS_CC;
using namespace std;

CCRect ccGetRect(CCNode * pNode)
{
	CCRect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();

	if (DESIGN_RESOLUTION_ANCHOR_POINT == DESIGN_RESOLUTION_ANCHOR_POINT_CENTER)
	{
		rc.origin.x -= rc.size.width / 2;
		rc.origin.y -= rc.size.height / 2;
	}
	else if (DESIGN_RESOLUTION_ANCHOR_POINT == DESIGN_RESOLUTION_ANCHOR_POINT_LEFT_TOP)
	{
		rc.origin.y -= rc.size.height;
	}

	return rc;
}


CCMyWndObject::CCMyWndObject()
	: m_nParentWndID(0)
	, m_nWndID(0)
	, m_nX(0)
	, m_nY(0)
	, m_nWidth(0)
	, m_nHeight(0)	
	, m_fRealX(0.0)
	, m_fRealY(0.0)
	, m_fArchorPointX(0.5)
	, m_fArchorPointY(0.5)
	, m_strAniSection("")
	, m_strAniPath(GUI_ANI)
	, m_strGuiPath(GUI_INI)
	, m_lpParent(NULL)
	, m_bMsgTransparent(false)
	, m_bMsgThrough(false)
{
	static int g_handle=0;
	++g_handle;
	m_handle = g_handle;
}

CCMyWndObject::~CCMyWndObject()
{

}

bool CCMyWndObject::containsPoint(CCPoint point) const
{
	float fMinX = 0.0f;
	float fMaxX = 0.0f;
	float fMinY = 0.0f;
	float fMaxY = 0.0f;

	if (DESIGN_RESOLUTION_ANCHOR_POINT == DESIGN_RESOLUTION_ANCHOR_POINT_CENTER)
	{
		fMinX = m_fRealX - (GLfloat)m_nWidth / 2;
		fMinY = m_fRealY - (GLfloat)m_nHeight / 2;

		fMaxX = m_fRealX + (GLfloat)m_nWidth / 2;
		fMaxY=  m_fRealY + (GLfloat)m_nHeight / 2;

	}
	else if (DESIGN_RESOLUTION_ANCHOR_POINT == DESIGN_RESOLUTION_ANCHOR_POINT_LEFT_TOP)
	{
		fMinX = m_fRealX;
		fMaxY = m_fRealY;

		fMaxX = m_fRealX + (GLfloat)m_nWidth;
		fMinY=  m_fRealY - (GLfloat)m_nHeight;		
	}

	if (point.x >= fMinX
		&& point.x <= fMaxX
		&& point.y >= fMinY 
		&& point.y <= fMaxY)
	{
		return true;
	}

	return false;
}

GLint CCMyWndObject::readNode()
{
	CMyIni* pIni = g_objIniMgr.GetMyIniPtr(m_strGuiPath.c_str());

	if (NULL == pIni)
	{
		return -1;
	}

	std::string strIndex = FORMAT("%d-%d") << m_nParentWndID << m_nWndID;

	m_nX = pIni->GetData(strIndex.c_str(), "x");
	m_nY =  pIni->GetData(strIndex.c_str(), "y");
	m_nWidth = pIni->GetData(strIndex.c_str(), "w");
	m_nHeight = pIni->GetData(strIndex.c_str(), "h");

	
	const char *pszValue = pIni->GetString(strIndex.c_str(), "Ani");
	if (pszValue)
	{
		m_strAniSection = pszValue;
	}
	else
	{
		m_strAniSection = "";
	}

	this->setAnchorPointType(DESIGN_RESOLUTION_ANCHOR_POINT);

	return 0;
}

void CCMyWndObject::setAnchorPointType(int nType)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	if (nType == DESIGN_RESOLUTION_ANCHOR_POINT_CENTER)
	{
		m_fArchorPointX = 0.5f;
		m_fArchorPointY = 0.5f;

		int nParentHeight = 0;
		if (IsRoot(m_lpParent))
		{
			nParentHeight = visibleSize.height;
		}
		else
		{
			if (m_lpParent)
			{
				nParentHeight = m_lpParent->getHeight();
			}
		}

		m_fRealX = origin.x + m_nX + (GLfloat)m_nWidth / 2;
		m_fRealY = origin.y + nParentHeight - m_nY - (GLfloat)m_nHeight / 2;
	}
	else if (nType == DESIGN_RESOLUTION_ANCHOR_POINT_LEFT_TOP)
	{
		m_fArchorPointX = 0.0f;
		m_fArchorPointY = 1.0f;

		int nParentHeight = 0;
		if (IsRoot(m_lpParent))
		{
			nParentHeight = visibleSize.height;
		}
		else
		{
			if (m_lpParent)
			{
				nParentHeight = m_lpParent->getHeight();
			}			
		}

		m_fRealX = origin.x + m_nX;
		m_fRealY = origin.y + nParentHeight - m_nY;
	}
}

CCMyWndObject* CCMyWndObject::GetUIParent()
{
	return m_lpParent;
}

void CCMyWndObject::BindToFront( void )
{
	if (NULL != m_lpParent)
	{
		if (CCMyWndObject::IsRoot(m_lpParent))
		{
			CUIManager::sharedInstance().BindToFront(m_handle);
		}
		else
		{
			m_lpParent->BindToFront();
		}
	}
}

DLG_HANDLE CCMyWndObject::GetTopParent( void )
{
	if (NULL != m_lpParent)
	{
		if (CCMyWndObject::IsRoot(m_lpParent))
		{
			return m_handle;
		}
		else
		{
			return m_lpParent->GetTopParent();
		}
	}
	else
	{
		return m_handle;
	}
}

void CCMyWndObject::SetUIParent(CCMyWndObject* lpParent)
{
	if (m_lpParent!=NULL)
	{
		m_lpParent->RemoveCld(this);
		m_lpParent = NULL;
	}
	m_lpParent=lpParent;
	if (lpParent!=NULL)
	{
		m_lpParent->AddCld(this);
	}
	else
	{
		if (GetType()==CTRL_DIALOG)
		{
			CUIManager::sharedInstance().GetAppWnd()->AddCld(this);
			m_lpParent = CUIManager::sharedInstance().GetAppWnd();
		}
	}
}

int CCMyWndObject::GetType() const
{
	return CTRL_WNDOBJ;
}

void CCMyWndObject::RemoveCld(CCMyWndObject* lpChild)
{
	if (m_lstChld.size()>0)
	{
		LIST_CTRL::iterator itr = find(m_lstChld.begin(),m_lstChld.end(),lpChild);
		if (itr != m_lstChld.end())
		{
			m_lstChld.erase(itr);
		}	
	}
}

void CCMyWndObject::RemoveAllCld()
{
	CCMyWndObject* lpItem = NULL;
	LIST_CTRL tmp;
	tmp.insert(tmp.end(),m_lstChld.begin(),m_lstChld.end());
	for (LIST_CTRL::iterator itr = tmp.begin();itr!=tmp.end();++itr)
	{
		lpItem = *itr;
		if (lpItem)
		{
//			lpItem->DestroyWindow();
		}
	}
	m_lstChld.clear();
}

void CCMyWndObject::AddCld(CCMyWndObject* lpChild)
{
	if (lpChild==NULL)
	{
		return;
	}

	CCMyWndObject* lpItem = NULL;

	LIST_CTRL::iterator itr = find(m_lstChld.begin(),m_lstChld.end(),lpChild);
	if (itr != m_lstChld.end())
	{
		return;//已有该窗口
	}	

	m_lstChld.push_back(lpChild);
}

LIST_CTRL& CCMyWndObject::GetChild()
{
	return m_lstChld;
}

bool CCMyWndObject::IsRoot(CCMyWndObject* lpWnd)
{
	if (lpWnd == CUIManager::sharedInstance().GetAppWnd())
	{
		return true;
	}
	else
	{
		return false;
	}
}

CCMyWndObject* CCMyWndObject::GetDlgItem(int iTemplateID,bool bChildrenDlg)
{
	CCMyWndObject* lpItem = NULL;
	LIST_CTRL::reverse_iterator itr = m_lstChld.rbegin();
	LIST_CTRL::reverse_iterator enditr = m_lstChld.rend();

	for( ;itr != enditr; ++itr)
	{
		lpItem = *itr;
		if (lpItem && iTemplateID == lpItem->getWndID())
		{
			if (bChildrenDlg)
			{
				if (lpItem->GetType()!= CTRL_DIALOG)
				{
					continue;
				}
			}
			return lpItem;
		}
	}

	return NULL;
}

CCMyWndObject* CCMyWndObject::GetWndObjWithHandle(int iHandle)
{
	CCMyWndObject* lpItem = NULL;
	CCMyWndObject* lpSubItem = NULL;

	if (iHandle == GetHandle())
	{
		return this;
	}

	LIST_CTRL::reverse_iterator itr = m_lstChld.rbegin();
	LIST_CTRL::reverse_iterator enditr = m_lstChld.rend();
	for (; itr != enditr; ++itr)
	{
		lpItem = *itr;
		if (NULL == lpItem)
		{
			continue;
		}

		if (iHandle==lpItem->GetHandle())
		{
			return lpItem;
		}
		else
		{
			lpSubItem = lpItem->GetWndObjWithHandle(iHandle);
			if (lpSubItem!=NULL)
			{
				return lpSubItem;
			}
		}
	}

	return NULL;
}

bool CCMyWndObject::IsMsgThrough() const
{
	return m_bMsgThrough;
}

void CCMyWndObject::SetMsgThrough(bool isMsgThrough)
{
	m_bMsgThrough = isMsgThrough;
}

void CCMyWndObject::SetMsgTransparent(bool isTransparent)
{
	m_bMsgTransparent = isTransparent;

	CCMyWndObject* lpItem = NULL;
	LIST_CTRL::reverse_iterator itr = m_lstChld.rbegin();
	LIST_CTRL::reverse_iterator enditr = m_lstChld.rend();
	for (; itr != enditr; ++itr)
	{
		lpItem = *itr;
		if (NULL == lpItem)
		{
			continue;
		}

		lpItem->SetMsgTransparent(m_bMsgTransparent);
	}
}

bool CCMyWndObject::IsMsgTransparent() const
{
	return m_bMsgTransparent;
}

int CCMyWndObject::GetHandle( void ) const
{
	return m_handle;
}

DWORD CCMyWndObject::SendMessage( UINT message,WPARAM wParam, LPARAM lParam )
{
	return WndProc(this,message, wParam, lParam);
}

DWORD CCMyWndObject::WndProc(CCMyWndObject* pObj, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	return 1;
}

CCMyWndObject* CCMyWndObject::GetPointObject(cocos2d::CCTouch* pTouch)
{
	return NULL;
}
