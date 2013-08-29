/*define basic types*/

#ifndef __QX_RAW_TYPE_H__
#define __QX_RAW_TYPE_H__

#include "generic_macro_define.h"

NS_QX_BEGIN

typedef char qxChar;
typedef unsigned char qxByte;

typedef signed short int qxInt16;
typedef unsigned short int qxUInt16;

typedef signed int qxInt32;
typedef unsigned int qxUInt32;

typedef float qxFloat32;

typedef bool qxBoolean;
typedef unsigned int qxOBJID;

typedef const qxChar* qxString;
typedef qxChar* qxBuff;
NS_QX_END

#endif //__QX_RAW_TYPE_H__
