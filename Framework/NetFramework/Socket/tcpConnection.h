#ifndef  _TCP_CONNECTION_
#define  _TCP_CONNECTION_

#include <string>


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
#include <sys/uio.h>
#endif

#if defined WIN32
#define _WINSOCKAPI_
#include <Windows.h>
#include <WinSock2.h>
#ifndef socklen_t
typedef int socklen_t;
#endif
#endif

class TcpServerSocket;
class TcpClientSocket;

typedef struct sockaddr SA;
#define MAXLINE   256

class TcpConnection
{
public:
	TcpConnection( bool blocking = true )
	{
		_blocking = blocking;
		_connId = 0;
		useNum = NULL;
		_timeout = -1;
		_live = false;
		_connAddrLen = 0;
		_bThrowException = false;
	}
	
	TcpConnection( int connId, bool blocking = true )
	{
		_connId = connId;
		_live = true;
		_connAddrLen = 0;
		_blocking = blocking;
		_timeout = -1;
		_bThrowException = false;
		setState();
	}
	
	void setConnId( int connid )
	{
		_connId = connid;
		setState();
	}

	inline int getConnId() const
	{
		return _connId;
	}

	inline struct sockaddr_in getConnAddr() const
	{
		return _connAddr;
	}

	inline socklen_t getConnAddrLen() const
	{
		return _connAddrLen;
	}
	
	TcpConnection( const TcpConnection& other );

	virtual ~TcpConnection();
	
	TcpConnection& operator=( const TcpConnection& other );
	
	bool operator==( const TcpConnection& other )
	{
		return ( _connId == other._connId );
	}
	
	bool operator!=( const TcpConnection& other )
	{
		return ( _connId != other._connId );
	}
	
	int readLine( void* data, int maxlen, int timeout=-1 );
	
	/**Reads nchar from the connection.
	Returns 0 if timeout
	Returns -1 if connection is closed */
	int readData( void* data, int nchar, int &bytesRead, int timeout = -1 );


	int readn( void *data, int nchar, int timeout=-1 );

	int readIfHasData( void* data, int nchar, int& bytesRead, int timeout );
	
	/** Writes data to the connection
	Returns 0 if timeout
	Returns 1 if connection is closed **/
	int writeData( const void* data, int n, int timeout=-1 );
	
	int writeData( const std::string& data, int timeout=-1 );
	
	//Gets the connection description IP_ADDRESSS:Port
	std::string getDescription() const;
	
	///Gets the IP of the destination 
	std::string getIp() const;

	unsigned short getPort() const;
	
	inline bool isLive() const
	{
		return _live;
	}
	
	void close();
	int* useNum;					//该Connection被引用的次数
	
	///Check if data is ready to be read within given seconds and microseconds
	bool isReadReady( int mSeconds=-1 ) const;
	bool isWriteReady( int mSeconds=500 ) const;
	void setBlocking( bool block = true );
	void setTimeout( int timeout );
	void enableException( bool bThrowException=true );
	
private:
	int _timeout;
	void setState();
	friend class TcpServerSocket;
	friend class TcpClientSocket;
	int _connId;
	bool _live;
	socklen_t _connAddrLen;
	struct sockaddr_in _connAddr;
	bool _blocking;
	bool _bThrowException;
};


#endif //_TCP_CONNECTION_

