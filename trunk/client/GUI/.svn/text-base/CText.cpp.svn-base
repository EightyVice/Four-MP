#include "CGUI.h"

CText::CText( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback )
{
	SetElement( Gui, X, Y, Width, Height, String, String2, Callback );

	SetThemeElement( pGui->GetThemeElement( _UI("Text") ) );

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("Text"), 0 );
	else
		SetElementState( _UI("Norm") );
}

CText::~CText()
{
	SAFE_DELETE(pString);
}

void CText::Draw()
{
	if(!GetFormatted().c_str()) return;

	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;
	
	GetFont()->DrawString( Pos.GetX(), Pos.GetY(), 0, pString, GetFormatted().c_str(), GetWidth() );
}

void CText::PreDraw()
{
	GetString( true );
}

bool CText::MouseMove( CMouse * pMouse, bool )
{
	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;

	SetElementState( SetMouseOver( pMouse->InArea( Pos.GetX(), Pos.GetY(), GetFont()->GetStringWidth( GetFormatted().c_str() ), GetFont()->GetStringHeight() ) )?_UI("MouseOver"):_UI("Norm") );
	return 0;
}

void CText::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pString = pState->GetColor( _UI("String") );
}