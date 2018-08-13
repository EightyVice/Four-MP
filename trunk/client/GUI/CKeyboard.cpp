#include "CGUI.h"

CKeyboard::CKeyboard(CGUI *Gui)
{
	pGui = Gui;
}

bool CKeyboard::HandleMessage( unsigned int uMsg, unsigned int wParam, long lParam )
{
	if( !pGui->IsVisible() || uMsg < WM_KEYFIRST || uMsg > WM_KEYLAST || pGui->GetMouse()->GetLeftButton() )
		return false;

	switch( uMsg )
	{
	case WM_KEYDOWN:
		SetKey( SKey( static_cast<uichar>( wParam ), true, lParam ) );
		break;
	case WM_KEYUP:
		SetKey( SKey( static_cast<uichar>( wParam ), false, lParam ) );
		break;
	}

	return pGui->KeyEvent( GetKey() );
}

void CKeyboard::SetKey( SKey sKey )
{
	m_sKey = sKey;
}

SKey CKeyboard::GetKey()
{
	SKey sRet = m_sKey;
	SetKey( SKey( 0, false ) );
	return sRet;
}