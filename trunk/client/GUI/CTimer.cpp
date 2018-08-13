#include "CGUI.h"

CTimer::CTimer()
{
	dwStop = 0;
}

CTimer::~CTimer()
{
}

void CTimer::Start( float fSec )
{
	dwStop = (DWORD)( fSec * 1000 ) + timeGetTime();
}

void CTimer::Stop()
{
	dwStop = 0;
}

float CTimer::TimeLeft()
{
	if( Running() )
		return ( ( (float)( dwStop - timeGetTime() ) / 1000 ) );
	return 0; 
}

bool CTimer::Running()
{
	return ( dwStop > timeGetTime() );
}