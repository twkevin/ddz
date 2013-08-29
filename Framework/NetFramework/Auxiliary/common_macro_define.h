#ifndef __QX_COMMON_MACRO_DEFINE_H__
#define __QX_COMMON_MACRO_DEFINE_H__

#include "generic_macro_define.h"

NS_QX_BEGIN


#define QXRANDOM_0_1() ((float)rand()/RAND_MAX)
#define QX_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180
#define QX_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f)   // PI * 180

#define QX_MAX(a, b)				(((a) > (b)) ? (a) : (b))
#define QX_MIN(a, b)				(((a) < (b)) ? (a) : (b))
#define QX_SAFE_DELETE(p)			if((p)) { delete (p); (p) = 0; }
#define QX_SAFE_DELETE_ARRAY(p)		if((p)) { delete[] (p); (p) = 0; }
#define QX_SAFE_FREE(p)				if((p)) { free((p)); (p) = 0; }
#define QX_SAFE_RELEASE(p)			if((p)) { (p)->release(); }
#define QX_SAFE_RELEASE_NULL(p)		if((p)) { (p)->release(); p = 0; }
#define QX_SAFE_RETAIN(p)			if(p) { p->retain(); }
#define QX_BREAK_IF(cond)			if(cond) break;
#define QX_FLOAT_EQUAL(x1, x2)      ((x1) == (x2))
#define QX_FLOAT_NO_LESS(x1, x2)    ((x1) >= (x2))
#define QX_FLOAT_GREATER(x1, x2)    ((x1) > (x2)) 
#define QX_ZERO_POINT(p)            (0==(p))
#define QX_VALID_POINT(p)           (0!=(p))
#define QX_NULL_POINT               0
#define QX_PURE_VIRTUAL             = 0
#define QX_OUT_PARAM
#define QX_IN_PARAM

#define QX_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void) const { return varName; }

#define QX_PROPERTY_READONLY_V(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define QX_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void) const { return varName; }\
public: inline void set##funName(varType var){ varName = var; }

#define QX_PROPERTY_V(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define QX_DECLARE_SINGLETON(cls)\
	private: cls();\
	public: ~cls();\
	public: static cls* getInstance();\
	private: static cls* m_pInstance;

#define QX_IMPLEMENT_SINGLETON(cls)\
	cls::cls(){}\
	cls::~cls(){}\
	cls* cls::getInstance()\
	{\
		if (QX_ZERO_POINT(m_pInstance))\
		{\
			m_pInstance = new cls();\
		}\
		return m_pInstance;\
	}\
cls* cls::m_pInstance=NULL;   

#define QX_IMPLEMENT_SINGLETON_WITHOUT_CONSTRUCTOR(cls)\
	cls::~cls(){}\
	cls* cls::getInstance()\
{\
	if (QX_ZERO_POINT(m_pInstance))\
{\
	m_pInstance = new cls();\
}\
	return m_pInstance;\
}\
	cls* cls::m_pInstance=NULL;  

#define QX_IMPLEMENT_SINGLETON_WITHOUT_DESTRUCTOR(cls)\
	cls::cls(){}\
	cls* cls::getInstance()\
{\
	if (QX_ZERO_POINT(m_pInstance))\
{\
	m_pInstance = new cls();\
}\
	return m_pInstance;\
}\
	cls* cls::m_pInstance=NULL;   

// assertion
//#include <assert.h>
#if (defined LOG_ENABLE) && (QX_TARGET_PLATFORM == QX_PLATFORM_WIN32)
#define QX_ASSERT(cond)                assert(cond)
#else
#define QX_ASSERT(cond)
#endif

#define QX_DLL
//#define QX_DLL_FORCE_EXPORT
//// platform depended macros
//#if (QX_TARGET_PLATFORM == QX_PLATFORM_WIN32)
//#undef QX_DLL
//#if defined(_USRDLL)
//#define QX_DLL     __declspec(dllexport)
//#else 		/* use a DLL library */
//#define QX_DLL     __declspec(dllimport)
//#endif
//#undef	QX_DLL_FORCE_EXPORT
//#define QX_DLL_FORCE_EXPORT __declspec(dllexport)
//#endif



NS_QX_END
#endif //__QX_COMMON_MACRO_DEFINE_H__