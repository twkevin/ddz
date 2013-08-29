#include "DialogBase.h"

#include "IniMgr.h"
#include "MyGlobal.h"


CCDialogBase::CCDialogBase()
{
}

CCDialogBase::~CCDialogBase()
{

}
void CCDialogBase::Create(int nWndID, CCMyWndObject *pParent)
{
	this->setWndID(nWndID);
	SetUIParent(pParent);
}

void CCDialogBase::BindEvent()
{

}

void CCDialogBase::DoDataExchange(void* pDX)
{

}

GLint CCDialogBase::readNode()
{
	GLint nRet = CCMyWndObject::readNode();

	return nRet;
}

GLint CCDialogBase::initGUI()
{
	GLint nRet = this->readNode();
	if (0 != nRet)
	{
		return nRet;
	}

	return nRet;
}

int CCDialogBase::GetType() const
{
	return CTRL_DLG;
}
