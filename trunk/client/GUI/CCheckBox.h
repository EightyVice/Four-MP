#pragma once

#include "CGUI.h"

class CCheckBox : public CElement
{
	bool m_bChecked;

	CColor * pString;
	CTexture * tCheck, * tChecked;

public:
	CCheckBox( CGUI *Gui, int X, int Y, int Width, int Height, bool Checked = 0, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CCheckBox();

	bool GetChecked();
	void SetChecked( bool bChecked );

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	void UpdateTheme( int iIndex );
};