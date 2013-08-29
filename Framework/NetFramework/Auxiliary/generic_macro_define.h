#ifndef __QX_GENERIC_MACROS_DEFINE_H__
#define __QX_GENERIC_MACROS_DEFINE_H__

/* generic macros */

// namespace quarkxV2 {}
#define NS_QX_BEGIN                     namespace quarkxV2 {
#define NS_QX_END                       }
#define USING_NS_QX                     using namespace quarkxV2;

#define QX_SUPPORT_MULTITHREAD

// define supported target platform macro which QX uses.
#define QX_PLATFORM_UNKNOWN            0
#define QX_PLATFORM_IOS                1
#define QX_PLATFORM_ANDROID            2
#define QX_PLATFORM_WIN32              3

// Determine target platform by compile environment macro.
#define QX_TARGET_PLATFORM             QX_PLATFORM_UNKNOWN

// ios
#if ! QX_TARGET_PLATFORM && (defined(TARGET_OS_IOS) || defined(TARGET_IOS_SIMULATOR))
#undef  QX_TARGET_PLATFORM
#define QX_TARGET_PLATFORM         QX_PLATFORM_IOS
#endif

// android
#if ! QX_TARGET_PLATFORM && defined(ANDROID)
#undef  QX_TARGET_PLATFORM
#define QX_TARGET_PLATFORM         QX_PLATFORM_ANDROID
#endif

// win32
#if ! QX_TARGET_PLATFORM && (defined(WIN32) && defined(_WINDOWS))
#undef  QX_TARGET_PLATFORM
#define QX_TARGET_PLATFORM         QX_PLATFORM_WIN32
#endif


#if ! QX_RENDER_C3 && defined(C3_VERSION)
#undef  QX_RENDER_C3
#define QX_RENDER_C3         1
#endif



#define QX_ANDROID QX_TARGET_PLATFORM == QX_PLATFORM_ANDROID
#define QX_IOS     QX_TARGET_PLATFORM == QX_PLATFORM_IOS
#define QX_WIN32   QX_TARGET_PLATFORM == QX_PLATFORM_WIN32

#define QX_C3   QX_RENDER_C3 == 1
#endif  //__QX_GENERIC_MACROS_DEFINE_H__


