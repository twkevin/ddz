#ifndef __BUFFSTREAM_H__
#define __BUFFSTREAM_H__

#define _NET_SEQUENCE 1

#pragma once
#include <string>
#include "common_macro_define.h"
#include "string_func.h"
#include <vector>
#include <iterator>

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料

#if QX_WIN32
#include <windows.h>
#if _NET_SEQUENCE
#define _WINSOCKAPI_
#include <WinSock2.h>
#endif
#elif QX_IOS || QX_ANDROID
typedef long long __int64;
typedef unsigned char BYTE; 
typedef unsigned int  DWORD;
#endif

#define MAX_STRING_SIZE 4096

#define	byte	BYTE
using namespace std;


typedef std::vector<BYTE> ByteSeq;

#define BUFFTOBYTESEQ(name, Buff, Size) ByteSeq name;copy((Buff), (Buff)+(Size), (back_inserter(name)));

class InvalidStringException : public std::exception
{	
public:
	virtual const char *what() const throw()
	{	
		// return pointer to message string
		return "invalid string length";
	}
};

class OutOfBoundException : public std::exception
{
public:
	virtual const char *what() const throw()
	{	
		// return pointer to message string
		return "read exceeds the size of the buf";
	}
};

class Stream
{
public:
	ByteSeq GetByteStream() const
	{
		return _stream;
	}
	virtual size_t GetSize() const
	{
		return _pointer;
	}
protected:
	ByteSeq		_stream;
	size_t		_pointer;
};

class InStream : public Stream
{
public:
	InStream(int initsize = 32)
	{
		_stream.reserve(initsize);
		_pointer = 0;
	}

	inline void __write(void* buf, size_t size)
	{
		BYTE* b = (BYTE*)buf;
		while(size>0)
		{
			_stream.push_back(b[0]);
			_pointer++;
			size--;
			b++;
		}
	}

	inline void writeString(const char* pszData, int nLen = -1)
	{
		__write((void*)pszData, nLen == -1 ? strlen(pszData) : nLen);
	}

	inline void writeBuff(const char* pszData, int nLen)
	{
		__write((void*)pszData, nLen);
	}

	inline void writeBuff(const unsigned char* pszData, int nLen)
	{
		__write((void*)pszData, nLen);
	}

	inline void writeInt(int nData)
	{
#if _NET_SEQUENCE
		u_long ulv = htonl(nData);
		__write(&ulv, sizeof(int));
#else
		__write(&nData, sizeof(int));
#endif
	}

	inline void writeBoolean(bool bData)
	{
		__write(&bData, sizeof(bool));
	}
};

inline InStream& operator << (InStream& is, int v)
{
#if _NET_SEQUENCE
	u_long ulv = htonl(v);
	is.__write((void*)&ulv, sizeof(v));
#else
	is.__write((void*)&v, sizeof(v));
#endif
	return is;
}

inline InStream& operator << (InStream& is, unsigned int v)
{
#if _NET_SEQUENCE
	u_long ulv = htonl(v);
	is.__write((void*)&ulv, sizeof(v));
#else
	is.__write((void*)&v, sizeof(v));
#endif
	return is;
}

inline InStream& operator << (InStream& is, long v)
{
#if _NET_SEQUENCE
	u_long ulv = htonl(v);
	is.__write((void*)&ulv, sizeof(v));
#else
	is.__write((void*)&v, sizeof(v));
#endif
	return is;
}
inline InStream& operator << (InStream& is, short v)
{
#if _NET_SEQUENCE
	u_short ulv = htons(v);
	is.__write((void*)&ulv, sizeof(v));
#else
	is.__write((void*)&v, sizeof(v));
#endif
	return is;
}
inline InStream& operator << (InStream& is, unsigned short v)
{
#if _NET_SEQUENCE
	u_short ulv = htons(v);
	is.__write((void*)&ulv, sizeof(v));
#else
	is.__write((void*)&v, sizeof(v));
#endif
	return is;
}
inline InStream& operator << (InStream& is, bool v)
{
	is.__write((void*)&v, sizeof(v));
	return is;
}
inline InStream& operator << (InStream& is, float v)
{
	is.__write((void*)&v, sizeof(v));
	return is;
}
inline InStream& operator << (InStream& is, double v)
{
	is.__write((void*)&v, sizeof(v));
	return is;
}
inline InStream& operator << (InStream& is, __int64 v)
{
	is.__write((void*)&v, sizeof(v));
	return is;
}
inline InStream& operator << (InStream& is, char v)
{
	is.__write((void*)&v, sizeof(v));
	return is;
}
inline InStream& operator << (InStream& is, byte v)
{
	is.__write((void*)&v, sizeof(v));
	return is;
}
	
// inline InStream& operator << (InStream& is, const std::string& v)
// {
// 	int s = (int)v.size();
// 	if (s > MAX_STRING_SIZE-1)
// 	{
// 		throw InvalidStringException();
// 	}
// 	if (s == 0)
// 	{
// 		is.__write(&s, sizeof(s));
// 		return is;
// 	}
// 	//write in utf8 format;
// 	int l = 0;
// 	const char* buf = v.c_str();
// 	char szUTF8[MAX_STRING_SIZE] = {0};
// 	size_t nUTF8Len = MAX_STRING_SIZE;
// 	size_t nSrcLen = v.length();
// 	l = quarkxV2::CQXString::Code_Convert("GB18030", "UTF-8", (char*)buf, nSrcLen, szUTF8, nUTF8Len);
// 	if (l < 0)
// 	{
// 		throw InvalidStringException();
// 	}
// 
// 	is.__write(&l, sizeof(l));
// 	is.__write((void*)szUTF8, l);
// 	return is;
// }
// inline InStream& operator << (InStream& is, const std::wstring& v)
// {
// 	int s = (int)v.size();
// 	if (s == 0)
// 	{
// 		is.__write(&s, sizeof(s));
// 		return is;
// 	}
// 	if (s > MAX_STRING_SIZE / 2)
// 	{
// 		throw InvalidStringException();
// 	}
// 	//write in utf8 format;
// 	int l = 0;
// 	string str  = quarkxV2::wstr2str(v);
// 	const char* buf = str.c_str();
// 	char szUTF8[MAX_STRING_SIZE] = {0};
// 	size_t nUTF8Len = MAX_STRING_SIZE;
// 	size_t nSrcLen = str.length();
// 	l = quarkxV2::CQXString::Code_Convert("GB18030", "UTF-8", (char*)buf, nSrcLen, szUTF8, nUTF8Len);
// 	if (l < 0)
// 	{
// 		throw InvalidStringException();
// 	}
// 
// 	is.__write(&l, sizeof(l));
// 	is.__write((void*)szUTF8, l);
// 	return is;
// }
inline InStream& operator << (InStream& is, const InStream& v)
{
	is.__write(&v.GetByteStream().at(0), v.GetSize());
	return is;
}

class OutStream : public Stream
{
public:
	OutStream(const ByteSeq& stream)
	{
		_stream = stream;
		_pointer = 0;
		_size = _stream.size();
	}

	inline void __read(void* buf, size_t size)
	{
		if (_pointer + size > _size)
		{
			throw OutOfBoundException();
		}

		void* srcbuf = (void*)(&_stream[_pointer]);
		memcpy(buf, srcbuf, size);
		_pointer += size;
	}
	size_t		_size;

	inline std::string readString(int nLen = -1)
	{
		int nStringSize = (nLen == -1 ? strlen((char*)&_stream[_pointer]) : nLen)+1;
		char* strVal = new char[nStringSize];
		memset(strVal, 0, nStringSize);
		memcpy(strVal, &_stream[_pointer], nStringSize-1);
		string strRet = strVal;
		delete[] strVal;
		_pointer += nLen == -1 ? nStringSize : nLen;
		return strRet;
	}

	inline int readInt()
	{
		int nData;
		__read(&nData, sizeof(int));
#if _NET_SEQUENCE
		nData = ntohl(nData);
#endif
		return nData;
	}

	inline bool readBoolean()
	{
		bool bData;
		__read(&bData, sizeof(bool));
		return bData;
	}

	inline void readBuff(unsigned char* buff, int nSize)
	{
		__read(buff, nSize);
	}

	inline void readBuff(char* buff, int nSize)
	{
		__read(buff, nSize);
	}
};

inline OutStream& operator >> (OutStream& os, int& v)
{
	os.__read((void*)&v, sizeof(v));
#if _NET_SEQUENCE
	v = ntohl(v);
#endif
	return os;
}
inline OutStream& operator >> (OutStream& os, unsigned int& v)
{
	os.__read((void*)&v, sizeof(v));
#if _NET_SEQUENCE
	v = ntohl(v);
#endif
	return os;
}
inline OutStream& operator >> (OutStream& os, long& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}
inline OutStream& operator >> (OutStream& os, short& v)
{
	os.__read((void*)&v, sizeof(v));
#if _NET_SEQUENCE
	v = ntohs(v);
#endif
	return os;
}
inline OutStream& operator >> (OutStream& os, unsigned short& v)
{
	os.__read((void*)&v, sizeof(v));
#if _NET_SEQUENCE
	v = ntohs(v);
#endif
	return os;
}
inline OutStream& operator >> (OutStream& os, bool& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}
inline OutStream& operator >> (OutStream& os, byte& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}
inline OutStream& operator >> (OutStream& os, char& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}
inline OutStream& operator >> (OutStream& os, float& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}
inline OutStream& operator >> (OutStream& os, double& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}
inline OutStream& operator >> (OutStream& os, __int64& v)
{
	os.__read((void*)&v, sizeof(v));
	return os;
}

// inline OutStream& operator >> (OutStream& os, std::string& v)
// {
// 	int l = 0;
// 	os.__read(&l, sizeof(l));
// 	if (l == 0)
// 	{
// 		v = string("");
// 		return os;
// 	}
// 	if (l > MAX_STRING_SIZE)
// 	{
// 		throw InvalidStringException();
// 	}
// 	char buf[MAX_STRING_SIZE] = {'\0'};
// 	os.__read((void*)buf, l);
// 	//read from utf8 format;
// 	char szDBCS[MAX_STRING_SIZE] = {0};
// 	size_t nDBCSLen = MAX_STRING_SIZE;
// 	size_t nSrcLen = strlen(buf);
// 	int ret = quarkxV2::CQXString::Code_Convert("UTF-8", "GB18030", (char*)buf, nSrcLen, szDBCS, nDBCSLen);
// 	if (ret < 0)
// 	{
// 		throw InvalidStringException();
// 	}
// 	v = string(szDBCS);
// 	return os;
// }

// inline OutStream& operator >> (OutStream& os, std::wstring& v)
// {
// 	int l = 0;
// 	os.__read(&l, sizeof(l));
// 	if (l == 0)
// 	{
// 		v = wstring(L"");
// 		return os;
// 	}
// 	if (l > MAX_STRING_SIZE)
// 	{
// 		char *buf = new char[l];
// 		memset(buf, 0, l);
// 		os.__read((void*)buf, l);
// 
// 		char *szDBCS = new char[l*2];
// 		size_t nDBCSLen = l*2;
// 		size_t nSrcLen = l;
// 		int ret = quarkxV2::CQXString::Code_Convert("UTF-8", "GB18030", (char*)buf, nSrcLen, szDBCS, nDBCSLen);
// 		v = quarkxV2::char2wstr(szDBCS);
// 		delete []buf;
// 		delete []szDBCS;
// 		if (ret < 0)
// 		{
// 			throw InvalidStringException();
// 		}
// 		return os;
// 		//throw InvalidStringException();
// 	}
// 	char buf[MAX_STRING_SIZE] = {'\0'};
// 	os.__read((void*)buf, l);
// 
// 	//read from utf8 format;
// 	char szDBCS[MAX_STRING_SIZE] = {0};
// 	size_t nDBCSLen = MAX_STRING_SIZE;
// 	size_t nSrcLen = strlen(buf);
// 	int ret = quarkxV2::CQXString::Code_Convert("UTF-8", "GB18030", (char*)buf, nSrcLen, szDBCS, nDBCSLen);
// 	if (ret < 0)
// 	{
// 		throw InvalidStringException();
// 	}
// 	v = quarkxV2::char2wstr(szDBCS);
// 	return os;
// }

#endif  //__BUFFSTREAM_H__