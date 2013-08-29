
#ifndef __PUBLIC_FUNC_H__
#define __PUBLIC_FUNC_H__

#include "CQConfig.h"
#include <string>
#include <cstdio>

#if CQ_PLATFORM == CQ_PLATFORM_ANDROID
#include <jni.h>
// 
// JavaVM* getJavaVM();
// jint JNI_OnLoad(JavaVM *vm, void *reserved);
// 
char* jstringTostring(JNIEnv* env, jstring jstr);
void ReleaseJstringTostring(char* pszDesc);

#endif

void SetResPath(const std::string& strResPath);
std::string GetResPath(void);

std::string GetFullPath(const char *pszFileName);
FILE * CQfopen(const char *, const char *);

std::string GetWriteableFullPath(const char *pszFileName);
std::string GetWriteablePath();
void SetWriteablePath(const std::string& strWriteablePath);

const char* GetFileData(const char *pszFileName, const char *pszMode, unsigned long& nSize);

#endif
