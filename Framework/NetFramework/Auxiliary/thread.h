#ifndef __QX_THREAD_H__
#define __QX_THREAD_H__

#include "raw_type.h"
#include "common_macro_define.h"

NS_QX_BEGIN

// VThread priorities
const qxInt32 VTHREAD_PRIORITY_DEFAULT = 0;

// VThread stack
const qxInt32 VTHREAD_STACK_SIZE_DEFAULT = 131072; // in bytes -- 2 ^ 17

// VThread flags
const qxUInt32 VTHREAD_SCHED_MASK = 0x0000000f;
const qxUInt32 VTHREAD_SCHED_DEFAULT = 0x00000001;
const qxUInt32 VTHREAD_SCHED_FIFO = 0x00000002;
const qxUInt32 VTHREAD_SCHED_RR = 0x00000004;

#if QX_IOS || QX_ANDROID
#include <pthread.h>
typedef pthread_t qxthread_t;
typedef pthread_attr_t qxthread_attr_t;
#elif QX_WIN32
#include "pthread.h"
/**
** Suspend execution of the calling task for the specified number 
** of seconds */
int QX_DLL sleep( int seconds );

/**
** Suspend execution of the calling task for the specified number 
** of micro seconds */
int QX_DLL usleep( int useconds );

// VThread types for WIN32 
typedef pthread_t  qxthread_t;
typedef pthread_attr_t qxthread_attr_t;    
// VThread constants for Win32
#else
#error "undefined thread"
#endif

class QX_DLL CQXThread
{
public:
	CQXThread(void);
	~CQXThread(void);

	qxBoolean spawn( void *(*startFunc)(void *),
		void *startArgs = 0,
		qxUInt32 flags = 0,
		qxUInt32 priority = VTHREAD_PRIORITY_DEFAULT,
		qxInt32 stack_size = VTHREAD_STACK_SIZE_DEFAULT );

	void DisableSelfId();
	qxInt32 join( void **status = 0 );
	qxInt32 getPriority() const;
	const qxthread_t getId() const;
	const qxthread_attr_t* getAttributes() const;
	void exit();
	void shutdown();
	qxBoolean isShutdown();
	void setparam( int param );
	qxInt32 getparam();
	static const qxthread_t selfId ();
private:
	qxthread_t m_ID;        
	qxthread_attr_t m_Attributes;
	qxBoolean m_bThreadCreated;
	qxBoolean m_bShutdown;
	qxInt32 m_nParam;
};

NS_QX_END

#endif //__QX_THREAD_H__

