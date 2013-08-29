
#ifndef __CQ_GLOBAL_H__
#define __CQ_GLOBAL_H__

#include "define.h"

#if CQ_PLATFORM == CQ_PLATFORM_WIN32
	#define TRY try
	#define CATCH(a) catch(a)
#else

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

	#define TRY
	#define CATCH(a)

	// object-c把BOOL typedef 成 unsigned char
	#ifndef __OBJC__
		typedef int                 BOOL;
	#endif
	typedef unsigned char       BYTE;
	typedef unsigned short      WORD;
	typedef unsigned int       DWORD;

	// typedef void                VOID;
	#define VOID                void
	typedef char                CHAR;
	typedef unsigned char       UCHAR;
	typedef short               SHORT;
	typedef unsigned short      USHORT;
	typedef int                 INT;
	typedef unsigned int        UINT;
	typedef long                LONG;
	typedef unsigned long       ULONG;
	typedef float               FLOAT;
	typedef double              DOUBLE;

	typedef char *PSTR, *LPSTR, *LPTSTR;
	typedef const char *PCSTR, *LPCSTR;
	typedef const wchar_t *LPCWSTR;
	typedef void *              LPVOID;
	typedef void *              HANDLE;

	typedef long long           I64;
	typedef unsigned long long  UI64;
	typedef long long           INT64;
	typedef DWORD               D3DCOLOR;

	typedef int                 SOCKET;
	typedef DWORD               WPARAM;
	typedef DWORD               LPARAM;
	typedef void*               HWND;

	typedef struct tagSIZE
		{
		LONG cx;
		LONG cy;
		} 	SIZE;

	typedef struct tagPOINT
	{
		LONG x;
		LONG y;
	} 	POINT, *LPPOINT;

	typedef struct tagRECT
	{
		LONG left;
		LONG top;
		LONG right;
		LONG bottom;
	} 	RECT;

	typedef RECT* LPRECT;
	typedef const RECT* LPCRECT;

	struct CMyPos
	{
		int x;
		int y;
	};
	
	struct CMySize
	{
		int iWidth;
		int iHeight;
	};

	//==================================================================================================
	// other macros
	#define FALSE               0
	#define TRUE                1
	#define _MAX_PATH           260
	#define MAX_PATH 256

	#define IN
	#define OUT
	#define OPTIONAL
	#define CONST               const

	#define D3DCOLOR_ARGB(a,r,g,b) \
		((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
	#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
	#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

	#define D3DCOLOR_COLORVALUE(r,g,b,a) \
		D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))
	#define SUCCEEDED(x) (((long)(x)) >= 0)

#endif

#define VERSION_RES_ID 10426

//==================================================================================================
// I64 format
// 提示：VC6只能使用%I64d，而GCC系列一般使用%lld
// 可以用宏来统一
// 以前写：printf("value = %I64d\n", v);
// 现在改为：printf("value = " I64_FORMAT "\n", v);
//
// VC6的int64常数使用i64结尾，例如1000i64，GCC写为1000LL
// 用宏来统一，写为LEXICAL_I64(1000)
#ifdef _MSC_VER
#	define I64_FORMAT       "%I64d"
#	define UI64_FORMAT      "%I64u"
#	define LEXICAL_I64(x)   x##i64
#else
#	define I64_FORMAT       "%lld"
#	define UI64_FORMAT      "%llu"
#	define LEXICAL_I64(x)   x##LL
#endif



//==================================================================================================
// special
#define ShowStringCommon                ShowString
#define ShowEmotionStringCommon(posX, posY, color, string, icon, fontname, fontsize, antialias, imgSize, imgOffsetX, imgOffsetY, style, secondColor, offset) \
	ShowEmotionString((posX), (posY), (color), (string), (icon), (fontname), (fontsize), (imgSize), (imgOffsetX), (imgOffsetY), (style), (secondColor), (offset))
#define CalcuTextExtentCommon           CalcuTextExtent

#define DATA_THRED_EXIGENCE_IMMEDIATE   C3_EXIGENCE_IMMEDIATE
#define EXIGENCE_NORMAL                 C3_EXIGENCE_NORMAL
#define EXIGENCE_IMMEDIATE              C3_EXIGENCE_IMMEDIATE
#ifndef _ASSERT
#define _ASSERT(x)          assert(x)
#endif

#include <cstring>

#ifdef _MSC_VER
//==================================================================================================
// for Microsoft Visual C++
#	pragma warning (disable: 4996)
#	pragma warning (disable: 4800)
#	pragma warning (disable: 4068)

class CPoint : public POINT {
public:
	CPoint() {
		x = 0;
		y = 0;
	}

	CPoint(int cx, int cy) {
		x = cx;
		y = cy;
	}

	bool operator ==(const CPoint& other) const {
		return x == other.x && y == other.y;
	}

	bool operator !=(const CPoint& other) const {
		return !(*this == other);
	}

	CPoint& operator +=(const CPoint& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	CPoint& operator -=(const CPoint& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	const CPoint operator +(const CPoint& rhs) const {
		CPoint tmp = *this;
		tmp += rhs;
		return tmp;
	}

	const CPoint operator -(const CPoint& rhs) const {
		CPoint tmp = *this;
		tmp -= rhs;
		return tmp;
	}
};

class CRect : public RECT {
public:
	CRect() {
		left = top = right = bottom = 0;
	}
	
	CRect(int l, int t, int r, int b) {
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	
	CRect(const RECT& rc) {
		left = rc.left;
		top = rc.top;
		right = rc.right;
		bottom = rc.bottom;
	}
	
	int Width() const {
		return right - left;
	}
	
	int Height() const {
		return bottom - top;
	}
	
	operator LPRECT() {
		return this;
	}
	
	operator LPCRECT() const {
		return this;
	}
	
	void SetRect(int x1, int y1, int x2, int y2) {
		left = x1;
		top = y1;
		right = x2;
		bottom = y2;
	}
	
	void NormalizeRect() {
		if (left > right) {
			int tmp = left;
			left = right;
			right = tmp;
		}
		
		if (top > bottom) {
			int tmp = top;
			top = bottom;
			bottom = tmp;
		}
	}
	
	BOOL PtInRect(POINT point) const {
		return ::PtInRect(this, point);
	}
	
	BOOL UnionRect(LPCRECT lprc1, LPCRECT lprc2) {
		left = min(lprc1->left, lprc2->left);
		right = max(lprc1->right, lprc2->right);
		top = min(lprc1->top, lprc2->top);
		bottom = max(lprc1->bottom, lprc2->bottom);
		return left < right && top < bottom;
	}
	
	void OffsetRect(int x, int y) {
		left += x;
		right += x;
		top += y;
		bottom += y;
	}
	
	void OffsetRect(POINT point) {
		OffsetRect(point.x, point.y);
	}
	
	void OffsetRect(SIZE size) {
		OffsetRect(size.cx, size.cy);
	}
	
	CRect& operator =(const RECT& rc) {
		if (this != &rc) {
			left = rc.left;
			top = rc.top;
			right = rc.right;
			bottom = rc.bottom;
		}
		
		return *this;
	}
};

struct CMyPos
{
	int x;
	int y;
};

struct CMySize
{
	int iWidth;
	int iHeight;
};

class CDC;
class CBkWnd;
class CFont;
class CDataExchange;

class CWnd {
public:
	void ScreenToClient(LPPOINT pPoint) {
		// do nothing
	}
};

class CDialog : public CWnd {
public:
	CDialog(int idd, CWnd* parent = NULL) {}
protected:
	virtual void DoDataExchange(CDataExchange* pDX) {}
};

class CButton : public CWnd {
};

class CWinApp {};

class CWebBrowser {};

#else // _MSC_VER
//==================================================================================================
// for Apple Xcode
#	define _atoi64             atoll
#	define _snprintf           snprintf
#	define _vsnprintf          vsnprintf
#	define _strdup             strdup
//#	define _stricmp            stricmp
//#	define stricmp(str1, str2) _strnicmp((str1), (str2), 9999)
#	define _strlwr             strlwr
//#	define _itoa               itoa
#	define _int64              I64
#	define __int64             long long
// #	define srand               vc6_srand
// #	define rand                vc6_rand
#	define INVALID_SOCKET      -1
#	define SOCKET_ERROR        -1
#	define WSAEWOULDBLOCK      EWOULDBLOCK
#	define _MAX_FNAME          256
#	define LOWORD(l)           (WORD)(((DWORD)(l)) & 0xFFFF)
#	define HIWORD(l)           (WORD)(((DWORD)(l) >> 16) & 0xFFFF)
#	define LOBYTE(w)           (BYTE)(((WORD)(w)) & 0xFF)
#	define HIBYTE(w)           (BYTE)(((WORD)(w) >> 8) & 0xFF)
#	define MAKELONG(a, b)      ((LONG)(((DWORD)(a) & 0xFFFF) | ((DWORD)(b) & 0xFFFF) << 16))
#	define MAKEWORD(a, b)      ((WORD)(((WORD)(a) & 0xFF) | ((WORD)(b) & 0xFF) << 8))
//#	define __max(a, b)         ((a) > (b)? (a) : (b))
//#	define __min(a, b)         ((a) < (b)? (a) : (b))
//#	define tolower ::tolower

#	define WritePrivateProfileStringA(...)
#	define WritePrivateProfileStructA(...)
#	define WritePrivateProfileSectionA(...)
#	define WritePrivateProfileString
#	define ShellExecute(...)
#	define GetCurrentTime()    TimeGet()

// extern void vc6_srand(unsigned int seed);
// extern int vc6_rand();
// 
// namespace std {
// 	using ::vc6_srand;
// 	using ::vc6_rand;
// }

#pragma pack (push, 2)
typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;
#pragma pack (pop)

typedef struct tagBITMAPINFOHEADER{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

//void _i64toa(I64 i64, char* buf, int radix);
//
//inline void itoa(int i, char* buf, int radix) {
//	return _i64toa(i, buf, radix);
//}

//inline void ltoa(long l, char* buf, int radix) {
//	return _i64toa(l, buf, radix);
//}

inline char* _strrev(char* buf) {
	if (!buf) {
		return NULL;
	}

	size_t len = strlen(buf);
	size_t half = len / 2;
	for (size_t i = 0; i < half; ++i) {
		char tmp = buf[i];
		buf[i] = buf[len - i - 1];
		buf[len - i - 1] = tmp;
	}
	
	return buf;
}

inline void ZeroMemory(void* ptr, size_t size) {
	memset(ptr, 0, size);
}

inline void closesocket(SOCKET s) {
	close(s);
}

inline int WSAGetLastError() {
	return errno;
}

inline void WSACleanup() {
}

inline DWORD GetTickCount() {
	DWORD TimeGet(void);
	return TimeGet();
}

inline unsigned int _rotl(unsigned int value, unsigned int shift) {
	return (value << shift) | (value >> (32 - shift));
}

inline unsigned int _rotr(unsigned int value, unsigned int shift) {
	return (value >> shift) | (value << (32 - shift));
}

// inline int _strnicmp(const char* str1, const char* str2, size_t n) {
// 	for (size_t i = 0; i < n; ++i) {
// 		int c1 = tolower(str1[i]);
// 		int c2 = tolower(str2[i]);
// 
// 		if (c1 != c2) {
// 			return c1 - c2;
// 		}
// 
// 		if (c1 == '\0') {
// 			return 0;
// 		}
// 	}
// 
// 	return 0;
// }

inline void InflateRect(RECT* rect, int dx, int dy) {
	if (!rect) {
		return;
	}
	
	rect->left -= dx;
	rect->right += dx;
	rect->top -= dy;
	rect->bottom += dy;
}

inline bool PtInRect(LPCRECT lprc, POINT pt) {
	return pt.x >= lprc->left
		&& pt.x < lprc->right
		&& pt.y >= lprc->top
		&& pt.y < lprc->bottom;
}

inline void OffsetRect(RECT* rect, int x, int y) {
	if (!rect) {
		return;
	}
	
	rect->left += x;
	rect->right += x;
	rect->top += y;
	rect->bottom += y;
}

inline int MulDiv(int a, int b, int c) {
	I64 tmp = I64(a);
	tmp *= b;
	tmp /= c;
	return static_cast<int>(tmp);
}

inline void PostQuitMessage(int code) {
	// do nothing for now
}

#define CALLBACK
#define DEBUG_NEW new
#define WINAPI
#define __cdecl
#define afx_msg
#define _T(x) x

typedef void* HWND;
typedef void* HICON;
typedef void* HCURSOR;
typedef void* HBITMAP;
typedef void* HBRUSH;
typedef void* HHOOK;
typedef void* HRGN;
typedef void* HTREEITEM;
typedef LONG LRESULT;
typedef const char* LPCTSTR;
typedef unsigned int        UINT;

typedef struct  tagMSG
{
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
}	MSG;

typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;

class CDC;
class CBkWnd;
class CFont;
class CDataExchange;

class CPoint : public POINT
{
public:
	CPoint() {
		x = 0;
		y = 0;
	}

	CPoint(int cx, int cy) {
		x = cx;
		y = cy;
	}

	bool operator ==(const CPoint& other) const {
		return x == other.x && y == other.y;
	}

	bool operator !=(const CPoint& other) const {
		return !(*this == other);
	}

	CPoint& operator +=(const CPoint& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	CPoint& operator -=(const CPoint& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	const CPoint operator +(const CPoint& rhs) const {
		CPoint tmp = *this;
		tmp += rhs;
		return tmp;
	}

	const CPoint operator -(const CPoint& rhs) const {
		CPoint tmp = *this;
		tmp -= rhs;
		return tmp;
	}
};

class CRect : public RECT {
public:
	CRect() {
		left = top = right = bottom = 0;
	}
	
	CRect(int l, int t, int r, int b) {
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	CRect(const RECT& rc) {
		left = rc.left;
		top = rc.top;
		right = rc.right;
		bottom = rc.bottom;
	}

	int Width() const {
		return right - left;
	}
	
	int Height() const {
		return bottom - top;
	}

	operator LPRECT() {
		return this;
	}

	operator LPCRECT() const {
		return this;
	}

	void SetRect(int x1, int y1, int x2, int y2) {
		left = x1;
		top = y1;
		right = x2;
		bottom = y2;
	}

	void NormalizeRect() {
		if (left > right) {
			int tmp = left;
			left = right;
			right = tmp;
		}

		if (top > bottom) {
			int tmp = top;
			top = bottom;
			bottom = tmp;
		}
	}

	BOOL PtInRect(POINT point) const {
		return ::PtInRect(this, point);
	}

// 	BOOL UnionRect(LPCRECT lprc1, LPCRECT lprc2) {
// 		left = __min(lprc1->left, lprc2->left);
// 		right = __max(lprc1->right, lprc2->right);
// 		top = __min(lprc1->top, lprc2->top);
// 		bottom = __max(lprc1->bottom, lprc2->bottom);
// 		return left < right && top < bottom;
// 	}

	void OffsetRect(int x, int y) {
		left += x;
		right += x;
		top += y;
		bottom += y;
	}

	void OffsetRect(POINT point) {
		OffsetRect(point.x, point.y);
	}

	void OffsetRect(SIZE size) {
		OffsetRect(size.cx, size.cy);
	}

	CRect& operator =(const RECT& rc) {
		if (this != &rc) {
			left = rc.left;
			top = rc.top;
			right = rc.right;
			bottom = rc.bottom;
		}

		return *this;
	}
};

class CWnd {
public:
	void ScreenToClient(LPPOINT pPoint) {
		// do nothing
	}
};

class CDialog : public CWnd {
public:
	CDialog(int idd, CWnd* parent = NULL) {}
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX) {}
};

class CButton : public CWnd {
};

class CWinApp {};

class CWebBrowser {};

const int IDD_ABOUTBOX = 100;
const int IDD_MYSHELL_DIALOG = 102;
const int LB_ERR = -1;
const int LIST_TRUNCATIONLEN = 15;

#define WM_USER 0x0400
#define WM_QUIT 0x0012
#define SW_HIDE 0
#define SW_SHOW 5
#define CB_ERR (-1)
#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_ENDSCROLL 8
#define LB_OKAY 0

#define SB_LEFT 6
#define SB_TOP 6
#define SB_RIGHT 7
#define SB_BOTTOM 7

#define CP_ACP 0

// windows虚拟键
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#define VK_BACK           0x08
#define VK_TAB            0x09

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_KANA           0x15
#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19

#define VK_ESCAPE         0x1B

#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */

#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

/*
 * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
 * No other API or message will distinguish left and right keys in this way.
 */
#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010

#endif // _MSC_VER

#endif