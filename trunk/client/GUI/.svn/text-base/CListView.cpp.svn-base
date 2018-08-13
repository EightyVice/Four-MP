#include "CListView.h"

CListView::CListView( CGUI *Gui, int X, int Y, int *Width, int Height, int Columns, const uichar *String, const uichar *String2, tAction Callback )
{
	Count = Columns;
	Poss = new int[Count];
	Widths = new int[Count];
	imgColumn = new ImageColumn[Count];

	int AllWidth = 0;
	Poss[0] = 0;
	for(int i = 0; i < Count; i++)
	{
		Widths[i] = Width[i];
		AllWidth += Width[i];
		if(i > 0)
			Poss[i] = Poss[i-1]+Widths[i-1];

		imgColumn[i].tFalse = imgColumn[i].tTitle = imgColumn[i].tTrue = 0;
		imgColumn[i].Height = imgColumn[i].Width = 0;
	}

	SetElement( Gui, X, Y, AllWidth, Height, String, String2, Callback );
	m_iMouseOverIndex = -1;
	m_iMouseSelect = -1;
	m_vRows = new std::vector<uistring>[Count];

	pSlider = new CScrollBar( Gui, CPos( GetWidth() - 1, 1 ), GetHeight()-2 );

	SetThemeElement( pGui->GetThemeElement( _UI("ListView") ) );

	ShowSlider(1);
	Widths[Count-1] -= pSlider->GetWidth();

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("ListView"), 0 );
	else
		SetElementState( _UI("Norm") );
}

CListView::~CListView()
{
	for(int i = 0; i < Count; i++)
	{
		SAFE_DELETE(imgColumn[i].tFalse);
		SAFE_DELETE(imgColumn[i].tTrue);
		SAFE_DELETE(imgColumn[i].tTitle);
	}

	SAFE_DELETE(pSlider);

	SAFE_DELETE(pInner);
	SAFE_DELETE(pBorder);
	SAFE_DELETE(pString);
	SAFE_DELETE(pMouseOverString);
	SAFE_DELETE(pSelInner);
	SAFE_DELETE(pSelString);
	SAFE_DELETE(pTitle);
	SAFE_DELETE(pbTitle);
	SAFE_DELETE(pbInner);
	SAFE_DELETE(pTitleString);
}

void CListView::Draw()
{
	EnterCriticalSection(&cs);
	CPos Pos = *GetRelPos();
	if(GetParent()) Pos = *GetParent()->GetAbsPos() + Pos;

	pGui->DrawOutlinedBox( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight(), pInner->GetD3DCOLOR(), pBorder->GetD3DCOLOR() );

	int iAddHeight = GetFont()->GetStringHeight();

	pGui->DrawOutlinedBox( Pos.GetX() + 1, Pos.GetY() + 1, GetWidth()-2, iAddHeight, pTitle->GetD3DCOLOR(), pTitle->GetD3DCOLOR() );
	for( int j = 0; j < Count; j++)
	{
		if( static_cast<int>( mTitles.size() ) > j)
		{
			if(imgColumn[j].tTitle)
				imgColumn[j].tTitle->Draw(Pos.GetX() + (Poss[j]?Poss[j]:0)+1, 
					Pos.GetY()+1, imgColumn[j].Width, imgColumn[j].Height);
			else
				GetFont()->DrawString( Pos.GetX() + Widths[j]/2 + (Poss[j]?Poss[j]:0), Pos.GetY(), FT_CENTER, pTitleString, mTitles[j], Widths[j] );
			if(j != Count-1) pGui->DrawLine(Pos.GetX()+Widths[j]+(Poss[j]?Poss[j]:0), Pos.GetY()+2, Pos.GetX()+Widths[j]+Poss[j] , Pos.GetY()+iAddHeight-1, 1, pbTitle->GetD3DCOLOR());
		}

		int iHeight = iAddHeight + 5;

		if(j != Count-1) pGui->DrawLine(Pos.GetX()+Widths[j]+(Poss[j]?Poss[j]:0), Pos.GetY()+iHeight, Pos.GetX()+Widths[j]+Poss[j] , Pos.GetY()+GetHeight()-2, 1, pbInner->GetD3DCOLOR());

		if( m_vRows[j].size() )
		{
			for( int i = pSlider->GetValue(); i < static_cast<int>( m_vRows[j].size() ) && iHeight < GetHeight() - GetFont()->GetStringHeight(); i++ )
			{
				CColor * pColor = 0;

				if( i == m_iMouseOverIndex && GetMouseOver())
					pColor = pMouseOverString;
				else
					pColor = pString;

				if(m_iMouseSelect == i)	
				{
					if(j == 0)
						pGui->DrawOutlinedBox( Pos.GetX() + 1, Pos.GetY() + iHeight, GetWidth()-2, iAddHeight, pSelInner->GetD3DCOLOR(), pSelInner->GetD3DCOLOR() );
					pColor = pSelString;
				}

				if(imgColumn[j].tTrue && imgColumn[j].tFalse)
					if(m_vRows[j][i][0] == _UI('0'))
						imgColumn[j].tFalse->Draw(Pos.GetX() + (Poss[j]?Poss[j]:0)+1, Pos.GetY()+iHeight+1, imgColumn[j].Width, imgColumn[j].Height);
					else
						imgColumn[j].tTrue->Draw(Pos.GetX() + (Poss[j]?Poss[j]:0)+1, Pos.GetY()+iHeight+1, imgColumn[j].Width, imgColumn[j].Height);
				else
					GetFont()->DrawString( Pos.GetX() + (Poss[j]?Poss[j]:0) + Widths[j]/2, Pos.GetY() + iHeight, FT_CENTER, pColor, m_vRows[j][i], Widths[j] );

				if(j == 0 && iHeight != iAddHeight + 5)
					pGui->DrawLine(Pos.GetX()+2, Pos.GetY()+iHeight, Pos.GetX()+GetWidth()-4 , Pos.GetY()+iHeight, 1, pbInner->GetD3DCOLOR());

				iHeight += iAddHeight;
			}
		}
	}

	pSlider->Draw( Pos );
	LeaveCriticalSection(&cs);
}	

void CListView::PreDraw()
{
	pSlider->PreDraw();
}

bool CListView::MouseMove( CMouse * pMouse, bool over )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();
	
	bool inArea = pMouse->InArea( Pos.GetX(), Pos.GetY(), GetWidth(), GetHeight() ) && over;
	SetMouseOver( inArea );
	
	m_iMouseOverIndex = -1;
	int iStringHeight = GetFont()->GetStringHeight();
	for( int i = pSlider->GetValue(), iHeight = iStringHeight+5; i < static_cast<int>( m_vRows[0].size() ) || iHeight < GetHeight(); i++ )
	{
		if( pMouse->InArea( Pos.GetX(), Pos.GetY() + iHeight, GetWidth() - 10, iStringHeight ) )
			m_iMouseOverIndex = i;

		iHeight += iStringHeight;
	}

	pSlider->MouseMove( Pos, pMouse );
	return inArea;
}

bool CListView::KeyEvent( SKey sKey )
{
	CPos Pos = *GetParent()->GetAbsPos() + *GetRelPos();

	if( !sKey.m_vKey )
	{
		if( GetMouseOver() )
		{
			if( m_iMouseOverIndex >= 0 && pGui->GetMouse()->GetLeftButton() )
			{
				if(m_iMouseSelect > -2) m_iMouseSelect = m_iMouseOverIndex;
				if( GetAction() )
					GetAction()( this, SELECT, m_iMouseOverIndex );
			}
		}
	}

	if( GetMouseOver() || ( !sKey.m_bDown && !pGui->GetMouse()->GetWheel() )  )
	{
		pSlider->KeyEvent( Pos, sKey );
		MouseMove( pGui->GetMouse(), 1 );
	}

	return 0;
}

int CListView::GetSize(int Index)
{
	if(Index >= Count || Index < 0) return -1;
	return m_vRows[Index].size();
}

void CListView::PutStr( uistring sString, int Column, int Row, uistring sHelp )
{
	if(Column < 0 || Column >= Count) return;
	EnterCriticalSection(&cs);

	if(Row >= static_cast<int>( m_vRows[Column].size() ) || Row == -1)
	{
		pSlider->SetMaxValue( m_vRows[Column].size() );
		m_vRows[Column].push_back(sString);
		m_vRowsHelp.push_back(sHelp);
	}
	else
	{
		m_vRows[Column][Row] = sString;
		m_vRowsHelp[Row] = sHelp;
	}

	LeaveCriticalSection(&cs);
}

uistring CListView::GetStr( int Row, int Column )
{
	if(Column < 0 || Column >= Count) return NULL;

	if( Row >= 0 && Row < static_cast<int>( m_vRows[Column].size() ) )
		return m_vRows[ Column ][ Row ];
	return uistring();
}

void CListView::SetTitle( uistring sString, int Column )
{
	EnterCriticalSection(&cs);
	if(Column == -1)
	{
		mTitles.push_back(sString);
	}
	else
	{
		mTitles[Column] = sString;
	}
	LeaveCriticalSection(&cs);
}

void CListView::Clear()
{
	EnterCriticalSection(&cs);
	for(int i = 0; i < Count; i++)
		while(!m_vRows[i].empty()) m_vRows[i].clear();
	LeaveCriticalSection(&cs);
}

void CListView::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );

	pInner = pState->GetColor( _UI("Inner") );
	pBorder = pState->GetColor( _UI("Border") );
	pString = pState->GetColor( _UI("String") );
	pMouseOverString = pState->GetColor( _UI("MouseOverString") );

	pTitle = pState->GetColor( _UI("Title") );
	pbTitle = pState->GetColor( _UI("TitleDel") );
	pbInner = pState->GetColor( _UI("InnerDel") );
	pTitleString = pState->GetColor( _UI("TitleString") );

	pSelInner = pState->GetColor( _UI("SelectInner"));
	pSelString = pState->GetColor( _UI("SelectString"));
}

void CListView::ShowSlider( bool bShow )
{
	pSlider->SetShow(bShow);
}

int CListView::GetSelected()
{
	return m_iMouseSelect;
}

void CListView::SetSelect(int Item)
{
	m_iMouseSelect = Item;
}

void CListView::SetColumnImage(int Index, uichar *True, uichar *False, uichar *Title, int W, int H)
{
	if(Index >= Count) return;
	imgColumn[Index].tTrue = new CTexture(pGui->GetSprite(), True);
	imgColumn[Index].tFalse = new CTexture(pGui->GetSprite(), False);
	imgColumn[Index].tTitle = new CTexture(pGui->GetSprite(), Title);
	imgColumn[Index].Width = W;
	imgColumn[Index].Height = H;
}

uistring CListView::GetHelpString(int row)
{
	return m_vRowsHelp[row];
}