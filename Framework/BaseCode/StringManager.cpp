
#include "Basefunc.h"
#include "StringFormat.h"
#include "PublicFunc.h"

#include "StringManager.h"

// =====================================================================================================================
// =======================================================================================================================
CStringManager::CStringManager()
{
	LoadFile("ini/language_zh.ini");

#ifdef DEBUG
//	LoadFile("ini/msglog.ini");
#endif
}

// =====================================================================================================================
// =======================================================================================================================
CStringManager::~CStringManager()
{
}

// =====================================================================================================================
// =======================================================================================================================
void CStringManager::Trim(char *pszStr)
{
	TrimLeft(pszStr);
	TrimRight(pszStr);
}

// =====================================================================================================================
// =======================================================================================================================
void CStringManager::TrimLeft(char *pszStr)
{
	if (pszStr == NULL) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~
	int len = strlen(pszStr);
	//~~~~~~~~~~~~~~~~~~~~~

	if (len > 0) {

		//~~~~~~
		int i = 0;
		//~~~~~~

		for (i = 0; i < len; ++i) {
			if (pszStr[i] != ' ' && pszStr[i] != '\t' && pszStr[i] != '\r' && pszStr[i] != '\n') {
				break;
			}
		}

		if (i > 0) {
			memmove(pszStr, pszStr + i, len - i + 1);
		}
	}
}

// =====================================================================================================================
// =======================================================================================================================
void CStringManager::TrimRight(char *pszStr)
{
	if (pszStr == NULL) {
		return;
	}

	for (int nLast = strlen(pszStr) - 1; nLast >= 0; --nLast) {
		if (pszStr[nLast] == ' ' || pszStr[nLast] == '\t' || pszStr[nLast] == '\r' || pszStr[nLast] == '\n') {
			pszStr[nLast] = '\0';
		} else {
			break;
		}
	}
}

// =====================================================================================================================
// =======================================================================================================================
void CStringManager::ParseLine(char *pszStr)
{
	//~~~~~~~~~~~~~~~~~
	char szTemp[1024 * 5];
	char *pszTemp = NULL;
	//~~~~~~~~~~~~~~~~~

	pszTemp = strchr(pszStr, '=');
	if (pszTemp == NULL) {
		return;
	}

	memset(szTemp, 0, sizeof(szTemp));
	strncpy(szTemp, pszStr, pszTemp - pszStr);
	Trim(szTemp);

	// 忽略空行、注释行
	if (strlen(szTemp) <= 0 || szTemp[0] == ';') {
		return;
	}

	std::string sID(szTemp);

	memset(szTemp, 0, sizeof(szTemp));
	strncpy(szTemp, pszTemp + 1, pszStr + strlen(pszStr) - pszTemp - 1);

	// 去掉字符串末尾的回车换行符
	if (szTemp[strlen(szTemp) - 1] == '\r' || szTemp[strlen(szTemp) - 1] == '\n') {
		szTemp[strlen(szTemp) - 1] = '\0';
	}

	if (szTemp[strlen(szTemp) - 1] == '\r' || szTemp[strlen(szTemp) - 1] == '\n') {
		szTemp[strlen(szTemp) - 1] = '\0';
	}

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	m_mapStrSource[sID] = szTemp;
#else
	std::string strTmp = szTemp;
	TqReplaceString(strTmp, "%I64", "%ll");
	m_mapStrSource[sID] = strTmp;
#endif
}

// =====================================================================================================================
// =======================================================================================================================
const char *CStringManager::GetStr(const std::string &idRes) const
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::map<std::string, std::string>::const_iterator it = m_mapStrSource.find(idRes);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (it != m_mapStrSource.end()) {
		return(it->second.c_str());
	}
/*
#ifdef _DEBUG
	if (m_iLogUnkownMsg) {
		return "UNKNOWN";
	}

	if (m_iLogUnkownMsg == 0) {
		return NULL;
	}
#endif*/
	// LOGERROR("ERROR: CStringManager::GetStr() Can't find string[%s]!", idRes.c_str());
	return "";
}

// =====================================================================================================================
// =======================================================================================================================
const char *CStringManager::GetStr(OBJID idRes) const
{
	std::string strIndex = FORMAT("%d") << idRes;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::map<std::string, std::string>::const_iterator it = m_mapStrSource.find(strIndex);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (it != m_mapStrSource.end()) {
		return(it->second.c_str());
	}

#ifdef _DEBUG
	if (m_iLogUnkownMsg) {
		return "UNKNOWN";
	}

	if (m_iLogUnkownMsg == 0) {
		return NULL;
	}
#endif
	LOGERROR("ERROR: CStringManager::GetStr() Can't find id[%d]!", idRes);
	return NULL;
}

// =====================================================================================================================
// =======================================================================================================================
const char *CStringManager::GetNetLog(unsigned int nType) const
{
	return NULL;
}

// =====================================================================================================================
//    加载CnRes.ini或MsgLog.ini
// =====================================================================================================================
void CStringManager::LoadFile(const char* pszFileName)
{
	m_iLogUnkownMsg = -1;

	//~~~~~
	//FILE *fp;
	//~~~~~

	if (NULL == pszFileName)
	{
		// LOGERROR("ERROR: CStringManager::CStringManager() get string resource file name fail!");
		return;
	}

// 	fp = CQfopen(pszFileName, "r");
// 	if (!fp)
// 	{
// 		// LOGERROR("ERROR: CStringManager::CStringManager() load string resource file %s fail!", pszFileName);
// 		return;
// 	}

	unsigned long ulLength = 0;
	const char* pBuffer = GetFileData(pszFileName, "r", ulLength);
	if (NULL == pBuffer)
	{
		LOG_ERROR("CStringManager::LoadFile[%s] failed", pszFileName);
		return;
	}

	DWORD dwOffset = 0;
	//~~~~~~~~~~~~~~~~~~~~~~
	char szLine[1024 * 5] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~

	while (true)
	{
		// 取出一行Txt
		if (!MemTxtLineGet(pBuffer, ulLength, dwOffset, szLine, sizeof(szLine)))
		//if (NULL == fgets(szLine, sizeof(szLine), fp))
		{
			break;
		}

		ParseLine(szLine);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef _DEBUG
	std::map<std::string, std::string>::const_iterator it = m_mapStrSource.find("LogUnkownMsg");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (it != m_mapStrSource.end())
	{
		m_iLogUnkownMsg = atoi(it->second.c_str());
	}
#endif

	//fclose(fp);
	SAFE_DELETE_EX(pBuffer);
}
