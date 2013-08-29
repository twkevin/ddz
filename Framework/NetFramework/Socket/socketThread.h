#ifndef  _SOCKET_THREAD_
#define  _SOCKET_THREAD_

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


#include "raw_type.h"
#include "common_macro_define.h"
#include <vector>
#include "thread.h"
#include "mutex.h"
#include "TcpClientSocket.h"
#include "TcpConnection.h"
#include "buffStream.h"

class SocketThread;

enum
{
	CONNECT_CLOSE,
	CONNECT_RECV,
	CONNECT_QUIT,
	CONNECT_OPEN,
	CONNECT_FAIL,
	CONNECT_WAIT,
};

typedef void (*MsgCallBackFunc)(SocketThread*, int, void*);
typedef quarkxV2::qxUInt32 (*MsgReadFunc)(const quarkxV2::qxByte* szData, quarkxV2::qxUInt32 unSize);

class QX_DLL SocketThread : public quarkxV2::CQXThread
{
public:
	SocketThread();
	~SocketThread();
	
	static void* msgloop(void* args);

	void registerCallBack(MsgCallBackFunc func);
	void registerCallBack(MsgReadFunc func);
	void requestConnet(const std::string& strIp, quarkxV2::qxUInt32 Port);
	void requestClose();
	quarkxV2::qxBoolean run();

	void processMsg();
	void postMsg(quarkxV2::qxByte* buff, quarkxV2::qxUInt32 size);
	void sendHttpRequest(std::string url);
	quarkxV2::qxBoolean isLive() const;
	std::string getHostAddress();
	std::string getIP();
	unsigned int getPort();

	quarkxV2::qxInt32 static initSocket();
private:
	quarkxV2::qxBoolean connect(const std::string& strIp, quarkxV2::qxUInt32 Port);
	void close();

	void msgloop();
	void recvMsg();
	void sendMsg();

	TcpClientSocket* m_pSocket;
	TcpConnection* m_pConn;
	quarkxV2::qxBoolean m_bIsConneting;
	quarkxV2::qxBoolean m_bCrypto;
	std::string m_strIp;
	quarkxV2::qxUInt32 m_nPort;

	quarkxV2::CQXMutex m_SendLock;
	quarkxV2::CQXMutex m_RecvLock;

	quarkxV2::qxByte* m_SendBuff;
	quarkxV2::qxUInt32 m_SendBuffSize;
	quarkxV2::qxUInt32 m_SendBuffMaxSize;

	quarkxV2::qxByte m_key[1024];
	quarkxV2::qxByte m_keyRecvStart;
	quarkxV2::qxByte m_keySendStart;
	quarkxV2::qxUInt32 m_keyLength;

	unsigned int m_msgReceiveBuffSize;
	char* m_msgReceiveBuffBegin;
	char* m_msgReceiveBuffEnd;
	char* m_msgReceiveBuffValueBegin;
	char* m_msgReceiveBuffValueEnd;

	MsgCallBackFunc m_MsgRecvCallBackFunc;
	MsgReadFunc m_MsgReadCallBackFunc;
	std::vector<OutStream*> m_vecRecList;
	int m_CmdFlg;
}; 
#endif

