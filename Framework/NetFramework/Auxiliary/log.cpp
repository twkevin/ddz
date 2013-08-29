#include "log.h"
#include "mutex.h"
#include "time_func.h"
#include "string_func.h"
#include <stdarg.h>

#if QX_WIN32
#include "Win32_setting.h"
#endif

NS_QX_BEGIN

std::map<qxUInt16, string> s_pMapPriName;

CQXLog::CQXLog()
: m_BuffUsed(0)
, m_Buff(0)
, m_FlushMode(true)
, m_BuffSize(0)
, m_Enable(false)
{

}

CQXLog::~CQXLog()
{
	if (!m_FlushMode)
	{
		QX_SAFE_DELETE_ARRAY(m_Buff);
	}
}

void CQXLog::init()
{
	s_pMapPriName[emerg] = "EMERG";
	s_pMapPriName[alert] = "ALERT";
	s_pMapPriName[crit] = "CRIT";
	s_pMapPriName[err] = "ERR";
	s_pMapPriName[warning] = "WARNING";
	s_pMapPriName[notice] = "NOTICE";
	s_pMapPriName[info] = "INFO";
	s_pMapPriName[debug] = "DEBUG";
}

void CQXLog::log(qxUInt16 Priority, qxString fmt, ...)
{
	if (!m_Enable)
	{
		return;
	}

	QX_THREAD_LOCK
	va_list ap;
	va_start(ap, fmt);
	log(Priority, fmt, ap);
	va_end(ap);
}


void CQXLog::log(qxUInt16 Priority, qxString fmt, va_list ap)
{
	if (!m_Enable)
	{
		return;
	}

	CQXMutexAss threadlock;
	if ((Priority&m_Priority) == Priority)
	{
		qxChar datebuf[EXTRA_INFO_SIZE]={0};

		struct qx_timeval tv;
		qxInt32 result = timeofday(&tv, NULL);

		if( result == -1 )
		{
			datebuf [0] = '\0';
		}
		else
		{
			const time_t timeInSeconds = (time_t) tv.tv_sec;
			strftime(datebuf, EXTRA_INFO_SIZE, "at %m-%d %H:%M:%S", localtime (&timeInSeconds));
		}

		char outBuff[DEFAULT_BUFF_SIZE_SIG]={0};
		std::string allInfo = "[";
		allInfo += datebuf;
		allInfo += "]";
		//if (QX_VALID_POINT(s_pMapPriName))
			allInfo += s_pMapPriName[Priority].c_str();
		allInfo += " ";
		if (QX_VALID_POINT(fmt))
		{
			vsnprintf(outBuff, DEFAULT_BUFF_SIZE_SIG-1, fmt, ap);
		}
		allInfo += outBuff;
		allInfo += "\n";
		
		qxInt32 nLen = allInfo.length();
		if (m_FlushMode)
		{
			m_Buff = ((qxChar*)allInfo.c_str());
			m_BuffUsed = ((qxInt16)nLen);
			this->onLogFlush();
		}
		else
		{
			if (m_BuffUsed + nLen > DEFAULT_BUFF_SIZE_ALL)
			{
				this->onLogFlush();
				m_BuffUsed = 0;
			}
			memcpy(m_Buff+m_BuffUsed, allInfo.c_str(), nLen);
			m_BuffUsed += ((qxInt16)nLen);
		}
	}
}

void CQXLog::logWithFile(qxString FileName, qxUInt32 FileLine, qxUInt16 Priority, qxString fmt, ...)
{
	if (!m_Enable)
	{
		return;
	}

	QX_THREAD_LOCK
	char linefmt[DEFAULT_BUFF_SIZE_SIG/4];
	va_list ap;
	va_start(ap, fmt);
	log(Priority, CQXString::Format(linefmt, DEFAULT_BUFF_SIZE_SIG/4, "%s %d %s", FileName, FileLine, fmt), ap);
	va_end(ap);
}

qxChar* CQXLog::InitLog(qxUInt16 Buffsize, qxBoolean FlushMode)
{
	m_FlushMode = FlushMode;
	if (!m_FlushMode)
	{
		m_Buff = new qxChar[Buffsize];
	}
	m_Enable = true;
	return m_Buff;
}

CQXLog* CQXLog::m_pDefaultLog;

CQXLog* CQXLog::SetDefaultLog(CQXLog* pLog)
{
	CQXLog* pOld = m_pDefaultLog;
	m_pDefaultLog = pLog;
	return pOld;
}

CQXLog* CQXLog::GetDefaultLog()
{
	return m_pDefaultLog;
}

void qxLog(qxUInt16 Priority, qxString fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	CQXLog::GetDefaultLog()->log(Priority, fmt, ap);
	va_end(ap);
	
}

void qxLogWithFile(qxString FileName, qxUInt32 FileLine, qxUInt16 Priority, qxString fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	CQXLog::GetDefaultLog()->logWithFile(FileName, FileLine, Priority, fmt, ap);
	va_end(ap);
}


void  qxLuaLog(qxString s)
{
	qxLog(warning,  s);
}

NS_QX_END
