#include "CGUI.h"

void CScrollBar::SetDragged( bool bDragged )
{
	m_bDragged = bDragged;
}

bool CScrollBar::GetDragged()
{
	return m_bDragged;
}

CScrollBar::CScrollBar( CGUI *Gui, CPos relPos, int inHeight )
{
	SetElement( Gui, 0, 0, 10, inHeight, NULL, NULL, NULL );
	SetHeight( inHeight );

	ibHeight = ibWidth = isHeight = 0;

	m_bShow = 1;

	m_bMouseOver[ 0 ] = m_bMouseOver[ 1 ] = m_bMouseOver[ 2 ] = false;
	SetDragged( false );

	SetThemeElement( pGui->GetThemeElement( _UI("ScrollBar") ) );
	SetThemeElement( pGui->GetThemeElement( _UI("ScrollBar") ), 1 );
	SetThemeElement( pGui->GetThemeElement( _UI("ScrollBar") ), 2 );

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("ScrollBar"), 0 );
	else
	{
		SetElementState( _UI("Norm") );
		SetElementState( _UI("Norm"), 1 );
		SetElementState( _UI("Norm"), 2 );
	}

	SetRelPos( CPos(relPos.GetX() - ibWidth, relPos.GetY()) );

	SetMinValue( 0 );
	SetMaxValue( 1 );
	SetStep( 1 );
	SetValue( 0 );
}

CScrollBar::~CScrollBar()
{
	SAFE_DELETE(back);
	SAFE_DELETE(pSlider);
	SAFE_DELETE(pUpArrow);
	SAFE_DELETE(pDownArrow);
}

int CScrollBar::GetWidth()
{
	return ibWidth;
}

void CScrollBar::Draw( CPos basePos )
{
	if(!GetShow()) return;
	CPos Pos = basePos + *GetRelPos();

	pGui->DrawOutlinedBox( Pos.GetX(), Pos.GetY(), ibWidth, GetHeight(), back->GetD3DCOLOR(), back->GetD3DCOLOR() );

	pUpArrow->Draw( CPos( Pos.GetX() + 1, Pos.GetY() + 1 ), ibWidth - 2, ibHeight - 2 );
	pDownArrow->Draw( CPos( Pos.GetX() + 1, Pos.GetY() + 1 + GetHeight() - ibHeight ), ibWidth - 2, ibHeight - 2 );

	if( GetMaxValue() < 2 )
		return;

	pSlider->Draw( Pos.GetX() + 1, Pos.GetY() - 1 + ibHeight + static_cast<int>( floor( (float)(GetHeight() - 2*ibHeight - isHeight) / GetMaxValue() * GetValue() ) ), ibWidth - 2, isHeight - 2 );
}

void CScrollBar::PreDraw()
{
	if(!GetShow()) return;
	if( (m_bPressed[ 0 ] && !pGui->GetMouse()->GetLeftButton()) || !m_bMouseOver[ 0 ] )
	{
		m_bPressed[ 0 ] = false;
		SetElementState( m_bMouseOver[ 0 ]?_UI("MouseOver"):_UI("Norm") );
	}
	if( (m_bPressed[ 2 ] && !pGui->GetMouse()->GetLeftButton()) || m_bMouseOver[ 2 ] )
	{
		m_bPressed[ 2 ] = false;
		SetElementState( m_bMouseOver[ 2 ]?_UI("MouseOver"):_UI("Norm"), 2 );
	}
}

bool CScrollBar::MouseMove( CPos basePos, CMouse * pMouse )
{
	if(!GetShow()) return 0;
	
	CPos Pos = basePos + *GetRelPos();
	SetElementState( ( ( m_bMouseOver[ 0 ]	= pMouse->InArea( Pos.GetX() + 1, Pos.GetY() + 1, ibWidth - 2, ibHeight - 2 ) ) != 0 )?_UI("MouseOver"):_UI("Norm") );
	SetElementState( ( ( m_bMouseOver[ 2 ]	= pMouse->InArea( Pos.GetX() + 1, Pos.GetY() + 1 + GetHeight() - ibHeight, ibWidth - 2, ibHeight - 2 ) ) != 0 )?_UI("MouseOver"):_UI("Norm"), 2 );

	if( GetMaxValue() < 2 )
		return 0;

	if( GetDragged() )
	{
		CPos mPos = pMouse->GetPos();

		if( mPos.GetX() == -1 && mPos.GetY() == -1 )
			mPos = pMouse->GetSavedPos();

		if( mPos.GetY() < Pos.GetY() + isHeight )
			SetValue( GetMinValue() );
		else if( mPos.GetY() > Pos.GetY() + GetHeight() - isHeight )
			SetValue( GetMaxValue() );
		else
			for( int i = GetMinValue(); i <= GetMaxValue(); i++ )
			{
				int iY = Pos.GetY() - 1 + ibHeight + static_cast<int>( floor( (float)( GetHeight() - ibHeight * 2 - isHeight) / GetMaxValue() * i ) );
				if( mPos.GetY() >= iY && mPos.GetY() <= iY + isHeight / 2 )
				{
					SetValue( i );
					break;
				}
			}
	}
	else
		SetElementState( ( ( m_bMouseOver[ 1 ]	= pMouse->InArea( Pos.GetX(),  Pos.GetY() + ibHeight + static_cast<int>( floor( (float)( GetHeight() - 2 * ibHeight - isHeight) / GetMaxValue() * GetValue() ) ), ibWidth, isHeight ) ) != 0 )?_UI("MouseOver"):_UI("Norm"), 1 );

	return 0;
}

bool CScrollBar::KeyEvent( CPos basePos, SKey sKey )
{
	CPos Pos = basePos + *GetRelPos();

	if( !sKey.m_vKey )
	{
		if( pGui->GetMouse()->GetLeftButton() )
		{
			if( m_bMouseOver[ 0 ] )
			{
				if( GetValue() > GetMinValue() )
					SetValue( GetValue() - 1 );

				m_bPressed[ 0 ] = true;
				SetElementState( _UI("Pressed") );
			}
			else if( m_bMouseOver[ 2 ] )
			{
				if( GetValue() < GetMaxValue() )
					SetValue( GetValue() + 1 );

				m_bPressed[ 2 ] = true;
				SetElementState( _UI("Pressed"), 2 );
			}
			else if( pGui->GetMouse()->InArea( Pos.GetX() + 1, Pos.GetY() + ibHeight, ibWidth, GetHeight() - ibHeight * 2 ) )
			{	
				SetElementState( _UI("Pressed"), 1 );
				m_bPressed[ 1 ] = true;

				SetDragged( true );
				MouseMove( Pos, pGui->GetMouse() );
			}
		}
		else
		{
			SetElementState( m_bMouseOver[ 1 ]?_UI("MouseOver"):_UI("Norm"), 1 );
			SetDragged( false );
		}

		if( !GetDragged() && pGui->GetMouse()->GetWheel() )
		{
			int iState = pGui->GetMouse()->GetWheel( 0 );

			int iTenth = ( GetMaxValue() / 10 )?GetMaxValue() / 10:1;

			if( iState == 1 )
				SetValue( GetValue() - iTenth );
			else if( iState == 2 )
				SetValue( GetValue() + iTenth );	
		}
	}
	return true;
}

int CScrollBar::GetMinValue()
{
	return m_iMinValue;
}

int CScrollBar::GetMaxValue()
{
	return m_iMaxValue;
}

int CScrollBar::GetValue()
{
	return m_iValue;
}

int CScrollBar::GetStep()
{
	return m_iStep;
}

void CScrollBar::SetMinValue( int iMinValue )
{
	m_iMinValue = iMinValue;
}

void CScrollBar::SetMaxValue( int iMaxValue )
{
	m_iMaxValue = iMaxValue;
}

void CScrollBar::SetValue( int iValue )
{
	if( iValue > GetMaxValue() )
		m_iValue = GetMaxValue();
	else if( iValue < GetMinValue() )
		m_iValue = GetMinValue();
	else
		m_iValue = iValue;

	SendMsg(CHANGE, iValue);
}

void CScrollBar::SetStep( int iStep )
{
	m_iStep = iStep;
}

void CScrollBar::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	if( iIndex == 1 )
	{
		ibHeight = pState->GetInt(_UI("bHeight"));
		ibWidth = pState->GetInt(_UI("bWidth"));
		isHeight = pState->GetInt(_UI("sHeight"));
		back = pState->GetColor( _UI("BG") );
		pSlider = pState->GetTexture( _UI("Scroll") );
	}
	else if( iIndex == 0 )
	{
		pUpArrow = pState->GetTexture( _UI("ArrowUp") );
	}
	else if(iIndex == 2)
	{
		pDownArrow = pState->GetTexture( _UI("ArrowDown") );
	}
}

uistring MinValue( const uichar *, CElement * pElement )
{
	unistream sStream;

	if( pElement )
	{
		CScrollBar * pSlider = (CScrollBar*)pElement;

		try
		{
			sStream << pSlider->GetMinValue();
		}
		catch( ... )
		{
			MessageBox( 0, _UI("$MinValue failed"), pElement->GetString().c_str(), 0 );
		}
	}
	return sStream.str();
}

uistring MaxValue( const uichar *, CElement * pElement )
{
	unistream sStream;

	if( pElement )
	{
		CScrollBar * pSlider = (CScrollBar*)pElement;

		try
		{
			sStream << pSlider->GetMaxValue();
		}
		catch( ... )
		{
			MessageBox( 0, _UI("$MaxValue failed"), pElement->GetString().c_str(), 0 );
		}
	}
	return sStream.str();
}

uistring SliderValue( const uichar *, CElement * pElement )
{
	unistream sStream;

	if( pElement )
	{
		CScrollBar * pSlider = (CScrollBar*)pElement;

		try
		{
			sStream << pSlider->GetValue();
		}
		catch( ... )
		{
			MessageBox( 0, _UI("$Value failed"), pElement->GetString().c_str(), 0 );
		}
	}
	return sStream.str();
}

void CScrollBar::SetShow(bool bShow)
{
	m_bShow = bShow;
}

bool CScrollBar::GetShow()
{
	return m_bShow;
}

int CScrollBar::GetSliderWidth()
{
	return ibHeight;
}