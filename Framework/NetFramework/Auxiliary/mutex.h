#ifndef __QX_MUTEX_H__
#define __QX_MUTEX_H__

#include "common_macro_define.h"

#if QX_WIN32
#include "pthread.h"
#elif QX_IOS
#include <pthread.h>
#elif QX_ANDROID
#include <pthread.h>
#else
#error "undefine mutex"
#endif


NS_QX_BEGIN

typedef pthread_mutex_t qx_mutex_t;

class QX_DLL CQXMutex
{
public:
	CQXMutex(void);
	~CQXMutex(void);

	void lock(void);
	void unlock(void);

private:
	qx_mutex_t m_ID;
};

class QX_DLL CQXMutexAss 
{
public:
	CQXMutexAss(void);
	~CQXMutexAss(void);
private:
	CQXMutex m_lock;
};

#if (defined QX_MULTITHREAD_SUPPORT)
#define QX_THREAD_LOCK CQXMutexAss threadlock;
#else
#define QX_THREAD_LOCK
#endif

NS_QX_END

#endif //__QX_MUTEX_H__

