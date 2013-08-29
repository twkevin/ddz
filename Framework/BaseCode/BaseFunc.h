
#ifndef _CQBASEFUNC_H
#define _CQBASEFUNC_H

#include "CQGlobal.h"

#include <assert.h>
#include <deque>
#include <list>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <sys/timeb.h>

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
#include <xstring>
#endif


const int _MAX_STRING	 = 256;
const int _MAX_LONG_STRING = 1024;
const int _MAX_NAMESIZE	 = 16;
const int _MAX_REGISTER_NAMESIZE = 11;
const int _MAX_MATCH_NAMESIZE = 50;
const int _MAX_MATCH_PRIZESIZE = 20;
const int _MAX_TEAMNAME_SIZE = 32;
const int _MAX_NAMESIZE_CLI = 32;
const int _MAX_FULLNAMESIZE = 64;
const int _MAX_LONGNAMESIZE = 36;
const int _MAX_TITLESIZE = 128;
const int _MAX_ITEM_NAMESIZE = 36;
const int _MAX_MAGIC_NAMESIZE = 36;
const int _MAX_MAP_NAMESIZE = 36;
const int _MAX_NPC_NAMESIZE = 36;
const int _MAX_SYNDICATE_NAMESIZE = 36;
const int _MAX_MACSIZE = 41;
const int _MAX_SYNENEMYSIZE = 5;		// “ªπ≤5∏ˆµ–∂‘∞Ô≈…ø’º‰
const int _MAX_SYNALLYSIZE = 5;			// “ªπ≤5∏ˆΩ·√À∞Ô≈…ø’º‰
const int _EMOTION_WIDTH = 21;
const int _MAX_USER_ATTRIBUTE = 128;	// ÕÊº“◊¥Ã¨ ˝£¨±£÷§Œ™32µƒ±∂ ˝
const int _MAX_CLIENT_USER_STATUS = 16;	// øÕªß∂À◊‘º∫Œ¨ª§µƒ◊¥Ã¨◊Ó¥Û÷µ
const int _MAX_SESSIONID = 40;
const int _MAX_COOORDSERIAL = 40;
const int _MAX_USER_HEAD_PATH = 50;

//hy
const int	MAX_USERNAME_SIZE = 15;					// ÕÊº“√˚◊÷◊Ó≥§Œ™15∏ˆ(ÕÊº“√˚◊÷∆ﬂ∏ˆ∞ÎA)
const int	MAX_MATCH_PRIZE_NAMESIZE = 15;
const int	PRIZE_MAX_NUM = 10;
const int	INT_INITVALUE = -1;

// ŒÔ∆∑acttype£¨÷˜“™”Îπ‚–ßœ‘ æ”–πÿ
const int ACTTYPE_NONE = 0;
const int ACTTYPE_FIRE = 1;
const int ACTTYPE_RED = 2;
const int ACTTYPE_BLUE = 3;
const int ACTTYPE_ROYALBLUE = 4;
const int ACTTYPE_GEM = 5;
const int ACTTYPE_YELLOW = 6;

const float PI = 3.1415926f;

// #ifndef OBJID
// typedef unsigned int OBJID;
// const OBJID	ID_NONE = 0;
// #endif

const int	DEFAULT_EQUIP_COLOR = 3;
const int	EQUIP_COLOR_MIN = 3;
const int	EQUIP_COLOR_MAX = 9;

struct CMouseInfo{
	int iPosX, iPosY;
	int iEvent;
	DWORD dwDownTime;
};

struct ITEM_CONTROL_INFO
{
	int m_nAddLev;
	int m_nNum;
	bool m_bMySelf;
	BOOL m_bTotemReg;
	ITEM_CONTROL_INFO()
	:
	m_nAddLev(0),
	m_nNum(0),
	m_bMySelf(true),
	m_bTotemReg(FALSE) {
	}
};

struct FLASH_VAR_INFO {
	char szVariable[64];
	char szArgs[1024];
	FLASH_VAR_INFO(void)
	{
		szVariable[0] = szArgs[0] = 0;
	}
};

struct MY_SSCANF_FORMAT_DATA
{
	bool bSkip;
	int iWidth;
	const char* pszModifier;
	char cType;
};

// µ˛º” ˝◊÷µ»£¨”¶∏√œ‘ æ‘⁄∏Ò◊”µƒ ≤√¥Œª÷√£¨◊Û…œ£¨◊Ûœ¬£¨”“…œ£¨”“œ¬Ω«
enum {
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN,
};

#ifdef CQ_IPAD_REMOVE
#ifdef _DEBUG
 	#define _PM_COMMAND_
#endif
#endif // CQ_IPAD_REMOVE

// mouse event define
enum {
	_MOUSE_NONE			= 0,
	_MOUSE_CLICK		= 10,
	_MOUSE_DOWN			= 01,
	_MOUSE_HOLD			= 11,
	_MOUSE_RIGHTCLICK	= -10,
	_MOUSE_RIGHTDOWN	= -01,
	_MOUSE_RIGHTHOLD	= -11,
	_MOUSE_ON			= 20,
	_MOUSE_DOWN_WITH_SHIFT = 101,		// SHIFT+ Û±Í◊Ûº¸
};

enum { CRITICAL_FALSE = false, CRITICAL_TRUE = true };

enum
{
	_MAX_MSG_SERVERNAME_SIZE		= 17,
	_MAX_MSG_LOGIN_SERVERNAME_SIZE	= 33,
	_MAX_MSG_CD_TAG_SIZE			= 33,
	_MAX_MSG_ACCOUNT_SIZE			= 129,
	_MAX_MSG_PSW_SIZE				= 129,
};

enum
{
	NORMAL_ACCOUNTMSG,			// ‘≠ ºœ˚œ¢
	BINDCHECK_ACCOUNTMSG,		// ◊ﬂ∞Û∂®œ˚œ¢
	SOFTKEYBOARD_ACCOUNTMSG,	// ◊ﬂ»Ìº¸≈Ãœ˚œ¢
};

enum
{
	SERVER_FREE, // √‚∑—
	SERVER_COST, //  ’∑—
	SERVER_CHARGE_MAX,
};

//----------------------------------------------------------
void	SafeStrcpy(char* pszTarget, const char* pszSource, int nBufSize);
int		Double2Int	(double dValue);
DWORD	Str2ID		(const char* pszString);

BOOL	IniStrGet	(const char *pszFileName, const char *pszTitle, const char *pszSubTitle, char *pszStr, BOOL bCritical=false);
BOOL	IniDataGet	(const char *pszFileName, const char *pszTitle, const char *pszSubTitle, int &iData, BOOL bCritical=false);

BOOL	MemTxtLineGet	(const char* pBuf, DWORD dwBufSize, DWORD& dwOffset, char* szLine, DWORD dwLineSize);

BOOL	MemIniStrGet	(const char *pBuf, DWORD dwSize, const char *pszTitle, const char *pszSubTitle, char *pszStr, BOOL bCritical=false);
BOOL	MemIniDataGet	(const char *pBuf, DWORD dwSize, const char *pszTitle, const char *pszSubTitle, int &iData, BOOL bCritical=false);

//bool IsDigit(char c);

BOOL	TxtStrGet	(const char *pszFileName, const char *pszTitle, char *pszStr, BOOL bCritical=false);
BOOL	TxtDataGet	(const char *pszFileName, const char *pszTitle, int &iData, BOOL bCritical=false);

DWORD	TimeGet		(void);
DWORD	SysTimeGet  (void);
DWORD	GetDate		(void);

int		RandGet		(int nMax, BOOL bRealRand=false);

void	DebugMsg	(const char* fmt, ...);
void	log_msg	(const char* fmt, ...);
int		code_convert (const char *from_charset, const char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen);

void	CQMouseInit		(void);
void	CQMouseSet		(int x, int y, int event);
void	CQMouseProcess	(void);
int		CQMouseCheck		(int& iMouseX, int& iMouseY);
int MouseCheckNotConvert(int& iMouseX, int& iMouseY);

//  µœ÷ŒÔ∆∑¡¥Ω”µƒµ„ª˜
int MyMouseCheck(int &iMouseX, int &iMouseY);
void MyMouseInit(void);
void MyMouseProcess(void);
void MyMouseSet(int x, int y, int event);

void	KeyClearBuffer	(void);
int		KeyAppend		(void);
int		KeyGet			(void);
bool	KeyUnGet		(void);

//int mystricmp(const char *str1,const char *str2);
int StrFindAsciiChar(const char *pSrc, char cFind, int nPos, const char *pszVersionInfo);
void	RepairString	(unsigned char* pszString);
void	TqReplaceString	(char* pszString, char cFind, char cReplace);
bool TqReplaceString(char* pszSource, int nSize, const char* pszFind, const char* pszReplace);
bool TqReplaceString(std::string &str, const char *pszFind, const char *pszReplace);
//bool TqReplaceString(std::wstring &str, const wchar_t *pszFind, const wchar_t *pszReplace);
//BOOL	IsDBCSLeadByte	(const char* pszString, int idx);
void	MD5Encrypt		(char* bufResult, const char* pszString);
/*int		SplitText2MLine	(const char *lpszText, const char *lpszFont,
						int iFontSize, int nPixelPerLine, std::vector < std::string > *pvecString,
						const char *pszVersionInfo, char cKey = ' ',
						bool bCutDBCSLeadByte = true, bool bEmotionType = false);*/
void	SeparateNumber	(char *pszNumber, int nMaxLen);
//void Split(const std::string & strText, std::vector<std::string> &vecString, const char * pszSplitChar);

//bool IsFileExist(const char* lpcszPathFilename);
//bool IsLocalBind(const char *pszAccount, int nChargesType);
bool ReadRegKey(LPCSTR strMainKey, LPCSTR strKeyName, LPVOID KeyData, DWORD dwDataSize);
//bool SHFileOpDelete(const char * pszPath);

UINT GetMsgBoxStyle(UINT nTypeOrg, BOOL bArabicLike);
std::string GetEscapeNTStr(const char* pszString);
std::string GetFilterTildeStr(const char* pszString);

DWORD ColorCmp(DWORD dwColor1, DWORD dwColor2);

//void LogSave(const char* fmt, ...);

// ºÏ≤È «∑Ò¬˙◊„°∞[*][øÌ∂»][h|l|I64|L]¿‡–Õ°±µƒƒ£ Ω
bool s_CheckFormat(const char* pszFormat, const char** ppszEnd, MY_SSCANF_FORMAT_DATA* pFormatData);
// ∫ˆ¬‘ø’∏Ò
void s_SkipSpace(const char* pszString, const char** ppszResult);
// ◊‘∂®“ÂºÚµ•sscanf
int my_sscanf(const char* pszBuffer, const char* pszFormat, ...);

void GetDirectoryFontFace(std::string &strPath, const char* pszFontDirectory);

//----------------------------------------------------------
//typedef C3_POS CMyPos;
//
//typedef struct
//{
//	int t, l, r, b;
//}CMyRect;
//
//typedef C3_DIR CMy3DDir;
//
//typedef struct 
//{
//	int	x, y, z;
//}CMy3DPos;

typedef struct {
	float		fRadianX;			// ”“∑ΩœÚ÷·£¨À≥ ±’Î
	float		fRadianY;			// …œ∑ΩœÚ÷·£¨À≥ ±’Î
	float		fRadianZ;			// ƒ⁄∑ΩœÚ÷·£¨À≥ ±’Î
}CMy3DPose;



//typedef C3_SIZE CMySize;

inline void log_msg(const char *type,
					const char *str,
					const char *file,
					int line)
{
	
}

#ifndef SAFE_DELETE
//	#ifdef _DEBUG
		#define SAFE_DELETE(p) { if(p) delete p; p=NULL; }
//	#else
//		#define SAFE_DELETE(p) { if(p){ TRY{ delete p; } CATCH(...){ \
//			LOGERROR("CATCH: *** SAFE_DELETE(%s) in %s %d", #p, __FILE__, __LINE__); \
//		} p=NULL; }}
//	#endif
#endif

#ifndef SAFE_DELETE_EX
//	#ifdef _DEBUG
		#define SAFE_DELETE_EX(p) { if(p) delete [] p; p=NULL; }
//	#else
//		#define SAFE_DELETE_EX(p) { if(p){ TRY{ delete [] p; } CATCH(...){ \
//			LOGERROR("CATCH: *** SAFE_DELETE_EX(%s) in %s %d", #p, __FILE__, __LINE__); \
//		} p=NULL; }}
//	#endif
#endif

#undef	SAFE_RELEASE
#define SAFE_RELEASE(ptr)	{ if(ptr){ ptr->Release(); ptr = 0;}
// #define SAFE_RELEASE(ptr)	{ if(ptr){ TRY{ ptr->Release(); }CATCH(...){ \
// 			LOGERROR("CATCH: *** SAFE_RELEASE(%s) in %s %d", #ptr, __FILE__, __LINE__); \
// 		} ptr = 0; } }

//----------------------------------------------------------
//#ifndef MYASSERT
#ifdef _DEBUG
#define	MYASSERT(x) {if(!(x)) log_msg("ASSERT", #x, __FILE__, __LINE__), assert(!(#x)); }
#else
#define	MYASSERT(x)	{if(!(x)) log_msg("ASSERT", #x, __FILE__, __LINE__); }
#endif
//#endif

//----------------------------------------------------------
#ifdef _DEBUG
#define CHECK(x) \
	do \
	{ \
		if (!(x)) { \
			("CHECK", #x, __FILE__, __LINE__)  , assert(!(#x)); \
			return; \
		} \
	} while (0)
#else
#define CHECK(x) \
	do \
	{ \
		if (!(x)) { \
			("CHECK", #x, __FILE__, __LINE__); \
			return; \
		} \
	} while (0)
#endif

//----------------------------------------------------------
#ifdef _DEBUG
#define CHECKC(x) \
	if (!(x)) { \
		log_msg("CHECK", #x, __FILE__, __LINE__)  , assert(!(#x)) ; \
		continue; \
	}
#else
#define CHECKC(x) \
	if (!(x)) { \
		("CHECK", #x, __FILE__, __LINE__); \
		continue; \
	}
#endif

//----------------------------------------------------------
#ifdef _DEBUG
#define CHECKF(x) \
	do \
	{ \
		if (!(x)) { \
			("CHECKF", #x, __FILE__, __LINE__)  , assert(!(#x)) ; \
			return 0; \
		} \
	} while (0)
#else
#define CHECKF(x) \
	do \
	{ \
		if (!(x)) { \
			("CHECKF", #x, __FILE__, __LINE__); \
			return 0; \
		} \
	} while (0)
#endif

#ifdef _DEBUG
#define CHECKS(x,T) \
	do \
	{ \
		if (!(x)) { \
			("CHECKS", #x, __FILE__, __LINE__)  , assert(!(#x))  ; \
			return T(); \
		} \
	} while (0)
#else
#define CHECKS(x,T) \
	do \
	{ \
		if (!(x)) { \
			("CHECKS", #x, __FILE__, __LINE__); \
			return T(); \
		} \
	} while (0)
#endif

//----------------------------------------------------------
#ifndef IF_SUC
	#ifdef _DEBUG
		#define	IF_SUC(x)  if( ((x)) ? true : (  assert(!("IF_SUC: " #x)),  false ) )
	#else
		#define	IF_SUC(x)  if( ((x)) ? true : ( log_msg("°ÔIF_SUC(%s)°Ô failed in %s, %d", #x, __FILE__, __LINE__), false ) )
	#endif
#endif

#define IF_TRUE	IF_SUC
#define IF_YES	IF_SUC
#define IF_OK	IF_SUC

//----------------------------------------------------------
#ifndef IF_NOT
	#ifdef _DEBUG
		#define	IF_NOT(x)  if( (!(x)) ? (  assert(!("IF_NOT: " #x)),  1 ) : 0 )
	#else
		#define	IF_NOT(x)  if( (!(x)) ? ( ("°ÔIF_NOT(%s)°Ô in %s, %d", #x, __FILE__, __LINE__), 1 ) : 0 )
	#endif
#endif

#define LOGERROR //
//const std::wstring MyConvertString(const std::string& str);
//const std::string MyConvertString(const std::wstring& str);

// #ifndef max
// #define max(a,b)    (((a) > (b)) ? (a) : (b))
// #endif
// #ifndef min
// #define min(a,b)    (((a) < (b)) ? (a) : (b))
// #endif


#if CQ_PLATFORM == CQ_PLATFORM_ANDROID
size_t mbstowcs(wchar_t *, const char *, size_t);
size_t wcstombs(char *, const wchar_t *, size_t);
int GetCursorPos(LPPOINT lpPoint);
void itoa(unsigned long val, char *buf, unsigned radix);
#endif

// #include "BaseCode/StringFormat.h"
// #include "BaseCode/StringManager.h"
#endif

