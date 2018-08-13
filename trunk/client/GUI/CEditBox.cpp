#include "CGUI.h"

CEditBox::CEditBox( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback )
{
	SetElement( Gui, X, Y, Width, Height, String, String2, Callback );
	SetHeight( 20 );

	SizeEdge = 0;

	m_iStart = 0;
	CenterAlign = 0;
	Hide = 0;
	SetIndex( 0 );
	m_bCursorState = false;
	SetAction( 0 );
	if( Callback )
	{
		SetAction( Callback );
	}
	SetThemeElement( pGui->GetThemeElement( _UI("EditBox") ) );
	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("EditBox"), 0 );
	else
		SetElementState( _UI("Norm") );
}

CEditBox::~CEditBox()
{
	SAFE_DELETE(pString);
	SAFE_DELETE(pCursor);
	SAFE_DELETE(pEdit[0]);
	SAFE_DELETE(pEdit[1]);
	SAFE_DELETE(pEdit[2]);
}

void CEditBox::Draw()
{
	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;

	SElementState * pState = GetElementState();
	uistring DataString;
	if(!Hide) DataString = GetString();
	else for(int i = 0; i < (int)GetString().size(); i++) DataString.push_back(_UI('*'));

	if( pState )
	{
		pEdit[0]->Draw( Pos, SizeEdge, GetHeight() );
		pEdit[2]->Draw( Pos.GetX()+GetWidth()-SizeEdge, Pos.GetY(), SizeEdge, GetHeight() );
		pEdit[1]->Draw( Pos.GetX()+SizeEdge-1, Pos.GetY(), GetWidth()-2*SizeEdge+2, GetHeight() );

		if(!CenterAlign) GetFont()->DrawString( Pos.GetX() + iPadding, Pos.GetY() + GetHeight() / 2, FT_VCENTER, 
			pString, DataString, GetWidth() - 2*iPadding );
		else
			GetFont()->DrawString( Pos.GetX() + GetWidth()/2, Pos.GetY() + GetHeight() / 2, FT_VCENTER|FT_CENTER, 
				pString, DataString );

		int hgt = (GetHeight()-GetFont()->GetStringHeight())/2;

		if( m_bCursorState && HasFocus() && GetEnabled())
		{
			int fSize = GetFont()->GetStringWidth( DataString.c_str() );
			DataString[m_iIndex] = 0;
			m_iCursorX = GetFont()->GetStringWidth( DataString.c_str() );
			if(m_iCursorX > GetWidth()-2*iPadding) m_iCursorX = GetWidth()-2*iPadding;
			if(!CenterAlign)
				pGui->FillArea( Pos.GetX() + 2 + m_iCursorX+iPadding, Pos.GetY() + hgt, 2, GetHeight() - 2*hgt, pCursor->GetD3DCOLOR() );
			else
			{
				pGui->FillArea( Pos.GetX() + 2 + (GetWidth()/2) - (fSize/2) + m_iCursorX, Pos.GetY() + hgt, 2, GetHeight() - 2*hgt, pCursor->GetD3DCOLOR() );
			}
		}
	}
}

bool CEditBox::GetTextAlign()
{
	return CenterAlign;
}

void CEditBox::SetTextAlign(bool center)
{
	CenterAlign = center;
}

void CEditBox::HideContent(bool hide)
{
	Hide = hide;
}

void CEditBox::PreDraw()
{
	SetElementState( HasFocus()?_UI("Active"):_UI("Norm") );

	if( !m_tCursorTimer.Running() )
	{
		m_bCursorState = !m_bCursorState;
		m_tCursorTimer.Start( 0.6f );
	}
}

bool CEditBox::MouseMove( CMouse * pMouse, bool over )
{
	if(!GetEnabled()) return 0;
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	bool inArea = pMouse->InArea( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight() ) && over;
	SetMouseOver( inArea );
	return inArea;
}

bool CEditBox::KeyEvent( SKey sKey )
{
	if(!GetEnabled()) return 0;
	if( !sKey.m_vKey )
	{
		if( pGui->GetMouse()->GetLeftButton() )
		{
			if( GetMouseOver() )
			{
				SendMsg(CLICK, 0);

				int iX = pGui->GetMouse()->GetPos().GetX();
				int iAbsX = ( *GetParent()->GetAbsPos() + *GetRelPos() ).GetX();

				uistring sString( &GetString()[ GetStart() ] );
				
				if( iX >= iAbsX + GetFont()->GetStringWidth( sString.c_str() ) )
					SetIndex( sString.length() );
				else
				{
					for( int i = 0; i <= static_cast<int>( sString.length() ); i++ )
					{
						if( iX <= iAbsX + GetFont()->GetStringWidth( sString.c_str() ) )
						{
							sString[ i ] = 0;
							if( iX > iAbsX + GetFont()->GetStringWidth( sString.c_str() ) )
								SetIndex( i );
						}
						sString = &GetString()[ GetStart() ];
					}
				}

				GetParent()->SetFocussedElement( this );
			}
		}
	}
	else if( sKey.m_bDown && HasFocus() )
	{
		switch( sKey.m_vKey )
		{
		case VK_END:
			{
				uistring sString = GetString();

				SetIndex( uislen( &sString[ GetStart() ] ) );

				while( GetFont()->GetStringWidth( &sString.c_str()[ GetStart() ] ) > GetWidth() - 5 || m_iCursorX > GetWidth() - 5 )
				{
					SetStart( GetStart() + 1 );
					SetIndex( GetIndex() - 1 );
				}
				break;
			}
		case VK_HOME:
			{
				SetStart( 0 );
				SetIndex( 0 );

				break;
			}
		case VK_BACK:
			{
				if( GetIndex() )
				{
					uistring sString = GetString();

					sString.erase( GetStart() + GetIndex() - 1,  1 );

					SetString( sString );
					SetIndex( GetIndex() - 1 );
				}
				else if( GetStart() )
				{
					SetStart( GetStart() - 1 );
					SetIndex( 1 );
				}

				break;
			}
		case VK_DELETE:
			{
				uistring sString = GetString();

				if( GetIndex() <= static_cast<int>( sString.length() ) )
					sString.erase( GetStart() + m_iIndex, 1 );

				SetString( const_cast<uichar*>( sString.c_str() ) );

				break;
			}
		case VK_LEFT:
			{
				if( !GetIndex() && GetStart() )
					SetStart( GetStart() - 1 );
				else if( GetIndex() )
					SetIndex( GetIndex() - 1 );

				break;
			}
		case VK_RIGHT:
			{
				SetIndex( GetIndex() + 1 );

				uistring sString = GetString();
				sString[ GetIndex() ] = 0;

				while( GetFont()->GetStringWidth( &sString.c_str()[ GetStart() ] ) > GetWidth() - 5 || m_iCursorX > GetWidth() - 5 )
				{
					SetStart( GetStart() + 1 );
					SetIndex( GetIndex() - 1 );
				}

				break;
			}
		case VK_RETURN:
			{
				GetParent()->SetFocussedElement( 0 );

				SendMsg(END, 0);

				break;
			}
		default:
			{
				uistring sString( GetString() );

				int iPrevLen = sString.length();

				BYTE bKeys[256] = { 0 };
				GetKeyboardState( bKeys );

				#ifndef _UNICODE
					WORD wKey = 0;
					ToAscii( sKey.m_vKey, HIWORD( sKey.m_lParam )&0xFF, bKeys, &wKey, 0 );
				#else
					wchar_t wKey = 0;
					ToUnicode( sKey.m_vKey, HIWORD( sKey.m_lParam )&0xFF, bKeys, &wKey, 1, 0 );
				#endif
				SendMsg(CHANGE, wKey);

				if(wKey < 32) break;

				uichar szKey[2] = { static_cast<uichar>( wKey ), 0 };
				if( GetStart() + m_iIndex >= 0 && GetStart() + m_iIndex <= static_cast<int>( sString.length() ) )
				{
					if( wKey != 22 )
						sString.insert( GetStart() + m_iIndex, szKey );
					else
					{
						if( !OpenClipboard( 0 ) )
							break;

						HANDLE hData = GetClipboardData( CF_TEXT );
						uichar * pszBuffer = static_cast<uichar*>( GlobalLock( hData ) );
						
						if( pszBuffer )
							sString.insert( GetStart() + m_iIndex, pszBuffer );

						GlobalUnlock( hData );
						CloseClipboard();
					}
				}

				SetString( const_cast<uichar*>( sString.c_str() ) );
				if( sKey.m_vKey == _UI(' ') )
					SetIndex( GetIndex() + 1 );
				else
					SetIndex( GetIndex() + sString.length() - iPrevLen );

				while( GetFont()->GetStringWidth( &GetString().c_str()[ GetStart() ] ) > GetWidth() - 5 )
				{
					SetStart( GetStart() + 1 );
					SetIndex( GetIndex() - 1 );
				}

				break;
			}
		}
	}
	return 0;
}

int CEditBox::GetIndex()
{
	return m_iIndex;
}

void CEditBox::SetIndex( int iIndex )
{
	uistring sString( &GetString()[ GetStart() ] );

	if( iIndex > static_cast<int>( sString.length() ) || iIndex < 0 )
		return;
	sString[ iIndex ] = 0;
	m_iCursorX = GetFont()->GetStringWidth( sString.c_str() );

	m_iIndex = iIndex;
}

int CEditBox::GetStart()
{
	return m_iStart;
}

void CEditBox::SetStart( int iStart )
{
	m_iStart = iStart;
}

void CEditBox::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pString = pState->GetColor( _UI("String") );
	pCursor = pState->GetColor( _UI("Cursor") );

	SizeEdge = pState->GetInt(_UI("SizeEdge"));
	SetHeight( pState->GetInt(_UI("Height")) );

	pEdit[0] = pState->GetTexture( _UI("Left") );
	pEdit[1] = pState->GetTexture( _UI("Middle") );
	pEdit[2] = pState->GetTexture( _UI("Right") );

	iPadding = pState->GetInt(_UI("Padding"));
}