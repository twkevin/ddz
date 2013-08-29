#ifndef __CONQUER_CONFIG_H__
#define __CONQUER_CONFIG_H__

#define CQ_PLATFORM_WIN32 1
#define CQ_PLATFORM_ANDROID 2
#define CQ_PLATFORM_IOS 3

#define CQ_IPAD

#ifdef WIN32
#define CQ_PLATFORM CQ_PLATFORM_WIN32
#else
#define CQ_PLATFORM CQ_PLATFORM_ANDROID
#endif

// ios
#if (defined(TARGET_OS_IOS) || defined(TARGET_IOS_SIMULATOR))
#undef  CQ_PLATFORM
#define CQ_PLATFORM    CQ_PLATFORM_IOS
#endif

//==================================================================================================
// namespace
#define CQ_NAMESPACE_BEGIN  // namespace cq {
#define CQ_NAMESPACE_END    // }
#define CQ_SYMBOL(x)        // cq::x
#define CQ_USING_SYMBOL(x)  // using cq::x
#define CQ_USING_NAMESPACE  // using namespace cq

#endif
