#pragma once

#include "CGUI.h"

class CTextBox : public CElement
{
	int m_iStart;
	int m_iLimit;

	CScrollBar * pSlider;

	std::vector<uistring> m_vStrings;

	CColor * pString, * pInner, * pBorder;
public:
	CTextBox( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CTextBox();

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	void AddString( uistring sString );
	void RemoveStrings(int Row, int Count  = 1);
	void Clear();

	void UpdateTheme( int iIndex );
	void ShowSlider( bool bShow );

	void SetMaxStrings(int limit = 128);
	int GetMaxStrings();
};