#include "CFont.h"

CFont::CFont(IDirect3DDevice9 *pd3dDevice, const char *pszFontName, const int iFontSize, const bool bFontBold, const bool bFontItalic)
{
	HDC hDC = GetDC( NULL );
	int nHeight = -MulDiv( iFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72 );
	ReleaseDC( NULL, hDC );

	D3DXCreateFontA(pd3dDevice, nHeight, 0, (bFontBold ? FW_BOLD : FW_NORMAL), 0, bFontItalic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pszFontName, &m_pFont);

	m_pFont->PreloadCharacters(0, 255);
	m_pFont->PreloadGlyphs(0, 255);
}

CFont::CFont(IDirect3DDevice9 *pd3dDevice, const wchar_t *pszFontName, const int iFontSize, const bool bFontBold, const bool bFontItalic)
{
	HDC hDC = GetDC( NULL );
	int nHeight = -MulDiv( iFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72 );
	ReleaseDC( NULL, hDC );

	D3DXCreateFontW(pd3dDevice, nHeight, 0, (bFontBold ? FW_BOLD : FW_NORMAL), 0, bFontItalic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pszFontName, &m_pFont);

	m_pFont->PreloadCharacters(0, 255);
	m_pFont->PreloadGlyphs(0, 255);
}

CFont::~CFont()
{

}

bool CFont::DrawText(const char *pszText, const int iX, const int iY, ID3DXSprite *pSprite, const D3DCOLOR Color)
{
	if(!m_pFont) return false;
	if(!pszText) return false;

	RECT rct = { iX, iY, 2000, 2000 };
	m_pFont->DrawTextA(pSprite, pszText, -1, &rct, 0, Color);

	return true;
}

bool CFont::DrawText(const wchar_t * pszText, const int iX, const int iY, ID3DXSprite *pSprite, const D3DCOLOR Color)
{
	if(!m_pFont) return false;
	if(!pszText) return false;

	RECT rct = { iX, iY, 2000, 2000 };
	m_pFont->DrawTextW(pSprite, pszText, -1, &rct, 0, Color);

	return true;
}

int CFont::GetTextWidth(const char * pszText)
{
	if(!m_pFont) return 0;
	if(!pszText) return 0;

	RECT rct = { 0 };
	m_pFont->DrawTextA(0, pszText, -1,&rct, DT_CALCRECT, 0);
	return rct.right - rct.left;
}

int CFont::GetTextWidth(const wchar_t * pszText)
{
	if(!m_pFont) return 0;
	if(!pszText) return 0;

	RECT rct = { 0 };
	m_pFont->DrawTextW(0, pszText, -1,&rct, DT_CALCRECT, 0);
	return rct.right - rct.left;
}

void CFont::OnLostDevice()
{
	m_pFont->OnLostDevice();
}

void CFont::OnResetDevice()
{
	m_pFont->OnResetDevice();
}

void CFont::Release()
{
	m_pFont->Release();
}