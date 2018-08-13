#include "CGUI.h"

CWindow::CWindow( CGUI *Gui, int X, int Y, int Width, int Height, const uichar * String, const uichar * String2, tAction Callback )
{
	m_pFocussedElement = 0;
	SetMaximized( true );
	SetTitleVisible( true );
	SetFocussedElement( 0 );
	posDif = CPos();
	m_bDragging = false;

	SetElement( Gui, X, Y, Width, Height, String, String2, Callback, 1 );

	SetMouseOver( false );
	SetVisible( true );

	hTitleBar = 0;
	m_bTab = 0;
	sButton[0] = sButton[1] = mButton[0] = mButton[1] = 0;

	SetThemeElement( pGui->GetThemeElement( _UI("Window") ) );

	if( !GetThemeElement() )
		MessageBox( 0, _UI("Theme element invalid."), _UI("Window"), 0 );
	else
		SetElementState( _UI("Norm") );

	SetThemeElement( pGui->GetThemeElement( _UI("TitleBar") ), 2 );

	if( !GetThemeElement( 2 ) )
		MessageBox( 0, _UI("Theme element invalid."), _UI("TitleBar"), 0 );
	else
		SetElementState( _UI("Norm"), 2 );

	SetThemeElement( pGui->GetThemeElement( _UI("CloseButton") ), 1 );

	if( !GetThemeElement( 1 ) )
		MessageBox( 0, _UI("Theme element invalid."), _UI("CloseButton"), 0 );
	else
	{
		SetElementState( _UI("Norm"), 1 );
		SetCloseButton( true );

		MouseMove( pGui->GetMouse() );
	}

	Gui->AddWindow(this);
}

CWindow::~CWindow()
{
	for( int i = 0; i < (int)m_eLine[0].size(); i++ )
		SAFE_DELETE( m_eLine[0][i] );
	m_eLine[0].clear();

	for( int i = 0; i < (int)m_eLine[1].size(); i++ )
		SAFE_DELETE( m_eLine[1][i] );
	m_eLine[1].clear();

	for( int i = 0; i < (int)m_eBox[0].size(); i++ )
		SAFE_DELETE( m_eBox[0][i] );
	m_eBox[0].clear();

	for( int i = 0; i < (int)m_eBox[1].size(); i++ )
		SAFE_DELETE( m_eBox[1][i] );
	m_eBox[1].clear();

	for( int i = 0; i < (int)m_eImage[0].size(); i++ )
		SAFE_DELETE( m_eImage[0][i] );
	m_eImage[0].clear();

	for( int i = 0; i < (int)m_eImage[1].size(); i++ )
		SAFE_DELETE( m_eImage[1][i] );
	m_eImage[1].clear();

	SAFE_DELETE( m_pFocussedElement );

	SAFE_DELETE( pTitle );
	SAFE_DELETE( pBody );
	SAFE_DELETE( pTitlebar ); 
	SAFE_DELETE( pButton );

	for(int i = 0; i < 8; i++)
		SAFE_DELETE( tBorder[i] );

	for( int iIndex = 0; iIndex < static_cast<int>( m_vElements.size() ); iIndex++ )
		SAFE_DELETE( m_vElements[ iIndex ] );
	m_vElements.clear();
}

void CWindow::AddElement( CElement * pElement )
{
	if(m_bTitleVisible)
		pElement->SetRelPos( *pElement->GetRelPos() + CPos( 0, hTitleBar ) );
	pElement->SetParent( this );

	m_vElements.push_back( pElement );
}
void CWindow::Draw()
{	
	if(m_bTitleVisible)
	{
		pTitlebar->Draw( GetAbsPos()->GetX(), GetAbsPos()->GetY(), GetWidth(), hTitleBar );
		GetFont()->DrawString( GetAbsPos()->GetX() + 5, GetAbsPos()->GetY() + 5, 0, pTitle, GetFormatted() );
		pButton->Draw( GetAbsPos()->GetX() + GetWidth() - mButton[0], GetAbsPos()->GetY() + mButton[1], sButton[0], sButton[1] );
	}

	if( GetMaximized() )
	{
		if(m_bTitleVisible)
		{
			pGui->DrawOutlinedBox( GetAbsPos()->GetX(), GetAbsPos()->GetY()+hTitleBar, GetWidth(), GetHeight() - hTitleBar,  pBody->GetD3DCOLOR(), pBody->GetD3DCOLOR() );
		}

		for(int i = 0; i < (int)m_eLine[0].size(); i++)
			m_eLine[0][i]->Draw();

		for(int i = 0; i < (int)m_eBox[0].size(); i++)
			m_eBox[0][i]->Draw();
	
		for(int i = 0; i < (int)m_eImage[0].size(); i++)
			m_eImage[0][i]->Draw();

		if(m_bTitleVisible)
		{
			CPos *pos = GetAbsPos();
			int width = GetWidth();
			int height = GetHeight();
			int xx = pos->GetX();
			int yy = pos->GetY();

			tBorder[0]->Draw( xx-hwBorder[2], yy+hwBorder[1]-hwBorder[2], hwBorder[0], height-2*hwBorder[1]+2*hwBorder[2] );
			tBorder[1]->Draw( xx+width-hwBorder[0]+hwBorder[2], yy+hwBorder[1]-hwBorder[2], hwBorder[0], height-2*hwBorder[1]+2*hwBorder[2] );
			tBorder[2]->Draw( xx-hwBorder[2], yy-hwBorder[2], hwBorder[0], hwBorder[1] );
			tBorder[3]->Draw( xx-hwBorder[2], yy+height-hwBorder[1]+hwBorder[2]-1, hwBorder[0], hwBorder[1] );
			tBorder[4]->Draw( xx+width-hwBorder[0]+hwBorder[2], yy-hwBorder[2], hwBorder[0], hwBorder[1] );
			tBorder[5]->Draw( xx+width-hwBorder[0]+hwBorder[2], yy+height+hwBorder[2]-hwBorder[1]-1, hwBorder[0], hwBorder[1] );
			tBorder[6]->Draw( xx-hwBorder[2]+hwBorder[0], yy-hwBorder[2], width+2*hwBorder[2]-2*hwBorder[1], hwBorder[1] );
			tBorder[7]->Draw( xx-hwBorder[2]+hwBorder[0], yy+height-hwBorder[1]+hwBorder[2]-1, width+2*hwBorder[2]-2*hwBorder[1], hwBorder[1] );
		}

		for( int iIndex = 0; iIndex < static_cast<int>( m_vElements.size() ); iIndex++ )
			if(m_vElements[iIndex]) m_vElements[iIndex]->Draw();

		for(int i = 0; i < (int)m_eLine[1].size(); i++)
			m_eLine[1][i]->Draw();

		for(int i = 0; i < (int)m_eBox[1].size(); i++)
			m_eBox[1][i]->Draw();

		for(int i = 0; i < (int)m_eImage[1].size(); i++)
			m_eImage[1][i]->Draw();
	}
	else
	{
		CPos *pos = GetAbsPos();
		int width = GetWidth();
		int height = hTitleBar;
		int xx = pos->GetX();
		int yy = pos->GetY();

		tBorder[0]->Draw( xx-hwBorder[2], yy+hwBorder[1]-hwBorder[2], hwBorder[0], height-2*hwBorder[1]+2*hwBorder[2] );
		tBorder[1]->Draw( xx+width-hwBorder[0]+hwBorder[2], yy+hwBorder[1]-hwBorder[2], hwBorder[0], height-2*hwBorder[1]+2*hwBorder[2] );
		tBorder[2]->Draw( xx-hwBorder[2], yy-hwBorder[2], hwBorder[0], hwBorder[1] );
		tBorder[3]->Draw( xx-hwBorder[2], yy+height-hwBorder[1]+hwBorder[2]-1, hwBorder[0], hwBorder[1] );
		tBorder[4]->Draw( xx+width-hwBorder[0]+hwBorder[2], yy-hwBorder[2], hwBorder[0], hwBorder[1] );
		tBorder[5]->Draw( xx+width-hwBorder[0]+hwBorder[2], yy+height+hwBorder[2]-hwBorder[1]-1, hwBorder[0], hwBorder[1] );
		tBorder[6]->Draw( xx-hwBorder[2]+hwBorder[0], yy-hwBorder[2], width+2*hwBorder[2]-2*hwBorder[1], hwBorder[1] );
		tBorder[7]->Draw( xx-hwBorder[2]+hwBorder[0], yy+height-hwBorder[1]+hwBorder[2]-1, width+2*hwBorder[2]-2*hwBorder[1], hwBorder[1] );
	}
}

void CWindow::PreDraw()
{
	GetString( true );

	if( GetMaximized() )
		for( int iIndex = 0; iIndex < static_cast<int>( m_vElements.size() ); iIndex++ )
		{
			if(m_vElements[iIndex]) m_vElements[ iIndex ]->PreDraw();
		}
}

bool CWindow::MouseMove( CMouse * pMouse, bool )
{
	if( GetDragging() )
	{
		if( !posDif.GetX() )
			posDif = *GetAbsPos() - pMouse->GetPos();
		else
		{
			CPos mPos = pMouse->GetPos();

			if( mPos.GetX() == -1 && mPos.GetY() == -1 )
				mPos = pMouse->GetSavedPos();

			SetAbsPos( mPos + posDif );
			SendMsg(CHANGE, 0);
		}
	}

	if( GetCloseButton() && m_bTitleVisible )
		SetElementState( SetMouseOver( pMouse->InArea( GetAbsPos()->GetX() + GetWidth() - mButton[0], GetAbsPos()->GetY() + mButton[1], sButton[0], sButton[1] ) )?_UI("MouseOver"):_UI("Norm"), 1 );

	bool isOver = 1;
	if( GetMaximized() )
		for( int iIndex = static_cast<int>( m_vElements.size() ) - 1; iIndex >= 0; iIndex-- )
			if(m_vElements[iIndex]) if(m_vElements[ iIndex ]->MouseMove( pMouse, isOver)) isOver = 0;

	return 0;
}

bool CWindow::KeyEvent( SKey sKey )
{
	CMouse * pMouse = pGui->GetMouse();

	if( pMouse->GetLeftButton() )
	{
		SendMsg(CLICK, 0);
		SetFocussedElement( 0 );

		if( GetMouseOver() && m_bCloseButtonEnabled && m_bTitleVisible )
		{
			SendMsg(END, 0);
			this->SetVisible( false );
		}
		else if( pMouse->InArea( GetAbsPos()->GetX(), GetAbsPos()->GetY(), GetWidth(), hTitleBar ) && m_bTitleVisible )
		{
			if( !pMouse->GetDragging() )
			{
				if( pMouse->GetLeftButton() == 1 )
				{
					pGui->BringToTop( this );

					SetDragging( true );
					pMouse->SetDragging( this );

					SetElementState( _UI("Dragging"), 2 );
				}
				else
				{
					SetMaximized( !GetMaximized() );

					SetElementState( GetMaximized()?_UI("Norm"):_UI("Minimized"), 2 );

					pGui->BringToTop( this );
				}
			}
		}
		else if(  pMouse->InArea( GetAbsPos()->GetX(), GetAbsPos()->GetY(), GetWidth(), GetHeight() ) )
			pGui->BringToTop( this );
	}
	else
	{
		posDif.SetX( 0 );

		pMouse->SetDragging( 0 );
		SetDragging( false );

		SetElementState( GetMaximized()?_UI("Norm"):_UI("Minimized"), 2 );
	}

	if(sKey.m_vKey == 9 && !m_bTab)
	{
		SetFocussedElement(m_vElements[0]);
		m_bTab = 1;
		return 0;
	}
	else
		m_bTab = 0;

	if( GetMaximized() )
		for( int iIndex = 0; iIndex < static_cast<int>( m_vElements.size() ); iIndex++ )
			if(m_vElements[ iIndex ]) m_vElements[ iIndex ]->KeyEvent( sKey );

	return 0;
}

void CWindow::SetMaximized( bool bMaximized )
{
	m_bMaximized = bMaximized;
}

bool CWindow::GetMaximized()
{
	return m_bMaximized;
}

void CWindow::SetVisible( bool bVisible )
{
	m_bVisible = bVisible;
	if(bVisible) pGui->BringToTop( this );
}

bool CWindow::IsVisible()
{
	return m_bVisible;
}

void CWindow::SetDragging( bool bDragging )
{
	m_bDragging = bDragging;
}

bool CWindow::GetDragging()
{
	return m_bDragging;
}

void CWindow::SetCloseButton( bool bEnabled )
{
	m_bCloseButtonEnabled = bEnabled;

	if(!bEnabled)
		SetElementState( _UI("Disabled"), 1 );
	else
		SetElementState( _UI("Norm"), 1 );
}

bool CWindow::GetCloseButton()
{
	return m_bCloseButtonEnabled;
}

void CWindow::SetFocussedElement( CElement * pElement )
{
	if(m_pFocussedElement)
		m_pFocussedElement->LostFocus();

	if(pElement != 0)
		pElement->GotFocus();

	m_pFocussedElement = pElement;

	if( pElement )
		BringToTop( pElement );
}

CElement * CWindow::GetFocussedElement()
{
	return m_pFocussedElement;
}

CElement * CWindow::GetNextElement( CElement * pElement )
{
	for( int i = 0; i < static_cast<int>( m_vElements.size() ); i++ )
		if(m_vElements[ i ])
			if( m_vElements[i] == pElement )
				return m_vElements[ i + 1 ];
	return *m_vElements.begin();
}

CElement * CWindow::GetElementByString( const uichar * pszString, int iIndex )
{
	for( int i = 0; i < static_cast<int>( m_vElements.size() ); i++ )
		if(m_vElements[ i ])
			if( m_vElements[ i ]->GetString( false, iIndex ) == pszString )
				return m_vElements[ i ];
	return 0;
}

void CWindow::BringToTop( CElement * pElement )
{
	for( int i = 0; i < static_cast<int>( m_vElements.size() ); i++ )
		if(m_vElements[i])
			if( m_vElements[i] == pElement )
				m_vElements.erase( m_vElements.begin() + i );
	m_vElements.insert(  m_vElements.end(), pElement );
}

void CWindow::UpdateTheme( int iIndex )
{
	SElementState * pState = GetElementState( iIndex );
	if( iIndex == 2 )
	{
		pTitle = pState->GetColor( _UI("Title") );
		pTitlebar = pState->GetTexture( _UI("Titlebar") );
		hTitleBar = pState->GetInt(_UI("Height"));
	}
	else if(iIndex == 1)
	{
		pButton = pState->GetTexture( _UI("Button") );
		mButton[0] = pState->GetInt(_UI("RightMargin"));
		mButton[1] = pState->GetInt(_UI("TopMargin"));
		sButton[0] = pState->GetInt(_UI("Width"));
		sButton[1] = pState->GetInt(_UI("Height"));
	}
	else
	{
		pBody = pState->GetColor( _UI("Body") );
		hwBorder[0] = pState->GetInt(_UI("BorderWidth"));
		hwBorder[1] = pState->GetInt(_UI("BorderHeight"));
		hwBorder[2] = pState->GetInt(_UI("BorderMargin"));

		tBorder[0] = pState->GetTexture(_UI("BorderCL"));
		tBorder[1] = pState->GetTexture(_UI("BorderCR")); 
		tBorder[2] = pState->GetTexture(_UI("BorderUL"));
		tBorder[3] = pState->GetTexture(_UI("BorderDL"));
		tBorder[4] = pState->GetTexture(_UI("BorderUR"));
		tBorder[5] = pState->GetTexture(_UI("BorderDR"));
		tBorder[6] = pState->GetTexture(_UI("BorderUC"));
		tBorder[7] = pState->GetTexture(_UI("BorderRC"));
	}
}

void CWindow::SetTitleVisible( bool v )
{
	m_bTitleVisible = v;
}

bool CWindow::GetTitleVisible()
{
	return m_bTitleVisible;
}

int CWindow::GetTitleBarHeight()
{
	return hTitleBar;
}

void CWindow::OnLostDevice()
{
	for(int i = 0; i < (int)m_vElements.size(); i++)
		m_vElements[i]->OnLostDevice();

	CElement::OnLostDevice();
}

void CWindow::OnResetDevice()
{
	for(int i = 0; i < (int)m_vElements.size(); i++)
		m_vElements[i]->OnResetDevice();

	CElement::OnResetDevice();
}