#pragma once

#include "CGUI.h"

class CScrollBar : public CElement
{
	bool m_bMouseOver[ 3 ], m_bPressed[ 3 ], m_bDragged;

	SElement * m_pThemeElement[ 3 ];
	SElementState * m_pElementState[ 3 ];

	void SetDragged( bool bDragged );
	bool GetDragged();

	int ibHeight, ibWidth, isHeight;
	CColor *back;
	CTexture * pSlider, * pUpArrow, * pDownArrow;

	int m_iMinValue, m_iMaxValue, m_iValue, m_iStep;
	bool m_bShow;

public:
	CScrollBar( CGUI *Gui, CPos relPos, int iHeight );
	~CScrollBar();

	void Draw( CPos basePos );
	void PreDraw();
	bool MouseMove( CPos basePos, CMouse * pMouse );
	bool KeyEvent( CPos basePos, SKey sKey );

	int GetMinValue();
	int GetMaxValue();
	int GetValue();
	int GetStep();

	int GetWidth();

	void SetMinValue( int iMinValue );
	void SetMaxValue( int iMaxValue );
	void SetValue( int iValue );
	void SetStep( int iStep );

	void SetShow( bool bShow );
	bool GetShow();

	void UpdateTheme( int iIndex );

	int GetSliderWidth();
};

uistring MinValue( const uichar *, CElement * pElement );
uistring MaxValue( const uichar *, CElement * pElement );
uistring SliderValue( const uichar *, CElement * pElement );