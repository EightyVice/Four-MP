#pragma once

#include "CGUI.h"

class CWindow : public CElement
{
	bool m_bMaximized, m_bDragging, m_bVisible;
	CPos posDif;
	std::vector<CElement*> m_vElements;
	CElement * m_pFocussedElement;

	bool m_bCloseButtonEnabled;
	CTimer m_tCloseButtonPressed;
	bool m_bTitleVisible;
	bool m_bTab;

	CColor * pTitle, * pBody;
	CTexture * pTitlebar, * pButton;
	CTexture * tBorder[8];
	int hTitleBar, hwBorder[3], mButton[2], sButton[2]; 
public:
	std::vector<CLine*> m_eLine[2];
	std::vector<CBox*> m_eBox[2];
	std::vector<CImage*> m_eImage[2];

	CWindow( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String = NULL, const uichar * String2 = NULL, tAction Callback = NULL );
	~CWindow();

	void AddElement( CElement * pElement );

	void Draw();
	void PreDraw();
	bool MouseMove( CMouse * pMouse, bool over = 1 );
	bool KeyEvent( SKey sKey );

	void SetMaximized( bool bMaximized );
	bool GetMaximized();

	void SetVisible( bool bVisible );
	bool IsVisible();

	void SetDragging( bool bDragging );
	bool GetDragging();

	void SetCloseButton( bool bEnabled );
	bool GetCloseButton();

	void SetFocussedElement( CElement * pElement );
	CElement * GetFocussedElement();

	CElement * GetNextElement( CElement * pElement );
	CElement * GetElementByString( const uichar * pszString, int iIndex = 0 );
	
	void BringToTop( CElement * pElement );

	void UpdateTheme( int iIndex );

	void SetTitleVisible( bool v );
	bool GetTitleVisible();

	int GetTitleBarHeight();

	virtual void OnLostDevice();
	virtual void OnResetDevice();
};