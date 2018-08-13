#pragma once

class CVar;

#include "CGUI.h"

class CVar
{
	double m_dValue;
	uistring m_sString;

	typedef uistring ( __cdecl * tAction )( const uichar * pszArgs, CElement * pElement );
	tAction m_pAction;
public:
	CVar( double dValue );
	CVar( float fValue );
	CVar( int iValue );
	CVar( bool bValue );
	CVar( uistring sString );
	CVar( tAction pAction );

	void SetDouble( double dValue );
	void SetFloat( float fValue );
	void SetInteger( int iValue );
	void SetBoolean( bool bValue );
	void SetString( uistring sString );
	void SetAction( tAction pAction );

	double GetDouble();
	float GetFloat();
	int GetInteger();
	bool GetBoolean();
	uistring GetString();
	uistring GetActionString( const uichar * pszString, CElement * pElement = 0 );
	tAction GetAction();
};

class CCommand
{
public:
};