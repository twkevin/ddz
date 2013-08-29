

#if QX_ANDROID
#include <cstdint>
#include <sys/types.h>
#endif

#include "socketThread.h"
#include "log.h"
#include <assert.h>
using namespace quarkxV2;

#if DEBUG
#define LOG_MSG
#endif
#define  _MAX_MSGSIZE 2048

SocketThread::SocketThread()
: m_pSocket(new TcpClientSocket())
, m_pConn(QX_NULL_POINT)
, m_bIsConneting(false)
, m_bCrypto(false)
, m_SendBuffMaxSize(1024)
, m_SendBuffSize(0)
, m_msgReceiveBuffSize(2048)
, m_MsgRecvCallBackFunc(QX_NULL_POINT)
, m_CmdFlg(CONNECT_WAIT)
{
	m_SendBuff = new quarkxV2::qxByte[m_SendBuffMaxSize];
	memset(m_key, 0, sizeof(m_key));

	m_msgReceiveBuffBegin = new char[m_msgReceiveBuffSize];
	m_msgReceiveBuffValueEnd = m_msgReceiveBuffValueBegin = m_msgReceiveBuffBegin;
	m_msgReceiveBuffEnd = &m_msgReceiveBuffBegin[m_msgReceiveBuffSize];
}

SocketThread::~SocketThread()
{
	if (m_pSocket != NULL)
	{
		m_pSocket->close();
		QX_SAFE_DELETE(m_pSocket);
	}
}

quarkxV2::qxBoolean SocketThread::connect(const std::string& strIp, quarkxV2::qxUInt32 Port)
{
	this->close();
	
	m_strIp = strIp;
	m_nPort = Port;
	m_pSocket->setServer(strIp, Port);
	m_bIsConneting = m_pSocket->connect();
	if (m_bIsConneting)
	{
		m_pConn = &m_pSocket->getConn();
		m_pConn->enableException();
	}
	else
	{
#ifdef LOG_ENABLE
		quarkxV2::qxLog(quarkxV2::err, "fail to connet server %s:%u", strIp.c_str(), Port);
#endif 
	}
	return m_bIsConneting;
}

void SocketThread::close()
{
	if (m_bIsConneting)
	{
		m_bIsConneting = false;
		usleep(30000);
		if (QX_VALID_POINT(m_pSocket))
		{
			m_pSocket->close();
		}
	}
}

void SocketThread::msgloop()
{
	while(!this->isShutdown())
	{
		this->recvMsg();
		this->sendMsg();
		usleep(10000);

		if (m_CmdFlg == CONNECT_OPEN)
		{
			if (m_bIsConneting)
			{
				close();
			}

			bool ret = this->connect(m_strIp, m_nPort);
			m_CmdFlg = ret ? CONNECT_RECV : CONNECT_FAIL;
		}
		else if (m_CmdFlg == CONNECT_CLOSE)
		{
			this->close();
			m_CmdFlg = CONNECT_WAIT;
		}
	}
}

void* SocketThread::msgloop(void* args)
{
	if (QX_VALID_POINT(args))
	{
		static_cast<SocketThread*>(args)->msgloop();
	}
	return 0;	
}

quarkxV2::qxBoolean SocketThread::run()
{
	return this->spawn(SocketThread::msgloop, this);
}

void SocketThread::recvMsg()
{
	if (!m_bIsConneting)
	{
		return;
	}

	if (QX_ZERO_POINT(m_pConn))
	{
		return;
	}
	unsigned char buff[_MAX_MSGSIZE];
	int nHaveRead = 0;
	memset(buff, 0, _MAX_MSGSIZE);
	if (m_pConn->readData(buff, _MAX_MSGSIZE, nHaveRead, 10)<0)
	{
#ifdef LOG_ENABLE
		quarkxV2::qxLog(quarkxV2::err, "connect error");
#endif 	
		//m_bIsConneting = false;
		m_CmdFlg = CONNECT_CLOSE;
		return;
	}
	if (nHaveRead <= 0 || nHaveRead > _MAX_MSGSIZE)
	{
		if (nHaveRead != 0)
		{
#ifdef LOG_ENABLE
			quarkxV2::qxLog(quarkxV2::err, "receive data occur error");
#endif
		}
		return;
	}
#ifdef LOG_ENABLE
	quarkxV2::qxLog(quarkxV2::info, "read buff %u", nHaveRead);
#endif

	if (m_msgReceiveBuffEnd - m_msgReceiveBuffValueEnd < nHaveRead)
	{
		int nMsgRemain = m_msgReceiveBuffValueEnd-m_msgReceiveBuffValueBegin;
		memcpy(m_msgReceiveBuffBegin, m_msgReceiveBuffValueBegin, nMsgRemain);
		m_msgReceiveBuffValueEnd = m_msgReceiveBuffBegin+nMsgRemain;
		m_msgReceiveBuffValueBegin = m_msgReceiveBuffBegin;
#ifdef LOG_MSG
		quarkxV2::qxLog(quarkxV2::info, "Recv buff rearrange Buff 0x%x - 0x%x(size:%u) cur:0x%x - 0x%x(size:%u)"
			, m_msgReceiveBuffBegin, m_msgReceiveBuffEnd, m_msgReceiveBuffEnd - m_msgReceiveBuffBegin
			, m_msgReceiveBuffValueBegin, m_msgReceiveBuffValueEnd, m_msgReceiveBuffValueEnd - m_msgReceiveBuffValueBegin);
#endif 

		if (m_msgReceiveBuffEnd - m_msgReceiveBuffValueEnd < nHaveRead)
		{
			char* bufftemp = m_msgReceiveBuffBegin;
			m_msgReceiveBuffSize *= 2;
			m_msgReceiveBuffBegin = new char[m_msgReceiveBuffSize];
			memcpy(m_msgReceiveBuffBegin, m_msgReceiveBuffValueBegin, nMsgRemain);
			m_msgReceiveBuffValueEnd = m_msgReceiveBuffBegin+nMsgRemain;
			m_msgReceiveBuffValueBegin = m_msgReceiveBuffBegin;
			m_msgReceiveBuffEnd = &m_msgReceiveBuffBegin[m_msgReceiveBuffSize];
			delete[] bufftemp;
#ifdef LOG_MSG
			quarkxV2::qxLog(quarkxV2::info, "Recv buff realloc Buff 0x%x - 0x%x(size:%u) cur:0x%x - 0x%x(size:%u)"
				, m_msgReceiveBuffBegin, m_msgReceiveBuffEnd, m_msgReceiveBuffEnd - m_msgReceiveBuffBegin
				, m_msgReceiveBuffValueBegin, m_msgReceiveBuffValueEnd, m_msgReceiveBuffValueEnd - m_msgReceiveBuffValueBegin);
#endif 
		}		
	}
	memcpy(m_msgReceiveBuffValueEnd, buff, nHaveRead);
	m_msgReceiveBuffValueEnd+=nHaveRead;

#ifdef LOG_MSG
	quarkxV2::qxLog(quarkxV2::info, "Recv buff %d Buff 0x%x - 0x%x(size:%u) cur:0x%x - 0x%x(size:%u)", nHaveRead
		, m_msgReceiveBuffBegin, m_msgReceiveBuffEnd, m_msgReceiveBuffEnd - m_msgReceiveBuffBegin
		, m_msgReceiveBuffValueBegin, m_msgReceiveBuffValueEnd, m_msgReceiveBuffValueEnd - m_msgReceiveBuffValueBegin);
#endif 

	while (true)
	{
		if (m_msgReceiveBuffValueBegin == m_msgReceiveBuffValueEnd)
		{
#ifdef LOG_MSG
			quarkxV2::qxLog(quarkxV2::info, "Recv buff Empty Buff 0x%x - 0x%x cur:0x%x", m_msgReceiveBuffBegin, m_msgReceiveBuffEnd, m_msgReceiveBuffValueBegin);
#endif 
			break;
		}
		unsigned int nBuffSize = m_msgReceiveBuffValueEnd - m_msgReceiveBuffValueBegin;

		if (nBuffSize < 4)
		{
#ifdef LOG_MSG
			quarkxV2::qxLog(quarkxV2::info, "Recv buff header(%u) is not enough", nBuffSize);
#endif 
			break;
		}

		if (m_MsgReadCallBackFunc != NULL)
		{
			unsigned int unReadCount = (*m_MsgReadCallBackFunc)((quarkxV2::qxByte*)m_msgReceiveBuffValueBegin, nBuffSize);

			if (0 == unReadCount)
			{
				m_msgReceiveBuffValueBegin += nBuffSize;
			}
			else
			{
				m_msgReceiveBuffValueBegin += QX_MIN(unReadCount, nBuffSize);
			}			
		}
	}
}

void SocketThread::sendMsg()
{
	if (!m_bIsConneting)
	{
		return;
	}

	if (m_CmdFlg != CONNECT_RECV)
	{
		// 正常连接状态才可发送消息
		return;
	}

	if (QX_ZERO_POINT(m_pConn))
	{
		return;
	}

	if (m_SendBuffSize > 0)
	{
		m_SendLock.lock();
		m_pConn->writeData(m_SendBuff, m_SendBuffSize);
		m_SendBuffSize = 0;
		m_SendLock.unlock();
	}
}

void SocketThread::postMsg(quarkxV2::qxByte* buff, quarkxV2::qxUInt32 size)
{
	m_SendLock.lock();
	if (QX_VALID_POINT(buff))
	{
		if (m_SendBuffMaxSize - m_SendBuffSize < size)
		{
			m_SendBuffMaxSize *= 2;
			quarkxV2::qxByte* pBuff = new quarkxV2::qxByte[m_SendBuffMaxSize];
			memcpy(pBuff, m_SendBuff, m_SendBuffSize);
			QX_SAFE_DELETE_ARRAY(m_SendBuff);
			m_SendBuff = pBuff;
		}

		if (m_SendBuffSize + size < m_SendBuffMaxSize)
		{
#ifdef LOG_ENABLE
			quarkxV2::qxLog(quarkxV2::info, "Send buff %u", size);
#endif
			memcpy(m_SendBuff+m_SendBuffSize, buff, size);
			m_SendBuffSize += size;
		}
		else
		{
#ifdef LOG_ENABLE
			quarkxV2::qxLog(quarkxV2::err, "Send buff error");
#endif
		}
	}
	m_SendLock.unlock();
}

void SocketThread::sendHttpRequest(std::string url)
{
	//if (pszUrlParam == NULL)
	//	return false;
	//	tq::LogSave("HttpSend","UrlParam:%s", pszUrlParam);
	//m_idUin = idUin;
	//m_iAct = iAct;

	char szTemBuffer[1024];
	std::string strSend;

	strSend += "GET ";
	//send(m_sock, m_httpServe.Get91Param(), strlen(m_httpServe.Get91Param()), 0);
	//send(m_sock, pszUrlParam, strlen(pszUrlParam), 0);
	strSend += url;

	sprintf(szTemBuffer," HTTP/1.0\r\n");
	strSend += szTemBuffer;

	sprintf(szTemBuffer,
		"Accept: image/gif, image/x-xbitmap,"
		" image/jpeg, image/pjpeg, application/vnd.ms-excel,"
		" application/msword, application/vnd.ms-powerpoint,"
		" */*\r\n");
	strSend += szTemBuffer;

	sprintf(szTemBuffer,"Accept-Language: en-us\r\n");
	strSend += szTemBuffer;

	sprintf(szTemBuffer,"Accept-Encoding: plain, default\r\n");
	strSend += szTemBuffer;

	sprintf(szTemBuffer,"User-Agent: Neeao/4.0\r\n");
	strSend += szTemBuffer;

	strSend += "Host: ";

	strSend += m_strIp;

	strSend += "\r\n";
	strSend += "\r\n";

	if (QX_VALID_POINT(m_pConn))
		m_pConn->writeData((quarkxV2::qxByte*)strSend.c_str(), strSend.size());
}

quarkxV2::qxInt32 SocketThread::initSocket()
{
#if QX_WIN32
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0)
	{
		return FALSE;
	}
	return TRUE;
#else
	return false;
#endif
}

void SocketThread::registerCallBack(MsgCallBackFunc func)
{
	m_MsgRecvCallBackFunc = func;
}

void SocketThread::registerCallBack(MsgReadFunc func)
{
	m_MsgReadCallBackFunc = func;
}

void SocketThread::processMsg()
{
	if (m_CmdFlg == CONNECT_RECV)
	{
		m_RecvLock.lock();
		std::vector<OutStream*> vecRecList = m_vecRecList;
		m_vecRecList.clear();
		m_RecvLock.unlock();

		if (QX_VALID_POINT(m_MsgRecvCallBackFunc))
		{
			std::vector< OutStream* >::iterator iterIndex = vecRecList.begin();
			for (; iterIndex != vecRecList.end(); iterIndex++)
			{			
				if (QX_VALID_POINT(*iterIndex))
				{
					(*m_MsgRecvCallBackFunc)(this, CONNECT_RECV, (*iterIndex));
				}
				QX_SAFE_DELETE(*iterIndex);
			}
		}
	}
	else if (m_CmdFlg == CONNECT_CLOSE 
		|| m_CmdFlg == CONNECT_FAIL
		|| m_CmdFlg == CONNECT_QUIT)
	{
		(*m_MsgRecvCallBackFunc)(this, m_CmdFlg, NULL);
		m_CmdFlg = CONNECT_WAIT;
	}
}

quarkxV2::qxBoolean SocketThread::isLive() const 
{
	return m_bIsConneting;
}

std::string SocketThread::getHostAddress()
{
	return m_strIp;
}

std::string SocketThread::getIP()
{
	return m_pConn ? m_pConn->getIp() : "";
}

unsigned int SocketThread::getPort()
{
	return m_nPort;
}

void SocketThread::requestConnet(const std::string& strIp, quarkxV2::qxUInt32 Port)
{
	m_CmdFlg = CONNECT_OPEN;
	m_strIp = strIp;
	m_nPort = Port;

	m_msgReceiveBuffValueEnd = m_msgReceiveBuffBegin;
	m_msgReceiveBuffValueBegin = m_msgReceiveBuffBegin;
	m_msgReceiveBuffEnd = &m_msgReceiveBuffBegin[m_msgReceiveBuffSize];

	m_SendBuffSize = 0;
}

void SocketThread::requestClose()
{
	m_CmdFlg = CONNECT_CLOSE;
}
 