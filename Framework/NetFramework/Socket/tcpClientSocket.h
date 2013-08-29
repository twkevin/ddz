#ifndef  _TCP_CLIENTSOCKET_
#define  _TCP_CLIENTSOCKET_

#if !defined WIN32
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#endif


#include "TcpConnection.h"

class NetworkAddress;

class TcpClientSocket
{

public:

	TcpClientSocket( const std::string& hostName, bool blocking = true );
	
	TcpClientSocket( const std::string& hostName, int servPort, bool blocking = true );
	
	TcpClientSocket( const NetworkAddress& server, bool blocking = true );
	
	TcpClientSocket( const TcpClientSocket& );
	
	TcpClientSocket& operator=( TcpClientSocket& other );

	TcpClientSocket( bool blocking=true );
	
	~TcpClientSocket();

	bool connect();

	void setServer( const std::string& server, int serverPort=-1, bool blocking=true );

	void setServer( struct sockaddr, bool blocking=true );

	void close();

	inline TcpConnection& getConn()
	{
		return _conn;
	};

private:
	
	TcpConnection _conn;
	struct sockaddr _addr;
	std::string _hostName;
	int _serverPort;
	bool _blocking;
	bool _bAddr;
};

#endif //_TCP_CLIENTSOCKET_
