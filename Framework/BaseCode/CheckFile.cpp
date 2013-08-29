
#include "CheckFile.h"

#ifdef CQ_IPAD_REMOVE
#define WINTRUST_ACTION_GENERIC_VERIFY_V2                       \
            { 0xaac56b,                                         \
              0xcd44,                                           \
              0x11d0,                                           \
              { 0x8c, 0xc2, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee } \
            }


typedef struct _WINTRUST_DATA
{
    DWORD           cbStruct;                   // = sizeof(WINTRUST_DATA)

    LPVOID          pPolicyCallbackData;        // optional: used to pass data between the app and policy
    LPVOID          pSIPClientData;             // optional: used to pass data between the app and SIP.

    DWORD           dwUIChoice;                 // required: UI choice.  One of the following.
#                       define      WTD_UI_ALL              1
#                       define      WTD_UI_NONE             2
#                       define      WTD_UI_NOBAD            3
#                       define      WTD_UI_NOGOOD           4

    DWORD           fdwRevocationChecks;        // required: certificate revocation check options
#                       define      WTD_REVOKE_NONE         0x00000000
#                       define      WTD_REVOKE_WHOLECHAIN   0x00000001

    DWORD           dwUnionChoice;              // required: which structure is being passed in?
#                       define      WTD_CHOICE_FILE         1
#                       define      WTD_CHOICE_CATALOG      2
#                       define      WTD_CHOICE_BLOB         3
#                       define      WTD_CHOICE_SIGNER       4
#                       define      WTD_CHOICE_CERT         5
    union
    {
        struct WINTRUST_FILE_INFO_      *pFile;         // individual file
        struct WINTRUST_CATALOG_INFO_   *pCatalog;      // member of a Catalog File
        struct WINTRUST_BLOB_INFO_      *pBlob;         // memory blob
        struct WINTRUST_SGNR_INFO_      *pSgnr;         // signer structure only
        struct WINTRUST_CERT_INFO_      *pCert;
    };

    DWORD           dwStateAction;                      // optional (Catalog File Processing)
#                       define      WTD_STATEACTION_IGNORE           0x00000000
#                       define      WTD_STATEACTION_VERIFY           0x00000001
#                       define      WTD_STATEACTION_CLOSE            0x00000002
#                       define      WTD_STATEACTION_AUTO_CACHE       0x00000003
#                       define      WTD_STATEACTION_AUTO_CACHE_FLUSH 0x00000004

    HANDLE          hWVTStateData;                      // optional (Catalog File Processing)

    WCHAR           *pwszURLReference;          // optional: (future) used to determine zone.

    // 17-Feb-1998 philh: added
    DWORD           dwProvFlags;
#       define WTD_PROV_FLAGS_MASK                      0x0000FFFF
#       define WTD_USE_IE4_TRUST_FLAG                   0x00000001
#       define WTD_NO_IE4_CHAIN_FLAG                    0x00000002
#       define WTD_NO_POLICY_USAGE_FLAG                 0x00000004
#       define WTD_REVOCATION_CHECK_NONE                0x00000010
#       define WTD_REVOCATION_CHECK_END_CERT            0x00000020
#       define WTD_REVOCATION_CHECK_CHAIN               0x00000040
#       define WTD_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT  0x00000080
#       define WTD_SAFER_FLAG                           0x00000100
#       define WTD_HASH_ONLY_FLAG                       0x00000200
#       define WTD_USE_DEFAULT_OSVER_CHECK              0x00000400
#       define WTD_LIFETIME_SIGNING_FLAG                0x00000800
#       define WTD_CACHE_ONLY_URL_RETRIEVAL             0x00001000 // affects CRL retrieval and AIA retrieval

    // 07-Jan-2004 tonyschr: added
    DWORD           dwUIContext;                // optional: used to determine action text in UI
#       define WTD_UICONTEXT_EXECUTE                    0
#       define WTD_UICONTEXT_INSTALL                    1
} WINTRUST_DATA, *PWINTRUST_DATA;


typedef struct WINTRUST_FILE_INFO_
{
    DWORD           cbStruct;                   // = sizeof(WINTRUST_FILE_INFO)

    LPCWSTR         pcwszFilePath;              // required, file name to be verified
    HANDLE          hFile;                      // optional, open handle to pcwszFilePath

    // 09-Dec-1997 pberkman: added
    GUID            *pgKnownSubject;            // optional: fill if the subject type is known.

} WINTRUST_FILE_INFO, *PWINTRUST_FILE_INFO;



typedef struct WINTRUST_CATALOG_INFO_
{
    DWORD           cbStruct;               // = sizeof(WINTRUST_CATALOG_INFO)

    DWORD           dwCatalogVersion;       // optional: Catalog version number
    LPCWSTR         pcwszCatalogFilePath;   // required: path/name to Catalog file

    LPCWSTR         pcwszMemberTag;         // required: tag to member in Catalog
    LPCWSTR         pcwszMemberFilePath;    // required: path/name to member file
    HANDLE          hMemberFile;            // optional: open handle to pcwszMemberFilePath

    // 30-Oct-1997 pberkman: added
    BYTE            *pbCalculatedFileHash;  // optional: pass in the calculated hash
    DWORD           cbCalculatedFileHash;   // optional: pass in the count bytes of the calc hash

    // 15-Jan-1998 pberkman: added
    // PCCTL_CONTEXT
    HANDLE  pcCatalogContext;       // optional: pass in to use instead of CatalogFilePath.

} WINTRUST_CATALOG_INFO, *PWINTRUST_CATALOG_INFO;



typedef struct CATALOG_INFO_
{
	DWORD cbStruct;
	WCHAR wszCatalogFile[255];
}CATALOG_INFO;
typedef HANDLE HCATADMIN ;
typedef HANDLE HCATINFO ;

typedef  BOOL (WINAPI *CRYPTCATADMINACQUIRECONTEXT)(HCATADMIN* phCatAdmin,const GUID* pgSubsystem,DWORD dwFlags);
typedef  BOOL (WINAPI *CRYPTCATADMINRELEASECONTEXT)(HCATADMIN hCatAdmin,DWORD dwFlags);
typedef  BOOL (WINAPI *CRYPTCATADMINCALCHASHFROMFILEHANDLE)(HANDLE hFile, DWORD* pcbHash, BYTE* pbHash, DWORD dwFlags);
typedef  BOOL (WINAPI *CRYPTCATCATALOGINFOFROMCONTEXT)(HCATINFO hCatInfo,CATALOG_INFO* psCatInfo,DWORD dwFlags);
typedef  BOOL (WINAPI *CRYPTCATADMINRELEASECATALOGCONTEXT)(HCATADMIN hCatAdmin,HCATINFO hCatInfo,DWORD dwFlags);
typedef  HCATINFO (WINAPI *CRYPTCATADMINENUMCATALOGFROMHASH)(HCATADMIN hCatAdmin,BYTE* pbHash,DWORD cbHash, DWORD dwFlags,HCATINFO* phPrevCatInfo);
typedef HRESULT (WINAPI *WINVERIFYTRUST)(HWND hWnd,GUID* pgActionID,LPVOID pWVTData);
CRYPTCATADMINACQUIRECONTEXT CryptCATAdminAcquireContext=NULL;
CRYPTCATADMINRELEASECONTEXT CryptCATAdminReleaseContext=NULL;
CRYPTCATADMINCALCHASHFROMFILEHANDLE CryptCATAdminCalcHashFromFileHandle=NULL;
CRYPTCATCATALOGINFOFROMCONTEXT CryptCATCatalogInfoFromContext=NULL;
CRYPTCATADMINRELEASECATALOGCONTEXT CryptCATAdminReleaseCatalogContext=NULL;
CRYPTCATADMINENUMCATALOGFROMHASH CryptCATAdminEnumCatalogFromHash=NULL;
WINVERIFYTRUST WinVerifyTrustX=NULL;

// =====================================================================================================================
// =======================================================================================================================
BOOL AnsitoUnicode(LPCSTR lpAnsi, LPWSTR lpBuff, INT nSize)
{
	//~~~~~~~~~~~~~~
	BOOL bRel = FALSE;
	//~~~~~~~~~~~~~~

	if (NULL == lpAnsi || NULL == lpBuff) {
		return bRel;
	}

	if (0 != MultiByteToWideChar(CP_ACP, 0, lpAnsi, -1, lpBuff, nSize)) {
		bRel = TRUE;
	}

	return bRel;
}

// =====================================================================================================================
// =======================================================================================================================
BOOL CheckFileTrust(LPCSTR lpFileName)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	BOOL bRet = FALSE;
	HCATADMIN hCatAdmin = NULL;
	DWORD dwCnt = MAX_PATH;
	WINTRUST_DATA stWinrstData;
	WINTRUST_FILE_INFO stWinstFileInfo;
	WINTRUST_CATALOG_INFO stWinstClogInfo;
	CATALOG_INFO stClogInfo;
	WCHAR wszFileName[MAX_PATH];
	BYTE byHash[MAX_PATH];
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ZeroMemory(byHash, MAX_PATH);
	ZeroMemory(wszFileName, MAX_PATH * sizeof(WCHAR));
	ZeroMemory(&stWinrstData, sizeof(WINTRUST_DATA));
	ZeroMemory(&stWinstFileInfo, sizeof(WINTRUST_FILE_INFO));
	ZeroMemory(&stWinstClogInfo, sizeof(WINTRUST_CATALOG_INFO));
	ZeroMemory(&stClogInfo, sizeof(CATALOG_INFO));

	if (FALSE == AnsitoUnicode(lpFileName, wszFileName, MAX_PATH)) {
		return FALSE;
	}

	if (FALSE == CryptCATAdminAcquireContext(&hCatAdmin, NULL, 0)) {
		return FALSE;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	HANDLE hFile = CreateFileW(wszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (INVALID_HANDLE_VALUE == hFile) {
		CryptCATAdminReleaseContext(hCatAdmin, 0);
		return FALSE;
	}

	CryptCATAdminCalcHashFromFileHandle(hFile, &dwCnt, byHash, 0);
	CloseHandle(hFile);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	LPWSTR pszMemberTag = new WCHAR[dwCnt * 2 + 1];
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for (DWORD dw = 0; dw < dwCnt; ++dw) {
		wsprintfW(&pszMemberTag[dw * 2], L"%02X", byHash[dw]);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	HCATINFO hCatInfo = CryptCATAdminEnumCatalogFromHash(hCatAdmin, byHash, dwCnt, 0, NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == hCatInfo) {
		stWinstFileInfo.cbStruct = sizeof(WINTRUST_FILE_INFO);
		stWinstFileInfo.pcwszFilePath = wszFileName;
		stWinstFileInfo.hFile = NULL;
		stWinstFileInfo.pgKnownSubject = NULL;

		stWinrstData.cbStruct = sizeof(WINTRUST_DATA);
		stWinrstData.dwUnionChoice = WTD_CHOICE_FILE;
		stWinrstData.pFile = &stWinstFileInfo;
		stWinrstData.dwUIChoice = WTD_UI_NONE;
		stWinrstData.fdwRevocationChecks = WTD_REVOKE_NONE;
		stWinrstData.dwStateAction = WTD_STATEACTION_IGNORE;
		stWinrstData.dwProvFlags = WTD_SAFER_FLAG;
		stWinrstData.hWVTStateData = NULL;
		stWinrstData.pwszURLReference = NULL;
	} else {
		CryptCATCatalogInfoFromContext(hCatInfo, &stClogInfo, 0);
		stWinstClogInfo.cbStruct = sizeof(WINTRUST_CATALOG_INFO);
		stWinstClogInfo.pcwszCatalogFilePath = stClogInfo.wszCatalogFile;
		stWinstClogInfo.pcwszMemberFilePath = wszFileName;
		stWinstClogInfo.pcwszMemberTag = pszMemberTag;

		stWinrstData.cbStruct = sizeof(WINTRUST_DATA);
		stWinrstData.dwUnionChoice = WTD_CHOICE_CATALOG;
		stWinrstData.pCatalog = &stWinstClogInfo;
		stWinrstData.dwUIChoice = WTD_UI_NONE;
		stWinrstData.fdwRevocationChecks = WTD_STATEACTION_VERIFY;
		stWinrstData.dwProvFlags = 0;
		stWinrstData.hWVTStateData = NULL;
		stWinrstData.pwszURLReference = NULL;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	GUID action = WINTRUST_ACTION_GENERIC_VERIFY_V2;
	HRESULT hr = WinVerifyTrustX(NULL, &action, &stWinrstData);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	bRet = SUCCEEDED(hr);

	if (NULL != hCatInfo) {
		CryptCATAdminReleaseCatalogContext(hCatAdmin, hCatInfo, 0);
	}

	CryptCATAdminReleaseContext(hCatInfo, 0);
	delete[] pszMemberTag;
	return bRet;
}

// =====================================================================================================================
//    验证签名 返回1 过签名 返回0不过签名
// =====================================================================================================================
BOOL FileTrust(const char *FileInTrust)
{
	if ((FileInTrust == NULL) || (strlen(FileInTrust) == 0)) {
		return TRUE;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	HMODULE hLibWintrust = LoadLibrary("wintrust.dll");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == hLibWintrust) {
		return TRUE;
	}

	CryptCATAdminAcquireContext = (CRYPTCATADMINACQUIRECONTEXT) GetProcAddress(hLibWintrust,
																			   "CryptCATAdminAcquireContext");

	CryptCATAdminReleaseContext = (CRYPTCATADMINRELEASECONTEXT) GetProcAddress(hLibWintrust,
																			   "CryptCATAdminReleaseContext");
	CryptCATAdminCalcHashFromFileHandle = (CRYPTCATADMINCALCHASHFROMFILEHANDLE) GetProcAddress(hLibWintrust,
																							   "CryptCATAdminCalcHashFromFileHandle");
	CryptCATAdminEnumCatalogFromHash = (CRYPTCATADMINENUMCATALOGFROMHASH) GetProcAddress(hLibWintrust,
																						 "CryptCATAdminEnumCatalogFromHash");
	CryptCATCatalogInfoFromContext = (CRYPTCATCATALOGINFOFROMCONTEXT) GetProcAddress(hLibWintrust,
																					 "CryptCATCatalogInfoFromContext");
	CryptCATAdminReleaseCatalogContext = (CRYPTCATADMINRELEASECATALOGCONTEXT) GetProcAddress(hLibWintrust,
																							 "CryptCATAdminReleaseCatalogContext");
	WinVerifyTrustX = (WINVERIFYTRUST) GetProcAddress(hLibWintrust, "WinVerifyTrust");

	if (NULL == CryptCATAdminAcquireContext || NULL == CryptCATAdminReleaseContext
	|| NULL == CryptCATAdminCalcHashFromFileHandle || NULL == CryptCATAdminEnumCatalogFromHash
	|| NULL == CryptCATCatalogInfoFromContext || NULL == CryptCATAdminReleaseCatalogContext || NULL == WinVerifyTrustX) {
		FreeLibrary(hLibWintrust);
		return TRUE;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	BOOL bRet = CheckFileTrust(FileInTrust);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FreeLibrary(hLibWintrust);
	return bRet;
}
#else
BOOL FileTrust(const char *FileInTrust)
{
	return TRUE;
}
#endif // CQ_IPAD_REMOVE
