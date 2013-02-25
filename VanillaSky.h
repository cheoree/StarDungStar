// VanillaSky.h : main header file for the VANILLASKY application
//

#if !defined(AFX_VANILLASKY_H__1EDBA6AE_F2AE_4818_A531_5B0089C38258__INCLUDED_)
#define AFX_VANILLASKY_H__1EDBA6AE_F2AE_4818_A531_5B0089C38258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVanillaSkyApp:
// See VanillaSky.cpp for the implementation of this class
//

class CVanillaSkyApp : public CWinApp
{
public:
	CVanillaSkyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVanillaSkyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVanillaSkyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VANILLASKY_H__1EDBA6AE_F2AE_4818_A531_5B0089C38258__INCLUDED_)
