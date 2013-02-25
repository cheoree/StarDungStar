// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__183A050F_BA46_4DF1_AA20_34B8D202D5B2__INCLUDED_)
#define AFX_STDAFX_H__183A050F_BA46_4DF1_AA20_34B8D202D5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define NUMBER_STARS					700		// 배경 별 갯 수
#define	NUMBER_SHOOTING_FRAMES			35		// 프레임 수
#define SPEED_SHOOTING					10		// 속도
#define RATE_APPEAR_MIN					1		
#define RATE_APPEAR_MAX					1000	// 발생 시간 범위
#define TIME_SHOOTING_MIN				1
#define TIME_SHOOTING_MAX				3000
#define WIDTH_SHOOTING_MAX				80		// 별똥별의 가로 범위
#define HEIGHT_SHOOTING_MAX				146		// 태어나서 죽는 각도 수직 최대
#define HEIGHT_SHOOTING_MIN				50
#define LUMIN_STAR_MIN					120
#define BOOL_BACK_STAR					true
#define COLOR_SHOOTINGSTAR				RGB( 255, 255, 255 )

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__183A050F_BA46_4DF1_AA20_34B8D202D5B2__INCLUDED_)
