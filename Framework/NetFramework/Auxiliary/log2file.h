#ifndef __QX_LOG2FILE_H__
#define __QX_LOG2FILE_H__

#include "common_macro_define.h"

#if QX_WIN32
#include <windows.h>
#include "Win32_setting.h"
#endif

#include "log.h"

NS_QX_BEGIN

class QX_DLL CQXLog2File : public CQXLog
{
public:
	CQXLog2File();
	virtual ~CQXLog2File();

	void setOutputFile(qxString FilePath);

	virtual void onLogFlush();
#if QX_WIN32
	void setOutputStringEncodeAsMBCS(bool bFlag){
		m_bUnicode = bFlag;
	};
#endif
private:
	FILE* m_pOutputFile;
#if QX_WIN32
	HANDLE m_hCMD;
	bool m_bUnicode;
#endif
};

NS_QX_END

#endif //__QX_LOG2FILE_H__