#pragma once

#define SAFE_DELETE( pData ) if( pData ){ delete pData; pData = 0; }

class CTexture;
class CTimer;
class CPos;
class CColor;
class CMouse;
class CKeyboard;
class CElement;
class CWindow;
class CButton;
class CCheckBox;
class CProgressBar;
class CTextBox;
class CListBox;

#include <windowsx.h>
#include <shlwapi.h>

#include <map>
#include <set>
#include <limits>
#include <iomanip>
#include <sstream>
#include <vector>

#include "unistr.h"

#include "D3D9.h"
#include "CD3DRender.h"
#include "TinyXML\tinyxml.h"

#include "CTexture.h"
#include "CFont.h"

#include "CVar.h"
#include "CTimer.h"

#include "CPos.h"
#include "CColor.h"

#include "CMouse.h"
#include "CKeyboard.h"

#include "CFigure.h"

#include "CElement.h"
#include "CText.h"
#include "CWindow.h"
#include "CScrollBar.h"
#include "CButton.h"
#include "CCheckBox.h"
#include "CEditBox.h"
#include "CDropDown.h"
#include "CTextBox.h"
#include "CListBox.h"
#include "CListView.h"

class CGUI
{
	bool m_bVisible;

	CMouse * m_pMouse;
	CKeyboard * m_pKeyboard;
	CFont * m_pFont;

	IDirect3DDevice9 * m_pDevice;

	ID3DXSprite * m_pSprite;

	ID3DXLine * m_pLine;
	
	CTimer m_tPreDrawTimer;

	std::vector<CWindow*> m_vWindows;
	CWindow * m_wFocus;

	uistring m_sCurTheme;
	std::vector<CLine*> m_eLine[2];
	std::vector<CBox*> m_eBox[2];
	std::vector<CText*> m_eText[2];
	std::vector<CImage*> m_eImage[2];

	typedef std::map<uistring, SElement*> tTheme;
	std::map<uistring, tTheme> m_mThemes;

	CRITICAL_SECTION cs;
public:

	CGUI( IDirect3DDevice9 * pDevice );
	~CGUI();

	void LoadFont(int size = 10, uichar *font = _UI("Tahoma"));
	void SetFontColors(int Index, int r, int g, int b, int a);
	void LoadInterfaceFromFile( const uichar * pszFilePath, const uichar * dir = _UI("") );
	void UpdateFromFile( const uichar * pszFilePath );

	void FillArea( int iX, int iY, int iWidth, int iHeight, D3DCOLOR d3dColor );
	void DrawLine( int iStartX, int iStartY, int iEndX, int iEndY, int iWidth, D3DCOLOR d3dColor );
	void DrawOutlinedBox( int iX, int iY, int iWidth, int iHeight, D3DCOLOR d3dInnerColor, D3DCOLOR d3dBorderColor );

	void AddWindow( CWindow * pWindow );
	void BringToTop( CWindow * pWindow );

	void Draw();
	void PreDraw();
	void MouseMove( CMouse * pMouse );
	bool KeyEvent( SKey sKey );

	void OnLostDevice();
	void OnResetDevice();

	CMouse * GetMouse();
	CKeyboard * GetKeyboard();

	IDirect3DDevice9 * GetDevice();
	CFont * GetFont();
	ID3DXSprite * GetSprite();

	CWindow * GetWindowByString( uistring sString, int iIndex = 0 );

	SElement * GetThemeElement( uistring sElement );

	void SetVisible( bool bVisible );
	bool IsVisible();

	void SetVarString(const uichar *name, uistring value);
	void SetVarInt(const uichar *name, int value);
	void SetVarBool(const uichar *name, bool value);

	bool IsFocus(CWindow * w);

	std::map<uistring,CVar*> Cvars;
};