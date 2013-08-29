// MyString.h: interface for the CMyString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTRING_H__04538BAC_0EF7_46EB_AAF7_9201677B5D10__INCLUDED_)
#define AFX_MYSTRING_H__04538BAC_0EF7_46EB_AAF7_9201677B5D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include <string>

// 这里要求后续使用CMyString格式化后的字符串长度不能超过4096-1
class CMyString : public std::string  
{
public:
	CMyString();
//	CMyString(const char* pstr)		{ if (pstr) this->assign(pstr); }
	CMyString(const char* fmt, ...);
	virtual ~CMyString();
	
	CMyString& operator = (const std::string& str)	{ this->assign(str); return *this; }
	CMyString& operator = (const char* pstr)		{ if (pstr) this->assign(pstr); return *this; }
	CMyString& operator = (int i)			{ format("%d", i); return *this; }
	CMyString& operator = (unsigned int u)	{ format("%u", u); return *this; }
	CMyString& operator = (float f)			{ format("%f", f); return *this; }
	CMyString& operator = (double d)		{ format("%f", d); return *this; }

	const char operator [] (int nPos)	{ return this->at(nPos); }

	bool operator == (const std::string& str)	{ return (0 == this->compare(str)); }
	bool operator != (const std::string& str)	{ return (0 != this->compare(str)); }

	bool operator == (const char* pstr)			
	{ 
		if (pstr) 
			return (0 == this->compare(pstr)); 
		else
			return false;
	}
	bool operator != (const char* pstr)			
	{ 
		return !(operator == (pstr));
	}

	operator const char*() const	{ return this->c_str(); }

	operator char	() const	{ return atoi(this->c_str()); }
	operator unsigned char	() const	{ return atoi(this->c_str()); }

	operator int	() const	{ return atoi(this->c_str()); }
	operator unsigned int	() const	{ return atoi(this->c_str()); }

	operator long	() const	{ return atol(this->c_str()); }
	operator unsigned long	() const	{ return atol(this->c_str()); }

	operator double	() const	{ return atof(this->c_str()); }

	enum { MAX_STRING = 4096 };
	void format(const char* fmt, ...);
};

#endif // !defined(AFX_MYSTRING_H__04538BAC_0EF7_46EB_AAF7_9201677B5D10__INCLUDED_)
