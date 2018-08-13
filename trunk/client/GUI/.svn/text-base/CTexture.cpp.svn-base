#include "CGUI.h"

CTexture::~CTexture()
{
	SAFE_RELEASE( m_pTexture );
	SAFE_DELETE( m_pColor );
}

CTexture::CTexture( ID3DXSprite * pSprite, const uichar * szPath )
{
	pSprite->GetDevice( &m_pDevice );

	D3DXCreateTextureFromFile( m_pDevice, szPath, &m_pTexture );

	if( !m_pTexture )
	{
		MessageBox( 0, _UI("Can't create texture"), _UI("CTexture::CTexture( ... )"), 0 );
		return;
	}

	m_pColor = new CColor(255,255,255,255);
	m_pTexture->GetLevelDesc( 0, &m_TexDesc );
	m_pSprite = pSprite;

	tPath = new uichar[uislen(szPath)+1];
	uiscpy_s(tPath, uislen(szPath)+1, szPath);
}

CTexture::CTexture( ID3DXSprite * pSprite, const uichar * szPath, CColor *color )
{
	pSprite->GetDevice( &m_pDevice );
	D3DXCreateTextureFromFile( m_pDevice, szPath, &m_pTexture );
	if( !m_pTexture )
	{
		MessageBox( 0, _UI("Can't create texture"), _UI("CTexture::CTexture( ... )"), 0 );
		return;
	}
	m_pColor = color;
	m_pTexture->GetLevelDesc( 0, &m_TexDesc );
	m_pSprite = pSprite;
	tPath = new uichar[uislen(szPath)+1];
	uiscpy_s(tPath, uislen(szPath)+1, szPath);
}

void CTexture::OnLostDevice()
{
	SAFE_RELEASE( m_pTexture );
}

void CTexture::OnResetDevice()
{
	D3DXCreateTextureFromFile( m_pDevice, tPath, &m_pTexture );

	if( !m_pTexture )
	{
		//MessageBox( 0, _UI("Can't create texture"), _UI("CTexture::CTexture( ... )"), 0 );
		return;
	}
	m_pTexture->GetLevelDesc( 0, &m_TexDesc );
}

void CTexture::SetColor(CColor *color)
{
	m_pColor = color;
}

CColor *CTexture::GetColor()
{
	return m_pColor;
}

void CTexture::Draw( CPos cpPos, int iWidth, int iHeight )
{
	//if( !m_pSprite || !m_pTexture ) return;

	D3DXVECTOR2 vTransformation = D3DXVECTOR2( static_cast<float>( cpPos.GetX() ), static_cast<float>( cpPos.GetY() ) );

	D3DXVECTOR2 vScaling( ( 1.0f ), ( 1.0f ) );
	if(iWidth >= 0 && m_TexDesc.Width > 0) vScaling.x = vScaling.x*iWidth/m_TexDesc.Width;
	if(iHeight >= 0 && m_TexDesc.Height > 0) vScaling.y = vScaling.y*iHeight/m_TexDesc.Height;

	D3DXMATRIX mainMatrix;

	D3DXMatrixTransformation2D( &mainMatrix, 0, 0, &vScaling, 0, 0, &vTransformation );

	m_pSprite->SetTransform( &mainMatrix );

	m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
	m_pSprite->Draw( m_pTexture, 0, 0, 0, m_pColor->GetD3DXCOLOR() );
	m_pSprite->End();
}

void CTexture::Draw( int iX, int iY, int iWidth, int iHeight )
{
	//if( !m_pSprite || !m_pTexture ) return;

	D3DXVECTOR2 vTransformation = D3DXVECTOR2( static_cast<float>( iX ), static_cast<float>( iY ) );

	D3DXVECTOR2 vScaling( ( 1.0f ), ( 1.0f ) );
	if(iWidth >= 0 && m_TexDesc.Width > 0) vScaling.x = vScaling.x*iWidth/m_TexDesc.Width;
	if(iHeight >= 0 && m_TexDesc.Height > 0) vScaling.y = vScaling.y*iHeight/m_TexDesc.Height;

	D3DXMATRIX mainMatrix;

	D3DXMatrixTransformation2D( &mainMatrix, 0, 0, &vScaling, 0, 0, &vTransformation );

	m_pSprite->SetTransform( &mainMatrix );

	m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
	m_pSprite->Draw( m_pTexture, 0, 0, 0, m_pColor->GetD3DXCOLOR() );
	m_pSprite->End();
}