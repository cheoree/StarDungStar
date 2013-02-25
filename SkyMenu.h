#if !defined(AFX_SKYMENU_H__34B56EEB_B58A_4D97_9639_890829C08539__INCLUDED_)
#define AFX_SKYMENU_H__34B56EEB_B58A_4D97_9639_890829C08539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkyMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkyMenu dialog

class CSkyMenu : public CDialog
{
// Construction
public:
	CSkyMenu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSkyMenu)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyMenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkyMenu)
	afx_msg void OnAboutmenu();
	afx_msg void OnAboutbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYMENU_H__34B56EEB_B58A_4D97_9639_890829C08539__INCLUDED_)
