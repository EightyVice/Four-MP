#pragma once

#include "CGUI.h"

class CButton : public CElement
{
	CTimer m_tPressed;

	CTexture * pButton[3];
	CColor * pString;

	bool m_bVisibleBack;

	int SizeEdge;

public:
	CButton( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CButton();

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	void SetBackVisible(bool v);
	bool GetBackVisible();

	void UpdateTheme( int iIndex );
};