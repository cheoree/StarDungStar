// SkyMenu.cpp : implementation file
//

#include "stdafx.h"
#include "VanillaSky.h"
#include "SkyMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyMenu dialog


CSkyMenu::CSkyMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CSkyMenu::IDD_ABOUTBOX, pParent)
{
	//{{AFX_DATA_INIT(CSkyMenu)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSkyMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkyMenu)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkyMenu, CDialog)
	//{{AFX_MSG_MAP(CSkyMenu)
	ON_COMMAND(IDD_ABOUTMENU, OnAboutmenu)
	ON_COMMAND(IDD_ABOUTBOX, OnAboutbox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyMenu message handlers

void CSkyMenu::OnAboutmenu() 
{
	//CAboutDlg menuAbout;
	
}

void CSkyMenu::OnAboutbox() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}
