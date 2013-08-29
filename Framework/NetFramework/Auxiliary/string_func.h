#ifndef __QX_STRING_H__
#define __QX_STRING_H__

#include "common_macro_define.h"
#include "raw_type.h"
#include <string>
using namespace std;

NS_QX_BEGIN

class QX_DLL CQXString
{
public:
	CQXString();
	~CQXString();

	static qxString Init(qxChar* str, qxUInt32 maxSize);
	static qxString Format(qxChar* strDes, qxUInt32 maxSize, qxString strFormat, ...);
	static qxString Format(qxChar* strDes, qxUInt32 maxSize, qxString strFormat, va_list arg_list);
	static qxString Copy(qxChar* strDes, qxUInt32 maxSize, qxString strSrc);

	static std::string& Filter(std::string& s, qxString strFilter);
	static std::string&	Replace(std::string& src, const std::string& tar, const std::string& str);

	static std::string	StringFromInt(qxInt32 val);
	static qxInt32		StringToInt(qxString s);

	static std::string	StringFromFloat(qxFloat32 val);
	static qxFloat32	StringToFloat(qxString s);

	static qxBoolean    IsLeadofMBSB(qxString mbstr, qxUInt32 nOffset);
	static qxInt32		Code_Convert (qxString fromCode, qxString toCode, qxChar *inbuf, size_t nInLen, qxChar *outbuf, size_t nOutLen);

	//static std::wstring   str2wstr(const std::string &str);///*string2wstring*/
	//static std::string    wstr2str(const std::wstring &wstr);///*wstring2string*/

private:
};




std::string QX_DLL  & StrFilter(std::string& s, qxString strFilter)		;//	CQXString::Filter(s, f)
std::string  QX_DLL  &  StrReplace(std::string& src, const std::string& tar, const std::string& str)	;//CQXString::Replace(src, t, s)
qxInt32    QX_DLL StrToInt(qxString s);//				CQXString::StringToInt(s)
std::string  QX_DLL  StrFromInt(qxInt32 val)	;//		CQXString::StringFromInt(val)

#define LeadofMBSB(s, o)	CQXString::IsLeadofMBSB(s, o)
#define code_convert1(fromCode, toCode, inbuf, nInLen, outbuf, nOutLen) CQXString::Code_Convert((fromCode), (toCode), (inbuf), (nInLen), (outbuf), (nOutLen))

// std::wstring QX_DLL  char2wstr(const char* str);
// std::wstring QX_DLL  str2wstr(const std::string &str);///*string2wstring*/
// std::string  QX_DLL  wstr2str(const std::wstring &wstr);///*wstring2string*/

qxString QX_DLL StrFormat(qxChar* strDes, qxUInt32 maxSize, qxString strFormat, ...);
qxString QX_DLL StrCopy(qxChar* strDes, qxUInt32 maxSize, qxString strSrc);

#if QX_WIN32
#define qxstricmp(a, b, l) stricmp(a, b)
#elif QX_IOS
#define qxstricmp(a, b, l) strncasecmp(a, b, l)
#endif

NS_QX_END

#endif //__QX_STRING_H__

