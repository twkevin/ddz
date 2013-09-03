/*
** Lua binding: UIFramework
** Generated automatically by tolua++-1.0.92 on 09/03/13 15:11:57.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "LuaUIFramework.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_UIFramework_open (lua_State* tolua_S);

#include "UIFramework.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_DLG_HANDLE (lua_State* tolua_S)
{
 DLG_HANDLE* self = (DLG_HANDLE*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DWORD (lua_State* tolua_S)
{
 DWORD* self = (DWORD*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCtrlStaticEx");
 tolua_usertype(tolua_S,"DLG_IDD");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCtrlPage");
 tolua_usertype(tolua_S,"CCtrlBMFontStatic");
 tolua_usertype(tolua_S,"DLG_HANDLE");
 tolua_usertype(tolua_S,"CCScrollViewDelegate");
 tolua_usertype(tolua_S,"CCDialogBase");
 tolua_usertype(tolua_S,"CCtrlButtonEx");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCtrlProgress");
 tolua_usertype(tolua_S,"DWORD");
 tolua_usertype(tolua_S,"WPARAM");
 tolua_usertype(tolua_S,"CCtrlCheckBox");
 tolua_usertype(tolua_S,"CCtrlImageEx");
 tolua_usertype(tolua_S,"CCLabelTTF");
 tolua_usertype(tolua_S,"UINT");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"CCMyDialog");
 tolua_usertype(tolua_S,"KeyboardNotificationLayer");
 tolua_usertype(tolua_S,"CCtrlEdit");
 tolua_usertype(tolua_S,"CCMyWndObject");
 tolua_usertype(tolua_S,"CCtrlStatic");
 tolua_usertype(tolua_S,"CCTextFieldDelegate");
 tolua_usertype(tolua_S,"CCLabelBMFont");
 tolua_usertype(tolua_S,"LPARAM");
 tolua_usertype(tolua_S,"CUIManager");
 tolua_usertype(tolua_S,"CCObject");
}

/* method: sharedInstancePtr of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_sharedInstancePtr00
static int tolua_UIFramework_CUIManager_sharedInstancePtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CUIManager* tolua_ret = (CUIManager*)  CUIManager::sharedInstancePtr();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CUIManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedInstancePtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_Destroy00
static int tolua_UIFramework_CUIManager_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'", NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateDlg of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_CreateDlg00
static int tolua_UIFramework_CUIManager_CreateDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  int nDialogIDD = ((int)  tolua_tonumber(tolua_S,2,0));
  bool bShow = ((bool)  tolua_toboolean(tolua_S,3,0));
  int hdlParent = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateDlg'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateDlg(nDialogIDD,bShow,hdlParent);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowDialog of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_ShowDialog00
static int tolua_UIFramework_CUIManager_ShowDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  int nDlgHandle = ((int)  tolua_tonumber(tolua_S,2,0));
  bool bShow = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool bFront = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowDialog'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ShowDialog(nDlgHandle,bShow,bFront);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisible of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_IsVisible00
static int tolua_UIFramework_CUIManager_IsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE nDlgHandle = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsVisible(nDlgHandle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDlgVisible of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_IsDlgVisible00
static int tolua_UIFramework_CUIManager_IsDlgVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_IDD",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_IDD nDialogIDD = *((DLG_IDD*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDlgVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDlgVisible(nDialogIDD);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDlgVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendMessage of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_SendMessage00
static int tolua_UIFramework_CUIManager_SendMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"UINT",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"WPARAM",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"LPARAM",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE hDlg = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
  UINT Msg = *((UINT*)  tolua_tousertype(tolua_S,3,0));
  WPARAM wParam = *((WPARAM*)  tolua_tousertype(tolua_S,4,0));
  LPARAM lParam = *((LPARAM*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendMessage'", NULL);
#endif
  {
   DWORD tolua_ret = (DWORD)  self->SendMessage(hDlg,Msg,wParam,lParam);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DWORD)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DWORD");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DWORD));
     tolua_pushusertype(tolua_S,tolua_obj,"DWORD");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWndObj of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetWndObj00
static int tolua_UIFramework_CUIManager_GetWndObj00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE nWndObjHandle = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWndObj'", NULL);
#endif
  {
   CCMyWndObject* tolua_ret = (CCMyWndObject*)  self->GetWndObj(nWndObjHandle);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMyWndObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWndObj'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDlg of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetDlg00
static int tolua_UIFramework_CUIManager_GetDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE nDlgHandle = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDlg'", NULL);
#endif
  {
   CCMyDialog* tolua_ret = (CCMyDialog*)  self->GetDlg(nDlgHandle);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCMyDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowModalDlg of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_ShowModalDlg00
static int tolua_UIFramework_CUIManager_ShowModalDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE nDlgHandle = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowModalDlg'", NULL);
#endif
  {
   self->ShowModalDlg(nDlgHandle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowModalDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAutoCloseDialog of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_SetAutoCloseDialog00
static int tolua_UIFramework_CUIManager_SetAutoCloseDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE handle = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
  bool bAutoClose = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoCloseDialog'", NULL);
#endif
  {
   self->SetAutoCloseDialog(handle,bAutoClose);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoCloseDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BindToFront of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_BindToFront00
static int tolua_UIFramework_CUIManager_BindToFront00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE hDlg = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BindToFront'", NULL);
#endif
  {
   self->BindToFront(hDlg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BindToFront'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BindToBack of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_BindToBack00
static int tolua_UIFramework_CUIManager_BindToBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE hDlg = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BindToBack'", NULL);
#endif
  {
   self->BindToBack(hDlg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BindToBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrontDlg of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetFrontDlg00
static int tolua_UIFramework_CUIManager_GetFrontDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrontDlg'", NULL);
#endif
  {
   DLG_HANDLE tolua_ret = (DLG_HANDLE)  self->GetFrontDlg();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DLG_HANDLE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DLG_HANDLE));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrontDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnTouchBegan of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_OnTouchBegan00
static int tolua_UIFramework_CUIManager_OnTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnTouchBegan'", NULL);
#endif
  {
   DLG_HANDLE tolua_ret = (DLG_HANDLE)  self->OnTouchBegan(pTouch);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DLG_HANDLE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DLG_HANDLE));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DoTouchOver of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_DoTouchOver00
static int tolua_UIFramework_CUIManager_DoTouchOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DoTouchOver'", NULL);
#endif
  {
   self->DoTouchOver();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DoTouchOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTouchHandleDlg of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetTouchHandleDlg00
static int tolua_UIFramework_CUIManager_GetTouchHandleDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CUIManager* self = (const CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTouchHandleDlg'", NULL);
#endif
  {
   DLG_HANDLE tolua_ret = (DLG_HANDLE)  self->GetTouchHandleDlg();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DLG_HANDLE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DLG_HANDLE));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTouchHandleDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTouchHandleObj of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetTouchHandleObj00
static int tolua_UIFramework_CUIManager_GetTouchHandleObj00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CUIManager* self = (const CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTouchHandleObj'", NULL);
#endif
  {
   DLG_HANDLE tolua_ret = (DLG_HANDLE)  self->GetTouchHandleObj();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DLG_HANDLE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DLG_HANDLE));
     tolua_pushusertype(tolua_S,tolua_obj,"DLG_HANDLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTouchHandleObj'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CleanTouchHandleObj of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_CleanTouchHandleObj00
static int tolua_UIFramework_CUIManager_CleanTouchHandleObj00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CleanTouchHandleObj'", NULL);
#endif
  {
   self->CleanTouchHandleObj();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CleanTouchHandleObj'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CloseAllDialog of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_CloseAllDialog00
static int tolua_UIFramework_CUIManager_CloseAllDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CloseAllDialog'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CloseAllDialog();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CloseAllDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseAllDialog of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_ReleaseAllDialog00
static int tolua_UIFramework_CUIManager_ReleaseAllDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseAllDialog'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ReleaseAllDialog();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseAllDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAppWnd of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetAppWnd00
static int tolua_UIFramework_CUIManager_GetAppWnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAppWnd'", NULL);
#endif
  {
   CCMyWndObject* tolua_ret = (CCMyWndObject*)  self->GetAppWnd();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMyWndObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAppWnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnNetPackage of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_OnNetPackage00
static int tolua_UIFramework_CUIManager_OnNetPackage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  void* pDataPkg = ((void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnNetPackage'", NULL);
#endif
  {
   self->OnNetPackage(pDataPkg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnNetPackage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSceneHoldDlg of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_AddSceneHoldDlg00
static int tolua_UIFramework_CUIManager_AddSceneHoldDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DLG_HANDLE",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  DLG_HANDLE hDlg = *((DLG_HANDLE*)  tolua_tousertype(tolua_S,2,0));
  CCMyDialog* pDlg = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSceneHoldDlg'", NULL);
#endif
  {
   self->AddSceneHoldDlg(hDlg,pDlg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSceneHoldDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SynOnSceneEnter of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_SynOnSceneEnter00
static int tolua_UIFramework_CUIManager_SynOnSceneEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pScene = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SynOnSceneEnter'", NULL);
#endif
  {
   self->SynOnSceneEnter(pScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynOnSceneEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SynOnSceneExit of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_SynOnSceneExit00
static int tolua_UIFramework_CUIManager_SynOnSceneExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pScene = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SynOnSceneExit'", NULL);
#endif
  {
   self->SynOnSceneExit(pScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynOnSceneExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnableAutoDelDialog of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_EnableAutoDelDialog00
static int tolua_UIFramework_CUIManager_EnableAutoDelDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  bool bEnableAutoDelDialog = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnableAutoDelDialog'", NULL);
#endif
  {
   self->EnableAutoDelDialog(bEnableAutoDelDialog);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableAutoDelDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHandleByIDD of class  CUIManager */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CUIManager_GetHandleByIDD00
static int tolua_UIFramework_CUIManager_GetHandleByIDD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUIManager* self = (CUIManager*)  tolua_tousertype(tolua_S,1,0);
  int nIDD = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHandleByIDD'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHandleByIDD(nIDD);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHandleByIDD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_Create00
static int tolua_UIFramework_CCMyDialog_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyWndObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyWndObject* pParent = ((CCMyWndObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'", NULL);
#endif
  {
   self->Create(nWndID,pParent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnNetPackage of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_OnNetPackage00
static int tolua_UIFramework_CCMyDialog_OnNetPackage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
  void* pDataPkg = ((void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnNetPackage'", NULL);
#endif
  {
   self->OnNetPackage(pDataPkg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnNetPackage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHoldScene of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_SetHoldScene00
static int tolua_UIFramework_CCMyDialog_SetHoldScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHoldScene'", NULL);
#endif
  {
   self->SetHoldScene();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHoldScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_setVisible00
static int tolua_UIFramework_CCMyDialog_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVisible of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_isVisible00
static int tolua_UIFramework_CCMyDialog_isVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShow of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_SetShow00
static int tolua_UIFramework_CCMyDialog_SetShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShow'", NULL);
#endif
  {
   self->SetShow(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShow of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_IsShow00
static int tolua_UIFramework_CCMyDialog_IsShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsShow'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsShow();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetType of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_GetType00
static int tolua_UIFramework_CCMyDialog_GetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCMyDialog* self = (const CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBgAni of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_GetBgAni00
static int tolua_UIFramework_CCMyDialog_GetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBgAni'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetBgAni();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBgAni of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_SetBgAni00
static int tolua_UIFramework_CCMyDialog_SetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
  const char* pszAni = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBgAni'", NULL);
#endif
  {
   self->SetBgAni(pszAni);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchInside of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_isTouchInside00
static int tolua_UIFramework_CCMyDialog_isTouchInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchInside(touch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchInside'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createEx of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_createEx00
static int tolua_UIFramework_CCMyDialog_createEx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCMyDialog* tolua_ret = (CCMyDialog*)  CCMyDialog::createEx(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCMyDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createEx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_create00
static int tolua_UIFramework_CCMyDialog_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CCMyDialog* tolua_ret = (CCMyDialog*)  CCMyDialog::create(nWndID);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCMyDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: newDlg of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCMyDialog_newDlg00
static int tolua_UIFramework_CCMyDialog_newDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CCMyDialog* tolua_ret = (CCMyDialog*)  CCMyDialog::newDlg(nWndID);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCMyDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'newDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCDialogBase__ of class  CCMyDialog */
#ifndef TOLUA_DISABLE_tolua_get_CCMyDialog___CCDialogBase__
static int tolua_get_CCMyDialog___CCDialogBase__(lua_State* tolua_S)
{
  CCMyDialog* self = (CCMyDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCDialogBase__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCDialogBase*>(self), "CCDialogBase");
#else
   tolua_pushusertype(tolua_S,(void*)((CCDialogBase*)self), "CCDialogBase");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlStatic */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlStatic_create00
static int tolua_UIFramework_CCtrlStatic_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlStatic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlStatic* tolua_ret = (CCtrlStatic*)  CCtrlStatic::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlStatic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlStatic */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlStatic___CCMyWndObject__
static int tolua_get_CCtrlStatic___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlStatic* self = (CCtrlStatic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlImageEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlImageEx_create00
static int tolua_UIFramework_CCtrlImageEx_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlImageEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlImageEx* tolua_ret = (CCtrlImageEx*)  CCtrlImageEx::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlImageEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBgAni of class  CCtrlImageEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlImageEx_GetBgAni00
static int tolua_UIFramework_CCtrlImageEx_GetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlImageEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlImageEx* self = (CCtrlImageEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBgAni'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetBgAni();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBgAni of class  CCtrlImageEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlImageEx_SetBgAni00
static int tolua_UIFramework_CCtrlImageEx_SetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlImageEx",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlImageEx* self = (CCtrlImageEx*)  tolua_tousertype(tolua_S,1,0);
  const char* pszAni = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBgAni'", NULL);
#endif
  {
   self->SetBgAni(pszAni);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAniStretch of class  CCtrlImageEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlImageEx_getAniStretch00
static int tolua_UIFramework_CCtrlImageEx_getAniStretch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlImageEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlImageEx* self = (CCtrlImageEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAniStretch'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAniStretch();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAniStretch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAniStretch of class  CCtrlImageEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlImageEx_setAniStretch00
static int tolua_UIFramework_CCtrlImageEx_setAniStretch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlImageEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlImageEx* self = (CCtrlImageEx*)  tolua_tousertype(tolua_S,1,0);
  int var = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAniStretch'", NULL);
#endif
  {
   self->setAniStretch(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAniStretch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlImageEx */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlImageEx___CCMyWndObject__
static int tolua_get_CCtrlImageEx___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlImageEx* self = (CCtrlImageEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_create00
static int tolua_UIFramework_CCtrlButtonEx_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlButtonEx* tolua_ret = (CCtrlButtonEx*)  CCtrlButtonEx::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlButtonEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBgAni of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_GetBgAni00
static int tolua_UIFramework_CCtrlButtonEx_GetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBgAni'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetBgAni();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBgAni of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_SetBgAni00
static int tolua_UIFramework_CCtrlButtonEx_SetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
  const char* pszAni = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBgAni'", NULL);
#endif
  {
   self->SetBgAni(pszAni);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAniStretch of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_getAniStretch00
static int tolua_UIFramework_CCtrlButtonEx_getAniStretch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAniStretch'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAniStretch();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAniStretch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAniStretch of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_setAniStretch00
static int tolua_UIFramework_CCtrlButtonEx_setAniStretch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
  int var = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAniStretch'", NULL);
#endif
  {
   self->setAniStretch(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAniStretch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZoomOnTouchDown of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_getZoomOnTouchDown00
static int tolua_UIFramework_CCtrlButtonEx_getZoomOnTouchDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZoomOnTouchDown'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getZoomOnTouchDown();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZoomOnTouchDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomOnTouchDown of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlButtonEx_setZoomOnTouchDown00
static int tolua_UIFramework_CCtrlButtonEx_setZoomOnTouchDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlButtonEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
  int var = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomOnTouchDown'", NULL);
#endif
  {
   self->setZoomOnTouchDown(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZoomOnTouchDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlButtonEx */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlButtonEx___CCMyWndObject__
static int tolua_get_CCtrlButtonEx___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlButtonEx* self = (CCtrlButtonEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlEdit */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlEdit_create00
static int tolua_UIFramework_CCtrlEdit_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlEdit* tolua_ret = (CCtrlEdit*)  CCtrlEdit::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getString of class  CCtrlEdit */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlEdit_getString00
static int tolua_UIFramework_CCtrlEdit_getString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlEdit* self = (CCtrlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlaceHolder of class  CCtrlEdit */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlEdit_getPlaceHolder00
static int tolua_UIFramework_CCtrlEdit_getPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlEdit* self = (CCtrlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlaceHolder'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getPlaceHolder();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setString of class  CCtrlEdit */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlEdit_setString00
static int tolua_UIFramework_CCtrlEdit_setString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlEdit* self = (CCtrlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* pszText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setString'", NULL);
#endif
  {
   self->setString(pszText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTextFieldDelegate__ of class  CCtrlEdit */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlEdit___CCTextFieldDelegate__
static int tolua_get_CCtrlEdit___CCTextFieldDelegate__(lua_State* tolua_S)
{
  CCtrlEdit* self = (CCtrlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTextFieldDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTextFieldDelegate*>(self), "CCTextFieldDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTextFieldDelegate*)self), "CCTextFieldDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlEdit */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlEdit___CCMyWndObject__
static int tolua_get_CCtrlEdit___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlEdit* self = (CCtrlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlBMFontStatic */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlBMFontStatic_create00
static int tolua_UIFramework_CCtrlBMFontStatic_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlBMFontStatic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlBMFontStatic* tolua_ret = (CCtrlBMFontStatic*)  CCtrlBMFontStatic::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlBMFontStatic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlBMFontStatic */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlBMFontStatic___CCMyWndObject__
static int tolua_get_CCtrlBMFontStatic___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlBMFontStatic* self = (CCtrlBMFontStatic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_create00
static int tolua_UIFramework_CCtrlProgress_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlProgress* tolua_ret = (CCtrlProgress*)  CCtrlProgress::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_setValue00
static int tolua_UIFramework_CCtrlProgress_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlProgress* self = (CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValue of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_getValue00
static int tolua_UIFramework_CCtrlProgress_getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCtrlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCtrlProgress* self = (const CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMinimumValue of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_setMinimumValue00
static int tolua_UIFramework_CCtrlProgress_setMinimumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlProgress* self = (CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinimumValue'", NULL);
#endif
  {
   self->setMinimumValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMinimumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMinimumValue of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_getMinimumValue00
static int tolua_UIFramework_CCtrlProgress_getMinimumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCtrlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCtrlProgress* self = (const CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinimumValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMinimumValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinimumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaximumValue of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_setMaximumValue00
static int tolua_UIFramework_CCtrlProgress_setMaximumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlProgress* self = (CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaximumValue'", NULL);
#endif
  {
   self->setMaximumValue(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaximumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaximumValue of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlProgress_getMaximumValue00
static int tolua_UIFramework_CCtrlProgress_getMaximumValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCtrlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCtrlProgress* self = (const CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaximumValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMaximumValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaximumValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlProgress */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlProgress___CCMyWndObject__
static int tolua_get_CCtrlProgress___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlProgress* self = (CCtrlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlCheckBox */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlCheckBox_create00
static int tolua_UIFramework_CCtrlCheckBox_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlCheckBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlCheckBox* tolua_ret = (CCtrlCheckBox*)  CCtrlCheckBox::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlCheckBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChecked of class  CCtrlCheckBox */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlCheckBox_getChecked00
static int tolua_UIFramework_CCtrlCheckBox_getChecked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlCheckBox* self = (CCtrlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChecked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getChecked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHighlighted of class  CCtrlCheckBox */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlCheckBox_setHighlighted00
static int tolua_UIFramework_CCtrlCheckBox_setHighlighted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlCheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlCheckBox* self = (CCtrlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHighlighted'", NULL);
#endif
  {
   self->setHighlighted(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHighlighted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChecked of class  CCtrlCheckBox */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlCheckBox_setChecked00
static int tolua_UIFramework_CCtrlCheckBox_setChecked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlCheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlCheckBox* self = (CCtrlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool Checked = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChecked'", NULL);
#endif
  {
   self->setChecked(Checked);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlCheckBox */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlCheckBox___CCMyWndObject__
static int tolua_get_CCtrlCheckBox___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlCheckBox* self = (CCtrlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlStaticEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlStaticEx_create00
static int tolua_UIFramework_CCtrlStaticEx_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlStaticEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlStaticEx* tolua_ret = (CCtrlStaticEx*)  CCtrlStaticEx::create(nWndID,pParent);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCtrlStaticEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setString of class  CCtrlStaticEx */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlStaticEx_setString00
static int tolua_UIFramework_CCtrlStaticEx_setString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlStaticEx",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlStaticEx* self = (CCtrlStaticEx*)  tolua_tousertype(tolua_S,1,0);
  const char* pszText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setString'", NULL);
#endif
  {
   self->setString(pszText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCScrollViewDelegate__ of class  CCtrlStaticEx */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlStaticEx___CCScrollViewDelegate__
static int tolua_get_CCtrlStaticEx___CCScrollViewDelegate__(lua_State* tolua_S)
{
  CCtrlStaticEx* self = (CCtrlStaticEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCScrollViewDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCScrollViewDelegate*>(self), "CCScrollViewDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCScrollViewDelegate*)self), "CCScrollViewDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlStaticEx */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlStaticEx___CCMyWndObject__
static int tolua_get_CCtrlStaticEx___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlStaticEx* self = (CCtrlStaticEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_create00
static int tolua_UIFramework_CCtrlPage_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCMyDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nWndID = ((int)  tolua_tonumber(tolua_S,2,0));
  CCMyDialog* pParent = ((CCMyDialog*)  tolua_tousertype(tolua_S,3,0));
  {
   CCtrlPage* tolua_ret = (CCtrlPage*)  CCtrlPage::create(nWndID,pParent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCtrlPage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddPageItem of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_AddPageItem00
static int tolua_UIFramework_CCtrlPage_AddPageItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMyDialog",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
  CCMyDialog* lpDlg = ((CCMyDialog*)  tolua_tousertype(tolua_S,2,0));
  bool bAutoDestory = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddPageItem'", NULL);
#endif
  {
   int tolua_ret = (int)  self->AddPageItem(lpDlg,bAutoDestory);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddPageItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPageCount of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_GetPageCount00
static int tolua_UIFramework_CCtrlPage_GetPageCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCtrlPage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCtrlPage* self = (const CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPageCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPageCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPageCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemovePageItem of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_RemovePageItem00
static int tolua_UIFramework_CCtrlPage_RemovePageItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemovePageItem'", NULL);
#endif
  {
   self->RemovePageItem(nIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemovePageItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearPages of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_ClearPages00
static int tolua_UIFramework_CCtrlPage_ClearPages00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearPages'", NULL);
#endif
  {
   self->ClearPages();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearPages'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurPageIndex of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_SetCurPageIndex00
static int tolua_UIFramework_CCtrlPage_SetCurPageIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
  int nPageIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  bool animated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurPageIndex'", NULL);
#endif
  {
   self->SetCurPageIndex(nPageIndex,animated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurPageIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurPageIndex of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_GetCurPageIndex00
static int tolua_UIFramework_CCtrlPage_GetCurPageIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCtrlPage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCtrlPage* self = (const CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurPageIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurPageIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurPageIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBgAni of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_GetBgAni00
static int tolua_UIFramework_CCtrlPage_GetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBgAni'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetBgAni();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBgAni of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_UIFramework_CCtrlPage_SetBgAni00
static int tolua_UIFramework_CCtrlPage_SetBgAni00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCtrlPage",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
  const char* pszAni = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBgAni'", NULL);
#endif
  {
   self->SetBgAni(pszAni);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBgAni'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCScrollViewDelegate__ of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlPage___CCScrollViewDelegate__
static int tolua_get_CCtrlPage___CCScrollViewDelegate__(lua_State* tolua_S)
{
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCScrollViewDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCScrollViewDelegate*>(self), "CCScrollViewDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCScrollViewDelegate*)self), "CCScrollViewDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCMyWndObject__ of class  CCtrlPage */
#ifndef TOLUA_DISABLE_tolua_get_CCtrlPage___CCMyWndObject__
static int tolua_get_CCtrlPage___CCMyWndObject__(lua_State* tolua_S)
{
  CCtrlPage* self = (CCtrlPage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCMyWndObject__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCMyWndObject*>(self), "CCMyWndObject");
#else
   tolua_pushusertype(tolua_S,(void*)((CCMyWndObject*)self), "CCMyWndObject");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_UIFramework_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CUIManager","CUIManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CUIManager");
   tolua_function(tolua_S,"sharedInstancePtr",tolua_UIFramework_CUIManager_sharedInstancePtr00);
   tolua_function(tolua_S,"Destroy",tolua_UIFramework_CUIManager_Destroy00);
   tolua_function(tolua_S,"CreateDlg",tolua_UIFramework_CUIManager_CreateDlg00);
   tolua_function(tolua_S,"ShowDialog",tolua_UIFramework_CUIManager_ShowDialog00);
   tolua_function(tolua_S,"IsVisible",tolua_UIFramework_CUIManager_IsVisible00);
   tolua_function(tolua_S,"IsDlgVisible",tolua_UIFramework_CUIManager_IsDlgVisible00);
   tolua_function(tolua_S,"SendMessage",tolua_UIFramework_CUIManager_SendMessage00);
   tolua_function(tolua_S,"GetWndObj",tolua_UIFramework_CUIManager_GetWndObj00);
   tolua_function(tolua_S,"GetDlg",tolua_UIFramework_CUIManager_GetDlg00);
   tolua_function(tolua_S,"ShowModalDlg",tolua_UIFramework_CUIManager_ShowModalDlg00);
   tolua_function(tolua_S,"SetAutoCloseDialog",tolua_UIFramework_CUIManager_SetAutoCloseDialog00);
   tolua_function(tolua_S,"BindToFront",tolua_UIFramework_CUIManager_BindToFront00);
   tolua_function(tolua_S,"BindToBack",tolua_UIFramework_CUIManager_BindToBack00);
   tolua_function(tolua_S,"GetFrontDlg",tolua_UIFramework_CUIManager_GetFrontDlg00);
   tolua_function(tolua_S,"OnTouchBegan",tolua_UIFramework_CUIManager_OnTouchBegan00);
   tolua_function(tolua_S,"DoTouchOver",tolua_UIFramework_CUIManager_DoTouchOver00);
   tolua_function(tolua_S,"GetTouchHandleDlg",tolua_UIFramework_CUIManager_GetTouchHandleDlg00);
   tolua_function(tolua_S,"GetTouchHandleObj",tolua_UIFramework_CUIManager_GetTouchHandleObj00);
   tolua_function(tolua_S,"CleanTouchHandleObj",tolua_UIFramework_CUIManager_CleanTouchHandleObj00);
   tolua_function(tolua_S,"CloseAllDialog",tolua_UIFramework_CUIManager_CloseAllDialog00);
   tolua_function(tolua_S,"ReleaseAllDialog",tolua_UIFramework_CUIManager_ReleaseAllDialog00);
   tolua_function(tolua_S,"GetAppWnd",tolua_UIFramework_CUIManager_GetAppWnd00);
   tolua_function(tolua_S,"OnNetPackage",tolua_UIFramework_CUIManager_OnNetPackage00);
   tolua_function(tolua_S,"AddSceneHoldDlg",tolua_UIFramework_CUIManager_AddSceneHoldDlg00);
   tolua_function(tolua_S,"SynOnSceneEnter",tolua_UIFramework_CUIManager_SynOnSceneEnter00);
   tolua_function(tolua_S,"SynOnSceneExit",tolua_UIFramework_CUIManager_SynOnSceneExit00);
   tolua_function(tolua_S,"EnableAutoDelDialog",tolua_UIFramework_CUIManager_EnableAutoDelDialog00);
   tolua_function(tolua_S,"GetHandleByIDD",tolua_UIFramework_CUIManager_GetHandleByIDD00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCMyDialog","CCMyDialog","CCLayer",NULL);
  tolua_beginmodule(tolua_S,"CCMyDialog");
   tolua_function(tolua_S,"Create",tolua_UIFramework_CCMyDialog_Create00);
   tolua_function(tolua_S,"OnNetPackage",tolua_UIFramework_CCMyDialog_OnNetPackage00);
   tolua_function(tolua_S,"SetHoldScene",tolua_UIFramework_CCMyDialog_SetHoldScene00);
   tolua_function(tolua_S,"setVisible",tolua_UIFramework_CCMyDialog_setVisible00);
   tolua_function(tolua_S,"isVisible",tolua_UIFramework_CCMyDialog_isVisible00);
   tolua_function(tolua_S,"SetShow",tolua_UIFramework_CCMyDialog_SetShow00);
   tolua_function(tolua_S,"IsShow",tolua_UIFramework_CCMyDialog_IsShow00);
   tolua_function(tolua_S,"GetType",tolua_UIFramework_CCMyDialog_GetType00);
   tolua_function(tolua_S,"GetBgAni",tolua_UIFramework_CCMyDialog_GetBgAni00);
   tolua_function(tolua_S,"SetBgAni",tolua_UIFramework_CCMyDialog_SetBgAni00);
   tolua_function(tolua_S,"isTouchInside",tolua_UIFramework_CCMyDialog_isTouchInside00);
   tolua_function(tolua_S,"createEx",tolua_UIFramework_CCMyDialog_createEx00);
   tolua_function(tolua_S,"create",tolua_UIFramework_CCMyDialog_create00);
   tolua_function(tolua_S,"newDlg",tolua_UIFramework_CCMyDialog_newDlg00);
   tolua_variable(tolua_S,"__CCDialogBase__",tolua_get_CCMyDialog___CCDialogBase__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlStatic","CCtrlStatic","CCLabelTTF",NULL);
  tolua_beginmodule(tolua_S,"CCtrlStatic");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlStatic_create00);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlStatic___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CTRLIMAGEANISTRETCH_NORMAL",CTRLIMAGEANISTRETCH_NORMAL);
  tolua_constant(tolua_S,"CTRLIMAGEANISTRETCH_STRETCH",CTRLIMAGEANISTRETCH_STRETCH);
  tolua_constant(tolua_S,"CTRLIMAGEANISTRETCH_STRETCHNINESIGNAL",CTRLIMAGEANISTRETCH_STRETCHNINESIGNAL);
  tolua_cclass(tolua_S,"CCtrlImageEx","CCtrlImageEx","CCControl",NULL);
  tolua_beginmodule(tolua_S,"CCtrlImageEx");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlImageEx_create00);
   tolua_function(tolua_S,"GetBgAni",tolua_UIFramework_CCtrlImageEx_GetBgAni00);
   tolua_function(tolua_S,"SetBgAni",tolua_UIFramework_CCtrlImageEx_SetBgAni00);
   tolua_function(tolua_S,"getAniStretch",tolua_UIFramework_CCtrlImageEx_getAniStretch00);
   tolua_function(tolua_S,"setAniStretch",tolua_UIFramework_CCtrlImageEx_setAniStretch00);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlImageEx___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CTRLBUTTONANISTRETCH_NORMAL",CTRLBUTTONANISTRETCH_NORMAL);
  tolua_constant(tolua_S,"CTRLBUTTONANISTRETCH_STRETCH",CTRLBUTTONANISTRETCH_STRETCH);
  tolua_constant(tolua_S,"CTRLBUTTONANISTRETCH_STRETCHNINESIGNAL",CTRLBUTTONANISTRETCH_STRETCHNINESIGNAL);
  tolua_cclass(tolua_S,"CCtrlButtonEx","CCtrlButtonEx","CCControl",NULL);
  tolua_beginmodule(tolua_S,"CCtrlButtonEx");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlButtonEx_create00);
   tolua_function(tolua_S,"GetBgAni",tolua_UIFramework_CCtrlButtonEx_GetBgAni00);
   tolua_function(tolua_S,"SetBgAni",tolua_UIFramework_CCtrlButtonEx_SetBgAni00);
   tolua_function(tolua_S,"getAniStretch",tolua_UIFramework_CCtrlButtonEx_getAniStretch00);
   tolua_function(tolua_S,"setAniStretch",tolua_UIFramework_CCtrlButtonEx_setAniStretch00);
   tolua_function(tolua_S,"getZoomOnTouchDown",tolua_UIFramework_CCtrlButtonEx_getZoomOnTouchDown00);
   tolua_function(tolua_S,"setZoomOnTouchDown",tolua_UIFramework_CCtrlButtonEx_setZoomOnTouchDown00);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlButtonEx___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlEdit","CCtrlEdit","KeyboardNotificationLayer",NULL);
  tolua_beginmodule(tolua_S,"CCtrlEdit");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlEdit_create00);
   tolua_function(tolua_S,"getString",tolua_UIFramework_CCtrlEdit_getString00);
   tolua_function(tolua_S,"getPlaceHolder",tolua_UIFramework_CCtrlEdit_getPlaceHolder00);
   tolua_function(tolua_S,"setString",tolua_UIFramework_CCtrlEdit_setString00);
   tolua_variable(tolua_S,"__CCTextFieldDelegate__",tolua_get_CCtrlEdit___CCTextFieldDelegate__,NULL);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlEdit___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlBMFontStatic","CCtrlBMFontStatic","CCLabelBMFont",NULL);
  tolua_beginmodule(tolua_S,"CCtrlBMFontStatic");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlBMFontStatic_create00);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlBMFontStatic___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlProgress","CCtrlProgress","CCControl",NULL);
  tolua_beginmodule(tolua_S,"CCtrlProgress");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlProgress_create00);
   tolua_function(tolua_S,"setValue",tolua_UIFramework_CCtrlProgress_setValue00);
   tolua_function(tolua_S,"getValue",tolua_UIFramework_CCtrlProgress_getValue00);
   tolua_function(tolua_S,"setMinimumValue",tolua_UIFramework_CCtrlProgress_setMinimumValue00);
   tolua_function(tolua_S,"getMinimumValue",tolua_UIFramework_CCtrlProgress_getMinimumValue00);
   tolua_function(tolua_S,"setMaximumValue",tolua_UIFramework_CCtrlProgress_setMaximumValue00);
   tolua_function(tolua_S,"getMaximumValue",tolua_UIFramework_CCtrlProgress_getMaximumValue00);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlProgress___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlCheckBox","CCtrlCheckBox","CCControl",NULL);
  tolua_beginmodule(tolua_S,"CCtrlCheckBox");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlCheckBox_create00);
   tolua_function(tolua_S,"getChecked",tolua_UIFramework_CCtrlCheckBox_getChecked00);
   tolua_function(tolua_S,"setHighlighted",tolua_UIFramework_CCtrlCheckBox_setHighlighted00);
   tolua_function(tolua_S,"setChecked",tolua_UIFramework_CCtrlCheckBox_setChecked00);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlCheckBox___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlStaticEx","CCtrlStaticEx","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCtrlStaticEx");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlStaticEx_create00);
   tolua_function(tolua_S,"setString",tolua_UIFramework_CCtrlStaticEx_setString00);
   tolua_variable(tolua_S,"__CCScrollViewDelegate__",tolua_get_CCtrlStaticEx___CCScrollViewDelegate__,NULL);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlStaticEx___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCtrlPage","CCtrlPage","CCLayer",NULL);
  tolua_beginmodule(tolua_S,"CCtrlPage");
   tolua_function(tolua_S,"create",tolua_UIFramework_CCtrlPage_create00);
   tolua_function(tolua_S,"AddPageItem",tolua_UIFramework_CCtrlPage_AddPageItem00);
   tolua_function(tolua_S,"GetPageCount",tolua_UIFramework_CCtrlPage_GetPageCount00);
   tolua_function(tolua_S,"RemovePageItem",tolua_UIFramework_CCtrlPage_RemovePageItem00);
   tolua_function(tolua_S,"ClearPages",tolua_UIFramework_CCtrlPage_ClearPages00);
   tolua_function(tolua_S,"SetCurPageIndex",tolua_UIFramework_CCtrlPage_SetCurPageIndex00);
   tolua_function(tolua_S,"GetCurPageIndex",tolua_UIFramework_CCtrlPage_GetCurPageIndex00);
   tolua_function(tolua_S,"GetBgAni",tolua_UIFramework_CCtrlPage_GetBgAni00);
   tolua_function(tolua_S,"SetBgAni",tolua_UIFramework_CCtrlPage_SetBgAni00);
   tolua_variable(tolua_S,"__CCScrollViewDelegate__",tolua_get_CCtrlPage___CCScrollViewDelegate__,NULL);
   tolua_variable(tolua_S,"__CCMyWndObject__",tolua_get_CCtrlPage___CCMyWndObject__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_UIFramework (lua_State* tolua_S) {
 return tolua_UIFramework_open(tolua_S);
};
#endif

