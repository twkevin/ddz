#include "common_macro_define.h"
#if QX_IOS || QX_ANDROID
#include "thread.h"
NS_QX_BEGIN

CQXThread::CQXThread()
{
	m_bShutdown = false;
	m_bThreadCreated = false;
}


CQXThread::~CQXThread()
{

}

bool CQXThread::spawn( void *( *startFunc )( void * ),
					   void *startArgs /*Default Arguments*/,
					   qxUInt32 flags /*Default Arguments*/,
					   qxUInt32 priority /*Default Arguments*/,
					   qxInt32 stack_size /* Default Arguments*/ )
{
	struct sched_param priorityParams;
	if ( pthread_attr_init(&m_Attributes) != 0 )
		return false;
#ifndef ANDROID
	// 设置程序的schedpolicy （实时，先入先出，一般）
	switch( flags & VTHREAD_SCHED_MASK )
	{
	case VTHREAD_SCHED_FIFO:
		{
			if ( pthread_attr_setinheritsched(&m_Attributes,PTHREAD_EXPLICIT_SCHED) != 0 )
				return false;
			if ( pthread_attr_setschedpolicy(&m_Attributes,SCHED_FIFO) != 0 )
				return false;
		}
		break;
	case VTHREAD_SCHED_RR:
		{
			if ( pthread_attr_setinheritsched(&m_Attributes,PTHREAD_EXPLICIT_SCHED) != 0 )
				return false;
			if ( pthread_attr_setschedpolicy(&m_Attributes,SCHED_RR) != 0 )
				return false;
		}
		break;
	case VTHREAD_SCHED_DEFAULT:
		break;
	default:
		break;
	}
#endif
	// if anything expect default, set scheduling priority explicitly;
	// note that by default the priority of the parent thread is inherited
	if ( (int)priority != VTHREAD_PRIORITY_DEFAULT )
	{
		// probably should improve to use relative values
		priorityParams.sched_priority = priority;
		if ( pthread_attr_setschedparam(&m_Attributes,&priorityParams) != 0 )
			return false;
	}
	// spawn the thread
	m_bThreadCreated = true;
	if ( pthread_create(&m_ID,&m_Attributes,startFunc,startArgs) != 0 )
		return false;
	else
		return true;
}


int CQXThread::join( void **status /*Default Arguments*/)
{
	if ( !m_bThreadCreated )
		return 0;
	int retVal = pthread_join( m_ID, status );
	return retVal;
}


int CQXThread::getPriority() const
{
	struct sched_param priorityParams;
	//assert( pthread_attr_getschedparam( &m_Attributes, &priorityParams ) == 0 );
	return priorityParams.sched_priority;
}


const qxthread_t CQXThread::getId() const
{
	return m_ID;
}


const qxthread_attr_t* CQXThread::getAttributes() const
{
	return &m_Attributes;
}

void CQXThread::exit()
{
#ifdef ANDROID
	pthread_exit(0);
#else
	pthread_cancel( m_ID );
#endif
}


const qxthread_t CQXThread::selfId()
{
	return pthread_self();
}

bool CQXThread::isShutdown()
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

int CQXThread::getparam()
{
	return m_nParam;
}

NS_QX_END

#elif QX_WIN32
#include "thread_win32.cpp"
#else
#error
#endif




