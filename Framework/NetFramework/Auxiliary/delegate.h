#ifndef __DELEGATE_H__
#define __DELEGATE_H__
// 能实现0-5个参数的单个委托或委托列表
// CDelegateX (单)
// CMultiDelegateX (多)
// X>=0 && X<=5 (X范围)
// CDelegateX cDelegate = newDelegate(&ClassIns, &Class::Method); (类委托)
// CDelegateX fDelegate = newDelegate(Method); (函数委托)

#include <typeinfo>
#include <list>
#include <cassert>


#define QX_SUFFIX        0
#define QX_TEMPLATE
#define QX_TEMPLATE_PARAMS
#define QX_TEMPLATE_ARGS
#define QX_T_TEMPLATE_PARAMS         <typename T>
#define QX_T_TEMPLATE_ARGS       <T>
#define QX_PARAMS
#define QX_ARGS
#define QX_TYPENAME

#include "delegate_impl.h"

#define QX_SUFFIX        1
#define QX_TEMPLATE      template
#define QX_TEMPLATE_PARAMS       <typename TP1>
#define QX_TEMPLATE_ARGS     <TP1>
#define QX_T_TEMPLATE_PARAMS         <typename T, typename TP1>
#define QX_T_TEMPLATE_ARGS       <T, TP1>
#define QX_PARAMS        TP1 p1
#define QX_ARGS      p1
#define QX_TYPENAME typename

#include "delegate_impl.h"

#define QX_SUFFIX        2
#define QX_TEMPLATE      template
#define QX_TEMPLATE_PARAMS       <typename TP1, typename TP2>
#define QX_TEMPLATE_ARGS         <TP1, TP2>
#define QX_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2>
#define QX_T_TEMPLATE_ARGS       <T, TP1, TP2>
#define QX_PARAMS        TP1 p1, TP2 p2
#define QX_ARGS      p1, p2
#define QX_TYPENAME      typename

#include "delegate_impl.h"

#define QX_SUFFIX        3
#define QX_TEMPLATE      template
#define QX_TEMPLATE_PARAMS       <typename TP1, typename TP2, typename TP3>
#define QX_TEMPLATE_ARGS         <TP1, TP2, TP3>
#define QX_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2, typename TP3>
#define QX_T_TEMPLATE_ARGS       <T, TP1, TP2, TP3>
#define QX_PARAMS        TP1 p1, TP2 p2, TP3 p3
#define QX_ARGS      p1, p2, p3
#define QX_TYPENAME      typename

#include "delegate_impl.h"

#define QX_SUFFIX        4
#define QX_TEMPLATE      template
#define QX_TEMPLATE_PARAMS       <typename TP1, typename TP2, typename TP3, typename TP4>
#define QX_TEMPLATE_ARGS         <TP1, TP2, TP3, TP4>
#define QX_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2, typename TP3, typename TP4>
#define QX_T_TEMPLATE_ARGS       <T, TP1, TP2, TP3, TP4>
#define QX_PARAMS        TP1 p1, TP2 p2, TP3 p3, TP4 p4
#define QX_ARGS      p1, p2, p3, p4
#define QX_TYPENAME      typename

#include "delegate_impl.h"

#define QX_SUFFIX        5
#define QX_TEMPLATE      template
#define QX_TEMPLATE_PARAMS       <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
#define QX_TEMPLATE_ARGS         <TP1, TP2, TP3, TP4, TP5>
#define QX_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
#define QX_T_TEMPLATE_ARGS       <T, TP1, TP2, TP3, TP4, TP5>
#define QX_PARAMS        TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5
#define QX_ARGS      p1, p2, p3, p4, p5
#define QX_TYPENAME      typename

#include "delegate_impl.h"


#endif // __DELEGATE_H__
