// ShootingStar.cpp: implementation of the CShootingStar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VanillaSky.h"
#include "VanillaSkyDlg.h"
#include "ShootingStar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShootingStar::CShootingStar(COLORREF colStar, CRect rectSky, CRect starRect, CDC *dc, HWND hwnd, CPoint *allstars, COLORREF *colstars)
{
	m_mainhWnd = hwnd;
	m_colStar = colStar;
	m_rectSky = rectSky;
	m_dc = dc;
	m_pBirth = 0;
	m_pDie = 0;
	m_pAllStars = allstars;
	m_colAllStarColor = colstars;

	SetShootingPos( starRect );
	Shoot();
}

CShootingStar::~CShootingStar()
{
	CVanillaSkyDlg* mainDlg = (CVanillaSkyDlg*)CWnd::FromHandle(m_mainhWnd);
	mainDlg->ReleaseDC( m_dc );
	//ReleaseDC( m_mainhWnd, (HDC)m_dc );
}

void CShootingStar::SetShootingPos( CRect starRect )
{
	m_pBirth.x = starRect.left;
	m_pBirth.y = starRect.top;
	m_pDie.x = starRect.right;
	m_pDie.y = starRect.bottom;

	m_pMoveX = (m_pDie.x - m_pBirth.x) / NUMBER_SHOOTING_FRAMES;
	m_pMoveY = (m_pDie.y - m_pBirth.y) / NUMBER_SHOOTING_FRAMES;
}

void CShootingStar::Shoot()
{
	// ���ϸ��̼� ȿ��
	for( int i=1;i<=NUMBER_SHOOTING_FRAMES;i++ ) {

		// ������ ���� ����� �׾������.
		if( i == NUMBER_SHOOTING_FRAMES ) {
			m_dc->SetPixel( m_pBirth, m_colPastSky );
			break;
		}
		// ó�� ��Ÿ���� �ڽ��� ���밡 ���� ���� �����Ƿ�..
		if( i != 1 ) 
			m_dc->SetPixel( m_pBirth, m_colPastSky );

		// �̵�
		m_pBirth.x += m_pMoveX;
		m_pBirth.y += m_pMoveY;

		// �̵��� �� �ڸ��� ������ �˾Ƴ���...
		// ���ư��� ���� ��ġ�� �� ���� ��������......
		//m_colPastSky = m_dc->GetPixel( m_pBirth );
		m_colPastSky = FindSkyPixel( m_pBirth );

		// �� �ڸ��� ���� �׸���.
		m_dc->SetPixel( m_pBirth, m_colStar );

		// ������ ����
		Sleep(SPEED_SHOOTING);
	}
	delete this;

	return;
}

COLORREF CShootingStar::FindSkyPixel( CPoint bgsky )
{
	double c = 255 / m_rectSky.bottom;
	long k = bgsky.y - m_rectSky.bottom/2;

	for( int i=0;i<NUMBER_STARS;i++ )
		if( m_pAllStars[i] == bgsky )
			return m_colAllStarColor[i];

	if( bgsky.y < m_rectSky.bottom / 2 )
		return RGB( 0, 0, c*bgsky.y*0.5 );

	else 
		return RGB( c*k, c*k*0.3, c*bgsky.y*0.5 );
}

