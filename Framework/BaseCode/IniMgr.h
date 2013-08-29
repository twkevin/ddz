// IniMgr.h: interface for the CIniMgr class.
#if !defined(AFX_INIMGR_H__BB959076_7E49_4CE2_ACCD_2C3359DAA0F6__INCLUDED_)
#define AFX_INIMGR_H__BB959076_7E49_4CE2_ACCD_2C3359DAA0F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>
#include "MyIni.h"
#include "MyString.h"
#include "Singleton.h"

class CIniMgr : public Singleton<CIniMgr>
{
public:
	CIniMgr(void);
	virtual ~CIniMgr(void);
public:
	typedef std::map<std::string, CMyIniPtr> MAP_INIFILE;	// �����ļ���->�����ļ�����
public:
	void DestroyFile(const char *pszFileName);

	// ��ȡCMyIni���������ļ�
	CMyIniPtr GetMyIniPtr(const std::string &strFileName);

	// ����������ʽ���عؼ��ֵ�ֵ
	int GetData(const std::string &strFileName, const std::string &strSectionName, const std::string &strKeyName,
				int nDefaultValue);

	int GetData(const std::string &strFileName, const std::string &strSectionName, const std::string &strKeyName,
				int nDefaultValue, bool bReadFileAlways);

	// ���ַ�������ʽ���عؼ��ֵ�ֵ
	std::string GetString(const std::string &strFileName, const std::string &strSectionName,
						  const std::string &strKeyName, const std::string &strDefaultValue);

	std::string GetString(const std::string &strFileName, const std::string &strSectionName,
						  const std::string &strKeyName, const std::string &strDefaultValue, bool bReadFileAlways);
	
	bool SetData(const std::string &strFileName, const std::string &strSectionName, const std::string &strKeyName,
				int nAssignValue);

	bool SetString(const std::string &strFileName, const std::string &strSectionName,
						  const std::string &strKeyName, const std::string &strAssignValue);

private:
	MAP_INIFILE m_mapIniFile;
};

#define g_objIniMgr CIniMgr::GetSingleton_AutoCreate()
#endif // !defined(AFX_INIMGR_H__BB959076_7E49_4CE2_ACCD_2C3359DAA0F6__INCLUDED_)
