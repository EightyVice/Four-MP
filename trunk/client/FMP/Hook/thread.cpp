#include "classes.h"
#include "hook.h"
#include "../../../Shared/logging/log.h"
// �������� ������ �������...
sysArray<GtaThread>* GetThreadsArray()
{
	return reinterpret_cast< sysArray<GtaThread>* >(ADDRESS_THREADS_ARRAY);
}

// �������� �������� �����...
scrThread* GetActiveThread()
{
	// �� ������ ������ ���� ���������
	return *reinterpret_cast< scrThread** >(ADDRESS_ACTIVE_THREAD);
}

// ������� �������� �����...
void SetActiveThread(scrThread* thread)
{
	*reinterpret_cast< scrThread** >(ADDRESS_ACTIVE_THREAD) = thread;
}

void FMPThread::AttachGtaThread(char *s_name)
{
	Log::Debug(L"FMPThread::AttachGtaThread called");

	while(*(PDWORD)ADDRESS_ACTIVE_THREAD == 0) Sleep(1);

	sysArray<GtaThread>* nowThreads = GetThreadsArray();

	int i;

	for(i = 0;i < nowThreads->wCount;i++)
	{
		// ��������� �� ����� �� ���� ������
		if(nowThreads->pData[i]->RetContext()->nThreadId == 0) break;
	}
	if(i == nowThreads->wCount) 
	{
		return;
	}

	strcpy(ThreadName, s_name);

	m_pOriginalThread = nowThreads->pData[i];
	m_nThreadIndex = i;

	// ������� ��� GtaThread � ���� ����

	nowThreads->pData[i] = this;

	// �������� ��� �������� GtaThread

	unsigned int hash;
	ptr call_this = ptr_cast(ADDRESS_HASH_GET);
	_asm
	{
		mov eax, s_name;
		call call_this;
		mov hash, eax;
	}

	// ������ ������ ���� � GtaThread
	Reset(hash,NULL,0);

	// �������� �� ������..
	m_context.nThreadId = *(PDWORD)ADDRESS_THREAD_ID;
	*(PDWORD)ADDRESS_THREAD_ID = m_context.nThreadId + 1;

	// ������� ���� ��� � ��� ���� ��� 1 ������ 
	*(PDWORD)ADDRESS_SCRIPTS_COUNT++;

	Log::Debug(L"FMPThread::AttachGtaThread complete");
}

ThreadStates FMPThread::Reset(unsigned int hash,int v2,int i3)
{
	Log::Debug(L"FMPThread::reset called");
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

	Log::Debug(L"FMPThread::reset complete");
	return m_context.eThreadState;
}

ThreadStates FMPThread::Run(int i1)
{
	Log::Debug(L"FMPThread::run called");

	scrThread* oldThread = GetActiveThread();
	SetActiveThread(this);

	if(m_context.eThreadState != ThreadStateKilled) 
	{
		
	}

	SetActiveThread(oldThread);
	Log::Debug(L"FMPThread::run complete");
	return m_context.eThreadState;
}

ThreadStates FMPThread::Tick(unsigned int msec)
{
	ptr fn = ptr_cast(ADDRESS_THREAD_TICK);
	scrThread *thread = this;
	_asm
	{
		push msec;
		mov ecx, thread;
		call fn;
	}

	return m_context.eThreadState;
}


FMPThread::FMPThread()
{
	strcpy_s(ThreadName, "FMP");

	memset((void*)(this+4), 0, sizeof(FMPThread)-4);

	m_pOriginalThread = NULL;
	m_nThreadIndex = -1;
}

FMPThread::~FMPThread()
{
	Log::Debug(L"FMPThread::~FMPThread called");
	if(m_pOriginalThread != NULL) Kill();
	Log::Debug(L"FMPThread::~FMPThread complete");
}

void FMPThread::Kill()
{
	Log::Debug(L"FMPThread::Kill called");
	sysArray<GtaThread>* nowThreads = GetThreadsArray();
	nowThreads->pData[m_nThreadIndex] = m_pOriginalThread;

	m_context.eThreadState = ThreadStateKilled;
	m_context.nThreadId = 0;

	m_pOriginalThread = NULL;
	m_nThreadIndex = -1;
	Log::Debug(L"FMPThread::Kill complete");
}