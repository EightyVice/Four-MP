#pragma once

#include "CPos.h"

class CGUI;

enum CMSG
{
	KEY_DOWN,
	CLICK,
	GOT_FOCUS,
	LOST_FOCUS,
	CHANGE,
	SELECT,
	MOUSE_OVER,
	MOUSE_OUT,
	END,
};

typedef void ( __cdecl * tAction )( CElement *, CMSG, int );

class CElement
{
	bool m_bHasFocus, m_bMouseOver, m_bEnabled;

	uistring m_sRaw[2], m_sFormatted[2];
	int m_iWidth, m_iHeight;

	CPos m_relPos, m_absPos;
	CWindow * m_pParent;

	tAction m_pAction;

	SElement * m_pThemeElement[ 3 ];
	SElementState * m_pElementState[ 3 ];

	CFont * pFont;
protected:
	CGUI *pGui;
	CRITICAL_SECTION cs;
public:
	~CElement();

	void SetElement( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL, bool abs = 0 );

	void SetParent( CWindow * pParent );
	CWindow * GetParent();

	void SetAction( tAction pAction );
	tAction GetAction();

	void SetRelPos( int X = -1, int Y = -1 );
	void SetRelPos( CPos relPos );
	void SetAbsPos( CPos absPos );

	CPos * GetRelPos();
	CPos * GetAbsPos();

	void SetWidth( int iWidth );
	void SetHeight( int iHeight );

	int GetWidth();
	int GetHeight();

	bool HasFocus();

	void SetString( uistring sString, int iIndex = 0 );
	uistring GetString( bool bReplaceVars = false, int iIndex = 0 );
	uistring GetFormatted( int iIndex = 0 );

	bool GetMouseOver();
	bool SetMouseOver( bool bMouseOver );

	SElement * SetThemeElement( SElement * pThemeElement, int iIndex = 0 );
	SElement * GetThemeElement( int iIndex = 0 );

	void SetElementState( uistring sState, int iIndex = 0 );
	SElementState * GetElementState( int iIndex = 0 );

	void LostFocus();
	void GotFocus();
	void SendMsg(CMSG, int);

	virtual void UpdateTheme( int iIndex );

	virtual void Draw();
	virtual void PreDraw();
	virtual bool MouseMove( CMouse * pMouse, bool over = 1 );
	virtual bool KeyEvent( SKey sKey );

	virtual void OnLostDevice();
	virtual void OnResetDevice();

	CFont * GetFont();
	void SetFont(int size, uichar *name, bool bold, bool italic);
	void SetFont(CFont *font);

	void SetEnabled(bool on = 1);
	bool GetEnabled();
};