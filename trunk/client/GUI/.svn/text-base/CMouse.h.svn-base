#pragma once

#include "CGUI.h"

class CMouse
{
	CGUI *pGui;
	IDirect3DDevice9 * m_pDevice;
	CPos m_pos, m_bpos;
	int size;

	CColor * m_pInnerColor, * m_pBorderColor;
	CTexture * pCursor;

	CElement * m_pDraggingElement;

	int m_iLeftButton, m_iRightButton, m_iMiddleButton, m_iWheel;
	CTimer m_tLeftButton, m_tRightButton, m_tMiddleButton;
public:
	CMouse( CGUI *Gui, IDirect3DDevice9 * pDevice, ID3DXSprite * pSprite );
	~CMouse();

	bool HandleMessage( unsigned int uMsg, WPARAM wParam, LPARAM lParam );

	void SetPos( int iX, int iY );
	void SetPos( CPos cPos );
	CPos GetPos();

	bool InArea( int iX, int iY, int iWidth, int iHeight );
	bool InArea( CElement * pElement, int iHeight = 0 );

	void Draw();

	int GetLeftButton( int iState = -1 );
	int GetRightButton( int iState = -1 );
	int GetMiddleButton( int iState = -1 );
	int GetWheel( int iState = -1 );

	void SetLeftButton( int iState );
	void SetRightButton( int iState );
	void SetMiddleButton( int iState );
	void SetWheel( int iState );

	void SetDragging( CElement * pElement );
	CElement * GetDragging();

	void SavePos();
	void LoadPos();
	CPos GetSavedPos();

	void SetSize(int);
	int GetSize();

	void OnLostDevice();
	void OnResetDevice();
};