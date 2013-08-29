#include <errno.h>

#if !defined WIN32
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#else
#pragma warning(disable: 4127)
#pragma warning(disable: 4996)
#endif

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <signal.h>
#include "tcpConnection.h"
#include "log.h"
#include "mutex.h"

using namespace std;
static quarkxV2::CQXMutex closeMutex;

TcpConnection::TcpConnection( const TcpConnection& other )
{
	_connId = other._connId;
	_live = other._live;
	_connAddrLen = other._connAddrLen;
	_blocking = other._blocking;
	_timeout = other._timeout;
	_bThrowException = other._bThrowException;
	memcpy( (void*)&_connAddr, (void*)&other._connAddr, sizeof( _connAddr ) );
	closeMutex.lock();
	useNum = other.useNum;
	if ( useNum != NULL )
		(*useNum)++;
	closeMutex.unlock();
}

TcpConnection& TcpConnection::operator=( const TcpConnection& other )
{
	if ( this != &other )
	{
		if ( _live )
		{
			close();
			_live = false;
		}
		closeMutex.lock();
		_connId = other._connId;
		_live = other._live;
		_connAddrLen = other._connAddrLen;
		_blocking = other._blocking;
		_timeout = other._timeout;
		_bThrowException = other._bThrowException;
		memcpy( (void*)&_connAddr, (void*)&other._connAddr, sizeof(_connAddr) );
		useNum = other.useNum;
		if ( NULL != useNum )
			(*useNum)++;
		closeMutex.unlock();
	}
	return *this;
}

int TcpConnection::readLine( void* dataRead, int maxlen, int timeout )
{
	memset( dataRead, 0, maxlen );
	char c;
	int rc, i;
	char* ptr = (char*)dataRead;
	for( i = 1; i<maxlen; i++ )
    {
		rc = readn( &c, 1, timeout );
        if ( rc == 1 )
        {
            *ptr++ = c;
            if ( c=='\n' )
			{
				i--;
				ptr--;
				if ( *(ptr-1) == '\r' )
				{ i--;ptr--; }
				break;
			}
        }
        else if ( rc == 0 )
        {
            quarkxV2::qxLogWithFile( __FILE__, __LINE__,  quarkxV2::err, "read line err" );	//can't not go here
			*ptr = 0;
			return -1;
        }
        else
        {
            return -2;
        }
    }
    *ptr = 0;
    return i;
}

int TcpConnection::readData( void *dataRead, int nchar, int &bytesRead, int timeout )
{
	if ( !_live )
	{
		if ( _bThrowException )
			quarkxV2::qxLogWithFile( __FILE__, __LINE__,  quarkxV2::info, "connection close");
			//throw VNetworkException( "connection close", __FILE__, __LINE__ );
		return -1;
	}
    int nleft;
    int nread;
    char *ptr = (char*)dataRead;
    nleft = nchar;
	bytesRead = 0;
    while ( nleft > 0 )
    {
        if ( ( nread = readn( ptr, nleft, timeout ) ) <= 0 )
		{
			return nread;
		}
        nleft -= nread;
        ptr += nread;
        bytesRead += nread;
    }
    return 1;
}

int TcpConnection::readn( void *dataRead, int nchar, int timeout )
{
	int iRead;
    assert( dataRead );
	int msec = timeout<0 ? _timeout : timeout;
	if ( !isReadReady( msec ) )
	{
		 return 0;
		//if ( _bThrowException )
		//	//throw VNetworkException( "read data timeout", __FILE__, __LINE__ );
		//return 0;
	}
	#ifndef WIN32
    iRead = read( _connId, dataRead, nchar );
	#else
    iRead = recv( _connId, (char*)dataRead, nchar, 0 );
	#endif
	if ( iRead < 0 )
	{
		if ( _bThrowException )
		{
			#ifdef WIN32
				int errorN = WSAGetLastError();
				quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "connection error %d", errorN);
			#else
				quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "connection error");
			#endif
		}
		return -1;
	}
	else
	{
		return iRead;
	}
}


int TcpConnection::readIfHasData( void* data, int nchar, int& bytesRead, int timeout )
{
	if ( !_live )
	{
		if ( _bThrowException )
			quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "connection close");
		return -1;
	}
	int nleft;
    int nread;
    char *ptr = (char*)data;
    nleft = nchar;
	bytesRead = 0;
	int tout = 0;
    do
    {
        if ( ( nread = readn( ptr, nleft, tout ) ) <= 0 )
		{
			return nread;
		}
		else
		{
			tout = timeout;
		}
        nleft -= nread;
        ptr += nread;
        bytesRead += nread;
    } while ( nleft > 0 );
	return nread;
}

int TcpConnection::writeData( const string& data, int timeout )
{
    char *ptr = (char*)data.c_str();
    int nleft = data.size();
    return writeData( ptr, nleft, timeout );
}

int TcpConnection::writeData( const void* data, int n, int timeout )
{
	if ( !_live )
	{
		if ( _bThrowException )
			quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "connection close");
		return -1;
	}
	int msec = timeout<0 ? _timeout : timeout;
    int nleft;
    int nwritten;
    char *ptr = (char*)data;
    nleft = n;
    while ( nleft > 0 )
    {
		if ( !isWriteReady( msec ) )
		{
			if ( _bThrowException )
				quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "write data timeout");
				//throw VNetworkException( "write data timeout", __FILE__, __LINE__ );
			return ptr-(char*)data;
		}
		#ifndef WIN32
        if ( ( nwritten = ::write( _connId, ptr, nleft ) ) < 0 )
		#else
		if ( ( nwritten = ::send( _connId, ptr, nleft, 0 ) ) < 0 )
		#endif
        {
			if ( _bThrowException )
			{
				#ifdef WIN32
				int errorN = WSAGetLastError();
				quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "connection close %d", errorN);
				if (errorN == 10054)
				{
				}
				#else
				quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::info, "connection close");
				#endif
			}
			if ( ptr != data )
			{
				return ptr-(char*)data;
			}
			else
			{
				return -1;
			}
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
	return ptr-(char*)data;
}


#ifdef _WIN32
#define snprintf _snprintf
#endif

string TcpConnection::getDescription() const
{
    string retStr;
    SA* sa = (SA*) & _connAddr;
    const u_char* p = (const u_char*)&_connAddr.sin_addr;
    switch ( sa->sa_family )
    {
    case AF_INET:
        char temp[256];
        snprintf( temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3] );
        char pStr[56];
        sprintf( pStr, ":%d", ntohs(_connAddr.sin_port) );
        retStr = temp;
        retStr += pStr;
		return ( retStr );
        break;
	default:
        return "Unknown";
        break;
    }
	return "Unknown";
}

string TcpConnection::getIp() const
{
    string retStr;
    SA* sa = (SA*)&_connAddr;
    const u_char* p = (const u_char*)&_connAddr.sin_addr;
    switch ( sa->sa_family )
    {
	case AF_INET:
        char temp[256];
        snprintf( temp, sizeof(temp), "%d.%d.%d.%d",
					p[0], p[1], p[2], p[3] );
        retStr = temp;
        return retStr;
        break;
	default:
        return "Unknown";
        break;
    }
	return "Unknown";
}

unsigned short TcpConnection::getPort() const
{
	return ntohs( _connAddr.sin_port );
}

TcpConnection::~TcpConnection()
{
	close();
}

void TcpConnection::close()
{
	closeMutex.lock();
	if ( !_live )
	{
		closeMutex.unlock();
		return;
	}
	else
	{
		_live = false;
	}
	(*useNum)--;
	if ( *useNum == 0 )
	{
		assert( _connId >= 0 );
		#ifndef WIN32
		::close( _connId );
		#else
		closesocket( _connId );
		#endif
		delete useNum;
	}
	_connId = 0;
	useNum = NULL;
	closeMutex.unlock();
}

void TcpConnection::setState()
{
	closeMutex.lock();
	useNum = new int;
	*useNum = 1;
    _live = true;
	setBlocking( _blocking );
	closeMutex.unlock();
}


void TcpConnection::setBlocking( bool block )
{
	_blocking = block;
	#ifndef WIN32
	int non_blocking = _blocking ? 0 : 1;
	if ( ioctl( _connId, FIONBIO, &non_blocking ) < 0 )
	{
		quarkxV2::qxLog( quarkxV2::err, "Error setting Connection FIONBIO: %s", strerror(errno) );	
	}
	#else
	unsigned long non_blocking = _blocking ? 0 : 1;
	if ( ioctlsocket( _connId, FIONBIO, &non_blocking ) == SOCKET_ERROR )
	{
		quarkxV2::qxLogWithFile(__FILE__, __LINE__,  quarkxV2::err, "Error setting Connection FIONBIO: %s", strerror(errno) );
	}
	#endif
}


void TcpConnection::setTimeout( int timeout )
{
	_timeout = timeout;
}

void TcpConnection::enableException( bool bThrowException )
{
	_bThrowException = bThrowException;
}


bool TcpConnection::isReadReady( int mSeconds ) const
{
    fd_set rfds;
	fd_set efds;
    struct timeval tv;
	struct timeval *ptv;
    int retval;
	FD_ZERO( &rfds );
	FD_ZERO( &efds );
	FD_SET( _connId, &rfds );
	FD_SET( _connId, &efds );
	if ( mSeconds < 0 )
	{
		ptv = NULL;
	}
	else
	{
		ptv = &tv;
		tv.tv_sec = mSeconds/1000;
		tv.tv_usec = ( mSeconds%1000 ) * 1000;
	}
    retval = select( _connId+1, &rfds, NULL, &efds, ptv );
    if ( retval>0 && FD_ISSET(_connId,&rfds) )
    {
        return true;
    }
    return false;
}

bool TcpConnection::isWriteReady( int mSeconds ) const
{
    fd_set wfds;
	fd_set efds;
    struct timeval tv;
	struct timeval *ptv;
    int retval;
    FD_ZERO( &wfds );
	FD_ZERO( &efds );
    FD_SET( _connId, &wfds );
	FD_SET( _connId, &efds );
	if ( mSeconds < 0 )
	{
		ptv = NULL;
	}
	else
	{
		ptv = &tv;
		tv.tv_sec = mSeconds/1000;
		tv.tv_usec = (mSeconds%1000)*1000;
	}
    retval = select( _connId+1, NULL, &wfds, &efds, ptv );
    if ( retval>0 && FD_ISSET(_connId,&wfds) )
        return true;
    return false;
}
