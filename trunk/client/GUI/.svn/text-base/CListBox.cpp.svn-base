#include "CListBox.h"

CListBox::CListBox( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback )
{
	SetElement( Gui, X, Y, Width, Height, String, String2, Callback );
	m_iMouseOverIndex = -1;
	m_iMouseSelect = -1;

	pSlider = new CScrollBar( Gui, CPos( GetWidth() + 2, 0 ), GetHeight() );

	SetThemeElement( pGui->GetThemeElement( _UI("ListBox") ) );

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("ListBox"), 0 );
	else
		SetElementState( _UI("Norm") );
}

CListBox::~CListBox()
{
	SAFE_DELETE(pSlider);

	SAFE_DELETE(pInner);
	SAFE_DELETE(pBorder);
	SAFE_DELETE(pString);
	SAFE_DELETE(pMouseOverString);
	SAFE_DELETE(pSelInner);
	SAFE_DELETE(pSelString);
}

void CListBox::Draw()
{
	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;

	pGui->DrawOutlinedBox( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight(), pInner->GetD3DCOLOR(), pBorder->GetD3DCOLOR() );

	int iAddHeight = GetFont()->GetStringHeight();
	if( m_vRows.size() )
		for( int i = pSlider->GetValue(), iHeight = 0; i < static_cast<int>( m_vRows.size() ) && iHeight < GetHeight() - GetFont()->GetStringHeight(); i++ )
		{
			CColor * pColor = 0;

			if( i == m_iMouseOverIndex && GetMouseOver() )
				pColor = pMouseOverString;
			else
				pColor = pString;

			if(m_iMouseSelect == i)	
			{
				pGui->DrawOutlinedBox( Pos.GetX() + 2, Pos.GetY() + iHeight, GetWidth() -  pSlider->GetSliderWidth(), iAddHeight, pSelInner->GetD3DCOLOR(), pSelInner->GetD3DCOLOR() );
				pColor = pSelString;
			}

			GetFont()->DrawString( Pos.GetX() + 3, Pos.GetY() + iHeight, 0, pColor, m_vRows[ i ].c_str(), GetWidth() -  pSlider->GetSliderWidth() );
			iHeight += iAddHeight;
		}

	pSlider->Draw( Pos );
}	

void CListBox::PreDraw()
{
	pSlider->PreDraw();
}

bool CListBox::MouseMove( CMouse * pMouse, bool over )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	bool inArea = pMouse->InArea( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight() ) && over;
	SetMouseOver( inArea );

	m_iMouseOverIndex = -1;
	for( int i = pSlider->GetValue(), iHeight = 0, iStringHeight = GetFont()->GetStringHeight(); i < static_cast<int>( m_vRows.size() ) || iHeight < GetHeight(); i++ )
	{
		if( pMouse->InArea( Pos.GetX(), Pos.GetY() + iHeight, GetWidth() -  pSlider->GetSliderWidth(), iStringHeight ) )
			m_iMouseOverIndex = i;

		iHeight += iStringHeight;
	}

	pSlider->MouseMove( Pos, pMouse );
	return inArea;
}

bool CListBox::KeyEvent( SKey sKey )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	if( !sKey.m_vKey )
	{
		if( GetMouseOver() )
		{
			if(m_iMouseSelect > -2) m_iMouseSelect = m_iMouseOverIndex;
			if( m_iMouseOverIndex >= 0 && GetAction() && pGui->GetMouse()->GetLeftButton() )
				GetAction()( this, SELECT, m_iMouseOverIndex );
		}
	}

	if( GetMouseOver() || ( !sKey.m_bDown && !pGui->GetMouse()->GetWheel() )  )
	{
		pSlider->KeyEvent( Pos, sKey );
		MouseMove( pGui->GetMouse(), 1 );
	}
	return 0;
}

int CListBox::GetSize()
{
	return m_vRows.size();
}

void CListBox::PutStr( uistring sString, int Index )
{
	if(Index >= static_cast<int>( m_vRows.size() ) || Index == -1)
	{
		pSlider->SetMaxValue( m_vRows.size() );
		m_vRows.push_back(sString);
	}
	else
	{
		m_vRows[Index] = sString;
	}
}

uistring CListBox::GetRow( int iIndex )
{
	if( iIndex >= 0 && iIndex < static_cast<int>( m_vRows.size() ) )
		return m_vRows[ iIndex ];
	return uistring();
}

void CListBox::Clear()
{
	m_vRows.clear();
}

void CListBox::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pInner = pState->GetColor( _UI("Inner") );
	pBorder = pState->GetColor( _UI("Border") );
	pString = pState->GetColor( _UI("String") );
	pMouseOverString = pState->GetColor( _UI("MouseOverString") );
	pSelInner = pState->GetColor( _UI("SelectInner"));
	pSelString = pState->GetColor( _UI("SelectString"));
}

void CListBox::ShowSlider( bool bShow )
{
	pSlider->SetShow(bShow);
}

int CListBox::GetSelected()
{
	return m_iMouseSelect;
}

void CListBox::SetSelect(int Item)
{
	m_iMouseSelect = Item;
}