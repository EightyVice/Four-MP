#pragma once
#include "CNativeThread.h"

class CScriptThread: 
	public CNativeThread
{
private:
	bool m_bKillRequested;
	ptr m_pPrimaryFiber;
	ptr m_pScriptFiber;
	unsigned int m_nWaitTick;

	static void _stdcall FiberStart(void* parameter);

protected:
	ThreadStates Reset(unsigned int hash,int v2,int i3);
	ThreadStates Run(int i1);

	void Wait(unsigned int timeMS);
	
	bool IsThreadAlive();
	void TerminateThisScript();

public:
	CScriptThread();
	~CScriptThread();
	void Kill();
	virtual void GameThread() = 0;
};