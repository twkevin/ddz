// MyIni.h: interface for the CMyIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYINI_H__B6531120_B054_4E2F_8482_889CCAB90144__INCLUDED_)
#define AFX_MYINI_H__B6531120_B054_4E2F_8482_889CCAB90144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CMyIni 实现思路是把ini文件中所有的section以字符方式读入内存，通过map容器管理和存取。
// 优点是可以快速查找信息，缺点是消耗较多内存，是一种典型的【内存换时间】的方案。
// 推荐在需要快速存取全局或者静态的ini时使用。ini较小的时候也可建立临时对象存取。
// Note:	支持 ' ', ';', '/', '\' 'TAB' 作为注释符号。
//			'=' 两边支持' ', 'TAB'；结束符号可以是' ', ';', 'TAB', '\r', '\n'。
//////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <vector>

#include "MyString.h"

#include "define.h"
#include "CQGlobal.h"

//namespace myini {

class CMyIni  
{
public:
	CMyIni(bool bCritical);
	CMyIni(const char* pszFile, bool bCritical);
	virtual ~CMyIni();

	// 以符号整数形式取回数据
	int		GetData			(const char* pszSection, const char* pszIndex) const;

	// 以字符串形式取回数据
	const char* GetString	(const char* pszSection, const char* pszIndex) const;

	// 搜寻section
	bool	SearchSection	(const char* pszSection) const;

	// 定位section，参数如果为空，则定位于第一个section
	bool	SeekSection		(const char* pszSection);
	
	// 开始枚举section， 定位于第一个section
	void	BeginEnumSection	(void) { m_iter = m_setSection.begin(); }

	// 枚举section，返回当前section的名字，如果到end了，返回NULL
	const char* EnumSection		(void);

	// 移动枚举指针到下个section, 如果到end了，返回false
	bool	EnumMoveNext		(void)	{ ++ m_iter; return m_iter != m_setSection.end(); }

	// 从当前section中按索引参数取回内容数据。失败返回空串。
	const CMyString&	GetContent	(const char* pszIndex) const;

	int GetKeyAmount(void) const;
	const char *GetKeyName(int nIndex) const;
 
	// GetData的带有默认返回值版本
	int GetValue(const char *pszSection, const char *pszIndex, int nDefaultValue) const;
	
	// GetString的带有默认返回值版本
	const char* GetValue(const char *pszSection, const char *pszIndex, const char *pszDefaultValue) const;
	
	bool Save(void) const;

private:
	bool	Open		(const char* pszIniFile);
	bool	OpenByBuf	(void* buf, DWORD dwSize, const char* pszFileName);
	bool	ParseSection(char* pszLine, CMyString& str) const;
	bool	ParseContent(char* pszLine, CMyString& strIndex, CMyString& strContent) const;
	bool	IsValidLine	(const char* pszLine) const;

	struct SECTION
	{
		std::map< CMyString, CMyString > setInfo;
	};

	std::map< CMyString, SECTION > m_setSection;
	std::map< CMyString, SECTION >::iterator m_iter;
	bool	m_bCritical;
	
	std::string		m_strFileName;
	std::vector<std::string> m_vecKey;

public:
	void AddSection(const char* pszSection, const char* pszIndex, const char* pszContext);
	void ChangeSectionVaule(const char* pszSection, const char* pszIndex, const char* pszContext);
public:
	static CMyIni*	CreateNew	(const char* pszIniFile, bool bCritical = false);
	static CMyIni*	CreateNewByBuf	(void* buf, DWORD dwSize, const char* pszFileName, bool bCritical = false);
};

typedef CMyIni* CMyIniPtr;

//} // namespace myini

//using myini::CMyIni;

#endif // !defined(AFX_MYINI_H__B6531120_B054_4E2F_8482_889CCAB90144__INCLUDED_)
