// MyIni.h: interface for the CMyIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYINI_H__B6531120_B054_4E2F_8482_889CCAB90144__INCLUDED_)
#define AFX_MYINI_H__B6531120_B054_4E2F_8482_889CCAB90144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CMyIni ʵ��˼·�ǰ�ini�ļ������е�section���ַ���ʽ�����ڴ棬ͨ��map��������ʹ�ȡ��
// �ŵ��ǿ��Կ��ٲ�����Ϣ��ȱ�������Ľ϶��ڴ棬��һ�ֵ��͵ġ��ڴ滻ʱ�䡿�ķ�����
// �Ƽ�����Ҫ���ٴ�ȡȫ�ֻ��߾�̬��iniʱʹ�á�ini��С��ʱ��Ҳ�ɽ�����ʱ�����ȡ��
// Note:	֧�� ' ', ';', '/', '\' 'TAB' ��Ϊע�ͷ��š�
//			'=' ����֧��' ', 'TAB'���������ſ�����' ', ';', 'TAB', '\r', '\n'��
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

	// �Է���������ʽȡ������
	int		GetData			(const char* pszSection, const char* pszIndex) const;

	// ���ַ�����ʽȡ������
	const char* GetString	(const char* pszSection, const char* pszIndex) const;

	// ��Ѱsection
	bool	SearchSection	(const char* pszSection) const;

	// ��λsection���������Ϊ�գ���λ�ڵ�һ��section
	bool	SeekSection		(const char* pszSection);
	
	// ��ʼö��section�� ��λ�ڵ�һ��section
	void	BeginEnumSection	(void) { m_iter = m_setSection.begin(); }

	// ö��section�����ص�ǰsection�����֣������end�ˣ�����NULL
	const char* EnumSection		(void);

	// �ƶ�ö��ָ�뵽�¸�section, �����end�ˣ�����false
	bool	EnumMoveNext		(void)	{ ++ m_iter; return m_iter != m_setSection.end(); }

	// �ӵ�ǰsection�а���������ȡ���������ݡ�ʧ�ܷ��ؿմ���
	const CMyString&	GetContent	(const char* pszIndex) const;

	int GetKeyAmount(void) const;
	const char *GetKeyName(int nIndex) const;
 
	// GetData�Ĵ���Ĭ�Ϸ���ֵ�汾
	int GetValue(const char *pszSection, const char *pszIndex, int nDefaultValue) const;
	
	// GetString�Ĵ���Ĭ�Ϸ���ֵ�汾
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
