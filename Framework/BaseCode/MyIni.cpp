// MyIni.cpp: implementation of the CMyIni class.
//
//////////////////////////////////////////////////////////////////////

#include <algorithm>

#include "BaseFunc.h"
#include "MyString.h"
#include "PublicFunc.h"

#include "MyIni.h"

//namespace myini {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyIni::CMyIni(bool bCritical) : m_bCritical(bCritical)
{

}

CMyIni::CMyIni(const char* pszFile, bool bCritical) : m_bCritical(bCritical)
{
	bool bSucOpen = this->Open(pszFile);
	if (!bSucOpen && m_bCritical)
		LOGERROR("%s open error.", pszFile);
	
	m_strFileName = pszFile;
}

CMyIni::~CMyIni()
{
	m_vecKey.clear();
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::SeekSection (const char* pszSection)
{
	if (!pszSection)
	{
		m_iter = m_setSection.begin();
		return true;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempSection = pszSection;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempSection.begin(), strTempSection.end(), strTempSection.begin(), tolower);

	m_iter = m_setSection.find(strTempSection.c_str());
	return (m_iter != m_setSection.end());
}

//////////////////////////////////////////////////////////////////////
const CMyString& CMyIni::GetContent(const char* pszIndex) const
{
	static const CMyString STR_ERROR = "";
	IF_NOT (pszIndex)
		return STR_ERROR;

	// search content
	SECTION& section = (*m_iter).second;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempIndex = pszIndex;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempIndex.begin(), strTempIndex.end(), strTempIndex.begin(), tolower);

	std::map<CMyString, CMyString>::const_iterator iter = section.setInfo.find(strTempIndex.c_str());
	if (iter == section.setInfo.end())
	{
		if (m_bCritical)
			LOGERROR("section[%s], index[%s] not found in %s!", (const char*)m_iter->first, pszIndex, m_strFileName.c_str());

		return STR_ERROR;
	}

	return (*iter).second;
}

//////////////////////////////////////////////////////////////////////
const char* CMyIni::EnumSection()
{
	if (m_iter == m_setSection.end())
		return NULL;

	return (*m_iter).first;
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::SearchSection (const char* pszSection) const
{
	if (!pszSection) {
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempSection = pszSection;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempSection.begin(), strTempSection.end(), strTempSection.begin(), tolower);

	return (m_setSection.find(strTempSection.c_str()) != m_setSection.end());
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::IsValidLine	(const char* szLine) const
{
	IF_NOT (szLine)
		return false;

	// length check
	if (::strlen(szLine) <= 2)
		return false;

	// first char check
	bool bValidLine = true;
	switch(szLine[0])
	{
	case '/':
	case '\\':
	case ';':
	case '=':
	case ' ':
	case '\t':
	case '\r':
	case 0x0a:
		bValidLine = false;
		break;

	default:
		break;
	}

	return bValidLine;
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::ParseSection(char* szLine, CMyString& str) const
{
	IF_NOT (szLine)
		return false;

	if ('[' != szLine[0])
		return false;

	int nStrLen = ::strlen(szLine);
	int i = 0;

	for (i=1; i<nStrLen; i++)
	{
		if (']' == szLine[i])
		{
			szLine[i] = '\0';
			break;
		}
	}
	
	if (i >= nStrLen)	// not valid section line
		return false;
		
	// section line found!
	str = szLine+1;
	std::transform(str.begin(), str.end(), str.begin(), tolower);

	return true;		
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::ParseContent(char* szLine, CMyString& strIndex, CMyString& strContent) const
{
	// valid check
	if (!this->IsValidLine(szLine))
		return false;

	// parse index
	int nLen = ::strlen(szLine);
	int i = 0;
	for (i=0; i<nLen; i++)
	{
		if ('=' == szLine[i])
		{
			szLine[i] = '\0';

			int idx = i;
			while (idx > 0)
			{
				--idx;

				int c = szLine[idx];
				if (' ' != c && '\t' != c)
					break;
				else
					szLine[idx] = '\0';
			}

			strIndex = szLine;
			break;
		}
	}

	if (i >= nLen)		// no '=' found, not valid line
		return false;

	// string forward
	if (i+1 >= nLen)	// empty content
		return true;

	szLine	+= (i+1);	// now szLine is string behind '='

	// remove format char
	nLen = ::strlen(szLine);
	for (i=0; i<nLen; i++)
	{
		int c = szLine[i];
		if (' ' != c && '\t' != c)
			break;
	}

	szLine += i;		// now szLine is string after format char
	
	// parse content
	nLen = ::strlen(szLine);
	for (i=0; i<nLen; i++)
	{
		if ('\t' == szLine[i] || ';' == szLine[i] 
				|| '\r' == szLine[i] || 0x0a == szLine[i])
		{
			szLine[i] = '\0';
			break;
		}
	}

	strContent = szLine;
	std::transform(strIndex.begin(), strIndex.end(), strIndex.begin(), tolower);
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::Open (const char* pszIniFile)
{
	IF_NOT (pszIniFile)
		return false;

	m_setSection.clear();
	m_vecKey.clear();

// 	FILE* fp = CQfopen(pszIniFile, "r");
// 	if (!fp)
// 	{
// 		LOG_ERROR("CMyIni::Open[%s] failed", pszIniFile);
// 		return false;
// 	}

	unsigned long ulLength = 0;
	const char* pBuffer = GetFileData(pszIniFile, "r", ulLength);
	if (NULL == pBuffer)
	{
		LOG_ERROR("CMyIni::Open[%s] failed", pszIniFile);
		return false;
	}

	SECTION section;
	CMyString strTitle;	
	DWORD dwOffset = 0;
	char szLine[1024]	= "";
	while(true)
	{
		// 取出一行Txt
		if (!MemTxtLineGet(pBuffer, ulLength, dwOffset, szLine, sizeof(szLine)))
		//if (NULL == fgets(szLine, sizeof(szLine), fp))
		{
			// save section info
			if (!strTitle.empty())
				m_setSection[strTitle] = section;

			break;
		}

		// string length chk
		int nStrLen = ::strlen(szLine);
		if (nStrLen <= 2)
			continue;

		// get rid of end char
		if (0x0a == szLine[nStrLen-1])
			szLine[nStrLen-1] = 0;

		// parse now
		CMyString str;
		if (this->ParseSection(szLine, str))
		{
			// a new section found, keep the old one
			if (!strTitle.empty())
				m_setSection[strTitle] = section;

			// replace section title string
			strTitle = str;
			m_vecKey.push_back(strTitle);

			// clear old section
			section.setInfo.clear();
		}
		else
		{
			if (!strTitle.empty())
			{
				// read section content
				CMyString strIndex, strContent;
				if (this->ParseContent(szLine, strIndex, strContent))
				{
					section.setInfo[strIndex] = strContent;
				}
			}
		}
	}

	//fclose(fp);
	SAFE_DELETE_EX(pBuffer);
	m_strFileName = pszIniFile;
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CMyIni::OpenByBuf(void* buf, DWORD dwSize, const char* pszFileName)
{
	IF_NOT (buf)
		return false;

	m_setSection.clear();
	m_vecKey.clear();

	SECTION section;
	CMyString strTitle;
		
	DWORD dwOffset = 0;
	while(true)
	{
		char szLine[1024]	= "";
		if (!::MemTxtLineGet((const char*)buf, dwSize, dwOffset, szLine, sizeof(szLine)))
		{
			// save section info
			if (!strTitle.empty())
				m_setSection[strTitle] = section;

			break;
		}

		// string length chk
		int nStrLen = ::strlen(szLine);
		if (nStrLen <= 2)
			continue;

		// get rid of end char
		if (0x0a == szLine[nStrLen-1])
			szLine[nStrLen-1] = 0;

		// parse now
		CMyString str;
		if (this->ParseSection(szLine, str))
		{
			// a new section found, keep the old one
			if (!strTitle.empty())
				m_setSection[strTitle] = section;

			// replace section title string
			strTitle = str;
			m_vecKey.push_back(strTitle);
			
			// clear old section
			section.setInfo.clear();
		}
		else
		{
			if (!strTitle.empty())
			{
				// read section content
				CMyString strIndex, strContent;
				if (this->ParseContent(szLine, strIndex, strContent))
				{
					section.setInfo[strIndex] = strContent;
				}
			}
		}
	}

	m_strFileName = pszFileName;
	return true;
}

//////////////////////////////////////////////////////////////////////
int CMyIni::GetData(const char* pszSection, const char* pszIndex) const
{
	IF_NOT (pszSection && pszIndex)
		return 0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempSection = pszSection;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempSection.begin(), strTempSection.end(), strTempSection.begin(), tolower);

	// search section
	std::map<CMyString, SECTION>::const_iterator iter = m_setSection.find(strTempSection.c_str());
	if (iter == m_setSection.end())
	{
		if (m_bCritical)
			LOGERROR("section[%s] not found in %s!", pszSection, m_strFileName.c_str());

		return 0;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempIndex = pszIndex;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	std::transform(strTempIndex.begin(), strTempIndex.end(), strTempIndex.begin(), tolower);

	// search content
	std::map<CMyString, CMyString>::const_iterator iter2 = (*iter).second.setInfo.find(strTempIndex.c_str());
	if (iter2 == (*iter).second.setInfo.end())
	{
		if (m_bCritical)
			LOGERROR("section[%s], index[%s] not found in %s!", pszSection, pszIndex, m_strFileName.c_str());

		return 0;
	}

	return (*iter2).second;
}

int CMyIni::GetKeyAmount(void) const
{
	return m_vecKey.size();
}

const char* CMyIni::GetKeyName(int nIndex) const
{
	if (0 <= nIndex && nIndex < static_cast<int>(m_vecKey.size())) {
		return m_vecKey[nIndex].c_str();
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
const char* CMyIni::GetString(const char* pszSection, const char* pszIndex) const
{
	IF_NOT (pszSection && pszIndex)
		return NULL;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempSection = pszSection;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempSection.begin(), strTempSection.end(), strTempSection.begin(), tolower);

	// search section
	std::map<CMyString, SECTION>::const_iterator iter = m_setSection.find(strTempSection.c_str());
	if (iter == m_setSection.end())
	{
		if (m_bCritical)
			LOGERROR("section[%s] not found in %s!", pszSection, m_strFileName.c_str());

		return NULL;
	}
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempIndex = pszIndex;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempIndex.begin(), strTempIndex.end(), strTempIndex.begin(), tolower);
	// search content
	std::map<CMyString, CMyString>::const_iterator iter2 = (*iter).second.setInfo.find(strTempIndex.c_str());
	if (iter2 == (*iter).second.setInfo.end())
	{
		if (m_bCritical)
			LOGERROR("section[%s], index[%s] not found in %s!", pszSection, pszIndex, m_strFileName.c_str());

		return NULL;
	}

	return (*iter2).second;
}

//////////////////////////////////////////////////////////////////////
// static
//////////////////////////////////////////////////////////////////////
CMyIni*	CMyIni::CreateNew(const char* pszIniFile, bool bCritical)
{
	IF_NOT (pszIniFile)
		return NULL;

	CMyIni* pMyIni = new CMyIni(bCritical);
	IF_NOT (pMyIni)
		return NULL;

	if (!pMyIni->Open(pszIniFile))
	{
		SAFE_DELETE(pMyIni)
		return NULL;
	}

	return pMyIni;
}

//////////////////////////////////////////////////////////////////////
CMyIni*	CMyIni::CreateNewByBuf	(void* buf, DWORD dwSize, const char* pszFileName, bool bCritical)
{
	IF_NOT (buf)
		return NULL;

	CMyIni* pMyIni = new CMyIni(bCritical);
	IF_NOT (pMyIni)
		return NULL;

	if (!pMyIni->OpenByBuf(buf, dwSize, pszFileName))
	{
		SAFE_DELETE(pMyIni)
		return NULL;
	}

	return pMyIni;
}


// =====================================================================================================================
//    GetData的带有默认返回值版本
// =======================================================================================================================
int CMyIni::GetValue(const char *pszSection, const char *pszIndex, int nDefaultValue) const
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nRet = nDefaultValue;
	const char *pszStr = this->GetString(pszSection, pszIndex);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!pszStr || 0 == pszStr[0]) {
		LOGERROR("%s - %s can't be find", pszSection, pszIndex);
		return nDefaultValue;
	}

	if (strlen(pszStr) > 2 && '0' == pszStr[0]
		&& ('x' == pszStr[1] || 'X' == pszStr[1]))
	{
		sscanf(pszStr, "%x", &nRet);
	}
	else
	{
		nRet = atoi(pszStr);
	}
	return nRet;
}

// =====================================================================================================================
//    GetString的带有默认返回值版本
// =====================================================================================================================
const char *CMyIni::GetValue(const char *pszSection, const char *pszIndex, const char *pszDefaultValue) const
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const char *pszStr = this->GetString(pszSection, pszIndex);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!pszStr || 0 == pszStr[0]) {
		LOGERROR("%s - %s can't be find", pszSection, pszIndex);
		return pszDefaultValue;
	}

	return pszStr;
}

// =====================================================================================================================
//    增加某个字段
// =====================================================================================================================
void CMyIni::AddSection(const char *pszSection, const char *pszIndex, const char *pszContext)
{
	if (!pszSection || !pszIndex || !pszContext) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempSection = pszSection;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempSection.begin(), strTempSection.end(), strTempSection.begin(), tolower);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// search section
	std::map<CMyString, SECTION>::iterator iter = m_setSection.find(strTempSection.c_str());
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (iter == m_setSection.end()) {

		//~~~~~~~~~~~~
		SECTION section;
		//~~~~~~~~~~~~

		section.setInfo[pszIndex] = pszContext;
		m_setSection[pszSection] = section;
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempIndex = pszIndex;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempIndex.begin(), strTempIndex.end(), strTempIndex.begin(), tolower);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// search content
	std::map<CMyString, CMyString>::iterator iter2 = (*iter).second.setInfo.find(strTempIndex.c_str());
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (iter2 == (*iter).second.setInfo.end()) {
		(*iter).second.setInfo[pszIndex] = pszContext;
	}
}

// =====================================================================================================================
//    改变某个字段的值
// =====================================================================================================================
void CMyIni::ChangeSectionVaule(const char *pszSection, const char *pszIndex, const char *pszContext)
{
	if (!pszSection || !pszIndex || !pszContext) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempSection = pszSection;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempSection.begin(), strTempSection.end(), strTempSection.begin(), tolower);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// search section
	std::map<CMyString, SECTION>::iterator iter = m_setSection.find(strTempSection.c_str());
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (iter == m_setSection.end()) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strTempIndex = pszIndex;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	std::transform(strTempIndex.begin(), strTempIndex.end(), strTempIndex.begin(), tolower);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// search content
	std::map<CMyString, CMyString>::iterator iter2 = (*iter).second.setInfo.find(strTempIndex.c_str());
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (iter2 == (*iter).second.setInfo.end()) {
		return;
	}
	(*iter2).second = pszContext;
}

bool CMyIni::Save(void) const
{
	return true;
}

//} // namespace myini
