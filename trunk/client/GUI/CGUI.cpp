#include "CGUI.h"
#include <stdarg.h>
#include <stdio.h>

CGUI::CGUI( IDirect3DDevice9 * pDevice )
{
	InitializeCriticalSection(&cs);

	if( !pDevice )
		MessageBox( 0, _UI("pDevice invalid."), 0, 0 );

	m_pDevice = pDevice;
	m_wFocus = 0;

	D3DXCreateSprite( pDevice, &m_pSprite );
	D3DXCreateLine( pDevice, &m_pLine );

	m_pMouse = new CMouse( this, pDevice, m_pSprite );
	m_pKeyboard = new CKeyboard(this);
	m_pFont = 0;

	Cvars[ _UI("$Value") ] = new CVar( SliderValue );
	Cvars[ _UI("$MaxValue") ] = new CVar( MaxValue );
	Cvars[ _UI("$MinValue") ] = new CVar( MinValue );

	SetVisible( false );
}

CGUI::~CGUI()
{
	EnterCriticalSection(&cs);

	for( std::map<uistring,CVar*>::iterator iIter = Cvars.begin(); iIter != Cvars.end(); iIter++ )
		SAFE_DELETE( iIter->second );

	SAFE_DELETE( m_pFont );
	SAFE_DELETE( m_pMouse );
	SAFE_DELETE( m_pKeyboard );

	SAFE_RELEASE( m_pSprite );
	SAFE_RELEASE( m_pLine );

	SAFE_DELETE( m_wFocus );

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

	for( int i = 0; i < (int)m_eText[0].size(); i++ )
		SAFE_DELETE( m_eText[0][i] );
	m_eText[0].clear();

	for( int i = 0; i < (int)m_eText[1].size(); i++ )
		SAFE_DELETE( m_eText[1][i] );
	m_eText[1].clear();

	for( int i = 0; i < (int)m_eImage[0].size(); i++ )
		SAFE_DELETE( m_eImage[0][i] );
	m_eImage[0].clear();

	for( int i = 0; i < (int)m_eImage[1].size(); i++ )
		SAFE_DELETE( m_eImage[1][i] );
	m_eImage[1].clear();
	
	for( int i = 0; i < static_cast<int>( m_vWindows.size() ); i++ )
		SAFE_DELETE( m_vWindows[i] );
	m_vWindows.clear();
	
	LeaveCriticalSection(&cs);
	DeleteCriticalSection(&cs);
}

void CGUI::LoadFont(int size, uichar *font)
{
	m_pFont = new CFont( this, GetDevice(), size, font );
}

void CGUI::SetFontColors(int Index, int r, int g, int b, int a)
{
	m_pFont->SetColor( Index, CColor( r, g, b, a ) );
}

void CGUI::SetVarInt(const uichar *name, int value)
{
	Cvars[ name ] = new CVar( value );
}

void CGUI::SetVarString(const uichar *name, uistring value)
{
	Cvars[ name ] = new CVar( value );
}

void CGUI::SetVarBool(const uichar *name, bool value)
{
	Cvars[ name ] = new CVar( value );
}

void CGUI::LoadInterfaceFromFile( const uichar * pszFilePath, const uichar * dir )
{
	TiXmlDocument Document;

	if( !Document.LoadFile( pszFilePath ) )
	{
		MessageBox( 0, Document.ErrorDesc(), _UI("XML Error"), 0 );
		exit(1);
		return;
	}
	
	TiXmlHandle hDoc( &Document );

	TiXmlElement * pGUI = hDoc.FirstChildElement( _UI("GUI") ).Element();
	if( pGUI )
	{
		TiXmlElement * pColorThemes = pGUI->FirstChildElement( _UI("ColorThemes") );
		if( pColorThemes )
		{
			const uichar * pszDefaultTheme = pColorThemes->Attribute( _UI("default") );
			if( pszDefaultTheme )
				m_sCurTheme = pszDefaultTheme;

			for( TiXmlElement * pThemeElement = pColorThemes->FirstChildElement(); pThemeElement; pThemeElement = pThemeElement->NextSiblingElement() )
				for( TiXmlElement * pElementElement = pThemeElement->FirstChildElement(); pElementElement; pElementElement = pElementElement->NextSiblingElement() )
				{
					SElement * sCurElement = new SElement();

					const uichar * pszDefault = pElementElement->Attribute( _UI("default") );
					if( pszDefault )
						sCurElement->sDefaultState = uistring( pszDefault );

					for( TiXmlElement * pStateElement = pElementElement->FirstChildElement( _UI("State") ); pStateElement; pStateElement = pStateElement->NextSiblingElement( _UI("State") ) )
					{
						const uichar * pszString = pStateElement->Attribute( _UI("string") );

						if( !pszString )
							continue;

						SElementState * pState = sCurElement->m_mStates[ pszString ] = new SElementState();

						pState->pParent = sCurElement;

						for( TiXmlElement * pColorElement = pStateElement->FirstChildElement( _UI("Color") ); pColorElement; pColorElement = pColorElement->NextSiblingElement( _UI("Color") ) )
						{
							pszString = pColorElement->Attribute( _UI("string") );

							if( !pszString )
								continue;

							pState->mColors[ pszString ] = new CColor( pColorElement );
						}
						for( TiXmlElement * pTextureElement = pStateElement->FirstChildElement( _UI("Texture") ); pTextureElement; pTextureElement = pTextureElement->NextSiblingElement( _UI("Texture") ) )
						{
							unistream sStream;

							sStream << pThemeElement->Value() << _UI("/") << dir << pTextureElement->Attribute( _UI("path") );
							
							pState->mTextures[ pTextureElement->Attribute( _UI("string") ) ] = new CTexture( GetSprite(), sStream.str().c_str(), new CColor(pTextureElement) );
						}
						for( TiXmlElement * pIntElement = pStateElement->FirstChildElement( _UI("Int") ); pIntElement; pIntElement = pIntElement->NextSiblingElement( _UI("Int") ) )
						{
							pszString = pIntElement->Attribute( _UI("string") );

							if( !pszString )
								continue;

							pState->mInts[ pszString ] = utoi(pIntElement->Attribute(_UI("value")));
					}

						m_mThemes[ pThemeElement->Value() ][ pElementElement->Value() ] = sCurElement;
					}
				}
		}
	}
}

void CGUI::UpdateFromFile( const uichar * pszFilePath )
{
	TiXmlDocument Document;

	if( !Document.LoadFile( pszFilePath ) )
	{
		MessageBox(NULL, Document.ErrorDesc(), _UI("UpdateGUI"), MB_OK);
		return;
	}

	TiXmlHandle hDoc( &Document );

	TiXmlElement * pGUI = hDoc.FirstChildElement( _UI("GUI") ).Element();
	if( !pGUI ) 
	{
		MessageBox(NULL, _UI("XML Error"), _UI("UpdateGUI"), MB_OK);
		return;
	}

	for( TiXmlElement * pThemeElement = pGUI->FirstChildElement(); pThemeElement; pThemeElement = pThemeElement->NextSiblingElement() )
	{
		int Index = 0;
		CWindow *wParent = NULL;

		if(uiscmp(pThemeElement->Value(), _UI("Over")) == 0) Index = 1;
		if(uiscmp(pThemeElement->Attribute(_UI("parent")), _UI("none")) != 0)
			wParent = GetWindowByString(pThemeElement->Attribute(_UI("parent")), 1);

		for( TiXmlElement * pElementElement = pThemeElement->FirstChildElement(); pElementElement; pElementElement = pElementElement->NextSiblingElement() )
		{
			const uichar *Element = pElementElement->Value();

			if(uiscmp(Element, _UI("Element")) == 0)
			{
				CElement *pElement;
				if(wParent == NULL)
					pElement = GetWindowByString(pElementElement->Attribute(_UI("name")), 1);
				else
					pElement = wParent->GetElementByString(pElementElement->Attribute(_UI("name")), 1);
		
				for(TiXmlElement * pElem = pElementElement->FirstChildElement( _UI("Base") ); pElem; pElem = pElem->NextSiblingElement( _UI("Base") ))
				{
					const uichar *name = pElem->Attribute(_UI("string"));
					const uichar *value = pElem->Attribute(_UI("value"));

					if(uiscmp(name, _UI("height")) == 0) pElement->SetHeight(utoi(value));
					else if(uiscmp(name, _UI("width")) == 0) pElement->SetWidth(utoi(value));
					else if(uiscmp(name, _UI("name")) == 0) pElement->SetString(value);
					else if(uiscmp(name, _UI("x")) == 0) pElement->SetRelPos(utoi(value), -1);
					else if(uiscmp(name, _UI("y")) == 0) pElement->SetRelPos(-1, utoi(value));
					else if(uiscmp(name, _UI("style")) == 0) 
					{
						pElement->SetThemeElement( GetThemeElement( value ), utoi(pElem->Attribute(_UI("number"))));
						pElement->SetElementState(_UI("Norm"), utoi(pElem->Attribute(_UI("number"))));
					}
				}

				TiXmlElement * pElem = pElementElement->FirstChildElement( _UI("Font") );
				if(pElem)
				{
					pElement->SetFont(utoi(pElem->Attribute(_UI("size"))), (uichar*)pElem->Attribute(_UI("name")), 
						pElem->Attribute(_UI("bold"))[0]==_UI('1'), pElem->Attribute(_UI("italic"))[0]==_UI('1'));
				}
			}
			else if(uiscmp(Element, _UI("Line")) == 0)
			{
				CLine *tLine = new CLine(this, utoi(pElementElement->Attribute(_UI("sx"))), utoi(pElementElement->Attribute(_UI("sy"))),
					utoi(pElementElement->Attribute(_UI("ex"))),	utoi(pElementElement->Attribute(_UI("ey"))),
					utoi(pElementElement->Attribute(_UI("size"))), new CColor(pElementElement), wParent);

				if(!wParent) m_eLine[Index].push_back(tLine);
				else wParent->m_eLine[Index].push_back(tLine);
			}
			else if(uiscmp(Element, _UI("Box")) == 0)
			{
				CColor *Inner, *Border;

				TiXmlElement * pColorElement = pElementElement->FirstChildElement( _UI("Color") ); 
				if(uiscmp(pColorElement->Attribute(_UI("string")), _UI("Inner")) == 0) Inner = new CColor(pColorElement);
				else if(uiscmp(pColorElement->Attribute(_UI("string")), _UI("Border")) == 0) Border = new CColor(pColorElement);

				pColorElement = pColorElement->NextSiblingElement( _UI("Color") );
				if(uiscmp(pColorElement->Attribute(_UI("string")), _UI("Inner")) == 0) Inner = new CColor(pColorElement);
				else if(uiscmp(pColorElement->Attribute(_UI("string")), _UI("Border")) == 0) Border = new CColor(pColorElement);

				CBox *tBox = new CBox(this, utoi(pElementElement->Attribute(_UI("x"))), utoi(pElementElement->Attribute(_UI("y"))),
					utoi(pElementElement->Attribute(_UI("width"))), utoi(pElementElement->Attribute(_UI("height"))),
					Inner, Border, wParent);

				if(!wParent) m_eBox[Index].push_back(tBox);
				else wParent->m_eBox[Index].push_back(tBox);
			}
			else if(uiscmp(Element, _UI("Text")) == 0)
			{
				CText *tText = new CText(this, utoi(pElementElement->Attribute(_UI("x"))), utoi(pElementElement->Attribute(_UI("y"))),
					utoi(pElementElement->Attribute(_UI("width"))), 20, pElementElement->Attribute(_UI("string")), 
					pElementElement->Attribute(_UI("name")), NULL);

				if(!wParent) m_eText[Index].push_back(tText);
				else wParent->AddElement(tText);
			}
			else if(uiscmp(Element, _UI("Image")) == 0)
			{
				CTexture *tTexture = new CTexture(GetSprite(), pElementElement->Attribute(_UI("src")), new CColor(pElementElement));

				CImage *tImg = new CImage(this, utoi(pElementElement->Attribute(_UI("x"))), utoi(pElementElement->Attribute(_UI("y"))),
					utoi(pElementElement->Attribute(_UI("width"))), utoi(pElementElement->Attribute(_UI("height"))),
					tTexture, wParent);

				if(!wParent) m_eImage[Index].push_back(tImg);
				else wParent->m_eImage[Index].push_back(tImg);
			}
		}
	}
}

void CGUI::FillArea( int iX, int iY, int iWidth, int iHeight, D3DCOLOR d3dColor )
{
	DrawLine( iX + iWidth / 2, iY, iX + iWidth / 2, iY + iHeight, iWidth, d3dColor );
}

void CGUI::DrawLine( int iStartX, int iStartY, int iEndX, int iEndY, int iWidth, D3DCOLOR d3dColor )
{
	m_pLine->SetWidth( static_cast<float>( iWidth ) );

	D3DXVECTOR2 d3dxVector[2];
	
	d3dxVector[0] = D3DXVECTOR2( static_cast<float>( iStartX ), static_cast<float>( iStartY ) );
	d3dxVector[1] = D3DXVECTOR2( static_cast<float>( iEndX ), static_cast<float>( iEndY ) );
	
	m_pLine->Begin();
	m_pLine->Draw( d3dxVector, 2, d3dColor );
	m_pLine->End();
}

void CGUI::DrawOutlinedBox( int iX, int iY, int iWidth, int iHeight, D3DCOLOR d3dInnerColor, D3DCOLOR d3dBorderColor )
{
	FillArea( iX + 1, iY + 1, iWidth - 2,  iHeight - 2, d3dInnerColor );

	DrawLine( iX,				iY,					iX,					iY + iHeight,		1, d3dBorderColor );
	DrawLine( iX + 1,			iY,					iX + iWidth - 1,	iY,					1, d3dBorderColor );
	DrawLine( iX + 1,			iY + iHeight - 1,	iX + iWidth - 1,	iY + iHeight - 1,	1, d3dBorderColor );
	DrawLine( iX + iWidth - 1,	iY,					iX + iWidth - 1,	iY + iHeight,		1, d3dBorderColor );
}

void CGUI::AddWindow( CWindow * pWindow ) 
{
	if(!pWindow) return;

	EnterCriticalSection(&cs);
	m_vWindows.push_back( pWindow );
	LeaveCriticalSection(&cs);
}

void CGUI::BringToTop( CWindow * pWindow )
{
	EnterCriticalSection(&cs);
	for( int i = 0; i < static_cast<int>( m_vWindows.size() ); i++ )
	{
		if(!m_vWindows[i]) continue;
		if( m_vWindows[i] == pWindow )
			m_vWindows.erase( m_vWindows.begin() + i );
}

	if(m_wFocus)
		m_wFocus->LostFocus();
	if(pWindow)
		pWindow->GotFocus();

	m_vWindows.insert(  m_vWindows.end(), pWindow );
	m_wFocus = pWindow;
	LeaveCriticalSection(&cs);
}

void CGUI::Draw()
{
	if( !IsVisible() )
		return;

	EnterCriticalSection(&cs);
	PreDraw();
	
	for(int i = 0; i < (int)m_eLine[0].size(); i++)
		if(m_eLine[0][i]) m_eLine[0][i]->Draw();

	
	for(int i = 0; i < (int)m_eBox[0].size(); i++)
		if(m_eBox[0][i]) m_eBox[0][i]->Draw();

	
	for(int i = 0; i < (int)m_eText[0].size(); i++)
		if(m_eText[0][i]) m_eText[0][i]->Draw();

	
	for(int i = 0; i < (int)m_eImage[0].size(); i++)
		if(m_eImage[0][i]) m_eImage[0][i]->Draw();

	
	for( int iIndex = 0; iIndex < static_cast<int>( m_vWindows.size() ); iIndex++ )
	{
		if(!m_vWindows[ iIndex ]) continue;
		if( !m_vWindows[ iIndex ]->IsVisible() )
			continue;

		m_vWindows[ iIndex ]->Draw();
	}

	
	for(int i = 0; i < (int)m_eLine[1].size(); i++)
		if(m_eLine[1][i]) m_eLine[1][i]->Draw();

	
	for(int i = 0; i < (int)m_eBox[1].size(); i++)
		if(m_eBox[1][i]) m_eBox[1][i]->Draw();

	
	for(int i = 0; i < (int)m_eText[1].size(); i++)
		if(m_eText[1][i]) m_eText[1][i]->Draw();

	
	for(int i = 0; i < (int)m_eImage[1].size(); i++)
		if(m_eImage[1][i]) m_eImage[1][i]->Draw();

	
	GetMouse()->Draw();
	LeaveCriticalSection(&cs);

}

void CGUI::PreDraw()
{
	if( !m_tPreDrawTimer.Running() )
	{
		for( int iIndex = static_cast<int>( m_vWindows.size() ) - 1; iIndex >= 0; iIndex-- )
		{
			if(!m_vWindows[ iIndex ]) continue;
			if( !m_vWindows[ iIndex ]->IsVisible() )
				continue;

			m_vWindows[ iIndex ]->PreDraw();
	}

		m_tPreDrawTimer.Start( 0.1f );
	}
}

void CGUI::MouseMove( CMouse * pMouse )
{
	EnterCriticalSection(&cs);
	CElement * pDragging = GetMouse()->GetDragging();

	if( !pDragging )
	{
		bool bGotWindow = false;

		for( int iIndex = static_cast<int>( m_vWindows.size() ) - 1; iIndex >= 0; iIndex-- )
		{
			if(!m_vWindows[ iIndex ]) continue;
			if( !m_vWindows[ iIndex ]->IsVisible() )
				continue;

			int iHeight = 0;

			if( !m_vWindows[ iIndex ]->GetMaximized() )
				iHeight = m_vWindows[ iIndex ]->GetTitleBarHeight();

			if( !bGotWindow && GetMouse()->InArea( m_vWindows[ iIndex ], iHeight ) )
			{
				m_vWindows[ iIndex ]->MouseMove( pMouse );
				bGotWindow = true;
				break;
			}
			else
			{
				pMouse->SavePos();
				pMouse->SetPos( -1, -1 );
				m_vWindows[ iIndex ]->MouseMove( pMouse );
				pMouse->LoadPos();
			}
		}
	}
	else
		pDragging->MouseMove( pMouse );
	LeaveCriticalSection(&cs);
}

bool CGUI::KeyEvent( SKey sKey )
{
	EnterCriticalSection(&cs);
	bool bTop = false;

	if( !sKey.m_vKey && ( sKey.m_bDown || ( GetMouse()->GetWheel() && !sKey.m_bDown ) ) )
	{
		CMouse * pMouse = GetMouse();

		//std::vector<CWindow*> vRepeat;

		for( int iIndex = static_cast<int>( m_vWindows.size() ) - 1; iIndex >= 0; iIndex-- )
		{
			if(!m_vWindows[ iIndex ]) continue;

			if( !m_vWindows[ iIndex ]->IsVisible() )
				continue;

			if( !bTop )
			{
				int iHeight = 0;

				if( !m_vWindows[ iIndex ]->GetMaximized() )
					iHeight = m_vWindows[ iIndex ]->GetTitleBarHeight();

				if( pMouse->InArea( m_vWindows[ iIndex ], iHeight ) && !bTop )
				{
					m_vWindows[ iIndex ]->KeyEvent( sKey );
					bTop = true;
					break;
				}
				/*else
					vRepeat.push_back( m_vWindows[ iIndex ] );*/
			}
			/*else
			{
				pMouse->SavePos();
				pMouse->SetPos( CPos( -1, -1 ) );
				m_vWindows[ iIndex ]->KeyEvent( sKey );
				pMouse->LoadPos();
			}*/
	}

		/*for( int iIndex = 0; iIndex < static_cast<int>( vRepeat.size() ); iIndex++ )
		{
			if(!vRepeat[ iIndex ]) continue;

			pMouse->SavePos();
			pMouse->SetPos( CPos( -1, -1 ) );
			vRepeat[ iIndex ]->KeyEvent( sKey );
			pMouse->LoadPos();
		}*/
	}
	else
	{
		bTop = false;

		/*for( */int iIndex = static_cast<int>( m_vWindows.size() ) - 1; /*iIndex >= 0; iIndex-- )
		{
			if(!m_vWindows[ iIndex ]) continue;*/
			if( m_vWindows[ iIndex ]->IsVisible() )
			{
				if( m_vWindows[ iIndex ]->GetFocussedElement() && m_vWindows[ iIndex ]->GetMaximized() )
					bTop = true;
				
				m_vWindows[ iIndex ]->KeyEvent( sKey );
			}
		/*}*/

		if( !sKey.m_bDown )
			bTop = false;
	}
	LeaveCriticalSection(&cs);
	return bTop;
}

void CGUI::OnLostDevice()
{
	//m_pDevice = 0;
	EnterCriticalSection(&cs);

	if( GetFont() )
		GetFont()->OnLostDevice();

	GetSprite()->OnLostDevice();
	
	m_pLine->OnLostDevice();
	m_pMouse->OnLostDevice();

	for(int i = 0; i < (int)m_eImage[0].size(); i++)
		m_eImage[0][i]->OnLostDevice();

	for(int i = 0; i < (int)m_eImage[1].size(); i++)
		m_eImage[1][i]->OnLostDevice();

	for(int i = 0; i < (int)m_vWindows.size(); i++)
		m_vWindows[i]->OnLostDevice();

	
	for (std::map<uistring, tTheme>::const_iterator p = m_mThemes.begin(); p != m_mThemes.end(); ++p)
		for (tTheme::const_iterator x = p->second.begin(); x != p->second.end(); ++x)
			for(std::map<uistring, SElementState*>::const_iterator y = x->second->m_mStates.begin(); y != x->second->m_mStates.end(); ++y)
				for(std::map<uistring, CTexture*>::const_iterator z = y->second->mTextures.begin(); z != y->second->mTextures.end(); ++z)
					z->second->OnLostDevice();			

	LeaveCriticalSection(&cs);
}

void CGUI::OnResetDevice()
{
	//m_pDevice = pDevice;

	EnterCriticalSection(&cs);

	if( GetFont() )
		GetFont()->OnResetDevice(  );
	GetSprite()->OnResetDevice();
	
	m_pLine->OnResetDevice();
	m_pMouse->OnResetDevice();

	for(int i = 0; i < (int)m_eImage[0].size(); i++)
		m_eImage[0][i]->OnResetDevice();

	for(int i = 0; i < (int)m_eImage[1].size(); i++)
		m_eImage[1][i]->OnResetDevice();

	for(int i = 0; i < (int)m_vWindows.size(); i++)
		m_vWindows[i]->OnResetDevice();

	for (std::map<uistring, tTheme>::const_iterator p = m_mThemes.begin(); p != m_mThemes.end(); ++p)
		for (tTheme::const_iterator x = p->second.begin(); x != p->second.end(); ++x)
			for(std::map<uistring, SElementState*>::const_iterator y = x->second->m_mStates.begin(); y != x->second->m_mStates.end(); ++y)
				for(std::map<uistring, CTexture*>::const_iterator z = y->second->mTextures.begin(); z != y->second->mTextures.end(); ++z)
					z->second->OnResetDevice();	
	
	LeaveCriticalSection(&cs);
}

CMouse * CGUI::GetMouse()
{
	return m_pMouse;
}

CKeyboard * CGUI::GetKeyboard()
{
	return m_pKeyboard;
}

IDirect3DDevice9 * CGUI::GetDevice()
{
	return m_pDevice;
}

CFont * CGUI::GetFont()
{
	return m_pFont;
}

ID3DXSprite * CGUI::GetSprite()
{
	return m_pSprite;
}

CWindow * CGUI::GetWindowByString( uistring sString, int iIndex )
{
	for( int i = 0; i < static_cast<int>( m_vWindows.size() ); i++ )
		if( m_vWindows[ i ] )
			if( m_vWindows[ i ]->GetString( false, iIndex ) == sString )
				return m_vWindows[ i ];
	return 0;
}

SElement * CGUI::GetThemeElement( uistring sElement )
{
	return m_mThemes[ m_sCurTheme ][ sElement ];
}

void CGUI::SetVisible( bool bVisible )
{
	EnterCriticalSection(&cs);
	m_bVisible = bVisible;
	LeaveCriticalSection(&cs);
}

bool CGUI::IsVisible()
{
	return m_bVisible;
}

bool CGUI::IsFocus(CWindow * w)
{
	return w == m_wFocus;
}