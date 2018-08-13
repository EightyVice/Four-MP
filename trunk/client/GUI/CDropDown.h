#pragma once

#include "CGUI.h"

class CDropDown : public CElement
{
	bool m_bDropped;
	int m_iMouseOverIndex, m_iSelected;
	
	struct SEntry
	{
		uistring m_sString, m_sValue;

		SEntry( uistring sString, uistring sValue )
		{
			m_sString = sString;
			m_sValue = sValue;
		}
	};
	std::vector<SEntry> m_vEntrys;

	CColor * pInner, * pBorder, * pString, * pSelectedInner, * pSelectedString;
	CTexture * pButton, *pLeft, *pMiddle;
	int iEdge, iButton, iPadding;

public:
	CDropDown( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CDropDown();

	void Draw();
	bool MouseMove( CMouse * pMouse, bool );
	bool KeyEvent( SKey sKey );

	void AddElement( uistring sElem, uistring sValue );
	uistring GetValue();

	void UpdateTheme( int iIndex );
};