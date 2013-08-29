#include <errno.h>
#include <cassert>
#include "mutex.h"

NS_QX_BEGIN

CQXMutex::CQXMutex(void)
{
	int err = pthread_mutex_init( &m_ID, NULL );
	assert( err == 0);
}

CQXMutex::~CQXMutex(void)
{
	int err = pthread_mutex_destroy( &m_ID );
	assert( err != EBUSY );
	assert( err == 0 );
}

void CQXMutex::lock ()
{
	int err = pthread_mutex_lock( &m_ID );
	assert( err != EINVAL );
	assert( err != EDEADLK );
	assert( err == 0 );
}

void CQXMutex::unlock ()
{
	int err = pthread_mutex_unlock( &m_ID );
	assert( err != EINVAL );
	assert( err != EPERM );
	assert( err == 0);
}

CQXMutexAss::CQXMutexAss()
{
	m_lock.lock();
}

CQXMutexAss::~CQXMutexAss()
{
	m_lock.unlock();
}

NS_QX_END