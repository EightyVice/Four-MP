#include "CGUI.h"

CFont::CFont( CGUI *Gui, IDirect3DDevice9 * pDevice, int iHeight, uichar * pszFaceName, bool bold, bool italic )
{
	pGui = Gui;
	HRESULT hResult = D3DXCreateFont( pDevice, -MulDiv( iHeight, GetDeviceCaps( GetDC( 0 ), LOGPIXELSY ), 72 ), 0, bold?FW_BOLD:FW_NORMAL, 0, italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pszFaceName, &m_pFont );

	if( FAILED( hResult ) )
		MessageBox( 0, /*DXGetErrorDescription9( hResult )*/_UI("Error"), _UI("D3DXCreateFontA failed"), 0 );
	m_pFont->PreloadCharacters( 0, 255 );
	InitializeCriticalSection(&cs);
}

CFont::~CFont()
{
	SAFE_RELEASE( m_pFont );
	DeleteCriticalSection(&cs);
}

void CFont::OnLostDevice()
{
	EnterCriticalSection(&cs);
	m_pFont->OnLostDevice();
	LeaveCriticalSection(&cs);
}

void CFont::OnResetDevice()
{
	EnterCriticalSection(&cs);
	m_pFont->OnResetDevice();
	LeaveCriticalSection(&cs);
}

void CFont::DrawString( int iX, int iY, DWORD dwFlags, CColor * pColor, uistring sString, int iWidth )
{
	if(!m_pFont) return;
	if(!pGui) return;
	if(!sString.c_str()) return;
	if(!pColor) return;

	EnterCriticalSection(&cs);
	if( iWidth )CutString( iWidth, sString );

	pGui->GetSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );

	D3DXMATRIX mat;
	D3DXMatrixTranslation( &mat, static_cast<float>( iX ), static_cast<float>( iY ), 0 );
	pGui->GetSprite()->SetTransform( &mat );

	RECT drawRect = { 0 };
	DWORD dwDrawFlags = DT_NOCLIP | ( ( dwFlags & FT_CENTER ) ? DT_CENTER : 0 ) | ( ( dwFlags & FT_VCENTER ) ? DT_VCENTER : 0 );
	m_pFont->DrawText( pGui->GetSprite(), sString.c_str(), -1, &drawRect, dwDrawFlags, pColor->GetD3DCOLOR() );

	pGui->GetSprite()->End();
	LeaveCriticalSection(&cs);
}

int CFont::GetStringWidth( const uichar * pszString )
{
	if(!m_pFont) return 0;
	if(!pszString) return 0;

	//uistring sString( pszString );
	RECT rRect = { 0 };

	/*for( int i = 0; i <= static_cast<int>( sString.size() ); i++ )
		if( sString[i] == _UI(' ') )
			sString[i] = _UI('.');*/

	EnterCriticalSection(&cs);
	m_pFont->DrawText( 0, /*sString.c_str()*/pszString, -1, &rRect, DT_CALCRECT, 0 );
	LeaveCriticalSection(&cs);

	return rRect.right - rRect.left;
}

int CFont::GetStringHeight()
{
	if(!m_pFont) return 0;

	RECT rRect = { 0 };
	EnterCriticalSection(&cs);
	m_pFont->DrawText( 0, _UI("Y"), -1, &rRect, DT_CALCRECT, 0 );
	LeaveCriticalSection(&cs);

	return rRect.bottom - rRect.top;
}

void CFont::SetColor( int iIndex, CColor cColor )
{
	if( iIndex < 0 || iIndex > 8 )
		return;

	m_cColors[ iIndex ] = cColor;
}

CColor & CFont::GetColor( int iIndex )
{
	if( iIndex < 0 || iIndex > 8 )
		return m_cColors[ 0 ];

	return m_cColors[ iIndex ];
}

void CFont::CutString( int iMaxWidth, uistring & rString )
{
	int iIndex = 0, iLength = rString.length();

	for( int iWidth = 0; iIndex < iLength && iWidth + 10 < iMaxWidth; )
	{
		uichar szCurrent[ 2 ] = { rString.c_str()[ iIndex ], 0 };
		iWidth += /*pGui->GetFont()->*/GetStringWidth( szCurrent );
		iIndex++;
	}

	if( iIndex < iLength )
		rString[ iIndex - 1 ] = _UI('\0');
}