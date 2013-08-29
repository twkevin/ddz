#include <errno.h>
#if !defined WIN32
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#else
#pragma warning(disable: 4996)
#endif
#include <stdio.h>


#include "tcpClientSocket.h"
#include "networkAddress.h"
#include "log.h"

using namespace std;

TcpClientSocket::TcpClientSocket( const std::string& hostName, bool blocking )
					: _hostName( hostName ), _serverPort( -1 ), _blocking( blocking ), _bAddr(false)
{

}

TcpClientSocket::TcpClientSocket( bool blocking/*=true*/ )
						: _serverPort( -1 ), _blocking( blocking ), _bAddr(false)
{

}

TcpClientSocket::TcpClientSocket( const std::string& hostName, int servPort, bool blocking )
								: _hostName( hostName ), _serverPort( servPort ), _blocking( blocking ),_bAddr(false)
{

}


TcpClientSocket::TcpClientSocket( const NetworkAddress& server, bool blocking )
												: _blocking( blocking )
{
    _hostName = server.getHostName();
    _serverPort = server.getPort();
}


TcpClientSocket::TcpClientSocket( const TcpClientSocket& other )
{
    _conn = other._conn;
	_hostName = other._hostName;
	_serverPort = other._serverPort;
	_blocking = other._blocking;
}


TcpClientSocket& TcpClientSocket::operator=( TcpClientSocket& other )
{
    if ( this != &other)
    {
        _conn = other._conn;
        _hostName = other._hostName;
        _serverPort = other._serverPort;
        _blocking = other._blocking;
    }
    return *this;
}


TcpClientSocket::~TcpClientSocket()
{
	close();
}


bool TcpClientSocket::connect()
{
	if ( _conn.isLive() )
	{
		quarkxV2::qxLog( quarkxV2::debug, __FILE__, __LINE__, "connection is alive" );
		return false;
	}
	int socketid = ::socket( AF_INET, SOCK_STREAM, 0 );
	if ( socketid == -1 )
	{
		quarkxV2::qxLog( quarkxV2::err, __FILE__, __LINE__, "Failed to create socket when connect to fserver %s, reason %s", _hostName.c_str(), strerror(errno) );
		return false;
	}

	memset( &_conn._connAddr, 0, sizeof(_conn._connAddr) );

	if ( _bAddr )
	{
		memcpy( &_conn._connAddr, &_addr, sizeof(sockaddr) );
	}
	else
	{
		NetworkAddress na( _hostName, (unsigned short)(_serverPort) );	
		_conn._connAddr.sin_family = AF_INET;
		_conn._connAddr.sin_addr.s_addr = inet_addr( na.getIpName().c_str() );
		_conn._connAddr.sin_port = htons( na.getPort() );
		if ( !na.isValid() )
		{
			quarkxV2::qxLog( quarkxV2::err, "addr err" );
			return false;
		}
		int nSndBuf = 64*1024;
		::setsockopt(socketid, SOL_SOCKET, SO_SNDBUF, (char*) &nSndBuf, sizeof(nSndBuf));
		::setsockopt(socketid, SOL_SOCKET, SO_RCVBUF, (char*) &nSndBuf, sizeof(nSndBuf));
	}

	if ( ::connect( socketid, (SA*)&_conn._connAddr, sizeof(_conn._connAddr) ) < 0 )
    {
		#ifndef WIN32
		::close( socketid );
		#else
		closesocket( socketid );
		#endif
        quarkxV2::qxLog( quarkxV2::err, __FILE__, __LINE__, "Failed to connect to server %s, reason %s", _hostName.c_str(), strerror(errno) );
		return false;
    }
	_conn._connId = socketid;
	_conn.setBlocking( _blocking );
    _conn.setState();
	return true;
}


void TcpClientSocket::setServer( const string& server, int serverPort, bool blocking )
{
	_bAddr = false;
	_hostName = server;
	_serverPort = serverPort;
	_blocking = blocking;
}

void TcpClientSocket::setServer( struct sockaddr addr, bool blocking )
{
	_bAddr = true;
	_addr = addr;
	_blocking = blocking;
}

void TcpClientSocket::close()
{
	_conn.close();
}
