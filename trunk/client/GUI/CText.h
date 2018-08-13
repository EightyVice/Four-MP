#pragma once

#include "CGUI.h"

class CText : public CElement
{
	CColor * pString;
public:
	CText( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CText();

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );

	void UpdateTheme( int iIndex );
};