#include "CGUI.h"

CButton::CButton( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback )
{
	SetElement( Gui, X, Y, Width, Height, String, String2, Callback );

	m_bVisibleBack = 1;
	SizeEdge = 0;

	SetThemeElement( pGui->GetThemeElement( _UI("Button") ) );

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("Button"), 0 );
	else
		SetElementState( _UI("Norm") );
}

CButton::~CButton()
{
	SAFE_DELETE(pButton[0]);
	SAFE_DELETE(pButton[1]);
	SAFE_DELETE(pButton[2]);
	SAFE_DELETE(pString);
}

void CButton::Draw()
{
	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;

	if(m_bVisibleBack) 
	{
		pButton[0]->Draw( Pos, SizeEdge, GetHeight() );
		pButton[2]->Draw( Pos.GetX()+GetWidth()-SizeEdge, Pos.GetY(), SizeEdge, GetHeight() );
		pButton[1]->Draw( Pos.GetX()+SizeEdge-1, Pos.GetY(), GetWidth()-2*SizeEdge+2, GetHeight() );
	}
	GetFont()->DrawString( Pos.GetX() + GetWidth() / 2, Pos.GetY() + GetHeight() / 2, FT_CENTER|FT_VCENTER, pString, GetString().c_str() );
}

void CButton::PreDraw()
{
	if( !m_tPressed.Running() && GetEnabled() )
		SetElementState( GetMouseOver()?_UI("MouseOver"):_UI("Norm") );
}

bool CButton::MouseMove( CMouse * pMouse, bool over )
{
	if(!GetEnabled()) return 0;

	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	bool inArea = pMouse->InArea( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight() ) && over;
	SetElementState( SetMouseOver( inArea )?_UI("MouseOver"):_UI("Norm") );

	return inArea;
}

bool CButton::KeyEvent( SKey sKey )
{
	if(!GetEnabled()) return 0;

	if( !sKey.m_vKey )
	{
		if( GetMouseOver() && pGui->GetMouse()->GetLeftButton( 0 ) )
		{
			SetElementState( _UI("Pressed") );

			if( GetAction() )
			{
				GetAction()( this, CLICK, 0 );
			}

			m_tPressed.Start( 0.1f );
		}
	}
	return 0;
}

void CButton::SetBackVisible(bool v)
{
	m_bVisibleBack = v;
}

bool CButton::GetBackVisible()
{
	return m_bVisibleBack;
}

void CButton::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pButton[0] = pState->GetTexture( _UI("ButtonLeft") );
	pButton[1] = pState->GetTexture( _UI("ButtonMiddle") );
	pButton[2] = pState->GetTexture( _UI("ButtonRight") );

	pString = pState->GetColor( _UI("String") );

	SetHeight( pState->GetInt( _UI("Height") ) );
	SizeEdge = pState->GetInt(_UI("SizeEdge"));
}


