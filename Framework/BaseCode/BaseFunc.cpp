//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "CQConfig.h"

#include <string>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <climits>

#include "BaseFunc.h"


// global... 
//////////////////////////////////////////////////////////////////////
//int	Double2Int(double dValue)
//{
//	if((int)(dValue+0.5) >(int)dValue)
//		return int(dValue)+1;
//	else
//		return int(dValue);
//}

//////////////////////////////////////////////////////////////////////
//BOOL IniStrGet(const char *pszFileName, const char *pszTitle, const char *pszSubTitle, char *pszStr, BOOL bCritical/*=false*/)
//{
//	if (!pszFileName || !pszTitle || !pszSubTitle || !pszStr)
//		return false;
//
//	FILE* fp = CQfopen(pszFileName, "r");
//	if (!fp)
//		return false;
//
//	char szSection[256]	= "";
//	_snprintf(szSection, sizeof(szSection) - 1, "[%s]", pszTitle);
//	szSection[sizeof(szSection) - 1] = 0;
//
//	bool bSucFound	=false;
//	while(true)
//	{
//		char szTemp[1024] = { 0 };
//		char szLine[1024]	="";
//		if (NULL == fgets(szTemp, sizeof(szTemp) - 1, fp))
//		{
//			break;
//		}
//		sscanf(szTemp, "%s\n", szLine);
//
//		if (0 != mystricmp(szSection, szLine))
//			continue;
//
//		// section found
//		char szFormat[256] = { 0 };
//		_snprintf(szFormat, sizeof(szFormat) - 1, "%s=%s\n", pszSubTitle, "%s");
//		szFormat[sizeof(szFormat) - 1] = 0;
//
//		while (true)
//		{
//			char szLine[1024]	="";
//			if (NULL == fgets(szLine, sizeof(szLine) - 1, fp))
//			{
//				goto out;
//			}
//
//			if (strrchr(szLine, '[') && strrchr(szLine, ']'))
//				goto out;
//
//			if (sscanf(szLine, szFormat, pszStr))
//			{
//				bSucFound = true;
//				goto out;
//			}
//		}
//	}
//
//out:
//	fclose(fp);
//
//	if (!bSucFound)
//	{
//		if (bCritical)
//		{
//			char szMsg[1024] = "";
//			_snprintf(szMsg, sizeof(szMsg) - 1, "Error: [%s] %s not found in %s.", pszTitle, pszSubTitle, pszFileName);
//			szMsg[sizeof(szMsg) - 1] = 0;
//#ifdef CQ_IPAD_REMOVE
//#ifdef _DEBUG
//			::MessageBox(NULL, szMsg, "Error", MB_OK|MB_ICONERROR);
//#endif
//#endif // CQ_PLATFORM_IPAD
//			LOGERROR(szMsg);
//		}
//		else
//			::DebugMsg("Error: [%s] %s not found in %s.", pszTitle, pszSubTitle, pszFileName);
//	}
//
//	return bSucFound;
//}

//////////////////////////////////////////////////////////////////////
//BOOL IniDataGet(const char *pszFileName, const char *pszTitle, const char *pszSubTitle, int &iData, BOOL bCritical/*=false*/)
//{
//	if (!pszFileName || !pszTitle || !pszSubTitle)
//		return false;
//
//	FILE* fp = CQfopen(pszFileName, "r");
//	if (!fp)
//		return false;
//
//	char szSection[256]	= "";
//	_snprintf(szSection, sizeof(szSection) - 1, "[%s]", pszTitle);
//	szSection[sizeof(szSection) - 1] = 0;
//
//	bool bSucFound	=false;
//	while(true)
//	{
//		char szTemp[1024] = { 0 };
//		char szLine[1024]	="";
//		if (NULL == fgets(szTemp, sizeof(szTemp) - 1, fp))
//		{
//			break;
//		}
//
//		sscanf(szTemp, "%s\n", szLine);
//		
//		if (0 != mystricmp(szSection, szLine))
//			continue;
//
//		// section found
//		char szFormat[256] = { 0 };
//		_snprintf(szFormat, sizeof(szFormat) - 1, "%s=%s\n", pszSubTitle, "%d");
//		szFormat[sizeof(szFormat) - 1] = 0;
//
//		while (true)
//		{
//			char szLine[1024]	="";
//			if (NULL == fgets(szLine, sizeof(szLine) - 1, fp))
//			{
//				goto out;
//			}
//
//			if (strrchr(szLine, '[') && strrchr(szLine, ']'))
//				goto out;
//
//			if (sscanf(szLine, szFormat, &iData))
//			{
//				bSucFound = true;
//				goto out;
//			}
//		}
//	}
//
//out:
//	fclose(fp);
//
//	if (!bSucFound)
//	{
//		if (bCritical)
//		{
//			char szMsg[1024] = { 0 };
//			_snprintf(szMsg, sizeof(szMsg) - 1, "Error: [%s] %s not found in %s.", pszTitle, pszSubTitle, pszFileName);
//			szMsg[sizeof(szMsg) - 1] = 0;
//#ifdef CQ_IPAD_REMOVE
//#ifdef _DEBUG
//			::MessageBox(NULL, szMsg, "Error", MB_OK|MB_ICONERROR);
//#endif
//#endif // CQ_IPAD_REMOVE
//			LOGERROR(szMsg);
//		}
//		else
//			::DebugMsg("Error: [%s] %s not found in %s.", pszTitle, pszSubTitle, pszFileName);
//	}
//
//	return bSucFound;
//}

// =====================================================================================================================
// =======================================================================================================================
// bool IsDigit(char c)
// {
// 	return c >= 0 && isdigit(c);
// }

//////////////////////////////////////////////////////////////////////
// 从文本内存缓冲区取得一行TXT, 回车符号0x0a或缓冲区尾部为结束, 返回 FALSE 表示读完缓冲区或者出错.
//#ifdef CQ_IPAD_REMOVE
BOOL MemTxtLineGet(const char* pBuf, DWORD dwBufSize, DWORD& dwOffset, char* szLine, DWORD dwLineSize)
{
	if (!pBuf || !szLine)
		return FALSE;

	if (dwOffset >= dwBufSize)
		return FALSE;

	//~~~~~~~~
	DWORD i = 0;
	//~~~~~~~~

	for (i = 0; i < dwLineSize; i++)
	{
		szLine[i] = pBuf[dwOffset++];
		if (0x0a == szLine[i] || dwOffset >= dwBufSize)
		{
			szLine[i] = '\0';
			if (i > 0 && 0x0d == szLine[i-1])
				szLine[i-1] = '\0';
			
			break;
		}
	}

	return (i < dwLineSize);	// 文本行缓冲如果小了也会返回 FALSE
}
//#else
//BOOL MemTxtLineGet(const char* pBuf, DWORD dwBufSize, DWORD& dwOffset, char* szLine, DWORD dwLineSize)
//{
//	extern bool MemTxtLineGet(const char* pBuf, DWORD dwBufSize, DWORD& dwOffset, char* szLine, DWORD dwLineSize);
//	
//	DWORD dwc3Offset = dwOffset;
//	BOOL bRet = MemTxtLineGet(pBuf, (DWORD)dwBufSize, dwc3Offset, szLine, (DWORD)dwLineSize);
//	dwOffset = dwc3Offset;
//	return bRet;
//}
//#endif // CQ_IPAD_REMOVE

//////////////////////////////////////////////////////////////////////
//BOOL MemIniStrGet(const char *pBuf, DWORD dwSize, const char *pszTitle, const char *pszSubTitle, char *pszStr, BOOL bCritical/*=false*/)
//{
//	if (!pBuf || !pszTitle || !pszSubTitle || !pszStr)
//		return FALSE;
//
//	char szSection[256]	= { 0 };
//	_snprintf(szSection, sizeof(szSection) - 1, "[%s]", pszTitle);
//	szSection[sizeof(szSection) - 1] = 0;
//
//	DWORD dwOffset = 0;
//	bool bSucFound	=false;
//	while(true)
//	{
//		// 取出一行Txt
//		char szLine[1024] = "";
//		if (!MemTxtLineGet(pBuf, dwSize, dwOffset, szLine, sizeof(szLine)))
//			goto out;
//
//		// 解析此行, 先寻找SECTION
//		if (0 != mystricmp(szSection, szLine))
//			continue;
//
//		// section found
//		char szFormat[256] = "";
//		_snprintf(szFormat, sizeof(szFormat) - 1, "%s=%s", pszSubTitle, "%s");
//		szFormat[sizeof(szFormat) - 1] = 0;
//
//		while (true)
//		{
//			char szLine[1024]	="";
//			if (!MemTxtLineGet(pBuf, dwSize, dwOffset, szLine, sizeof(szLine)))
//				goto out;
//
//			if (strrchr(szLine, '[') && strrchr(szLine, ']'))
//				goto out;
//
//			if (sscanf(szLine, szFormat, pszStr))
//			{
//				bSucFound = true;
//				goto out;
//			}
//		}
//	}
//
//out:
//	if (!bSucFound)
//	{
//		if (bCritical)
//		{
//			char szMsg[1024] = "";
//			_snprintf(szMsg, sizeof(szMsg) - 1, "Error: [%s] %s not found in MemIniStrGet.", pszTitle, pszSubTitle);
//			szMsg[sizeof(szMsg) - 1] = 0;
//#ifdef CQ_IPAD_REMOVE
//#ifdef _DEBUG
//			::MessageBox(NULL, szMsg, "Error", MB_OK|MB_ICONERROR);
//#endif
//#endif // CQ_IPAD_REMOVE
//			LOGERROR(szMsg);
//		}
//		else
//			::DebugMsg("Error: [%s] %s not found in MemIniStrGet.", pszTitle, pszSubTitle);
//	}
//
//	return bSucFound;
//}

//////////////////////////////////////////////////////////////////////
//BOOL MemIniDataGet(const char *pBuf, DWORD dwSize, const char *pszTitle, const char *pszSubTitle, int &iData, BOOL bCritical/*=false*/)
//{
//	if (!pBuf || !pszTitle || !pszSubTitle)
//		return FALSE;
//	
//	char szSection[256]	= { 0 };
//	_snprintf(szSection, sizeof(szSection) - 1, "[%s]", pszTitle);
//	szSection[sizeof(szSection) - 1] = 0;
//	
//	DWORD dwOffset = 0;
//	bool bSucFound	=false;
//	while(true)
//	{
//		// 取出一行Txt
//		char szLine[1024] = "";
//		if (!MemTxtLineGet(pBuf, dwSize, dwOffset, szLine, sizeof(szLine)))
//			goto out;
//		
//		// 解析此行, 先寻找SECTION
//		if (0 != mystricmp(szSection, szLine))
//			continue;
//		
//		// section found
//		char szFormat[256] = "";
//		_snprintf(szFormat, sizeof(szFormat) - 1, "%s=%s", pszSubTitle, "%d");
//		szFormat[sizeof(szFormat) - 1] = 0;
//		
//		while (true)
//		{
//			char szLine[1024]	="";
//			if (!MemTxtLineGet(pBuf, dwSize, dwOffset, szLine, sizeof(szLine)))
//				goto out;
//			
//			if (strrchr(szLine, '[') && strrchr(szLine, ']'))
//				goto out;
//			
//			if (sscanf(szLine, szFormat, &iData))
//			{
//				bSucFound = true;
//				goto out;
//			}
//		}
//	}
//	
//out:
//	if (!bSucFound)
//	{
//		if (bCritical)
//		{
//			char szMsg[1024] = "";
//			_snprintf(szMsg, sizeof(szMsg) - 1, "Error: [%s] %s not found in MemIniDataGet.", pszTitle, pszSubTitle);
//			szMsg[sizeof(szMsg) - 1] =0;
//#ifdef CQ_IPAD_REMOVE
//#ifdef _DEBUG			
//			::MessageBox(NULL, szMsg, "Error", MB_OK|MB_ICONERROR);
//#endif
//#endif // CQ_IPAD_REMOVE
//			LOGERROR(szMsg);
//		}
//		else
//			::DebugMsg("Error: [%s] %s not found in MemIniDataGet.", pszTitle, pszSubTitle);
//	}
//	
//	return bSucFound;
//}

//////////////////////////////////////////////////////////////////////
//BOOL TxtStrGet(const char *pszFileName, const char *pszTitle, char *pszStr, BOOL bCritical/*=false*/)
//{
//	if (!pszFileName || !pszTitle || !pszStr)
//		return false;
//
//	FILE* fp = CQfopen(pszFileName, "r");
//	if (!fp)
//		return false;
//
//	char szFormat[256]	= { 0 };
//	_snprintf(szFormat, sizeof(szFormat) - 1, "%s=%s", pszTitle, "%s");
//	szFormat[sizeof(szFormat) - 1] = 0;
//
//	bool bSucFound	=false;
//	while(true)
//	{
//		char szLine[1024]	="";
//		if (NULL == fgets(szLine, sizeof(szLine) - 1, fp))
//		{
//			break;
//		}
//
//		if (sscanf(szLine, szFormat, pszStr))
//		{
//			bSucFound	=true;
//			break;
//		}
//	}
//
//	fclose(fp);
//
//	if (!bSucFound)
//	{
//		if (bCritical)
//			LOGERROR("Error: %s not found in %s.", pszTitle, pszFileName);
//		else
//			::DebugMsg("Error: %s not found in %s.", pszTitle, pszFileName);
//	}
//
//	return bSucFound;
//}

//////////////////////////////////////////////////////////////////////
//BOOL TxtDataGet(const char *pszFileName, const char *pszTitle, int& nData, BOOL bCritical/*=false*/)
//{
//	if (!pszFileName || !pszTitle)
//		return false;
//
//	FILE* fp = CQfopen(pszFileName, "r");
//	if (!fp)
//		return false;
//
//	char szFormat[256]	="";
//	_snprintf(szFormat, sizeof(szFormat) - 1, "%s=%s\n", pszTitle, "%d");
//	szFormat[sizeof(szFormat) - 1] = 0;
//
//	bool bSucFound	=false;
//	while(true)
//	{
//		char szLine[1024] = "";
//		if (NULL == fgets(szLine, sizeof(szLine) - 1, fp))
//		{
//			break;
//		}
//
//		if (sscanf(szLine, szFormat, &nData))
//		{
//			bSucFound	=true;
//			break;
//		}
//	}
//
//	fclose(fp);
//	
//	if (bCritical && !bSucFound)
//		LOGERROR("Error: %s not found in %s.", pszTitle, pszFileName);
//
//	return bSucFound;
//}

//////////////////////////////////////////////////////////////////////
DWORD TimeGet(void)
{
//#if CQ_PLATFORM == CQ_PLATFORM_ANDROID
	timeb t;
    ftime(&t);
    return static_cast<DWORD>(1000 * t.time + t.millitm);

//#endif	
	
	//return timeGetTime();
}
//////////////////////////////////////////////////////////////////////
//DWORD SysTimeGet(void)
//{
//	time_t long_time;
//	time( &long_time );                /* Get time as long integer. */
//
//	struct tm *pTime;
//	pTime = localtime( &long_time ); /* Convert to local time. */
//
//	DWORD dwTime	=pTime->tm_hour*100 + pTime->tm_min;
//	return dwTime;
//}

/////////////////////////////////////////////////////////////////////////////
const int MAX_LOGMSG = 3;
//char g_setMsg[MAX_LOGMSG][1024] = { "", "", "" };
//DWORD g_dwMsgPt = 0;

/////////////////////////////////////////////////////////////////////////////
#ifdef CQ_IPAD_REMOVE
void DebugMsg (const char* fmt, ...)
{
    char szMsg[1024];
    _vsnprintf( szMsg, sizeof(szMsg) - 1, fmt, (char*) ((&fmt)+1) );
	szMsg[sizeof(szMsg) - 1] = 0;
	strcat(szMsg, "\n");

	::OutputDebugString(szMsg);
}
#endif // CQ_IPAD_REMOVE

//////////////////////////////////////////////////////////////////////
//int	RandGet(int nMax, BOOL bRealRand)
//{
//	if(nMax == 0)
//		return 0;
//	if (bRealRand)
//		::srand( (unsigned)TimeGet() );
//
//	return ::rand()%nMax;
//}

//////////////////////////////////////////////////////////////////////
#ifdef CQ_IPAD_REMOVE
DWORD Str2ID (const char* str)
{
	DWORD dwHash = 0;
	while (*str)
		dwHash = (dwHash << 5) + dwHash + *str++;
	
	return dwHash;	
}
#endif // CQ_IPAD_REMOVE

/*
int mystricmp(const char *str1,const char *str2)
{
	const char *p1 = NULL;
	const char *p2 = NULL;
	int  i = 0;
	int len = 0;

	if(str1 == NULL)
	{ 
		if(str2 != NULL) 
		{
			return -1;
		}

		if(str2 == NULL) 
		{
			return 0;
		}
	}

	p1 = str1;
	p2 = str2;
	len = (strlen(str1)<strlen(str2))? strlen(str1):strlen(str2);

	for(i=0; i<len; i++)
	{
		if(toupper(*p1)==toupper(*p2))
		{ 
			p1++;
			p2++;
		}
		else
		{
			return toupper(*p1)-toupper(*p2);
		}
	}

	return strlen(str1)-strlen(str2);
}*/


//////////////////////////////////////////////////////////////////////
//void	RepairString	(unsigned char* pszString)
//{
//	if (true)
//		return;
//	
//	const unsigned char VALID_CHAR = '?';
//
//	if (!pszString)
//		return;
//
//	int nLen	=strlen((const char*)pszString);
//	for (int i=0; i < nLen; i++)
//	{
//		unsigned char c	=(unsigned char)pszString[i];
//
//		if (c >= 0x81 && c <= 0xfe)
//		{
//			// the last char is cut improperly
//			if (i+1 >= nLen)
//			{
//				pszString[i] = VALID_CHAR;
//				continue;
//			}
//
//			// special case
//			{
//				if (0xa1 == pszString[i] && 0xa1 == pszString[i+1])
//				{
//					pszString[i]	= VALID_CHAR;
//					pszString[i+1]	= VALID_CHAR;
//
//					i++;
//					continue;
//				}
//
//				/*
//				if (pszString[i] >= 0xa4 && pszString[i] <= 0xa9)
//				{
//					pszString[i]	= VALID_CHAR;
//					pszString[i+1]	= VALID_CHAR;
//
//					i++;
//					continue;
//				}
//				*/
//			}
//			
//			// the second char is outof range
//			unsigned char c2	=(unsigned char)pszString[i+1];
//			if (c2 < 0x40 && c2 > 0x7e && c2 < 0x80 && c2 > 0xfe)
//			{
//				pszString[i]	= VALID_CHAR;
//				pszString[i+1]	= VALID_CHAR;
//
//				i++;
//				continue;
//			}
//			else
//				i++;
//		}
//		else
//		{
//			if (c == 0x80)
//			{
//				pszString[i] = VALID_CHAR;
//			}
//		}
//	}
//}

/*
// =====================================================================================================================
//    在字符串中从第3个参数位置起开始查找指定ASCII字符出现的第一个位置
// =====================================================================================================================
int StrFindAsciiChar(const char *pSrc, char cFind, int nPos, const char *pszVersionInfo)
{
	if (!pSrc || nPos < 0 || !pszVersionInfo) {
		return -1;
	}

	for (int i = 0; pSrc[i] != '\0'; ++i) {
		if (i < nPos) {
			continue;
		} else if (pSrc[i] < 0) {

			// 非ASCII字符,如果不是单字节字符集，就跳过一个字符查找
			if (mystricmp(pszVersionInfo, "English") == 0 || mystricmp(pszVersionInfo, "French") == 0
			|| mystricmp(pszVersionInfo, "German") == 0 || mystricmp(pszVersionInfo, "Spanish") == 0
			|| mystricmp(pszVersionInfo, "Arabic") == 0 || 0 == mystricmp(pszVersionInfo, "Russia")
			|| 0 == mystricmp(pszVersionInfo, "Thai") || 0 == mystricmp(pszVersionInfo, "Vietnam")
			|| 0 == mystricmp(pszVersionInfo, "Brazil")) {
				continue;
			} else {
				++i;
				continue;
			}
		} else if (pSrc[i] == cFind) {
			return i;
		}
	}

	return -1;
}*/

/*
// ============================================================================
//    lpszText 源字符串;
//    nNumPerLine 一行要显示的字符数;
//    strArray 折行后的子串集;
//    pszVersionInfo 版本;
//    cKey 特殊字符,遇到要在单词内折行时，外文版本会回逆到这个特殊字符上;
//    bCutDBCSLeadByte = true 表示半个汉字归到下一行;
//    bEmotionType 是否表情，表情由“#08”组成;
// ============================================================================
int SplitText2MLine(const char *lpszText,
					const char *lpszFont,
					int iFontSize,
					int nPixelPerLine,
					std::vector<std::string> *pvecString,
					const char *pszVersionInfo,
					char cKey,
					bool bCutDBCSLeadByte,
					bool bEmotionType)
{
	if (!lpszText) {
		return 0;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nTextLen = strlen(lpszText);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!pvecString || nTextLen == 0 || nPixelPerLine == 0) {
		return 0;
	}

	pvecString->clear();

	// 大部分情况下并不需要进入下面多个for的高复杂度算法，在此做一个快速返回判断;
	// 阿拉伯的最后一个字符可能拖长，导致删除最后一个字符后长度反而更长
	if (!strstr(lpszText, "\\n")) {
		C3_SIZE sizeText;

		sizeText = CMyBitmap::CalcuTextExtentCommon(lpszText, lpszFont, iFontSize, NULL, 21);

		// 如果长度够，直接返回
		if (sizeText.iWidth < nPixelPerLine) {
			(*pvecString).push_back(lpszText);
			
			return (*pvecString).size();
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~
	int nDescLine = 0;
	int nCharIndex[512] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~~~

	nCharIndex[0] = 0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool bNewLine = false;
	int nLineNum = 0;
	C3_SIZE sizeSubStr = {0, 0};
	C3_SIZE FontSize;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	CMyBitmap::GetFontSize(FontSize);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nPixelWidth = (nPixelPerLine > 2 * FontSize.iWidth + 1) ? nPixelPerLine : (2 * FontSize.iWidth + 1);
	int i = 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (bEmotionType) {
		sizeSubStr = CMyBitmap::CalcuTextExtentCommon("#30", lpszFont, iFontSize, NULL, 21);
		nPixelWidth = nPixelWidth > sizeSubStr.iWidth ? nPixelWidth : sizeSubStr.iWidth;
	}

	for (i = 0; i < nTextLen; ++i) {
		if (IsDBCSLeadByte(lpszText, i)) {
			nLineNum += 2;
			++i;
		} else {
			++nLineNum;
		}

		if (lpszText[i] == '\n') {
			nLineNum = 0;
			++nDescLine;
			nCharIndex[nDescLine] = i + 1;
			if (!bNewLine) {
				++nDescLine;
			} else {
				nCharIndex[nDescLine - 1] = i + 1;
			}

			nCharIndex[nDescLine] = i + 1;
			bNewLine = true;
			continue;
		}

		//~~~~~~~~~~~~~~~~~~~~
		char szSubStr[256] = "";
		//~~~~~~~~~~~~~~~~~~~~

		strncpy(szSubStr, lpszText + nCharIndex[nDescLine], nLineNum);
		szSubStr[nLineNum] = '\0';
		// 计算到目前为止的字符串的宽度，以像素计
		sizeSubStr = CMyBitmap::CalcuTextExtentCommon(szSubStr, lpszFont, iFontSize, NULL, 21);

		if (sizeSubStr.iWidth > nPixelWidth) {

			// 保证一个单词不被拆分
			if (mystricmp(pszVersionInfo, "English") == 0
			|| mystricmp(pszVersionInfo, "French") == 0
			|| mystricmp(pszVersionInfo, "German") == 0
			|| mystricmp(pszVersionInfo, "Spanish") == 0
			|| mystricmp(pszVersionInfo, "Arabic") == 0
			|| 0 == mystricmp(pszVersionInfo, "Russia")
			|| 0 == mystricmp(pszVersionInfo, "Thai")
			|| 0 == mystricmp(pszVersionInfo, "Vietnam")
			|| 0 == mystricmp(pszVersionInfo, "Brazil")) {

				// Search the last word
				for (int j = i; j > nCharIndex[nDescLine]; --j) {
					if (lpszText[j] == cKey) {
						strncpy(szSubStr, lpszText + nCharIndex[nDescLine], j - nCharIndex[nDescLine]);
						szSubStr[j - nCharIndex[nDescLine]] = '\0';
						sizeSubStr = CMyBitmap::CalcuTextExtentCommon(szSubStr, lpszFont, iFontSize, NULL, 21);
						nLineNum -= (i - j);
						i = j;
						break;
					}
				}
			}

			//~~~~~~~~~
			int nPos = 0;		// 下一行的起始位置
			//~~~~~~~~~

			// 保持一个汉字不被拆分
			if (IsDBCSLeadByte(lpszText, i - 1)) {
				if (bCutDBCSLeadByte) {

					// 半个汉字归下一行
					nPos = i - 1;
				} else {

					// 半个汉字归本行
					nPos = i + 1;
				}
			} else {
				nPos = i;
			}

			// 保持一个表情不被拆分
			if (bEmotionType) {

				// lpszText[i] == '#'的时候不用考虑表情的截取
				// 为数字的时候，要考虑前面是否为表情
				if (IsDigit(lpszText[i])) {
					if (IsDigit(lpszText[i - 1])
						&& lpszText[i - 2] == '#') {
							nPos -= 2;
					} else if (i + 1 < static_cast<int>(strlen(lpszText))
						 && lpszText[i - 1] == '#'
						 && IsDigit(lpszText[i + 1])) {
							nPos -= 1;
					}
				}
			}

			if (nPos < i) {
				nLineNum = i - nPos + 1;
			} else {
				nLineNum = 0;
			}

			if (!bNewLine) {
				++nDescLine;
			} else {
				bNewLine = false;
			}

			// nCharIndex[...]放的是一行的起始下标
			nCharIndex[nDescLine] = nPos;
		}
	}

	if (sizeSubStr.iWidth < nPixelWidth && nLineNum != 0 || i == nTextLen) {
		if (!bNewLine) {
			++nDescLine;
			bNewLine = false;
		}
		nCharIndex[nDescLine] = i;
	}

	//~~~~~~~~~~~~~~~~~~
	char szTemp[256] = "";
	//~~~~~~~~~~~~~~~~~~

	for (i = 0; i < nDescLine; ++i) {
		strncpy(szTemp, lpszText + nCharIndex[i], nCharIndex[i + 1] - nCharIndex[i]);
		szTemp[nCharIndex[i + 1] - nCharIndex[i]] = '\0';
		if (szTemp[nCharIndex[i + 1] - nCharIndex[i] - 2] == 0x0d
		&& szTemp[nCharIndex[i + 1] - nCharIndex[i] - 1] == 0x0a) {
			szTemp[nCharIndex[i + 1] - nCharIndex[i] - 2] = '\0';
		}

		if (' ' != cKey) {
			TqReplaceString(szTemp, cKey, ' ');
		}
		(*pvecString).push_back(szTemp);
	}

	return(*pvecString).size();
}

void SeparateNumber(char *pszNumber, int nMaxLen)
{
	if (!pszNumber || nMaxLen <= 0) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~
	int nLen = strlen(pszNumber);
	//~~~~~~~~~~~~~~~~~~~~~~~~~

	if (nLen > 3 && nLen < 7) {

		//~~~~~~~~~~~~~~~~~~~~~~~~
		std::string tmp = pszNumber;
		//~~~~~~~~~~~~~~~~~~~~~~~~

		tmp.insert(tmp.begin() + nLen - 3, ',');
		strncpy(pszNumber, tmp.c_str(), nMaxLen);
	} else if (nLen >= 7) {

		//~~~~~~~~~~~~~~~~~~~~~~~~
		std::string tmp = pszNumber;
		//~~~~~~~~~~~~~~~~~~~~~~~~

		tmp.insert(tmp.begin() + nLen - 6, ',');
		tmp.insert(tmp.begin() + nLen - 2, ',');
		strncpy(pszNumber, tmp.c_str(), nMaxLen);
	} else if (nLen >= 10) {

		//~~~~~~~~~~~~~~~~~~~~~~~~
		std::string tmp = pszNumber;
		//~~~~~~~~~~~~~~~~~~~~~~~~

		tmp.insert(tmp.begin() + nLen - 9, ',');
		tmp.insert(tmp.begin() + nLen - 5, ',');
		tmp.insert(tmp.begin() + nLen - 1, ',');
		strncpy(pszNumber, tmp.c_str(), nMaxLen);
	}
}
*/
// =====================================================================================================================
// =======================================================================================================================
bool ReadRegKey(LPCSTR strMainKey, LPCSTR strKeyName, LPVOID KeyData, DWORD dwDataSize)
{
#ifdef CQ_IPAD_REMOVE
	//~~~~~~~~~~
	LONG lRtn;
	HKEY hMainKey;
	//~~~~~~~~~~

	lRtn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strMainKey, 0, KEY_READ, &hMainKey);
	if (lRtn == ERROR_SUCCESS) {

		//~~~~~~~~~~~~~
		DWORD dwType = 0;
		//~~~~~~~~~~~~~

		::RegQueryValueEx(hMainKey, strKeyName, NULL, &dwType, (LPBYTE) KeyData, &dwDataSize);
		::RegCloseKey(hMainKey);
		return true;
	} else {
		::RegCloseKey(hMainKey);
		return false;
	}
#else
	return false;
#endif // CQ_IPAD_REMOVE
}
/*
// =====================================================================================================================
// =======================================================================================================================
bool IsFileExist(const char* lpcszPathFilename)
{
#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	//~~~~~~~~~~~~~~~~~~~~~~~~~
	bool bExist = false;
	HANDLE Handle;
	WIN32_FIND_DATA struFindData;
	//~~~~~~~~~~~~~~~~~~~~~~~~~

	Handle = FindFirstFile(lpcszPathFilename, &struFindData);
	if (Handle != INVALID_HANDLE_VALUE) {
		FindClose(Handle);
		bExist = true;
	}

	return(bExist);
#else
	int result = access(lpcszPathFilename, R_OK);
	return result == 0;
#endif
}

// =====================================================================================================================
// =======================================================================================================================
bool SHFileOpDelete(const char *pszPath)
{
#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	SHFILEOPSTRUCT FileOp = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	FileOp.pFrom = pszPath;
	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;
	return SHFileOperation(&FileOp) == 0;
#else
	return false;
#endif
}*/
/*
// =====================================================================================================================
// =======================================================================================================================
bool IsLocalBind(const char *pszAccount, int nChargesType)
{
	if (NULL == pszAccount || strlen(pszAccount) <= 0) {
		return false;
	}

	CHECKF(nChargesType >= 0 && nChargesType < SERVER_CHARGE_MAX);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const int TQND_HEAD_SIZE = 16;
	char szRegDir[MAX_PATH] = "SOFTWARE\\Tqdigital\\Conquer\\Accounts\\";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	switch (nChargesType) {
	case SERVER_FREE:	break;
	case SERVER_COST:	strncat(szRegDir, "$", sizeof(szRegDir) - 1); break;
	}

	strncat(szRegDir, pszAccount, sizeof(szRegDir) - 1);

	//~~~~~~~~~~~~~~~~~~~~~
	char szFile[256] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~

	if (!ReadRegKey(szRegDir, "tqDir", szFile, sizeof(szFile))) {
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char szTextValue[TQND_HEAD_SIZE] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!ReadRegKey(szRegDir, "tqValue", szTextValue, TQND_HEAD_SIZE)) {
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	FILE *fp = CQfopen(szFile, "r");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == fp) {
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char szTqndValue[TQND_HEAD_SIZE] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	fread(szTqndValue, TQND_HEAD_SIZE, 1, fp);
	if (0 != strcmp(szTextValue, szTqndValue)) {
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}
*/
/*
//////////////////////////////////////////////////////////////////////
// 探测字符串中第idx个字符是否是DBCS的LEAD BYTE
BOOL IsDBCSLeadByte	(const char* pszString, int idx)
{
	return CMyBitmap::IsDBCSLeadByte(pszString, idx);
}*/

//////////////////////////////////////////////////////////////////////
void TqReplaceString(char* pszString, char cFind, char cReplace)
{
	if(!pszString)
		return;
	DWORD dwLength = strlen(pszString);
	if (dwLength > 1024)
		return;
	for(DWORD i = 0; i < dwLength; i ++)
	{
		if(pszString[i] == cFind)
			pszString[i] = cReplace;
	}
}

bool TqReplaceString(char* pszSource, int nSize, const char* pszFind, const char* pszReplace)
{
	if (!pszSource || nSize <= 0 || !pszFind || !pszReplace || strlen(pszFind) <= 0) {
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nLenFind = strlen(pszFind);
	int nLenReplace = strlen(pszReplace);
	size_t pos = 0;
	std::string strSource = pszSource;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	while (true) {
		pos = strSource.find(pszFind, pos);

		if (pos == std::string::npos) {
			break;
		}

		strSource.replace(pos, nLenFind, pszReplace);
		pos += nLenReplace;
	}

	if (nSize <= static_cast<int>(strSource.size())) {
		return false;
	} else {
		strncpy(pszSource, strSource.c_str(), nSize);
		pszSource[nSize - 1] = 0;
	}

	return true;
}

// =====================================================================================================================
// =======================================================================================================================
bool TqReplaceString(std::string &str, const char *pszFind, const char *pszReplace)
{
	if (!pszFind || strlen(pszFind) <= 0) {
		return false;
	}

	if (!pszReplace) {
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nLenFind = strlen(pszFind);
	int nLenReplace = strlen(pszReplace);
	std::string::size_type sizeIndex = str.find(pszFind);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	while (sizeIndex != std::string::npos) {
		str.replace(sizeIndex, nLenFind, pszReplace);
		sizeIndex = str.find(pszFind, sizeIndex + nLenReplace);
	}

	return true;
}

// =====================================================================================================================
// =======================================================================================================================
// bool TqReplaceString(std::wstring &str, const wchar_t *pszFind, const wchar_t *pszReplace)
// {
// 	if (!pszFind || wcslen(pszFind) <= 0) {
// 		return false;
// 	}
// 
// 	if (!pszReplace) {
// 		return false;
// 	}
// 
// 	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	int nLenFind = wcslen(pszFind);
// 	int nLenReplace = wcslen(pszReplace);
// 	std::wstring::size_type sizeIndex = str.find(pszFind);
// 	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
// 	while (sizeIndex != std::string::npos) {
// 		str.replace(sizeIndex, nLenFind, pszReplace);
// 		sizeIndex = str.find(pszFind, sizeIndex + nLenReplace);
// 	}
// 
// 	return true;
// }
/*
// =====================================================================================================================
// =======================================================================================================================
void Split(const std::string &strText, std::vector<std::string> &vecString, const char *pszSplitChar)
{
	if (!pszSplitChar) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nSplitCharLen = strlen(pszSplitChar);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (0 == nSplitCharLen) {
		return;
	}

	vecString.clear();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	char szDestribe[1024] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	strncpy(szDestribe, strText.c_str(), sizeof(szDestribe) - 1);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nIndex = 0;
	const char *pBeg = szDestribe;
	const char *pPos = strstr(pBeg, pszSplitChar);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	while (pPos) {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		char szTemp[_MAX_STRING] = { 0 };
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		strncpy(szTemp, pBeg, min((size_t)(pPos - pBeg), sizeof(szTemp) - 1));
		vecString.push_back(szTemp);
		pBeg = pPos + nSplitCharLen;
		pPos = strstr(pPos + nSplitCharLen, pszSplitChar);
	}

	vecString.push_back(pBeg);
}
*/
// =====================================================================================================================
// =======================================================================================================================
UINT GetMsgBoxStyle(UINT nTypeOrg, BOOL bArabicLike)
{
#ifdef CQ_IPAD_REMOVE
	if (bArabicLike) {
		return nTypeOrg | MB_RIGHT | MB_RTLREADING;
	}
#endif // CQ_IPAD_REMOVE

	return nTypeOrg;
}

// =====================================================================================================================
// =======================================================================================================================
DWORD ColorCmp(DWORD dwColor1, DWORD dwColor2)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nA1 = (dwColor1 >> 24) & 0xff;
	int nR1 = (dwColor1 >> 16) & 0xff;
	int nG1 = (dwColor1 >> 8) & 0xff;
	int nB1 = dwColor1 & 0xff;
	int nA2 = (dwColor2 >> 24) & 0xff;
	int nR2 = (dwColor2 >> 16) & 0xff;
	int nG2 = (dwColor2 >> 8) & 0xff;
	int nB2 = dwColor2 & 0xff;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	return
		(
			(nA1 - nA2) * (nA1 - nA2) + (nR1 - nR2) * (nR1 - nR2) + (nG1 - nG2) * (nG1 - nG2) + (nB1 - nB2) *
				(nB1 - nB2)
		);
}


//void LogSave(const char* pszLog)
//{
//	char buffer[1024] = "";
//    vsprintf( buffer, fmt, (char*) ((&fmt)+1) );
//	buffer[sizeof(buffer) - 1] = '\0';
//
//	LOGERROR(buffer);
//	SendErrorLogToHttp(strLogBuf.c_str());
//}

//////////////////////////////////////////////////////////////////////
//DWORD GetDate()
//{
//	time_t t = time(NULL);
//	struct tm* pTime = localtime( &t );
//	return pTime->tm_mday;	
//}

//////////////////////////////////////////////////////////////////////
void SafeStrcpy	(char* pszTarget, const char* pszSource, int nBufSize)
{
	if (!pszTarget || !pszSource || nBufSize <= 0)
		return;

	strncpy(pszTarget, pszSource, nBufSize);
	pszTarget[nBufSize - 1] = 0;
}

//////////////////////////////////////////////////////////////////////
// mouse functions
//////////////////////////////////////////////////////////////////////
static CMouseInfo infoMouse;
static CMouseInfo infoMyMouse;
int g_MouseX;
int g_MouseY;

void CQMouseInit(void)
{
	infoMouse.iEvent	=_MOUSE_NONE;
}

void CQMouseSet(int x, int y, int event)
{
	infoMouse.iEvent	=event;
	infoMouse.iPosX		=x;
	infoMouse.iPosY		=y;
}

int CQMouseCheck(int& iMouseX, int& iMouseY)
{
	iMouseX	=infoMouse.iPosX;
	iMouseY	=infoMouse.iPosY;
//	iMouseX = g_MouseX;
//	iMouseY = g_MouseY;
	return infoMouse.iEvent;
}
int MouseCheckNotConvert(int& iMouseX, int& iMouseY)
{
	iMouseX = g_MouseX;
	iMouseY = g_MouseY;
	return infoMouse.iEvent;
}

void CQMouseProcess(void)
{
	infoMouse.iEvent	=_MOUSE_NONE;
}

// =====================================================================================================================
// =======================================================================================================================
void MyMouseInit(void)
{
	infoMyMouse.iEvent = _MOUSE_NONE;
}

// =====================================================================================================================
// =======================================================================================================================
void MyMouseSet(int x, int y, int event)
{
	infoMyMouse.iEvent = event;
	infoMyMouse.iPosX = x;
	infoMyMouse.iPosY = y;
}

// =====================================================================================================================
// =======================================================================================================================
int MyMouseCheck(int &iMouseX, int &iMouseY)
{
	iMouseY = infoMyMouse.iPosX;
	iMouseY = infoMyMouse.iPosY;
	return infoMyMouse.iEvent;
}

// =====================================================================================================================
// =======================================================================================================================
void MyMouseProcess(void)
{
	infoMyMouse.iEvent = _MOUSE_NONE;
}


// =====================================================================================================================
// =======================================================================================================================
bool s_CheckFormat(const char *pszFormat, const char **ppszEnd, MY_SSCANF_FORMAT_DATA *pFormatData)
{
	if (!ppszEnd || !pFormatData || !pszFormat || *pszFormat == '\0') {
		return false;
	}

	// 检查'*'符号，可选
	if (*pszFormat == '*') {
		++pszFormat;
		pFormatData->bSkip = true;
	} else {
		pFormatData->bSkip = false;
	}

	// 检查宽度，可选。宽度是一个十进制正整数
	pFormatData->iWidth = 0;
	while (*pszFormat >= '0' && *pszFormat <= '9') {
		pFormatData->iWidth *= 10;
		pFormatData->iWidth += (*pszFormat - '0');
		++pszFormat;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 匹配"h"或者"l"或者"I64"或者"L"，可选 if (*pszFormat == 'h' || *pszFormat ==
	// 'l' || *pszFormat == 'L' || strncmp("I64",
	const char *arrModifiers[] = { "h", "l", "I64", "L" };
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	pFormatData->pszModifier = "";
	for (int i = 0; i < sizeof(arrModifiers) / sizeof(arrModifiers[0]); ++i) {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		const char *pszModifier = arrModifiers[i];
		size_t uLen = strlen(pszModifier);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (strncmp(pszFormat, pszModifier, uLen) == 0) {
			pFormatData->pszModifier = pszModifier;
			pszFormat += uLen;
			break;
		}
	}

	// 匹配类型，必须有此项内容
	switch (*pszFormat) {
	case 'e':
	case 'E':
	case 'f':
	case 'g':
	case 'G':
	case 'd':
	case 'i':
	case 'o':
	case 'x':
	case 'X':
	case 'u':
	case 'c':
	case 'C':
	case 's':
	case 'S':
		pFormatData->cType = *pszFormat;
		++pszFormat;
		break;
	default:
		return false;
		break;
	}

	*ppszEnd = pszFormat;
	return true;
}

// =====================================================================================================================
// =======================================================================================================================
void s_SkipSpace(const char *pszString, const char **ppszResult)
{
	if (!pszString || !ppszResult) {
		return;
	}

	for (;;) {

		//~~~~~~~~~~
		bool bIsSpace;
		//~~~~~~~~~~

		switch (*pszString) {
		case ' ':
		case '\t':
		case '\n':
			bIsSpace = true;
			break;
		default:
			bIsSpace = false;
			break;
		}

		if (bIsSpace) {
			++pszString;
		} else {
			break;
		}
	}

	*ppszResult = pszString;
}

#if CQ_PLATFORM == CQ_PLATFORM_ANDROID
size_t mbstowcs(wchar_t *, const char *, size_t)
{
};

size_t wcstombs(char *, const wchar_t *, size_t)
{
};

int GetCursorPos(LPPOINT lpPoint)
{
	return 0;
}

void itoa(unsigned long val, char *buf, unsigned radix)   
{   
	char   *p = NULL;
	char   *firstdig = NULL;
	char   temp = NULL;
	unsigned   digval;
	p = buf;
	firstdig = p;
	
	do
	{
		digval  =  (unsigned)(val % radix);   
		val /= radix;

		if (digval> 9)
		{
			*p++ = (char)(digval - 10 + 'a');
		}
		else
		{
			*p++ = (char)(digval + '0');
		}
	} while (val > 0);

	*p-- = '\0';

	do
	{
		temp = *p;
		*p  = *firstdig;
		*firstdig = temp;
		--p;
		++firstdig;
	} while (firstdig < p);
}
#endif

/*
// TODO: IPAD:: test it
// 多字节字符串转为宽字符串
const std::wstring MyConvertString(const std::string& str)
{
	if (str.empty()) {
		return std::wstring();
	}

	size_t bufsize = str.length();
	std::vector<wchar_t> buf(bufsize);
	size_t newLength = mbstowcs(&buf[0], str.c_str(), bufsize);
	return std::wstring(&buf[0], &buf[0] + newLength);
}

// TODO: IPAD:: test it
// 宽字符串转为多字节字符
const std::string MyConvertString(const std::wstring& str)
{
	if (str.empty()) {
		return std::string();
	}

	size_t bufsize = str.length() * 2;
	std::vector<char> buf(bufsize);
	size_t newLength = wcstombs(&buf[0], str.c_str(), bufsize);
	return std::string(&buf[0], &buf[0] + newLength);
}*/

// ======================================================================================================================================================
// TODO: IPAD:: ipad add
//
//class CMemoryAlloc
//{
//public:
//	CMemoryAlloc();
//	~CMemoryAlloc();
//
//	void* Alloc(size_t size);
//	void Free(void* ptr);
//
//private:
//	typedef boost::pool<boost::default_user_allocator_malloc_free> MemoryPool;
//	static const size_t s_MemoryAlign = 4;		// 4字节对齐
//	static const size_t s_MaxBlockInPool = 512;	// 小于512字节则使用内存池，否则直接使用malloc/free
//	static const size_t s_PoolCount = s_MaxBlockInPool / s_MemoryAlign;
//	
//	struct CHUNK_INFO {
//		size_t size;
//	};
//
//	CHUNK_INFO* RealAlloc(size_t size);
//
//	MemoryPool* m_arrPools[s_PoolCount];
//};
//
//CMemoryAlloc::CMemoryAlloc()
//{
//	for (size_t i = 0; i < s_PoolCount; ++i) {
//		m_arrPools[i] = static_cast<MemoryPool*>(malloc(sizeof(MemoryPool)));
//		if (!m_arrPools[i]) {
//			throw std::bad_alloc();
//		}
//
//		new(m_arrPools[i]) MemoryPool(i * s_MemoryAlign);
//	}
//}
//
//CMemoryAlloc::~CMemoryAlloc()
//{
//	for (size_t i = 0; i < s_PoolCount; ++i) {
//		m_arrPools[i]->~MemoryPool();
//	}
//}
//
//void* CMemoryAlloc::Alloc(size_t size)
//{
//	// 0字节视为1字节
//	if (size == 0) {
//		size = 1;
//	}
//
//	// 在所分配内存前面加上CHUNK_INFO，并注意字节对齐
//	const size_t more = (sizeof(CHUNK_INFO) + s_MemoryAlign - 1) / s_MemoryAlign * s_MemoryAlign;
//	size += more;
//
//	// 分配。若失败，则抛出异常，不会返回NULL
//	CHUNK_INFO* pChunk = RealAlloc(size);
//
//	// 记录CHUNK_INFO
//	pChunk->size = size;
//
//	// 返回
//	return reinterpret_cast<char*>(pChunk) + more;
//}
//
//void CMemoryAlloc::Free(void* ptr)
//{
//	if (!ptr) {
//		return;
//	}
//
//	const size_t more = (sizeof(CHUNK_INFO) + s_MemoryAlign - 1) / s_MemoryAlign * s_MemoryAlign;
//	CHUNK_INFO* pChunk = reinterpret_cast<CHUNK_INFO*>(static_cast<char*>(ptr) - more);
//	if (pChunk->size >= s_MaxBlockInPool) {
//		free(ptr);
//		return;
//	}
//
//	size_t index = (pChunk->size + s_MemoryAlign - 1) / s_MemoryAlign;
//	MemoryPool*& pPool = m_arrPools[index];
//	pPool->free(pChunk);
//}
//
//CMemoryAlloc::CHUNK_INFO* CMemoryAlloc::RealAlloc(size_t size)
//{
//	// 较大内存，直接malloc
//	if (size >= s_MaxBlockInPool) {
//		void* ptr = malloc(size);
//		if (!ptr) {
//			throw std::bad_alloc();
//		}
//
//		return static_cast<CHUNK_INFO*>(ptr);
//	}
//
//	// 选择第index个pool
//	size_t index = (size + s_MemoryAlign - 1) / s_MemoryAlign;
//	MemoryPool*& pPool = m_arrPools[index];
//
//	// 采用pool分配内存
//	void* ptr = pPool->malloc();
//	if (!ptr) {
//		throw std::bad_alloc();
//	}
//
//	return static_cast<CHUNK_INFO*>(ptr);
//}
//
//static CMemoryAlloc* s_pMemoryAlloc = NULL;
//
//static boost::recursive_mutex& s_GetAllocMutex()
//{
//	static boost::recursive_mutex s_mutex;
//	return s_mutex;
//}
//
//static void EnsureMemoryAlloc()
//{
//	if (!s_pMemoryAlloc) {
//		CMemoryAlloc* pMemoryAlloc = static_cast<CMemoryAlloc*>(malloc(sizeof(CMemoryAlloc)));
//		if (!pMemoryAlloc) {
//			throw std::bad_alloc();
//		}
//
//		new(pMemoryAlloc) CMemoryAlloc;
//		s_pMemoryAlloc = pMemoryAlloc;
//	}
//}
/*
void* operator new (size_t size)
{
	boost::recursive_mutex::scoped_lock lock(s_GetAllocMutex());
	EnsureMemoryAlloc();
	return s_pMemoryAlloc->Alloc(size);
}

void* operator new[] (size_t size)
{
	return operator new(size);
}

void operator delete(void* ptr)
{
	if (!ptr) {
		return;
	}

	boost::recursive_mutex::scoped_lock lock(s_GetAllocMutex());
	EnsureMemoryAlloc();
	s_pMemoryAlloc->Free(ptr);
}

void operator delete[](void* ptr)
{
	operator delete(ptr);
}
*/

// added by tw without implementation
void log_msg	(const char* fmt, ...) 
{

};

int code_convert (const char *from_charset, const char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	_snprintf(outbuf, outlen, "%s", inbuf);
	return inlen;
}
