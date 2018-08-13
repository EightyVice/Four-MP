#pragma once

class CPos
{
	int m_iX, m_iY;

public:

	CPos( CPos * pPos );
	CPos( int iX, int iY );
	CPos();

	~CPos();

	int GetX();
	int GetY();

	void SetX( int iX );
	void SetY( int iY );

	CPos operator + ( CPos otherPos );
	CPos operator - ( CPos otherPos );
};