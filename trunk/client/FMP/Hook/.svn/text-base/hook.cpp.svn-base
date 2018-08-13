#include "classes.h"
#include "hook.h"
#include "../../../Shared/logging/log.h"

DWORD dwLoadOffset = ((DWORD)GetModuleHandle (NULL)-0x400000);
/* DirectX */
DWORD ADDRESS_CREATE_DEVICE = 0x0;
/* Scripts */
DWORD ADDRESS_HASH_GET = 0x0;
DWORD ADDRESS_THREAD_ID = 0x0;
DWORD ADDRESS_SCRIPTS_COUNT = 0x0;
DWORD SCRIPT_POINTER_1 = 0x0;
DWORD SCRIPT_POINTER_2 = 0x0;
/* Threads */
DWORD ADDRESS_ACTIVE_THREAD = 0x0; 
DWORD ADDRESS_THREADS_ARRAY = 0x0;
DWORD ADDRESS_THREAD_TICK = 0x0;
/* Pools */
DWORD ADDRESS_PED_POOL = 0x0;
DWORD ADDRESS_PLAYER_POOL = 0x0;
DWORD ADDRESS_VEHICLE_POOL = 0x0;
/* Game */
DWORD CGAME_PROCESS_SLEEP = 0x0;
DWORD CGAME_PROCESS_LOAD_MENU = 0x0;
DWORD CGAME_PROCESS_START_GAME = 0x0;
DWORD GAME_NAME = 0x0;
DWORD ADDRESS_GET_SPAWN_POS = 0x0;
DWORD ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE = 0x0;
DWORD ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE = 0x0;
DWORD ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN = 0x0;
DWORD ADDRESS_STR_POPCYCLE_DAT = 0x0;
/* */
DWORD MOUSE_POS_X = 0x0;
DWORD MOUSE_POS_Y = 0x0;


FMPHook::FMPHook(): FMPThread()
{
	m_pPrimaryFiber = NULL;
	m_pScriptFiber = NULL;
	m_bKillRequested = false;
	m_nWaitTick = 0;
	spawnposition.X = -43.250000;
	spawnposition.Y = -2.875000;
	spawnposition.Z = 14.818866;
	spawnposition.W = 0;
	playerstate = PlayerStateOnFoot;
}

FMPHook::~FMPHook()
{
	Log::Debug(L"FMPHook::~FMPHook called");
	Log::Debug(L"FMPHook::~FMPHook complete");
}

ThreadStates FMPHook::Reset(unsigned int hash,int v2,int i3)
{
	Log::Debug(L"FMPHook::reset called");
	if (m_pScriptFiber)
		DeleteFiber(m_pScriptFiber);

	m_pScriptFiber = CreateFiber(0, &FiberStart, this);

	if (!m_pScriptFiber)
	{
		Kill();
		return m_context.eThreadState;
	}
	Log::Debug(L"FMPHook::reset complete");
	return FMPThread::Reset(hash,v2,i3);
}

void FMPHook::FiberStart(void* parameter)
{
	Log::Debug(L"FMPHook::FiberStart called");
	FMPHook* Thread = ptr_cast<FMPHook>(parameter);
	Thread->GameThread();
	Thread->m_bKillRequested = true;
	SwitchToFiber(Thread->m_pPrimaryFiber);
	Log::Debug(L"FMPHook::FiberStart complete");
}

ThreadStates FMPHook::Run(int i1)
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

	scrThread* old = GetActiveThread();
	SetActiveThread(this);

	if(m_context.eThreadState != ThreadStateKilled)
		if(GetTickCount() > m_nWaitTick) SwitchToFiber(m_pScriptFiber);

	if(m_bKillRequested) Kill();

	SetActiveThread(old);
	return m_context.eThreadState;
}

void FMPHook::wait(unsigned int timeMS)
{
	m_nWaitTick = GetTickCount() + timeMS;
	SwitchToFiber(m_pPrimaryFiber);
}

void FMPHook::Kill()
{
	Log::Debug(L"FMPHook::Kill called");
	if (GetCurrentFiber() != m_pPrimaryFiber) 
	{
		Log::Debug(L"FMPHook::Kill exited");
		return;
	}

	DeleteFiber(m_pScriptFiber);

	m_pPrimaryFiber = NULL;
	m_pScriptFiber = NULL;
	m_bKillRequested = false;

	FMPThread::Kill();
	Log::Debug(L"FMPHook::Kill complete");
}

bool FMPHook::IsThreadAlive()
{
	return m_context.eThreadState != ThreadStateKilled;
}

void FMPHook::TerminateThisScript()
{
	Log::Debug(L"FMPHook::TerminateThisScript called");
	if (GetCurrentFiber() != m_pScriptFiber)
		return;

	m_bKillRequested = true;	
	SwitchToFiber(m_pPrimaryFiber);
	Log::Debug(L"FMPHook::TerminateThisScript complete");
}

//-----------------------------------------------------------

void InstallMethodHook(DWORD dwInstallAddress,DWORD dwHookFunction)
{
	DWORD oldProt, oldProt2;
	VirtualProtect((LPVOID)dwInstallAddress,4,PAGE_EXECUTE_READWRITE,&oldProt);
	*(PDWORD)dwInstallAddress = (DWORD)dwHookFunction;
	VirtualProtect((LPVOID)dwInstallAddress,4,oldProt,&oldProt2);
}

//-----------------------------------------------------------

void InstallHook(DWORD dwInstallAddress,DWORD dwHookFunction,DWORD dwHookStorage,BYTE* pbyteJmpCode,int iJmpCodeSize)
{
	DWORD oldProt, oldProt2;

	// Install the pointer to procaddr.
	VirtualProtect((PVOID)dwHookStorage,4,PAGE_EXECUTE_READWRITE,&oldProt);
	*(PDWORD)dwHookStorage = (DWORD)dwHookFunction;
	VirtualProtect((PVOID)dwHookStorage,4,oldProt,&oldProt2);

	// Install the Jmp code.
	VirtualProtect((PVOID)dwInstallAddress,iJmpCodeSize,PAGE_EXECUTE_READWRITE,&oldProt);		
	memcpy((PVOID)dwInstallAddress,pbyteJmpCode,iJmpCodeSize);
	VirtualProtect((PVOID)dwInstallAddress,iJmpCodeSize,oldProt,&oldProt2);	
}

//-----------------------------------------------------------

bool Unlock(void *address, int len)
{
	DWORD oldp;
		// Shut up the warnings :D
	return !!VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &oldp);
}

//-----------------------------------------------------------

void Call(DWORD from, DWORD to)
{
	if (Unlock((LPVOID)from, 5))
	{
		DWORD disp = to - (from + 5);
		*(BYTE *)(from) = 0xE8;
		*(DWORD *)(from + 1) = (DWORD)disp;
	}
}

//-----------------------------------------------------------

void JmpHook(DWORD from, DWORD to) 
{
    DWORD oldp;
    VirtualProtect((LPVOID)from, 5, PAGE_EXECUTE_READWRITE, &oldp);
    BYTE *patch = (BYTE *)from;
    *patch = 0xE9;    // JMP
    *(DWORD *)(patch + 1) = (to - (from + 5));    
}

void CallHook(DWORD from, DWORD to) 
{
    DWORD oldp;
    VirtualProtect((LPVOID)from, 5, PAGE_EXECUTE_READWRITE, &oldp);
    BYTE *patch = (BYTE *)from;
    *patch = 0xFF;    // CALL
    *(DWORD *)(patch + 1) = (to - (from + 5));    
}

void PushHook(DWORD from, DWORD to) 
{
    DWORD oldp;
    VirtualProtect((LPVOID)from, 5, PAGE_EXECUTE_READWRITE, &oldp);
    BYTE *patch = (BYTE *)from;
    *patch = 0x68;    // PUSH
    *(DWORD *)(patch + 1) = (to - (from + 5));    
}

void DataHook(DWORD from, DWORD to) 
{
    DWORD oldp;
    VirtualProtect((LPVOID)from, 5, PAGE_EXECUTE_READWRITE, &oldp);
    BYTE *patch = (BYTE *)from;
    *(DWORD *)(patch + 1) = to;   
}

void ChangeByte(DWORD from, BYTE b, int start)
{
	BYTE *patch = (BYTE *)from;
	*(BYTE*)(patch+start) = b;
}

//-----------------------------------------------------------

void SetString(DWORD address, char* string) 
{
    DWORD oldp;
    VirtualProtect((PVOID)address,2,PAGE_EXECUTE_READWRITE,&oldp);
    strcpy((PCHAR)address,string);
}

void GetAddresses(DWORD version)
{
	switch(version)
	{
	case 0x1070: // Patch 1.0.7.0 (ENG-US)
		{
			ADDRESS_CREATE_DEVICE = 0xD305C4+dwLoadOffset;
			ADDRESS_HASH_GET = 0x5A8290+dwLoadOffset;
			ADDRESS_THREAD_ID = 0x1849ADC+dwLoadOffset;
			ADDRESS_SCRIPTS_COUNT = 0x1849AF8+dwLoadOffset;
			SCRIPT_POINTER_1 = 0x198332C+dwLoadOffset;
			SCRIPT_POINTER_2 = 0x1983328+dwLoadOffset;
			ADDRESS_ACTIVE_THREAD = 0x1849AE0+dwLoadOffset; 
			ADDRESS_THREADS_ARRAY = 0x1983310+dwLoadOffset;
			ADDRESS_THREAD_TICK = 0xBBCDF0+dwLoadOffset;
			CGAME_PROCESS_SLEEP = 0x402B3C+dwLoadOffset;
			CGAME_PROCESS_LOAD_MENU = 0x402BCA+dwLoadOffset;
			CGAME_PROCESS_START_GAME = 0x402C07+dwLoadOffset;
			GAME_NAME = 0xE9E17C+dwLoadOffset;
			MOUSE_POS_X = 0x188AB90+dwLoadOffset;
			MOUSE_POS_Y = 0x188AB9C+dwLoadOffset;
			ADDRESS_GET_SPAWN_POS = 0x8E65B0+dwLoadOffset;
			ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB5DF20+dwLoadOffset;
			ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB5DEC0+dwLoadOffset;
			ADDRESS_STR_POPCYCLE_DAT = 0xD6CDBC+dwLoadOffset;
			ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN = 0xB5DEA0 + dwLoadOffset;
		} break;
	case 0x1061: // Patch 1.0.6.1 (RUS)
		{
			ADDRESS_CREATE_DEVICE = 0xD2FE92+dwLoadOffset;
			ADDRESS_HASH_GET = 0x5A7F10+dwLoadOffset;
			ADDRESS_THREAD_ID = 0x1848B00+dwLoadOffset;
			ADDRESS_SCRIPTS_COUNT = 0x1848B1C+dwLoadOffset;
			SCRIPT_POINTER_1 = 0x198234C+dwLoadOffset;
			SCRIPT_POINTER_2 = 0x1982348+dwLoadOffset;
			ADDRESS_ACTIVE_THREAD = 0x1848B04+dwLoadOffset; 
			ADDRESS_THREADS_ARRAY = 0x1982330+dwLoadOffset;
			ADDRESS_THREAD_TICK = 0xBC0330+dwLoadOffset;
			CGAME_PROCESS_SLEEP = 0x402B5C+dwLoadOffset;
			CGAME_PROCESS_LOAD_MENU = 0x402BEA+dwLoadOffset;
			CGAME_PROCESS_START_GAME = 0x402C27+dwLoadOffset;
			GAME_NAME = 0xE9D18C+dwLoadOffset;
			MOUSE_POS_X = 0x1889BB4+dwLoadOffset;
			MOUSE_POS_Y = 0x1889BC0+dwLoadOffset;
			ADDRESS_GET_SPAWN_POS = 0x8F6410+dwLoadOffset;
			ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB61420+dwLoadOffset;
			ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB613C0+dwLoadOffset;
			ADDRESS_STR_POPCYCLE_DAT = 0xD6BAE4+dwLoadOffset;
			ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN = 0xB613A0 + dwLoadOffset;
		} break;
	case 0x1060: // Patch 1.0.6.0 (ENG-US)
		{
			ADDRESS_CREATE_DEVICE = 0xD301E4+dwLoadOffset;
			ADDRESS_HASH_GET = 0x5A7FC0+dwLoadOffset;
			ADDRESS_THREAD_ID = 0x1848B00+dwLoadOffset;
			ADDRESS_SCRIPTS_COUNT = 0x1848B1C+dwLoadOffset;
			SCRIPT_POINTER_1 = 0x198233C+dwLoadOffset;
			SCRIPT_POINTER_2 = 0x1982338+dwLoadOffset;
			ADDRESS_ACTIVE_THREAD = 0x1848B04+dwLoadOffset; 
			ADDRESS_THREADS_ARRAY = 0x1982320+dwLoadOffset;
			ADDRESS_THREAD_TICK = 0xBBCC40+dwLoadOffset;
			CGAME_PROCESS_SLEEP = 0x402B5C + dwLoadOffset;
			CGAME_PROCESS_LOAD_MENU = 0x402BEA + dwLoadOffset;
			CGAME_PROCESS_START_GAME = 0x402C1D + dwLoadOffset;
			GAME_NAME = 0xE9D13C+dwLoadOffset;
			MOUSE_POS_X = 0x1889BB4+dwLoadOffset;
			MOUSE_POS_Y = 0x1889BC0+dwLoadOffset;
			ADDRESS_GET_SPAWN_POS = 0x8E6840+dwLoadOffset;
			ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB5DD40+dwLoadOffset;
			ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB5DCE0+dwLoadOffset;
			ADDRESS_STR_POPCYCLE_DAT = 0xD6BDD4+dwLoadOffset;
			ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN = 0xB5DCC0 + dwLoadOffset;
		} break;
	case 0x1051: // Patch 1.0.6.0 / 1.0.5.1 (RUS)
		{
			ADDRESS_CREATE_DEVICE = 0xD2FF52+dwLoadOffset;
			ADDRESS_HASH_GET = 0x5A7D10+dwLoadOffset;
			ADDRESS_THREAD_ID = 0x1848B00+dwLoadOffset;
			ADDRESS_SCRIPTS_COUNT = 0x1848B1C+dwLoadOffset;
			SCRIPT_POINTER_1 = 0x198233C+dwLoadOffset;
			SCRIPT_POINTER_2 = 0x1982338+dwLoadOffset;
			ADDRESS_ACTIVE_THREAD = 0x1848B04+dwLoadOffset; 
			ADDRESS_THREADS_ARRAY = 0x1982320+dwLoadOffset;
			ADDRESS_THREAD_TICK = 0xBC0230+dwLoadOffset;
			CGAME_PROCESS_SLEEP = 0x402B5C + dwLoadOffset;
			CGAME_PROCESS_LOAD_MENU = 0x402BEA + dwLoadOffset;
			CGAME_PROCESS_START_GAME = 0x402C1D + dwLoadOffset;
			GAME_NAME = 0xE9D11C+dwLoadOffset;
			MOUSE_POS_X = 0x1889BB4+dwLoadOffset;
			MOUSE_POS_Y = 0x1889BC0+dwLoadOffset;
			ADDRESS_GET_SPAWN_POS = 0x8F6140+dwLoadOffset;
			ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB61360+dwLoadOffset;
			ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE = 0xB61300+dwLoadOffset;
			ADDRESS_STR_POPCYCLE_DAT = 0xD6BADC+dwLoadOffset;
			ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN = 0xB612E0 + dwLoadOffset;
		} break;
	case 0x1050: // Patch 1.0.0.4
		{	
			ADDRESS_CREATE_DEVICE = 0xCE32AC+dwLoadOffset;
			ADDRESS_HASH_GET = 0x6CF530+dwLoadOffset;
			ADDRESS_THREAD_ID = 0x17DF36C+dwLoadOffset;
			ADDRESS_SCRIPTS_COUNT = 0x17DF364+dwLoadOffset;
			SCRIPT_POINTER_1 = 0x18DF6E4+dwLoadOffset;
			SCRIPT_POINTER_2 = 0x18DF6E0+dwLoadOffset;
			ADDRESS_ACTIVE_THREAD = 0x17DF370+dwLoadOffset; 
			ADDRESS_THREADS_ARRAY = 0x18DF6C8+dwLoadOffset;
			ADDRESS_THREAD_TICK = 0xB4E1F0+dwLoadOffset;
			CGAME_PROCESS_SLEEP = 0x526E79 + dwLoadOffset;
			CGAME_PROCESS_START_GAME = 0x526F43 + dwLoadOffset;
			GAME_NAME = 0xDEC28C+dwLoadOffset;
			MOUSE_POS_X = 0x17DE95C+dwLoadOffset;
			MOUSE_POS_Y = 0x17DE968+dwLoadOffset;
			ADDRESS_GET_SPAWN_POS = 0x81E300+dwLoadOffset;
			ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE = 0x9C36D0+dwLoadOffset;
			ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE = 0x9C3670+dwLoadOffset;
			ADDRESS_STR_POPCYCLE_DAT = 0xD3256C+dwLoadOffset;
			ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN = 0xAF49C0 + dwLoadOffset;
		} break;
	}
}