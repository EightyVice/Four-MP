#include "CScriptThread.h"
#include "CGameHook.h"
#include "log/log.h"

extern CGameHook * pGameHook;

CScriptThread::CScriptThread(): CNativeThread()
{
	m_pPrimaryFiber = NULL;
	m_pScriptFiber = NULL;
	m_bKillRequested = false;
	m_nWaitTick = 0;
}

CScriptThread::~CScriptThread()
{
	Log::Debug("CScriptThread::~CScriptThread called");
	Log::Debug("CScriptThread::~CScriptThread complete");
}

ThreadStates CScriptThread::Reset(unsigned int hash,int v2,int i3)
{
	Log::Debug("CScriptThread::reset called");
	if (m_pScriptFiber)
		DeleteFiber(m_pScriptFiber);

	m_pScriptFiber = CreateFiber(0, &FiberStart, this);

	if (!m_pScriptFiber)
	{
		Kill();
		return m_context.eThreadState;
	}
	Log::Debug("CScriptThread::reset complete");
	return CNativeThread::Reset(hash,v2,i3);
}

void CScriptThread::FiberStart(void* parameter)
{
	Log::Debug("CScriptThread::FiberStart called");
	CScriptThread* Thread = ptr_cast<CScriptThread>(parameter);
	Thread->GameThread();
	Thread->m_bKillRequested = true;
	SwitchToFiber(Thread->m_pPrimaryFiber);
	Log::Debug("CScriptThread::FiberStart complete");
}

ThreadStates CScriptThread::Run(int i1)
{
	if(m_pPrimaryFiber == NULL)
	{
		
		if (!IsBadReadPtr(GetCurrentFiber(),sizeof(ptr)))
		{
			m_pPrimaryFiber = GetCurrentFiber();
		}
		else
		{
			m_pPrimaryFiber = ConvertThreadToFiber(NULL);
		}

		m_pScriptFiber = CreateFiber(0,&FiberStart,this);

		if (!m_pScriptFiber)
		{
			Kill();
			return m_context.eThreadState;
		}
	}

	scrThread* old = pGameHook->GetActiveThread();
	pGameHook->SetActiveThread(this);

	if(m_context.eThreadState != ThreadStateKilled)
		if(GetTickCount() > m_nWaitTick) SwitchToFiber(m_pScriptFiber);

	if(m_bKillRequested) Kill();

	pGameHook->SetActiveThread(old);
	return m_context.eThreadState;
}

void CScriptThread::Wait(unsigned int timeMS)
{
	m_nWaitTick = GetTickCount() + timeMS;
	SwitchToFiber(m_pPrimaryFiber);
}

void CScriptThread::Kill()
{
	Log::Debug("CScriptThread::Kill called");
	if (GetCurrentFiber() != m_pPrimaryFiber) 
	{
		Log::Debug("CScriptThread::Kill exited");
		return;
	}

	DeleteFiber(m_pScriptFiber);

	m_pPrimaryFiber = NULL;
	m_pScriptFiber = NULL;
	m_bKillRequested = false;

	CNativeThread::Kill();
	Log::Debug("CScriptThread::Kill complete");
}

bool CScriptThread::IsThreadAlive()
{
	return m_context.eThreadState != ThreadStateKilled;
}

void CScriptThread::TerminateThisScript()
{
	Log::Debug("CScriptThread::TerminateThisScript called");
	if (GetCurrentFiber() != m_pScriptFiber)
		return;

	m_bKillRequested = true;	
	SwitchToFiber(m_pPrimaryFiber);
	Log::Debug("CScriptThread::TerminateThisScript complete");
}
