#include "string_func.h"
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <errno.h>
#include "log.h"
#if QX_WIN32
#include "Win32_setting.h"
#include <mbstring.h>
#include "iconv.h"
#elif QX_IOS || QX_ANDROID
#include <iconv.h>
#include<stdlib.h>
#endif

NS_QX_BEGIN

CQXString::CQXString()
{

}

CQXString::~CQXString()
{

}

qxString CQXString::Init(qxChar* str, qxUInt32 maxSize)
{
	memset(str, 0, maxSize);
	return str;
}

qxString CQXString::Format(qxChar* strDes, qxUInt32 maxSize, qxString strFormat, ...)
{
	va_list ap;
	va_start(ap, strFormat);
	qxString ret = CQXString::Format(strDes, maxSize, strFormat, ap);
	va_end(ap);
	return ret;
}

qxString CQXString::Format(qxChar* strDes, qxUInt32 maxSize, qxString strFormat, va_list arg_list)
{
	vsnprintf(strDes, maxSize-1, strFormat, arg_list);
	strDes[maxSize-1]=0;
	return strDes;
}

qxString CQXString::Copy(qxChar* strDes, qxUInt32 maxSize, qxString strSrc)
{
	strDes[maxSize-1]=0;
	memcpy(strDes, strSrc, maxSize-1);
	return strDes;
}


std::string& CQXString::Filter(std::string& s, qxString strFilter) 
{
	unsigned int nBegin = s.find_first_not_of(strFilter);

	if (std::string::npos == nBegin)
	{
		s = "";
		return s;
	}

	int nEnd = s.find_last_not_of(strFilter);
	s = s.substr(nBegin, nEnd-nBegin+1);
	return s;
}

std::string& CQXString::Replace(std::string& src, const std::string& tar, const std::string& str)
{
	qxUInt32 p = src.find(tar);
	while (p != std::string::npos) 
	{
		src.replace(p, tar.size(), str);
		p = src.find(tar);
	}
	return src;
}

std::string CQXString::StringFromInt(qxInt32 val)
{
	std::string str;
	int sign = val,i = 0;
	qxChar temp[11];

	if(sign<0)
	{
		val = -val;
	};

	do
	{
		temp[i] = val%10+'0';
		val/=10;
		i++;
	}while(val>0);

	if(sign<0)
	{
		temp[i++] = '-';
	}
	temp[i] = '\0';
	i--;

	while(i>=0)
	{
		str  += temp[i];
		i--;
	}
	return str;
}


int CQXString::StringToInt(qxString s)
{
	qxInt32 i = 0,sum = 0,sign;
	while(' '==s[i]||'\t'==s[i])
	{
		i++;
	}


	sign = ('-'==s[i])?-1:1;
	if('-'==s[i]||'+'==s[i])
	{
		i++;
	}

	while(s[i]!='\0')
	{
		sum = s[i]-'0'+sum*10;
		i++;
	}

	return sign*sum;

}

std::string	CQXString::StringFromFloat(qxFloat32 val)
{
	std::stringstream strStream;                                                            
	std::cout.setf(std::ios::fixed);
	strStream<<val;       
	return strStream.str(); 
}

qxFloat32 CQXString::StringToFloat(qxString s)
{
	std::stringstream strStream(s);                                             
	qxFloat32  val; 
	strStream>>val;     
	return val; 
}

qxBoolean CQXString::IsLeadofMBSB(qxString mbstr, qxUInt32 nOffset)
{
#if QX_WIN32	
	const unsigned char* pstr = (const unsigned char*)mbstr;
	return 1==_mbsbtype(pstr, nOffset);
#elif QX_IOS || QX_ANDROID
	unsigned char c = mbstr[nOffset];
	return c >= 0x81 && c <= 0xfe;
#endif	
}

qxInt32 CQXString::Code_Convert (qxString fromCode, qxString toCode, qxChar *inbuf, size_t nInLen, qxChar *outbuf, size_t nOutLen)
{
	iconv_t cd;
	qxChar **in = &inbuf;
	qxChar **out = &outbuf;
	qxChar *old;
	old = outbuf;
	
	cd = iconv_open(toCode, fromCode);
	if (0 == cd)
		return -1;
	
	memset(outbuf, 0, nOutLen);
#if QX_IOS || QX_ANDROID
	if (-1 == iconv(cd, in, &nInLen, out, &nOutLen)) 
		return -1;
#else
	if (-1 == iconv(cd, (char**)in, &nInLen, out, &nOutLen))
	{
		QXLOGW("failed to convert %s from %s to %s", inbuf, fromCode, toCode);
		return -1;
	}
#endif
	
	iconv_close(cd);
	return outbuf - old;
}

qxString StrFormat(qxChar* strDes, qxUInt32 maxSize, qxString strFormat, ...)
{
	va_list ap;
	va_start(ap, strFormat);
	qxString ret = CQXString::Format(strDes, maxSize, strFormat, ap);
	va_end(ap);
	return ret;
}

std::string  &  StrFilter(std::string& s, qxString strFilter)		//	CQXString::Filter(s, f)
{
		return  CQXString::Filter(s, strFilter);
}
std::string&    StrReplace(std::string& src, const std::string& tar, const std::string& str)	//CQXString::Replace(src, t, s)
{
		return  CQXString::Replace(src, tar, str);
}
qxInt32     StrToInt(qxString s)//				CQXString::StringToInt(s)
{
	return CQXString::StringToInt(s);
}
std::string    StrFromInt(qxInt32 val)	//		CQXString::StringFromInt(val)
{
		return CQXString::StringFromInt(val);
}

// wstring   char2wstr(const char* str)
// {
// 			std::string strTest = str;
// 			return str2wstr(strTest);
// }
// 
// 
// std::wstring   str2wstr(const std::string &str)///*string2wstring*/
// {
// 	return 	CQXString::str2wstr(str);
// }
// std::string      wstr2str(const std::wstring &wstr)///*wstring2string*/
// {      
// 	std::string  str = CQXString::wstr2str(wstr);
// 		return 	str;
// }

qxString StrCopy(qxChar* strDes, qxUInt32 maxSize, qxString strSrc)
{
	return CQXString::Copy(strDes, maxSize, strSrc);
}

// std::wstring   CQXString::str2wstr(const std::string &str)
// {
// 	setlocale(LC_ALL, "chs");
// 	const char* _Source = str.c_str();
// 	size_t _Dsize = str.size() + 1;
// 	wchar_t *_Dest = new wchar_t[_Dsize];
// 	wmemset(_Dest, 0, _Dsize);
// 	mbstowcs(_Dest,_Source,_Dsize);
// 	std::wstring result = _Dest;
// 	delete []_Dest;
// 
// 	setlocale(LC_ALL, "C");
// 
// 	return result;
// }

// std::string      CQXString::wstr2str(const std::wstring &wstr)
// {
// 	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
// 	setlocale(LC_ALL, "chs");
// 
// 	const wchar_t* _Source = wstr.c_str();
// 	size_t _Dsize = 2 * wstr.size() + 1;
// 	char *_Dest = new char[_Dsize];
// 	memset(_Dest,0,_Dsize);
// 	wcstombs(_Dest,_Source,_Dsize);
// 	std::string result = _Dest;
// 	delete []_Dest;
// 
// 	setlocale(LC_ALL, curLocale.c_str());
// 
// 	return result;
// 
// }

NS_QX_END