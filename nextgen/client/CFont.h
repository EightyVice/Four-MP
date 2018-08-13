#pragma once
#include <d3dx9.h>

class CFont
{
public:
	CFont(IDirect3DDevice9 *pd3dDevice, const char * pszFontName, const int iFontSize, const bool bFontBold = false, const bool bFontItalic = false);
	CFont(IDirect3DDevice9 *pd3dDevice, const wchar_t * pszFontName, const int iFontSize, const bool bFontBold = false, const bool bFontItalic = false);
	~CFont();

	bool DrawText(const char *, const int iX, const int iY, ID3DXSprite *pSprite, const D3DCOLOR Color); 
	bool DrawText(const wchar_t *, const int iX, const int iY, ID3DXSprite *pSprite, const D3DCOLOR Color);

	int GetTextWidth(const char *);
	int GetTextWidth(const wchar_t *);

	void OnLostDevice();
	void OnResetDevice();
	void Release();
private:
	ID3DXFont * m_pFont;
};