/*
 *  DialogImpl.cpp
 */

#include "DialogImpl.h"


CDialogImpl::CDialogImpl()
{
}
CDialogImpl::~CDialogImpl()
{
}
void CDialogImpl::DDX_Control_Imp(void *pDX, int nIDC, CCMyWndObject &rControl)
{
	rControl.setParentWndID((int)pDX);
	rControl.setWndID(nIDC);
	rControl.SetUIParent(this);
	rControl.initGUI();
}
