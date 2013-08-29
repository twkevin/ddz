#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"

template<typename T>
class Singleton
{
public:
	Singleton(void);
	virtual ~Singleton();

	static T &GetSingleton(void);
	static T *GetSingletonPtr(void);

	static T &GetSingleton_AutoCreate(void);
	static T *GetSingletonPtr_AutoCreate(void);

	static void CreateSingleton(void);
	static void DestroySingleton(void);

private:
	static T*& GetInnerPtr(void);
};

template<typename T>
inline Singleton<T>::Singleton(void)
{
}

template<typename T>
inline Singleton<T>::~Singleton(void)
{
}

template<typename T>
inline T &Singleton<T>::GetSingleton(void)
{
	return *GetSingletonPtr();
}

template<typename T>
inline T * Singleton<T>::GetSingletonPtr(void)
{
	T* innerPtr = GetInnerPtr();
	MYASSERT(innerPtr != NULL);
	return innerPtr;
}

template<typename T>
inline void Singleton<T>::CreateSingleton(void)
{
	T*& innerPtr = GetInnerPtr();
	MYASSERT(innerPtr == NULL);
	innerPtr = new T;
	MYASSERT(innerPtr != NULL);
}

template<typename T>
inline T &Singleton<T>::GetSingleton_AutoCreate(void)
{
	return *GetSingletonPtr_AutoCreate();
}

template<typename T>
inline T * Singleton<T>::GetSingletonPtr_AutoCreate(void)
{
	if (GetInnerPtr() == NULL) {
		CreateSingleton();
	}

	return GetInnerPtr();
}

template<typename T>
inline void Singleton<T>::DestroySingleton(void)
{
	T*& innerPtr = GetInnerPtr();
	SAFE_DELETE(innerPtr);
}

template<typename T>
inline T*& Singleton<T>::GetInnerPtr(void)
{
	static T* innerPtr = NULL;
	return innerPtr;
}

#endif
