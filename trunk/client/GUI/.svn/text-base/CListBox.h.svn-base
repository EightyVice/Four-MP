#pragma once

#include "CGUI.h"

class CListBox : public CElement
{
	int m_iMouseOverIndex;
	int m_iMouseSelect;

	CScrollBar * pSlider;

	std::vector<uistring> m_vRows;

	CColor * pInner, * pBorder, * pString, * pMouseOverString, * pSelInner, * pSelString;
public:
	CListBox( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CListBox();

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	void PutStr( uistring sString, int Index = -1 );
	uistring GetRow( int iIndex );

	void Clear();
	int GetSize();

	void UpdateTheme( int iIndex );
	void ShowSlider( bool bShow );

	int GetSelected();
	void SetSelect(int Item = -1);
};