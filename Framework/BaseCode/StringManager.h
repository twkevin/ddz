#ifndef __STRINGMANAGER_H__
#define __STRINGMANAGER_H__

// 从配置文件加载字符串资源，并提供给其他模块调用查找字符串
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "Singleton.h"

#include <string>
#include <map>

class CStringManager : public Singleton<CStringManager>
{
private:
	// NON-CONST method
	void ParseLine(char *pszStr);

	// STATIC method
	static void Trim(char *pszStr);
	static void TrimLeft(char *pszStr);
	static void TrimRight(char *pszStr);

	int m_iLogUnkownMsg;
	std::map<std::string, std::string> m_mapStrSource;
	std::map<unsigned int, std::string> m_mapNetLog;
public:
	CStringManager();
	virtual ~CStringManager();

	// CONST method
	void LoadFile(const char* pszFileName);
	const char *GetStr(const std::string &idRes) const;
	const char *GetStr(OBJID idRes) const;
	const char *GetNetLog(unsigned int nType) const;
};

#define g_objStrMgr CStringManager::GetSingleton_AutoCreate()

#endif
