#include "CNativeThread.h"
#include "CGameHook.h"
#include "log/log.h"

extern CGameHook * pGameHook;

void CNativeThread::AttachGtaThread()
{
	Log::Debug("CNativeThread::AttachGtaThread called");

	sysArray<GtaThread>* nowThreads = pGameHook->GetThreadsArray();

	int i;

	for(i = 0;i < nowThreads->wCount;i++)
	{
		if(nowThreads->pData[i]->RetContext()->nThreadId == 0) break;
	}
	if(i == nowThreads->wCount) 
	{
		return;
	}

	m_pOriginalThread = nowThreads->pData[i];
	m_nThreadIndex = i;

	nowThreads->pData[i] = this;

	Reset(pGameHook->GetHash(ThreadName),NULL,0);

	m_context.nThreadId = pGameHook->GetThreadID();
	pGameHook->SetThreadID( m_context.nThreadId + 1 );

	pGameHook->SetScriptCount( pGameHook->GetScriptCount() + 1 );

	Log::Info("Thread %s attached", ThreadName);
	Log::Debug("CNativeThread::AttachGtaThread complete");
}

ThreadStates CNativeThread::Reset(unsigned int hash,int v2,int i3)
{
	Log::Debug("CNativeThread::reset called");
	m_context.dwOpcodeOff = 0;
	m_context.field_10 = 0;
	m_context.nStackOff = 0;
	m_context.nTimerA = 0;
	m_context.nTimerB = 0;
	m_context.nTimerC = 0;
	m_context.field_44 = 0;
	m_context.field_48 = 0;
	m_context.field_4C = 0;
	m_context.field_50 = 0;
	m_context.eThreadState = ThreadStateIdle;
	m_context.dwScriptHash = hash;
	m_pszExitMessage = "Normal exit";
	m_bCanBePaused = true;

	Log::Debug("CNativeThread::reset complete");
	return m_context.eThreadState;
}

ThreadStates CNativeThread::Run(int i1)
{
	Log::Debug("CNativeThread::run called");

	scrThread* oldThread = pGameHook->GetActiveThread();
	pGameHook->SetActiveThread(this);

	if(m_context.eThreadState != ThreadStateKilled) 
	{
		
	}

	pGameHook->SetActiveThread(oldThread);
	Log::Debug("CNativeThread::run complete");
	return m_context.eThreadState;
}

ThreadStates CNativeThread::Tick(unsigned int msec)
{
	pGameHook->ThreadTick(this, msec);
	return m_context.eThreadState;
}


CNativeThread::CNativeThread()
{
	strcpy_s(ThreadName, "SimpleScript");

	memset((void*)(this+4), 0, sizeof(CNativeThread)-4);

	m_pOriginalThread = NULL;
	m_nThreadIndex = -1;
}

CNativeThread::~CNativeThread()
{
	Log::Debug("CNativeThread::~FMPThread called");
	if(m_pOriginalThread != NULL) Kill();
	Log::Debug("CNativeThread::~FMPThread complete");
}

void CNativeThread::Kill()
{
	Log::Debug("CNativeThread::Kill called");
	sysArray<GtaThread>* nowThreads = pGameHook->GetThreadsArray();
	nowThreads->pData[m_nThreadIndex] = m_pOriginalThread;

	m_context.eThreadState = ThreadStateKilled;
	m_context.nThreadId = 0;

	m_pOriginalThread = NULL;
	m_nThreadIndex = -1;
	Log::Debug("CNativeThread::Kill complete");
}

void CNativeThread::SetName(char * name)
{
	strcpy_s(ThreadName, name);
}