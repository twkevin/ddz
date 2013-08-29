#pragma warning(disable: 4786) 

#include "MyDialog.h"
#include "BaseFunc.h"
#include "StringFormat.h"
#include "UIManager.h"
#include "AppWnd.h"

USING_NS_CC;

using namespace std;

#ifdef WIN32
LRESULT MY_CUSTOM_WND_PROC(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
	*pProcessed = TRUE;

	switch (message)
	{
	case WM_RBUTTONDOWN:
		{
			CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
			if (NULL == pEGLView)
			{
				return 1;
			}

			if (MK_RBUTTON == wParam)
			{
				float fFrameZoomFactor = pEGLView->getFrameZoomFactor();
				POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
				CCPoint pt(point.x, point.y);
				pt.x /= fFrameZoomFactor;
				pt.y /= fFrameZoomFactor;

				CCSize obScreenSize = pEGLView->getFrameSize();
				CCPoint tmp = ccp(pt.x, obScreenSize.height - pt.y);

				CCRect obViewPortRect = pEGLView->getViewPortRect();
				if (obViewPortRect.equals(CCRectZero) || obViewPortRect.containsPoint(tmp))
				{
					CCTouch* pHitTouch = new CCTouch;
					CHECKF(pHitTouch);
					pHitTouch->setTouchInfo(1, pt.x, pt.y);
					g_objUIMgr.OnTouchBegan(pHitTouch);
					DLG_HANDLE hWndTouch = g_objUIMgr.GetTouchHandleObj();

					if (0 == hWndTouch)
					{
						return 1;
					}

					CCMyWndObject* pWndObj = g_objUIMgr.GetWndObj(hWndTouch);
					if (NULL == pWndObj)
					{
						return 1;
					}

					std::string strContent = FORMAT("[%d-%d]")
						<< pWndObj->getParentWndID() << pWndObj->getWndID();
					std::cout << strContent << std::endl;

					if (CTRL_DIALOG == pWndObj->GetType() || CTRL_LIST_CELL == pWndObj->GetType())
					{
						const char* pName = get_DlgBuilderMap[pWndObj->getWndID()]->GetDialogClassName();
						if (NULL != pName)
						{
							std::cout << pName << std::endl;
						}
					}
					else
					{
						CCMyWndObject* pParent = pWndObj->GetUIParent();
						if (pParent && (CTRL_DIALOG == pParent->GetType() || CTRL_LIST_CELL == pParent->GetType()))
						{
							const char* pName = get_DlgBuilderMap[pParent->getWndID()]->GetDialogClassName();
							if (NULL != pName)
							{
								std::cout << pName << std::endl;
							}
						}
					}

					CC_SAFE_DELETE(pHitTouch);
					g_objUIMgr.DoTouchOver();
				}
			}
		}
		break;

	default:
		{
			*pProcessed = FALSE;
		}
		break;
	}

	return 0;
}
#endif

void CMyTouchDispatcher::touchesBegan(CCSet* touches, CCEvent* pEvent)
{
	CCTouchDispatcher::touchesBegan(touches, pEvent);
}

void CMyTouchDispatcher::touchesMoved(CCSet* touches, CCEvent* pEvent)
{
	CCTouchDispatcher::touchesMoved(touches, pEvent);
}

void CMyTouchDispatcher::touchesEnded(CCSet* touches, CCEvent* pEvent)
{
	CCTouchDispatcher::touchesEnded(touches, pEvent);
	g_objUIMgr.DoTouchOver();
}

void CMyTouchDispatcher::touchesCancelled(CCSet* touches, CCEvent* pEvent)
{
	CCTouchDispatcher::touchesCancelled(touches, pEvent);
	g_objUIMgr.DoTouchOver();
}

CAppWnd::CAppWnd()
	:CCMyWndObject()
{
	this->initGUI();
}
CAppWnd::~CAppWnd()
{
}
void CAppWnd::ReleaseAll()
{
	LIST_CTRL& cld = GetChild();
	LIST_CTRL toRelease;
	toRelease.swap(cld);	
	CCMyWndObject* lpItem = NULL;
	for(LIST_CTRL::iterator itr = toRelease.begin();itr!=toRelease.end();itr++)
	{
		lpItem = *itr;
		if(lpItem->GetType()==CTRL_DIALOG||lpItem->GetType()==CTRL_DLG)
		{
//			lpItem->DestroyWindow();
			SAFE_DELETE(lpItem);
		}
	}
}

GLint CAppWnd::initGUI(void)
{
	CMyTouchDispatcher* pNewTouchDispatcher = new CMyTouchDispatcher;
	if (NULL == pNewTouchDispatcher || !pNewTouchDispatcher->init())
	{
		return 0;
	}

	CCDirector::sharedDirector()->setTouchDispatcher(pNewTouchDispatcher);
	CCEGLView* pView = CCDirector::sharedDirector()->getOpenGLView();
	if (pView)
	{
		pView->setTouchDelegate(pNewTouchDispatcher);
		pNewTouchDispatcher->setDispatchEvents(true);
	}

	CC_SAFE_RELEASE(pNewTouchDispatcher);

#ifdef WIN32
	pView->setWndProc(MY_CUSTOM_WND_PROC);
#endif

	return 0;
}
