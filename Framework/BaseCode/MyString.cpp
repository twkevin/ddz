// MyString.cpp: implementation of the CMyString class.
//
//////////////////////////////////////////////////////////////////////

#include "MyString.h"
#include "CQGlobal.h"
#include "BaseFunc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyString::CMyString()
{

}

//////////////////////////////////////////////////////////////////////
CMyString::CMyString(const char* fmt, ...)
{
	if (fmt)
	{
		char buffer[MAX_STRING] = "";
		TRY {
			char *pLastChar = buffer + sizeof(buffer) - 1;
			*pLastChar = 0;
			va_list ap;
			va_start(ap, fmt);
			_vsnprintf(buffer, sizeof(buffer), fmt, ap);
			va_end(ap);

			if (*pLastChar) {
				*pLastChar = 0;
				//LOGERROR("CMyString construction : too big size of string, cut off at %s, %d, %s", __FILE__, __LINE__, buffer);
			}
			this->assign(buffer);
		}CATCH(...)
		{
		//	LOGERROR("Error: too big size of string in format. %s", buffer);
		}
	}
}

//////////////////////////////////////////////////////////////////////
CMyString::~CMyString()
{

}

//////////////////////////////////////////////////////////////////////
void CMyString::format(const char* fmt, ...)
{
	if (!fmt)
		return;

	char buffer[MAX_STRING] = "";
	TRY {
		char *pLastChar = buffer + sizeof(buffer) - 1;
		*pLastChar = 0;
		va_list ap;
		va_start(ap, fmt);
		_vsnprintf(buffer, sizeof(buffer), fmt, ap);
		va_end(ap);
		if (*pLastChar) {
			*pLastChar = 0;
			LOGERROR("CMyString format : too big size of string, cut off at %s, %d, %s", __FILE__, __LINE__, buffer);
		}
		this->assign(buffer);
	}CATCH(...)
	{
		LOGERROR("Error: too big size of string in format. %s", buffer);
	}
}
