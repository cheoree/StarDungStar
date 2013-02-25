// VanillaSkyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VanillaSky.h"
#include "VanillaSkyDlg.h"
#include "ShootingStar.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CALLBACK TimeProc(HWND hwnd, UINT iMsg, UINT wParam, DWORD lParam);
UINT threadShoot(LPVOID lparam);
UINT threadCount(LPVOID lparam);
// 다이알로그에 컨트롤이 하나라도 있을 때 OnKeyDown함수 문제 -> PretrenslateMsg()로 대체
// 마찬가지로 타이머도..
// 컨트롤배경 투명으로 했을 때 텍스트는 계속 겹치는 현상. -> InvaledateRect
// 타이머 문제 해결. -> OnInitDialog()함수가 아닌 다른 곳에서 처음의 SetTimer()를 호출해서..
// 시간이 지날 수록 버벅거림 문제 ->
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVanillaSkyDlg dialog

CVanillaSkyDlg::CVanillaSkyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVanillaSkyDlg::IDD, pParent)
{
	m_pBirth = NULL;
	m_pMoveX = 0;
	m_pMoveY = 0;

	m_nShooting = 0;
	m_iFallingRate = 100;

	m_bFirst = false;
	m_bShowCount = true;

	for( int i=0;i<3000;i++ ) {
		m_pAllStars[i].x = 0;
		m_pAllStars[i].y = 0;
		m_colAllStarColor[i] = 0;
	}
	//{{AFX_DATA_INIT(CVanillaSkyDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CVanillaSkyDlg::~CVanillaSkyDlg()
{
	//ReleaseDC( m_dc );
}

void CVanillaSkyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVanillaSkyDlg)
	DDX_Control(pDX, IDC_STATICCOUNT, m_ctlStaticCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVanillaSkyDlg, CDialog)
	//{{AFX_MSG_MAP(CVanillaSkyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDD_ABOUTBOX, OnAboutbox)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVanillaSkyDlg message handlers

BOOL CVanillaSkyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	
	
	// TODO: Add extra initialization here
	GetClientRect(m_rectWholeSky);
	m_rectWholeSky.NormalizeRect();

	m_ctlStaticCount.GetClientRect(m_rect);
	//rect.NormalizeRect();
	m_rect.left = m_rectWholeSky.right - m_rect.right;
	m_rect.right = m_rectWholeSky.right;
	m_rect.top = m_rectWholeSky.bottom - (m_rect.bottom + 20 );
	m_rect.bottom = m_rectWholeSky.bottom;
	// 윈도우 창 모양 바꾸기
	//CRgn rgn;
	//rgn.CreateEllipticRgnIndirect( m_rectWholeSky );
	//SetWindowRgn( rgn, true );

	// 타이틀 바가 없을 경우 최소화되었을 때도 타이틀바가 있는 것처럼..
	//ModifyStyle(0, WS_SYSMENU);
	//SetWindowText(_T("Vanilla Sky"));

	// 윈도우 최상위 or 취소
	//SetWindowPos(&wndNoTopMost, 300, 500, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	m_bFirst = true;

	SetTimer( ID_SHOOTING_TIMER, 50, TimeProc );
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVanillaSkyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVanillaSkyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawSky(BOOL_BACK_STAR);
		CDC *dc = GetDC();
		m_dc = dc;
		//CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVanillaSkyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVanillaSkyDlg::SetBackStar(long MaxNumberOfStars)
{
	long r, g, b;
	long rRand = 255;
	long gRand = 255;
	long bRand = 255;

	long xRand = m_rectWholeSky.right - m_rectWholeSky.left;
	long yRand = m_rectWholeSky.top - m_rectWholeSky.bottom;

	srand( (unsigned)time(NULL) );

	for( int j=0;j<MaxNumberOfStars;j++ ) {
		m_pAllStars[j].x = rand() % xRand;
		m_pAllStars[j].y = rand() % yRand;

		do { // 별들의 밝기 제한
			r = rand() % rRand;
		}while( r < LUMIN_STAR_MIN );
		do {

			g = rand() % gRand;
		}while( g < LUMIN_STAR_MIN );
		do {
			b = rand() % bRand;
		}while( b < LUMIN_STAR_MIN );

		m_colAllStarColor[j] = RGB( r, g, b );
	}	

	m_nMaxNumberOfStars = MaxNumberOfStars;
}

void CVanillaSkyDlg::DrawSky(bool a_bBackStar)
{
	if( m_bFirst ) 	{
		if(a_bBackStar)
			SetBackStar( NUMBER_STARS );
		m_bFirst = false;
	}

	CPaintDC dc(this);
	CPoint pStart;
	CPoint pEnd;
	CPen *lOldPen;

	int k=0;

	double c = 255 / m_rectWholeSky.bottom;
	CPen pen;
	
	// 세가지 색의 경우로 그라데이션
	for( int i=0;i<m_rectWholeSky.bottom;i++ ) {
		if( m_rectWholeSky.bottom / 2 > i ) {
			CPen lSolidPen( PS_SOLID, 1, RGB( 0, 0, c*i*0.5 ) );
			pStart.x = m_rectWholeSky.left;
			pStart.y = m_rectWholeSky.top + i;
			pEnd.x = m_rectWholeSky.right;
			pEnd.y = m_rectWholeSky.top + i;
			lOldPen = dc.SelectObject(&lSolidPen);
			dc.MoveTo(pStart);
			dc.LineTo(pEnd);
			dc.SelectObject(lOldPen);
		}
		else {
			CPen lSolidPen( PS_SOLID, 1, RGB( c*k, c*k*0.3, c*i*0.5 ) );
			pStart.x = m_rectWholeSky.left;
			pStart.y = m_rectWholeSky.top + i;
			pEnd.x = m_rectWholeSky.right;
			pEnd.y = m_rectWholeSky.top + i;
			lOldPen = dc.SelectObject(&lSolidPen);
			dc.MoveTo(pStart);
			dc.LineTo(pEnd);
			dc.SelectObject(lOldPen);
			k++;
		}
	}
	 
	if( a_bBackStar ) 
		for( int j=0;j<m_nMaxNumberOfStars;j++ )
			dc.SetPixel( m_pAllStars[j], m_colAllStarColor[j] );

	dc.SelectObject(lOldPen);
	// 0.1 초 떨어지기 시작

	//m_dc = &dc;
}

CRect CVanillaSkyDlg::SetRandStar()
{
	CRect starRect;

	CRect lRect;
	GetClientRect(lRect);
	lRect.NormalizeRect();

	long birth_x, birth_y, die_x, die_y;
	long lVert = lRect.bottom - lRect.top;
	long lHor = lRect.right - lRect.left;

	if( lVert == 0 || lHor == 0 ) return NULL;

	// 위에서 아래로 향하도록.
	do{
		birth_y = rand() % (lVert + 100);
		die_y = rand() % (lVert + 100);
		if( birth_y <= 10 ) birth_y = 0;
	}while( die_y - birth_y < HEIGHT_SHOOTING_MIN || die_y - birth_y > HEIGHT_SHOOTING_MAX ); // 높이 차가 20이상으로

	// 너무 누워서 날아가지 못하도록
	do{
		birth_x = rand() % (lHor+ 50);
		die_x = rand() % (lHor+50);
	}while( abs(die_x - birth_x) > WIDTH_SHOOTING_MAX ); // 너비 차를 50 이하로

	starRect.left = birth_x;
	starRect.right = die_x;

	starRect.top = birth_y;
	starRect.bottom = die_y;

	return starRect;
}

/*
//////////////////////////////////////////////////////////////
// 별똥별의 위치를 세팅, 쏠 준비를 한다.
void CVanillaSkyDlg::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == ID_SHOOTING_TIMER ) {
		m_starRect = SetRandStar();

		AfxBeginThread( threadShoot, (LPVOID)this );

		KillTimer( ID_SHOOTING_TIMER );
		
		long iFall = (rand() % m_iFallingRate) + RATE_APPEAR_MIN; // 별똥별 발생 최소 간격
		SetTimer( ID_SHOOTING_TIMER, iFall, NULL );	
	}
	CDialog::OnTimer(nIDEvent);
}
*/

void CALLBACK TimeProc(HWND hwnd, UINT iMsg, UINT wParam, DWORD lParam)
{
	CVanillaSkyDlg* mainDlg = (CVanillaSkyDlg*)CWnd::FromHandle(hwnd);
	mainDlg->m_starRect = mainDlg->SetRandStar();

	AfxBeginThread( threadShoot, (LPVOID)mainDlg );
	if( mainDlg->m_bShowCount )
		AfxBeginThread( threadCount, (LPVOID)mainDlg );

	KillTimer( hwnd, ID_SHOOTING_TIMER );	
	long iFall = (rand() % mainDlg->m_iFallingRate) + RATE_APPEAR_MIN; 
	SetTimer( hwnd, ID_SHOOTING_TIMER, iFall, TimeProc );
}

BOOL CVanillaSkyDlg::PreTranslateMessage(MSG* pMsg) 
{
	CString temp;
	if(pMsg->message == WM_KEYDOWN) {
		switch( pMsg->wParam ) {
		case 0x20 :
			if( !m_bShowCount ) m_bShowCount = true;
			else m_bShowCount = false;
			//m_starRect = SetRandStar();
			//AfxBeginThread( threadShoot, (LPVOID)this );
			break;
		case 33 :
			m_iFallingRate -= 50;
			if( m_iFallingRate <= TIME_SHOOTING_MIN ) {
				m_iFallingRate = 1;
				return false;
			}
			break;
		case 34 :
			if( m_iFallingRate >= (TIME_SHOOTING_MAX - TIME_SHOOTING_MIN) ) return false;
			m_iFallingRate += 50;
			break;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CVanillaSkyDlg::CreateShootingStar()
{	
	CShootingStar *star = new CShootingStar( RGB(255, 255, 255), m_rectWholeSky, m_starRect, m_dc, m_hWnd, m_pAllStars, m_colAllStarColor );
}

void CVanillaSkyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

UINT threadShoot(LPVOID lParam)
{
	CVanillaSkyDlg * mainDlg = (CVanillaSkyDlg *)lParam;

	mainDlg->CreateShootingStar();
	mainDlg->m_nShooting++;

	return 0;
}

UINT threadCount(LPVOID lParam)
{
	CVanillaSkyDlg * mainDlg = (CVanillaSkyDlg *)lParam;
	CString temp;
	CRect rect;
	CPoint textSize;
	temp.Format("%d", mainDlg->m_nShooting);
	
	mainDlg->m_ctlStaticCount.SetWindowText(temp);
	CDC *dc = mainDlg->m_ctlStaticCount.GetDC();
	textSize = dc->GetTextExtent( temp );
	
	rect.left = mainDlg->m_rectWholeSky.right - textSize.x;
	rect.right = mainDlg->m_rectWholeSky.right;
	rect.top = mainDlg->m_rectWholeSky.bottom - textSize.y;
	rect.bottom = mainDlg->m_rectWholeSky.bottom;

	mainDlg->InvalidateRect(rect, false);

	return 0;
}

void CVanillaSkyDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu Menu;
	CMenu* pPopupMenu;

	if( Menu.LoadMenu(IDR_MENU1) ) {
		pPopupMenu = Menu.GetSubMenu( 0 );
		if( pPopupMenu ) {
			pPopupMenu->TrackPopupMenu( TPM_LEFTALIGN|TPM_LEFTBUTTON, 
			point.x, point.y, pWnd );
		}
	}
}


void CVanillaSkyDlg::OnAboutbox() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}



HBRUSH CVanillaSkyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//if( nCtlColor == CTLCOLOR_STATIC )	{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor( RGB(255, 255, 255) );
	//hbr = m_staticBrush;
	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	// TODO: Return a different brush if the default is not desired
}
