// VanillaSkyDlg.h : header file
//

#if !defined(AFX_VANILLASKYDLG_H__AACA4666_AB53_4A39_947C_A90252891A7C__INCLUDED_)
#define AFX_VANILLASKYDLG_H__AACA4666_AB53_4A39_947C_A90252891A7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ShootingStar.h"
/////////////////////////////////////////////////////////////////////////////
// CVanillaSkyDlg dialog

class CVanillaSkyDlg : public CDialog
{
// Construction
public:
	~CVanillaSkyDlg();
	CVanillaSkyDlg(CWnd* pParent = NULL);	// standard constructor
	void DrawSky(bool backStar);
	void SetBackStar( long MaxNumberOfStars );
	void CreateShootingStar();
	BOOL PreTranslateMessage(MSG* pMsg);
	CRect SetRandStar();

	CShootingStar *m_star;
	CRect m_rectWholeSky;
	CRect m_rect;
	long m_nShooting;
	CDC *m_dc;
	CRect m_starRect;
	bool m_bFirst;
	bool m_bShowCount;
	int m_iFallingRate;
	
	CPoint m_pAllStars[5000];
	COLORREF m_colAllStarColor[5000];
// Dialog Data
	//{{AFX_DATA(CVanillaSkyDlg)
	enum { IDD = IDD_VANILLASKY_DIALOG };
	CStatic	m_ctlStaticCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVanillaSkyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVanillaSkyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAboutbox();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPoint m_pBirth;
	CPoint m_pDie;
	CPoint m_pMousePoint;


	long m_pMoveX;
	long m_pMoveY;
	int m_ibusy;

	COLORREF m_colPastSky;
	COLORREF m_colPastSky1;
	COLORREF m_colPastSky2;
	COLORREF m_colPastSky3;
	long m_nMaxNumberOfStars;



};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VANILLASKYDLG_H__AACA4666_AB53_4A39_947C_A90252891A7C__INCLUDED_)
