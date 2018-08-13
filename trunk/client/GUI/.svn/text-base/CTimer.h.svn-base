#pragma once

#pragma comment (lib, "winmm.lib")
#include <windows.h>

class CTimer
{
public:

	CTimer();
	~CTimer();

	void Start( float fSec );
	void Stop();

	float TimeLeft();
	bool Running();

protected:
	DWORD dwStop;
};