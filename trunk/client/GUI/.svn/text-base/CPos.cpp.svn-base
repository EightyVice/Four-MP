#include "CGUI.h"

CPos::CPos( CPos * pPos )
{
	m_iX = pPos->GetX();
	m_iY = pPos->GetY();
}

CPos::CPos( int iX, int iY )
{
	m_iX = iX;
	m_iY = iY;
}

CPos::CPos()
{
	m_iX = 0;
	m_iY = 0;
}

CPos::~CPos()
{
}

int CPos::GetX()
{
	return m_iX;
}

int CPos::GetY()
{
	return m_iY;
}

void CPos::SetX( int iX )
{
	m_iX = iX;
}

void CPos::SetY( int iY )
{
	m_iY = iY;
}

CPos CPos::operator + ( CPos otherPos )
{
	return CPos( GetX() + otherPos.GetX(), GetY() + otherPos.GetY() );
}

CPos CPos::operator - ( CPos otherPos )
{
	return CPos( GetX() - otherPos.GetX(), GetY() - otherPos.GetY() );
}