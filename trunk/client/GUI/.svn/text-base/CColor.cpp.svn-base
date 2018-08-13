#include "CGUI.h"

CColor::CColor()
{
}

CColor::CColor( int iRed, int iGreen, int iBlue, int iAlpha )
{
	SetRed( iRed );
	SetGreen( iGreen );
	SetBlue( iBlue );
	SetAlpha( iAlpha );
}

CColor::CColor( D3DCOLOR d3dColor )
{
	SetD3DCOLOR( d3dColor );
}

CColor::CColor( TiXmlElement * pElement )
{
	int iColors[ 4 ] = { 0 };

	pElement->QueryIntAttribute( _UI("r"), &iColors[ 0 ] );
	pElement->QueryIntAttribute( _UI("g"), &iColors[ 1 ] );
	pElement->QueryIntAttribute( _UI("b"), &iColors[ 2 ] );
	pElement->QueryIntAttribute( _UI("a"), &iColors[ 3 ] );

	SetRed( iColors[ 0 ] );
	SetGreen( iColors[ 1 ] );
	SetBlue( iColors[ 2 ] );
	SetAlpha( iColors[ 3 ] );
}

CColor::~CColor()
{
}

CColor CColor::operator / ( int iDivisor )
{
	return CColor( GetRed() / iDivisor, GetGreen() / iDivisor, GetBlue() / iDivisor, GetAlpha() );
}

CColor CColor::operator - ( CColor cSubColor )
{
	return CColor( GetRed() - cSubColor.GetRed(), GetGreen() - cSubColor.GetGreen(), GetBlue() - cSubColor.GetBlue(), GetAlpha() );
}

CColor CColor::operator + ( CColor cAddColor )
{
	return CColor( GetRed() + cAddColor.GetRed(), GetGreen() + cAddColor.GetGreen(), GetBlue() + cAddColor.GetBlue(), GetAlpha() );
}

CColor CColor::operator * ( int iMultiplicator )
{
	return CColor( GetRed() * iMultiplicator, GetGreen() * iMultiplicator, GetBlue() * iMultiplicator, GetAlpha() );
}

void CColor::SetD3DCOLOR( D3DCOLOR d3dColor )
{
	SetAlpha( d3dColor >> 24 );
	SetRed( ( d3dColor >> 16 )&0xFF );
	SetGreen( ( d3dColor >> 8 )&0xFF );
	SetBlue( d3dColor&0xFF ); 
}

void CColor::SetRed( int iRed )
{
	m_iRed = iRed;
}

void CColor::SetGreen( int iGreen )
{
	m_iGreen = iGreen;
}

void CColor::SetBlue( int iBlue )
{
	m_iBlue = iBlue;
}

void CColor::SetAlpha( int iAlpha )
{
	m_iAlpha = iAlpha;
}

D3DCOLOR CColor::GetD3DCOLOR()
{
	return D3DCOLOR_RGBA( GetRed(), GetGreen(), GetBlue(), GetAlpha() );
}

D3DCOLOR CColor::GetD3DXCOLOR()
{
	return D3DCOLOR_ARGB( GetAlpha(), GetRed(), GetGreen(), GetBlue() );
}

int CColor::GetRed()
{
	return m_iRed;
}

int CColor::GetGreen()
{
	return m_iGreen;
}

int CColor::GetBlue()
{
	return m_iBlue;
}

int CColor::GetAlpha()
{
	return m_iAlpha;
}

CColor * SElementState::GetColor( uistring sString )
{
	CColor * pRet = mColors[ sString ];

	if( !pRet )
		pRet = pParent->m_mStates[ pParent->sDefaultState ]->mColors[ sString ];

	if( !pRet )
		MessageBox( 0, _UI("Color not found."), sString.c_str(), 0 );

	return pRet;
}

CTexture * SElementState::GetTexture( uistring sString )
{
	CTexture * pRet = mTextures[ sString ];

	if( !pRet )
		pRet = pParent->m_mStates[ pParent->sDefaultState ]->mTextures[ sString ];

	return pRet;
}

int SElementState::GetInt( uistring sString )
{
	int pRet = mInts[ sString ];

	if(!pRet)
		pRet = pParent->m_mStates[ pParent->sDefaultState ]->mInts [ sString ];

	return pRet;
}
