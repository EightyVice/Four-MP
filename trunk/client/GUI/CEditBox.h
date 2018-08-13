#pragma once

#include "CGUI.h"

class CEditBox : public CElement
{
	int m_iStart, m_iIndex;
	int m_iCursorX;
	CTimer m_tCursorTimer;
	bool m_bCursorState;

	CColor * pString, * pCursor;
	CTexture *pEdit[3];

	int SizeEdge, iPadding;
	bool CenterAlign;
	bool Hide;

public:
	CEditBox( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CEditBox();

	void Draw();

	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	int GetIndex();
	void SetIndex( int iIndex );

	int GetStart();
	void SetStart( int iStart );

	bool GetTextAlign();
	void SetTextAlign( bool Center );
	void HideContent(bool hide);

	void UpdateTheme( int iIndex );
};