// ShootingStar.h: interface for the CShootingStar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOOTINGSTAR_H__59074EB4_3061_414B_BFCA_2DF3E1908FD1__INCLUDED_)
#define AFX_SHOOTINGSTAR_H__59074EB4_3061_414B_BFCA_2DF3E1908FD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShootingStar
{
private:
	COLORREF	m_colStar;
	COLORREF	m_colPastSky;
	CRect		m_rectSky;
	long		m_pMoveX;		// 떨어지는 에니메이션 간격
	long		m_pMoveY;
	CPoint		m_pBirth;
	CPoint		m_pDie;
	HWND		m_mainhWnd;
	CPoint		*m_pAllStars;
	COLORREF	*m_colAllStarColor;

public:
	CShootingStar(COLORREF colstar, CRect sky, CRect starRect, CDC *dc, HWND hwnd, CPoint *, COLORREF *);
	virtual ~CShootingStar();
	void SetShootingPos( CRect starRect );
	void Shoot();
	COLORREF FindSkyPixel( CPoint bgcolor );

	CDC			*m_dc;
	bool		m_bDie;

};

#endif // !defined(AFX_SHOOTINGSTAR_H__59074EB4_3061_414B_BFCA_2DF3E1908FD1__INCLUDED_)
