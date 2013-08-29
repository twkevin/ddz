#include "windows.h"
#pragma warning( disable : 4786)
#pragma warning( disable : 4290)
#include "pthread.h"
#include "semaphore.h"
#include "thread.h"
#include <assert.h>

NS_QX_BEGIN

CQXThread::CQXThread(void)
: m_nParam(0)
, m_bShutdown(false)
, m_bThreadCreated(false)
{
	memset( &m_Attributes, 0, sizeof( pthread_attr_t ) );
}

CQXThread::~CQXThread( void )
{

}

qxBoolean CQXThread::spawn( void* (*startFunc)(void *), void *startArgs, qxUInt32 flags, qxUInt32 /*priority*/, int /*stack_size*/ )
{
	m_bShutdown = false;
	struct sched_param priorityParams;
	if ( pthread_attr_init(&m_Attributes)!=0 )
		return false;

	//一些属性在win32下不受支持,所以在这里分三个级别作处理,忽略priority参数
	switch( flags & VTHREAD_SCHED_MASK )
	{
	case VTHREAD_SCHED_FIFO:
		priorityParams.sched_priority = THREAD_PRIORITY_ABOVE_NORMAL;
		if ( pthread_attr_setschedparam(&m_Attributes,&priorityParams) != 0 )
			return false;
		break;

	case VTHREAD_SCHED_RR:
		priorityParams.sched_priority = THREAD_PRIORITY_HIGHEST;
		if ( pthread_attr_setschedparam(&m_Attributes,&priorityParams) != 0 )
			return false;
		break;

	case VTHREAD_SCHED_DEFAULT:
		priorityParams.sched_priority = THREAD_PRIORITY_NORMAL;
		if ( pthread_attr_setschedparam(&m_Attributes,&priorityParams) != 0 )
			return false;
	default:
		break;
	}
	m_bThreadCreated = true;
	if ( pthread_create(&m_ID,&m_Attributes,startFunc,startArgs) != 0 )
		return false;
	else
		return true;
}

qxInt32 CQXThread::join( void **status )
{
	if ( !m_bThreadCreated )
		return 0;
	int retVal = pthread_join( m_ID, status );
	m_bThreadCreated = false;
	return retVal;
}


qxInt32 CQXThread::getPriority( void ) const
{
	struct sched_param priorityParams;
	memset( &priorityParams, 0, sizeof(priorityParams) );
	assert( pthread_attr_getschedparam( &m_Attributes, &priorityParams ) == 0 );
	return priorityParams.sched_priority;
}


const qxthread_t CQXThread::getId( void ) const
{
	return m_ID;
}


const qxthread_attr_t* CQXThread::getAttributes( void ) const
{
	return &m_Attributes;
}


void CQXThread::exit( void )
{
	pthread_cancel( m_ID );
}

const qxthread_t CQXThread::selfId( void )
{
	return pthread_self();
}

qxBoolean CQXThread::isShutdown()
{
	return m_bShutdown;
}

void CQXThread::shutdown()
{
	m_bShutdown = true;
}

void CQXThread::setparam( int param )
{
	m_nParam = param;
}


qxInt32 CQXThread::getparam()
{
	return m_nParam;
}

qxInt32 sleep( int seconds )
{
	Sleep (seconds * 1000);
	return 0;
}

qxInt32 usleep( int useconds )
{
	Sleep (useconds / 1000);
	return 0;
}

NS_QX_END