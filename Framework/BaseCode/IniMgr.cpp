// IniMgr.cpp: implementation of the CIniMgr class.

#include <algorithm>
#include <utility>

#include "BaseFunc.h"
#include "IniMgr.h"


// =====================================================================================================================
//    Construction
// =====================================================================================================================
CIniMgr::CIniMgr(void)
{
}

// =====================================================================================================================
//    Destruction
// =====================================================================================================================
CIniMgr::~CIniMgr(void)
{
	MAP_INIFILE::iterator itInifile = m_mapIniFile.begin();

	for (; itInifile != m_mapIniFile.end(); ++itInifile)
	{
		SAFE_DELETE(itInifile->second);
	}

	m_mapIniFile.clear();
}

// =====================================================================================================================
//    销毁内存中的配置文件
// =====================================================================================================================
void CIniMgr::DestroyFile(const char *pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTemp = pszFileName;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTemp.begin(), strTemp.end(), strTemp.begin(), tolower);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	MAP_INIFILE::iterator itInifile = m_mapIniFile.find(strTemp);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (itInifile != m_mapIniFile.end()) {
		CMyIniPtr pMyIni = itInifile->second;
		m_mapIniFile.erase(itInifile);
		SAFE_DELETE(pMyIni);
	}
}

// =====================================================================================================================
//    获取CMyIni，即配置文件
// =====================================================================================================================
CMyIniPtr CIniMgr::GetMyIniPtr(const std::string &strFileName)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTemp = strFileName;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTemp.begin(), strTemp.end(), strTemp.begin(), tolower);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	MAP_INIFILE::iterator itInifile = m_mapIniFile.find(strTemp);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (itInifile == m_mapIniFile.end()) {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		CMyIni *pMyIni = CMyIni::CreateNew(strTemp.c_str(), true);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (pMyIni) {

			//~~~~~~~~~~~~~~~~~~~~~~~~~
			CMyIniPtr pCMyIniPtr(pMyIni);
			//~~~~~~~~~~~~~~~~~~~~~~~~~

			m_mapIniFile.insert(std::make_pair(strTemp, pCMyIniPtr));
			return pCMyIniPtr;
		}

		return CMyIniPtr();
	}

	return itInifile->second;
}

// =====================================================================================================================
//    以整数的形式返回关键字的值
// =====================================================================================================================
int CIniMgr::GetData(const std::string &strFileName,
					 const std::string &strSectionName,
					 const std::string &strKeyName,
					 int nDefaultValue)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CMyIniPtr pCMyIniPtr = GetMyIniPtr(strFileName);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pCMyIniPtr) {
		return pCMyIniPtr->GetValue(strSectionName.c_str(), strKeyName.c_str(), nDefaultValue);
	}

	return nDefaultValue;
}

// =====================================================================================================================
//    GetData的可重读版本,参数顺序也许与GetPrivateProfileInt一致较好,但优先与既有函数统一;
//    需要重读的地方(如程序中写了配置,或提供了Relaod的PM命令);
//    请调用此函数并使参数bReadFileAlways=true,避免之后被误修改
// =====================================================================================================================
int CIniMgr::GetData(const std::string &strFileName,
					 const std::string &strSectionName,
					 const std::string &strKeyName,
					 int nDefaultValue,
					 bool bReadFileAlways)
{

	return GetData(strFileName, strSectionName, strKeyName, nDefaultValue);
}

// =====================================================================================================================
//    以字符串的形式返回关键字的值
// =====================================================================================================================
std::string CIniMgr::GetString(const std::string &strFileName,
							   const std::string &strSectionName,
							   const std::string &strKeyName,
							   const std::string &strDefaultValue)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CMyIniPtr pCMyIniPtr = GetMyIniPtr(strFileName);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pCMyIniPtr) {
		return pCMyIniPtr->GetValue(strSectionName.c_str(), strKeyName.c_str(), strDefaultValue.c_str());
	}

	return strDefaultValue;
}

// =====================================================================================================================
//    GetString的可重读版本,需要重读的地方(如程序中写了配置,或提供了Relaod的PM命令);
//    请调用此函数并使参数bReadFileAlways=true,避免之后被误修改
// =====================================================================================================================
std::string CIniMgr::GetString(const std::string &strFileName,
							   const std::string &strSectionName,
							   const std::string &strKeyName,
							   const std::string &strDefaultValue,
							   bool bReadFileAlways)
{
	return GetString(strFileName, strSectionName, strKeyName, strDefaultValue);
}

bool CIniMgr::SetData(const std::string &strFileName, const std::string &strSectionName, const std::string &strKeyName,
			 int nAssignValue)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CMyIniPtr pCMyIniPtr = GetMyIniPtr(strFileName);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pCMyIniPtr) {

		char szContent[128] = { 0 };
		_snprintf(szContent, sizeof(szContent) - 1, "%d", nAssignValue);
		szContent[sizeof(szContent) - 1] = '\0';
		std::string strContent = szContent;
		pCMyIniPtr->AddSection(strSectionName.c_str(), strKeyName.c_str(), strContent.c_str());
		return true;
	}
	
	return false;
}

bool CIniMgr::SetString(const std::string &strFileName, const std::string &strSectionName,
			   const std::string &strKeyName, const std::string &strAssignValue)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CMyIniPtr pCMyIniPtr = GetMyIniPtr(strFileName);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pCMyIniPtr) {
		pCMyIniPtr->AddSection(strSectionName.c_str(), strKeyName.c_str(), strAssignValue.c_str());
		return true;
	}

	return false;
}
