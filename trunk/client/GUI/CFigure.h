#pragma once

#include "CGUI.h"

class CGUI;

class CLine
{
	CGUI *pGui;
	CColor *color;
	int sX, sY, eX, eY, Size;
	CWindow *wParent;
public:
	CLine( CGUI *Gui, int sX, int sY, int eX, int eY, int size, CColor *color, CWindow *eP = NULL);
	~CLine();
	void Draw();
};

class CBox
{
	CGUI *pGui;
	CColor * pInner, * pBorder;
	int X, Y, Width, Height;
	CWindow *wParent;
public:
	CBox( CGUI *Gui, int iX, int iY, int iWidth, int iHeight, CColor *In, CColor *Bor, CWindow *eP = NULL);
	~CBox();
	void Draw();
};

class CImage
{
	CGUI *pGui;
	int X, Y, Width, Height;
	CTexture * pImg;
	CWindow *wParent;
public:
	CImage( CGUI *Gui, int iX, int iY, int iWidth, int iHeight, CTexture *iTxt, CWindow *eP = NULL);
	~CImage();
	void Draw();
	void OnLostDevice();
	void OnResetDevice();
};

