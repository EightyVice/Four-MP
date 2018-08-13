#pragma once

#include "CGUI.h"

struct ImageColumn
{
	CTexture * tTrue;
	CTexture * tFalse;
	CTexture * tTitle;

	int Width, Height;
};

class CListView : public CElement
{
	int Count;
	int * Widths;
	int * Poss;
	ImageColumn * imgColumn;

	int m_iMouseOverIndex;
	int m_iMouseSelect;

	CScrollBar * pSlider;

	std::vector<uistring> *m_vRows;
	std::vector<uistring> m_vRowsHelp;
	std::vector<uistring> mTitles;

	CColor * pInner, * pBorder, * pString, * pMouseOverString, * pSelInner, * pSelString;
	CColor * pTitle, * pbTitle, * pbInner, * pTitleString;
public:
	CListView( CGUI *Gui, int X, int Y, int *Width, int Height, int Columns, const uichar * String = NULL, const uichar *String2 = NULL, tAction Callback = NULL );
	~CListView();

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	int GetSize(int Index = 0);

	void PutStr( uistring sString, int Column, int Row = -1, uistring sHelp = _UI("") );
	uistring GetStr( int Row, int Column );

	void SetTitle( uistring sString, int Column = -1 );

	void Clear();
	void UpdateTheme( int iIndex );
	void ShowSlider( bool bShow );

	int GetSelected();
	void SetSelect(int Item = -1);

	uistring GetHelpString(int row);

	void SetColumnImage(int Index, uichar *True, uichar *False, uichar *Title, int W = 16, int H = 16);
};