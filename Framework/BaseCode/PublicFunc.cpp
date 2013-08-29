
#pragma warning(disable: 4251)

#include "PublicFunc.h"
#include <stdlib.h>
#include "cocos2d.h"


#if CQ_PLATFORM == CQ_PLATFORM_WIN32
#include <direct.h>
#elif CQ_PLATFORM == CQ_PLATFORM_IOS || CQ_PLATFORM == CQ_PLATFORM_ANDROID
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#endif

USING_NS_CC;

namespace
{
	bool MkDirExist(const std::string& szPath, char s)  
	{  
		std::string strDir(szPath);//存放要创建的目录字符串  
		//确保以'\'结尾以创建最后一个目录  
		if (strDir[strDir.length()-1]!=s)  
		{  
			strDir += s;
		}  
		std::vector<std::string> vPath;//存放每一层目录字符串  
		std::string strTemp = "";//一个临时变量,存放目录字符串  
		bool bSuccess = false;//成功标志  
		//遍历要创建的字符串  
		for (int i=0;i<strDir.length();++i)  
		{  
			if (strDir[i] != s)   
			{//如果当前字符不是'\\'  
				strTemp += strDir[i];  
			}  
			else   
			{//如果当前字符是'\\' 
				if (!strTemp.empty())
					vPath.push_back(strTemp);//将当前层的字符串添加到数组中  
				strTemp += s;  
			}  
		}  

		//遍历存放目录的数组,创建每层目录  
		std::vector<std::string>::iterator vIter;  
		int ret = 0;  
		for (vIter = vPath.begin(); vIter != vPath.end(); vIter++)   
		{  
			//如果CreateDirectory执行成功,返回true,否则返回false
#if CQ_PLATFORM == CQ_PLATFORM_WIN32
			ret = _mkdir(vIter->c_str());
// #elif CQ_PLATFORM == CQ_PLATFORM_IOS
// 			const char* pszPath = vIter->c_str();
// 			const char* pszFind = strstr(pszPath, "Documents/");
// 			if (pszFind != NULL)
// 			{
// 				if (access(vIter->c_str(), 0)==0)
// 				{
// 					ret = 0;
// 				}
// 				else 
// 				{
// 					//quarkxV2::qxLog(warning, "%s", vIter->c_str());
// 					ret = mkdir(vIter->c_str(), 0777);
// 					ret = ret != 0 ? errno : 0;
// 				}
// 				if (access(vIter->c_str(), W_OK)!=0)
// 					chmod(vIter->c_str(), 0777);
// 			}
#elif CQ_PLATFORM == CQ_PLATFORM_ANDROID || CQ_PLATFORM == CQ_PLATFORM_IOS
			if (access(vIter->c_str(), 0)==0)
			{
				ret = 0;
			}
			else 
			{
				ret = mkdir(vIter->c_str(), 0777);
				ret = ret != 0 ? errno : 0;
			}
			if (access(vIter->c_str(), W_OK)!=0)
			{
				chmod(vIter->c_str(), 0777);
			}
#endif
		} 
#if CQ_PLATFORM == CQ_PLATFORM_WIN32 
		// If the CreateDirectory succeeds, the return value is nonzero.  
		// If the CreateDirectory fails, the return value is zero.   
		// ERROR_ALREADY_EXISTS: The specified directory already exists.  
		if ( 0 != ret || (0 == ret) )  
		{  
			bSuccess = true;  
		}
#elif CQ_PLATFORM == CQ_PLATFORM_IOS || CQ_PLATFORM == CQ_PLATFORM_ANDROID
		bSuccess = 0 == ret;  
#endif
		return bSuccess;  
	}
}

#if CQ_PLATFORM == CQ_PLATFORM_WIN32 
#pragma warning(disable:4996)
#endif

static	std::string g_strResPath = "";
static	std::string g_strWriteablePath = "";

#if CQ_PLATFORM == CQ_PLATFORM_ANDROID


//static	JavaVM*	g_pJavaVM = 0;

// extern "C"
// {
// 	jint JNI_OnLoad(JavaVM *vm, void *reserved)
// 	{
// 		g_pJavaVM = vm;
// 		return JNI_VERSION_1_4;
// 	}
// }
// 
// JavaVM* getJavaVM()
// {
// 	return g_pJavaVM;
// }
// 
char* jstringTostring(JNIEnv* env, jstring jstr)
{
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("gb2312");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	if (0 == alen)
	{
		return NULL;
	}

	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = new char[alen + 1];
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

void ReleaseJstringTostring(char* pszDesc)
{
	if(NULL != pszDesc)
	{
		delete pszDesc;
		pszDesc = NULL;
	}
}
#endif

void SetResPath(const std::string& strResPath)
{
	g_strResPath = strResPath;
}

std::string GetResPath(void)
{
	return g_strResPath;
}

std::string GetFullPath(const char *pszFileName)
{
	if (NULL == pszFileName)
	{
		return std::string("");
	}

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	return std::string(pszFileName);
#else
	std::string strFullPatch = "";
	std::string strResPath = GetResPath();
	if (strResPath.empty())
	{
		strResPath = CCFileUtils::sharedFileUtils()->getWriteablePath();
		strFullPatch = strResPath + std::string(pszFileName);
	}
	else
	{
		strFullPatch = strResPath + "/" + std::string(pszFileName);
	}

	char s = '/';
	size_t nIndex = strFullPatch.find_last_of(s);
	if (nIndex != std::string::npos)
	{
		if (!MkDirExist(strFullPatch.substr(0, nIndex).c_str(), s))
		{
			CCLOG("PublicFunc.cpp GetFullPath strFullPatch = %s not exist", strFullPatch.c_str());
		}
	}

	return strFullPatch;
#endif
}

void SetWriteablePath(const std::string& strWriteablePath)
{
	g_strWriteablePath = strWriteablePath;
}

std::string GetWriteablePath()
{
	return g_strWriteablePath;
}

std::string GetWriteableFullPath(const char *pszFileName)
{
	if (NULL == pszFileName)
	{
		return std::string("");
	}

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	return std::string(pszFileName);
#else
	std::string strFullPatch = "";
	std::string strResPath = GetWriteablePath();
	if (strResPath.empty())
	{
		strResPath = CCFileUtils::sharedFileUtils()->getWriteablePath();
		strFullPatch = strResPath + std::string(pszFileName);
	}
	else
	{
		strFullPatch = strResPath + "/" + std::string(pszFileName);
	}

	char s = '/';
	size_t nIndex = strFullPatch.find_last_of(s);
	if (nIndex != std::string::npos)
	{
		if (!MkDirExist(strFullPatch.substr(0, nIndex).c_str(), s))
		{
			CCLOG("PublicFunc.cpp GetFullPath strFullPatch = %s not exist", strFullPatch.c_str());
		}
	}

	return strFullPatch;
#endif
}

FILE * CQfopen(const char *pszFileName, const char *pszMode)
{
#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	return fopen(pszFileName, pszMode);
#endif

#if CQ_PLATFORM == CQ_PLATFORM_IOS || CQ_PLATFORM == CQ_PLATFORM_ANDROID
	if(NULL == pszFileName || NULL == pszMode)
	{
		return NULL;
	}

	FILE* pFile = fopen(pszFileName, pszMode);

	if (pFile)
	{
		return pFile;
	}
	std::string strFullPatch = GetWriteableFullPath(pszFileName);
	pFile = fopen(strFullPatch.c_str(), pszMode);

	return pFile;
#endif
}

const char* GetFileData(const char *pszFileName, const char *pszMode, unsigned long& nSize)
{
	if (NULL == pszFileName || NULL == pszMode)
	{
		return NULL;
	}

	CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
	if (NULL == pFileUtils)
	{
		return NULL;
	}

	unsigned char* pBuffer = pFileUtils->getFileData(pszFileName, pszMode, &nSize);	
	if (pBuffer == NULL)
	{
		CCLOG("PublicFunc.cpp GetFileData pszFileName = %s failed", pszFileName);
	}

	return (const char*)pBuffer;
}
