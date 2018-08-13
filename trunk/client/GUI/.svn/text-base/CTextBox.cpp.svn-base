#include "CGUI.h"

CTextBox::CTextBox( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback )
{
	m_iLimit = 128;
	SetElement( Gui, X, Y, Width, Height, String, String2, Callback );

	pSlider = new CScrollBar( Gui, CPos( GetWidth() + 2, 0 ), GetHeight() );

	SetThemeElement( pGui->GetThemeElement( _UI("TextBox") ) );

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("TextBox"), 0 );
	else
		SetElementState( _UI("Norm") );

}

CTextBox::~CTextBox()
{
	SAFE_DELETE(pSlider);
	SAFE_DELETE(pString);
	SAFE_DELETE(pInner);
	SAFE_DELETE(pBorder);
}

void CTextBox::Draw()
{
	EnterCriticalSection(&cs);
	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;
	pGui->DrawOutlinedBox( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight(), pInner->GetD3DCOLOR(), pBorder->GetD3DCOLOR() );
	int iAddHeight = GetFont()->GetStringHeight();
	int iMaxHeight = GetHeight() - iAddHeight;
	if( m_vStrings.size() )
		for( int i = pSlider->GetMaxValue()-pSlider->GetValue(), iHeight = 0; i >= 0 && iHeight < iMaxHeight; i-- )
		{
			if(m_vStrings.at(i).c_str()) 
				GetFont()->DrawString( Pos.GetX() + 3, Pos.GetY() + iHeight, 0, pString, m_vStrings.at(i).c_str(), GetWidth() - pSlider->GetSliderWidth() );
			iHeight += iAddHeight;
		}
	pSlider->Draw( Pos );
	LeaveCriticalSection(&cs);
}

void CTextBox::PreDraw()
{
	pSlider->PreDraw();
}

bool CTextBox::MouseMove( CMouse * pMouse, bool over )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	bool inArea = pMouse->InArea( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight() ) && over;
	SetMouseOver( inArea );

	pSlider->MouseMove( Pos, pMouse );
	return inArea;
}

bool CTextBox::KeyEvent( SKey sKey )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();
	if(GetMouseOver() && pGui->GetMouse()->GetLeftButton())
		SendMsg(CLICK, 0);

	if( GetMouseOver() || ( !sKey.m_bDown && !pGui->GetMouse()->GetWheel() )  )
		pSlider->KeyEvent( Pos, sKey );
	return 0;
}

void CTextBox::AddString( uistring sString )
{
	if( !sString.length() )
		return;

	if(!pSlider) return;

	EnterCriticalSection(&cs);
	/*std::vector<uistring> vPending;
	int iLength = static_cast<int>( sString.length() );
	for( int i = iLength - 1; i > 0; i-- )
	{
		if( sString[ i ] == _UI('\n') )
		{
			sString[ i ] = _UI('\0');
			
			if( i + 1 < iLength )
			{
				if( sString[ i + 1 ] == _UI('\r') )
				{
					if( i + 2 < iLength )
						vPending.push_back( &sString.c_str()[ i + 2 ] );
				}
				else
					vPending.push_back( &sString.c_str()[ i + 1 ] );
			}
		}
	}*/

	m_vStrings.insert( m_vStrings.begin(), sString );

	if((int)m_vStrings.size() >= m_iLimit) 
	{
		RemoveStrings(m_iLimit, 0);
		pSlider->SetMaxValue( m_iLimit-1 );
	}
	else
		pSlider->SetMaxValue( m_vStrings.size()-1 );

	int iHeight = 0;
	for( int i = pSlider->GetValue(); i <= pSlider->GetMaxValue(); i++ )
	{
		if( !m_vStrings[ i ].c_str() ) continue;

		float fWidth = static_cast<float>( GetFont()->GetStringWidth( m_vStrings[ i ].c_str() ) );
		int iLines = static_cast<int>( ceilf( fWidth / ( GetWidth() -  pSlider->GetSliderWidth() ) ) );

		int iTempHeight = iLines*GetFont()->GetStringHeight();
		iHeight += iTempHeight;
	
		while( iHeight > GetHeight() - GetFont()->GetStringHeight() )
		{
			pSlider->SetValue( pSlider->GetValue() + iLines );
			iHeight -= iTempHeight;
		}
	}/*

	for( std::vector<uistring>::reverse_iterator iIter = vPending.rbegin(); iIter != vPending.rend(); iIter++ )
		AddString( *iIter );*/

	LeaveCriticalSection(&cs);
}

void CTextBox::Clear()
{
	EnterCriticalSection(&cs);
	m_vStrings.clear();
	LeaveCriticalSection(&cs);
}

void CTextBox::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pString = pState->GetColor( _UI("String") );
	pInner = pState->GetColor( _UI("Inner") );
	pBorder = pState->GetColor( _UI("Border") );
}

void CTextBox::ShowSlider(bool bShow)
{
	pSlider->SetShow(bShow);
}

void CTextBox::SetMaxStrings(int limit)
{
	m_iLimit = limit;
	m_vStrings.resize(limit);
}

int CTextBox::GetMaxStrings()
{
	return m_iLimit;
}

void CTextBox::RemoveStrings(int Row, int Count)
{
	EnterCriticalSection(&cs);
	if((int)m_vStrings.size() > Row)
		m_vStrings.erase(m_vStrings.begin()+Row, (!Count?m_vStrings.end():m_vStrings.begin()+Row+Count));
	pSlider->SetMaxValue(Row);
	LeaveCriticalSection(&cs);
}