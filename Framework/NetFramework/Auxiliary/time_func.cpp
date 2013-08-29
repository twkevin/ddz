#include "time_func.h"

#if QX_WIN32
#include <Windows.h>
#include <time.h>
#elif QX_IOS || QX_ANDROID
#include <sys/time.h>
#endif

NS_QX_BEGIN

CQXTime::CQXTime()
{

}

CQXTime::~CQXTime()
{

}

qxInt32 CQXTime::getTimeOfDay(struct qx_timeval *tp, void* tzp)
{
#if QX_WIN32
	if (tp)
	{
		tzp;
		SYSTEMTIME wtm;
		GetLocalTime(&wtm);

		struct tm tTm;
		tTm.tm_year     = wtm.wYear - 1900;
		tTm.tm_mon      = wtm.wMonth - 1;
		tTm.tm_mday     = wtm.wDay;
		tTm.tm_hour     = wtm.wHour;
		tTm.tm_min      = wtm.wMinute;
		tTm.tm_sec      = wtm.wSecond;
		tTm.tm_isdst    = -1;

		tp->tv_sec     = (qxInt32)mktime(&tTm);       // time_t is 64-bit on win32
		tp->tv_usec    = wtm.wMilliseconds * 1000;
	}
#endif
	return 0;
}


qxInt32 CQXTime::getTime()
{
	unsigned int currentTime;
#if QX_WIN32
	qx_timeval current;
	CQXTime::getTimeOfDay(&current, NULL);
#elif QX_IOS || QX_ANDROID
	struct timeval current;
	::gettimeofday(&current, NULL);
#endif
	currentTime = current.tv_sec * 1000 + current.tv_usec/1000;
	return currentTime;
}


NS_QX_END