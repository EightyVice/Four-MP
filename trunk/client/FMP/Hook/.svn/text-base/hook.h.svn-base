#pragma once
#include "classes.h"
/* ----------------------------------------------------------------------------------------------------- */
/*                                Функции работы с игровыми потоками                                     */
/* ----------------------------------------------------------------------------------------------------- */
//DWORD (__cdecl * HashFromString)(char*) = (DWORD(__cdecl *)(char*))(0x16257C0 + dwLoadOffset);
extern DWORD dwLoadOffset;
/* ----------------------------------------------------------------------------------------------------- */
/*                                            Адреса игры                                                */
/* ----------------------------------------------------------------------------------------------------- */
/* Offsets */
#define OFFSET_PLAYER_ID 0x4CA
#define OFFSET_PLAYER_MAX_HEALTH 0x53A
#define OFFSET_PLAYER_MAX_ARMOR 0x53C
#define OFFSET_PLAYER_COLOR 0x560
#define OFFSET_PLAYER_PED 0x578

/* DirectX */
extern DWORD ADDRESS_CREATE_DEVICE;
/* Scripts */
extern DWORD ADDRESS_HASH_GET;
extern DWORD ADDRESS_THREAD_ID;
extern DWORD ADDRESS_SCRIPTS_COUNT;
extern DWORD SCRIPT_POINTER_1;
extern DWORD SCRIPT_POINTER_2;
/* Threads */
extern DWORD ADDRESS_ACTIVE_THREAD; 
extern DWORD ADDRESS_THREADS_ARRAY;
extern DWORD ADDRESS_THREAD_TICK;
/* Pools */
extern DWORD ADDRESS_PED_POOL;
extern DWORD ADDRESS_PLAYER_POOL;
extern DWORD ADDRESS_VEHICLE_POOL;
/* Game */
extern DWORD CGAME_PROCESS_SLEEP;
extern DWORD CGAME_PROCESS_LOAD_MENU;
extern DWORD CGAME_PROCESS_START_GAME;
extern DWORD GAME_NAME;
extern DWORD ADDRESS_GET_SPAWN_POS;
extern DWORD ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE;
extern DWORD ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE;
extern DWORD ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN;
extern DWORD ADDRESS_STR_POPCYCLE_DAT;
/* */
extern DWORD MOUSE_POS_X;
extern DWORD MOUSE_POS_Y;

sysArray<GtaThread>* GetThreadsArray();
scrThread* GetActiveThread();
void SetActiveThread(scrThread* thread);

void JmpHook(DWORD from, DWORD to);
void CallHook(DWORD from, DWORD to);
void DataHook(DWORD from, DWORD to);
void PushHook(DWORD from, DWORD to);
void ChangeByte(DWORD from, BYTE b, int start = 0);
void SetString(DWORD address, char* string);

void GetAddresses(DWORD version);

void InstallMethodHook(DWORD dwInstallAddress,DWORD dwHookFunction);
void InstallHook(DWORD dwInstallAddress,DWORD dwHookFunction,DWORD dwHookStorage,BYTE* pbyteJmpCode,int iJmpCodeSize);

bool Unlock(void *address, int len);
void Call(DWORD from, DWORD to);

#define POINTER_TO_MEMBER(m,n,o) temp = n, m = *(o *)&temp