#include "log2file.h"
#include "string.h"
#include "../BaseCode/PublicFunc.h"


NS_QX_BEGIN

CQXLog2File::CQXLog2File()
: CQXLog()
, m_pOutputFile(QX_NULL_POINT)
{

}

CQXLog2File::~CQXLog2File()
{
	if (QX_VALID_POINT(m_pOutputFile))
	{
		fclose(m_pOutputFile);
	}
}

void CQXLog2File::setOutputFile(qxString FilePath)
{
	m_pOutputFile = CQfopen(FilePath, "a+");
#if QX_WIN32
	AllocConsole();
	m_hCMD = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
	if (QX_VALID_POINT(m_pOutputFile))
	{
		fseek(m_pOutputFile, 0, SEEK_END); 
		int nFileSize = ftell(m_pOutputFile); 

		if (nFileSize >= 512 * 1024)
		{
			fclose(m_pOutputFile);
			m_pOutputFile = NULL;
			m_pOutputFile = CQfopen(FilePath, "w+");
			if (!m_pOutputFile)
			{
				return;
			}
		}
		qxString logInfo = "-------------Open new log file---------------\n";
		fwrite(logInfo, strlen(logInfo), 1, m_pOutputFile);
	}
}

void CQXLog2File::onLogFlush()
{
	if (QX_VALID_POINT(m_pOutputFile)) 
	{
		fwrite(m_Buff, m_BuffUsed, 1, m_pOutputFile);
		fflush(m_pOutputFile);
	}
#if QX_WIN32
	DWORD num = 0; 
	if (m_bUnicode)
	{
		unsigned int nSize = DEFAULT_BUFF_SIZE_ALL;
		wchar_t out[DEFAULT_BUFF_SIZE_ALL];
		nSize = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, m_Buff, m_BuffUsed, out, nSize);  
		WriteConsole(m_hCMD, out, nSize, &num, NULL);
	}
	else
	{
		WriteConsole(m_hCMD, m_Buff, m_BuffUsed, &num, NULL);
	}
#else
	printf("%s", m_Buff);
#endif
}

//static CQXLog2File* m_pDefaultLog = QX_NULL_POINT;

NS_QX_END