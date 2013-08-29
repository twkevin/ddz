#ifndef _GUI_APPWND_H
#define _GUI_APPWND_H

#include <vector>
#include <map>
#include "MyGlobal.h"
#include "MyWndObject.h"
#include "cocos2d.h"

class CMyTouchDispatcher : public cocos2d::CCTouchDispatcher
{
	virtual void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* pEvent);
	virtual void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* pEvent);
	virtual void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* pEvent);
	virtual void touchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* pEvent);
};

//�����CWndObject,���еĴ��ںͿؼ����������Ӵ��ڻ�������Ӵ���
class CAppWnd : public CCMyWndObject
{
public:
	CAppWnd();
	virtual ~CAppWnd();

	//�ͷ�ȫ������
	void ReleaseAll();

	virtual GLint initGUI();
};

#endif
