#include "CGUI.h"

CElement::~CElement()
{
	SAFE_DELETE(pFont);
}

void CElement::SetElement( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback, bool abs)
{
	InitializeCriticalSection(&cs);
	pGui = Gui;

	if(!abs)
		SetRelPos( CPos( X, Y ) );
	else
		SetAbsPos( CPos( X, Y ) );
	SetWidth( Width );
	SetHeight( Height );

	if( String )
	{
		SetString( String );
	}

	if( String2 )
	{
		SetString( String2, 1 );
	}

	if( Callback )
	{
		SetAction( Callback );
	}
	else
		SetAction( 0 );

	pFont = pGui->GetFont();
	m_bEnabled = 1;
	m_pParent = NULL;
	SetMouseOver( false );
}

void CElement::SetParent( CWindow * pParent )
{
	m_pParent = pParent;
}

CWindow * CElement::GetParent()
{
	return m_pParent;
}

void CElement::SetAction( tAction pAction )
{
	m_pAction = pAction;
}

tAction CElement::GetAction()
{
	return m_pAction;
}

void CElement::SetRelPos( CPos relPos )
{
	m_relPos = relPos;
}

void CElement::SetRelPos( int X, int Y )
{ 
	if(X != -1)
		m_relPos.SetX(X);
	if(Y != -1)
		m_relPos.SetY(Y);
}

CPos * CElement::GetRelPos()
{
	return &m_relPos;
}

void CElement::SetAbsPos( CPos absPos )
{
	m_absPos = absPos;
}

CPos * CElement::GetAbsPos()
{
	return &m_absPos;
}

void CElement::SetWidth( int iWidth )
{
	m_iWidth = iWidth;
}

int CElement::GetWidth()
{
	return m_iWidth;
}

void CElement::SetHeight( int iHeight )
{
	m_iHeight = iHeight;
}

int CElement::GetHeight()
{
	return m_iHeight;
}

bool CElement::HasFocus()
{
	return GetParent()->GetFocussedElement() == this;
}

void CElement::SetString( uistring sString, int iIndex )
{
	if( static_cast<int>( sString.length() ) > 255 )
		return;

	m_sRaw[ iIndex ] = sString;
}

uistring CElement::GetString( bool bReplaceVars, int iIndex )
{
	m_sFormatted[ iIndex ] = m_sRaw[ iIndex ];

	if( bReplaceVars && m_sRaw[ iIndex ].find( _UI("$") ) != uistring::npos )
	{
		for( std::map<uistring,CVar*>::reverse_iterator iIter = pGui->Cvars.rbegin(); iIter != pGui->Cvars.rend(); iIter++ )
		{
			int iPos = m_sFormatted[ iIndex ].find( iIter->first );

			if( iPos == static_cast<int>( uistring::npos ) )
				continue;

			int iLen = iIter->first.length();
			if( static_cast<int>( m_sFormatted[ iIndex ].length() ) - iPos >= iLen )
			{
				bool bReplace = true;

				for( int i = 0; i < iLen; i++ )
					if( iIter->first[ i ] != m_sFormatted[ iIndex ][ iPos + i ] )
						bReplace = false;

				if( bReplace && iIter->second )
				{
					if( iIter->second->GetString().length() )
						m_sFormatted[ iIndex ].replace( iPos, iIter->first.length(), iIter->second->GetString() );
					else
						m_sFormatted[ iIndex ].replace( iPos, iIter->first.length(), iIter->second->GetActionString( 0, this ) );
				}
			}
		}

		return m_sFormatted[ iIndex ];
	}
	return m_sRaw[ iIndex ];
}

uistring CElement::GetFormatted( int iIndex )
{
	return m_sFormatted[ iIndex ];
}

bool CElement::GetMouseOver()
{
	return m_bMouseOver;
}

bool CElement::SetMouseOver( bool bMouseOver )
{
	if(GetAction())
		if(bMouseOver) GetAction()(this, MOUSE_OVER, 0);
		else GetAction()(this, MOUSE_OUT, 0);

	return m_bMouseOver = bMouseOver;
}

SElement * CElement::SetThemeElement( SElement * pThemeElement, int iIndex )
{
	return m_pThemeElement[ iIndex ] = pThemeElement;
}

SElement * CElement::GetThemeElement( int iIndex )
{
	return m_pThemeElement[ iIndex ];
}

void CElement::SetElementState( uistring sState, int iIndex )
{
	m_pElementState[ iIndex ] = GetThemeElement( iIndex )->m_mStates[ sState ];

	if( !m_pElementState )
		m_pElementState[ iIndex ] = GetThemeElement( iIndex )->m_mStates[ GetThemeElement( iIndex )->sDefaultState ];

	UpdateTheme( iIndex );
}

SElementState * CElement::GetElementState( int iIndex )
{
	return m_pElementState[ iIndex ];
}

void CElement::LostFocus()
{
	if(GetAction())
		GetAction()(this, LOST_FOCUS, 0);
}

void CElement::GotFocus()
{
	if(GetAction())
		GetAction()(this, GOT_FOCUS, 0);
}

void CElement::SendMsg(CMSG msg, int Param)
{
	if(GetAction())
		GetAction()(this, msg, Param);
}

void CElement::UpdateTheme( int )
{
}

void CElement::Draw()
{
}

void CElement::PreDraw()
{
}

bool CElement::MouseMove( CMouse *, bool )
{
	return 0;
}

bool CElement::KeyEvent( SKey )
{
	return 0;
}

void CElement::SetFont(int size, uichar *name, bool bold, bool italic)
{
	pFont = new CFont(pGui, pGui->GetDevice(), size, name, bold, italic);
}

void CElement::SetFont(CFont *font)
{
	pFont = font;
}

CFont * CElement::GetFont()
{
	return pFont;
}

void CElement::SetEnabled(bool on)
{
	m_bEnabled = on;
	SetMouseOver(0);

	if(on)
		SetElementState( _UI("Norm") );
	else
		SetElementState( _UI("Disabled") );
}

bool CElement::GetEnabled()
{
	return m_bEnabled;
}

void CElement::OnLostDevice()
{
	if(pFont != pGui->GetFont())
		pFont->OnLostDevice();
}

void CElement::OnResetDevice()
{
	if(pFont != pGui->GetFont())
		pFont->OnResetDevice();
}