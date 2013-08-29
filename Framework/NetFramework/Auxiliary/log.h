#ifndef __QX_LOG_H__
#define __QX_LOG_H__

#include "common_macro_define.h"
#include "raw_type.h"
#include <stdio.h>
#include <map>


#if QX_ANDROID
#include <stdarg.h>
#endif

NS_QX_BEGIN

typedef enum{
	emerg       = 1, 							//系统错误
	alert       = 1 << 1,						//重要提示错误
	crit        = 1	<< 2,						//危险错误
	err         = 1	<< 3,						//一般错误
	warning     = 1	<< 4,						//警告
	notice      = 1	<< 5,						//重要信息
	info        = 1	<< 6,						//提示
	debug       = 1	<< 7,						//调试
	all         = 0xFFFF
} qx_log_priority;

const qxUInt16 EXTRA_INFO_SIZE = 256;
const qxUInt16 DEFAULT_BUFF_SIZE_SIG = 1024*4;
const qxUInt16 DEFAULT_BUFF_SIZE_ALL = 10240;
const qxUInt16 LOG_PRIORITY_NUM = 8;

class QX_DLL CQXLog
{
public:
	CQXLog();
	virtual ~CQXLog();

	QX_PROPERTY(qxBoolean, m_Enable, LogEnable);
	QX_PROPERTY(qxUInt16, m_Priority, Priority);
	QX_PROPERTY(qxBoolean, m_FlushMode, FlushMode);
	qxChar* InitLog(qxUInt16 Buffsize, qxBoolean FlushMode = true);

	void log(qxUInt16 Priority, qxString fmt, ...);
	void log(qxUInt16 Priority, qxString fmt, va_list ap);
	void logWithFile(qxString FileName, qxUInt32 FileLine, qxUInt16 Priority, qxString fmt, ...);

	static void init();
	static CQXLog* SetDefaultLog(CQXLog* pLog);
	static CQXLog* GetDefaultLog();

	virtual void onLogFlush() QX_PURE_VIRTUAL;
protected:
	qxUInt16 m_BuffSize;
	qxChar* m_Buff;
	qxUInt16 m_BuffUsed;
	static CQXLog* m_pDefaultLog;
};


void QX_DLL qxLog(qxUInt16 Priority, qxString fmt, ...);
void QX_DLL qxLuaLog(qxString s);
void QX_DLL qxLogWithFile(qxString FileName, qxUInt32 FileLine, qxUInt16 Priority, qxString fmt, ...);

#define QX_IF_NOT(b, s) if(!b){QXLOGW(s);}

#if LOG_ENABLE
#define QXLOG(L, format, ...)                qxLog(L, format, ##__VA_ARGS__)
#define QXLOGW(format, ...)                  qxLog(warning, format, ##__VA_ARGS__)
#define QXLOGWITHFILE(format, ...)           qxLogFile(__FILE__, __LINE__, warning, format, ##__VA_ARGS__)
#define QXLOGWITHSCREEN(L, format, ...)         qxLogWithScreen(L, format, ##__VA_ARGS__)
#else
#define QXLOG(L, format, ...)
#define QXLOGW(format, ...) 
#define QXLOGWITHFILE(format, ...)
#define QXLOGWITHSCREEN(format, ...)
#endif

NS_QX_END

#endif //__QX_LOG_H__

