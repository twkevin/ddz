#ifndef __DEFINE_H__
#define __DEFINE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <winsock.h>

#include "Primitive.h"
#include "CQConfig.h"

#if CQ_PLATFORM == CQ_PLATFORM_ANDROID
#include <android/log.h>
#endif

typedef unsigned int OBJID;
const OBJID	ID_NONE = 0;

struct C2DPoint
{
	C2DPoint(int nX, int nY)
	{
		m_nX = nX;
		m_nY = nY;
	};

	C2DPoint()
	{
		m_nX = 0;
		m_nY = 0;
	};

	int m_nX;
	int m_nY;
};

#ifndef NULL
#define NULL 0
#endif//NULL

#define TRUE 	1
#define FALSE 	0

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
#include <windows.h>

// added by tw for some definition
#include <WTYPES.H>

#define DEBUG_NEW new
#define __cdecl
#define afx_msg
#define _T(x) x
#endif

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
#pragma warning (disable: 4514 4786) 
#endif

#if CQ_PLATFORM == CQ_PLATFORM_WIN32 || CQ_PLATFORM == CQ_PLATFORM_IOS
#define LOG_DEBUG
#define LOG_INFO
#define LOG_WARN
#define LOG_ERROR
#define LOG_FATAL
#else
#ifndef LOG_TAG
#define LOG_TAG "log_dzpk"
#endif
#define LOG_DEBUG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_WARN(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOG_FATAL(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)
#endif

#endif
