#include "CVar.h"

CVar::CVar( double dValue )
{
	SetDouble( dValue );
	SetAction( 0 );
	SetString( _UI("") );
}

CVar::CVar( float fValue )
{
	SetFloat( fValue );
	SetAction( 0 );
	SetString( _UI("") );
}

CVar::CVar( int iValue )
{
	SetInteger( iValue );
	SetAction( 0 );
	SetString( _UI("") );
}

CVar::CVar( bool bValue )
{
	SetBoolean( bValue );
	SetAction( 0 );
	SetString( _UI("") );
}

CVar::CVar( uistring sString )
{
	SetString( sString );
	SetAction( 0 );
	SetDouble( 0.0 );
}

CVar::CVar( tAction pAction )
{
	SetAction( pAction );
	SetDouble( 0.0 );
	SetString( _UI("") );
}

void CVar::SetDouble( double dValue )
{
	m_dValue = dValue;
}

void CVar::SetFloat( float fValue )
{
	m_dValue = static_cast<double>( fValue );
}

void CVar::SetInteger( int iValue )
{
	m_dValue = static_cast<double>( iValue );
}

void CVar::SetBoolean( bool bValue )
{
	if( bValue )
		m_dValue = 1.0;
	else
		m_dValue = 0.0;
}

void CVar::SetString( uistring sString )
{
	m_sString = sString;
}

void CVar::SetAction( tAction pAction )
{
	m_pAction = pAction;
}

double CVar::GetDouble()
{
	return m_dValue;
}

float CVar::GetFloat()
{
	return static_cast<float>( m_dValue );
}

int CVar::GetInteger()
{
	return static_cast<int>( m_dValue );
}

bool CVar::GetBoolean()
{
	return ( m_dValue != 0.0 );
}

uistring CVar::GetString()
{
	return m_sString;
}

uistring CVar::GetActionString( const uichar * pszString, CElement * pElement )
{
	/*unistream sStream;

	if( m_pAction )
		sStream << m_pAction( pszString, pElement );
	else if( GetString().length() )
		sStream << GetString();
	else if( GetInteger() )
		sStream << GetInteger();
	else
		sStream << _UI("Cvar invalid.");

	return sStream.str();*/
	if( GetAction() )
		return GetAction()( pszString, pElement );
	return uistring();
}

CVar::tAction CVar::GetAction()
{
	return m_pAction;
}