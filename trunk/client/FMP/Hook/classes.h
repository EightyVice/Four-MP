/*
*	Created:			26.10.09
*	Created by:			009 & VoLT & WNeZRoS
*	Last Modifed:		-
*/
#pragma once
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include "types.h"
#include "../../../Shared/Network/PlayerDefines.h"
#include "../../../Shared/Network/NetworkProtocol.h"
/* ----------------------------------------------------------------------------------------------------- */
/*					             Классы и структуры работы с потоками                                    */
/* ----------------------------------------------------------------------------------------------------- */
template<typename T> struct sysArray {
	T**	pData;
	unsigned short	wCount;	
	unsigned short	wSize;	
};

enum ThreadStates
{
	ThreadStateIdle,
	ThreadStateRunning,
	ThreadStateKilled,
	ThreadState3,
	ThreadState4
};

struct scrThreadContext
{
	DWORD nThreadId;
	DWORD dwScriptHash;
	ThreadStates eThreadState;
	DWORD dwOpcodeOff;
	DWORD field_10;
	DWORD nStackOff;
	DWORD nTimerA;
	DWORD nTimerB;
	DWORD nTimerC;
	float fWaitTime;
	DWORD field_28;
	DWORD field_2C;
	DWORD field_30;
	DWORD field_34;	
	DWORD field_38;
	DWORD field_3C;
	DWORD field_40;
	DWORD field_44;
	DWORD field_48;
	DWORD field_4C;
	DWORD field_50;
};

class scrThread
{
protected:
	scrThreadContext m_context;
	void* m_pScriptStack;
	DWORD field_5C;
	void* m_protectedStorage; // void*	XLiveBuffer; взято с http://www.gtamodding.com/index.php?title=Memory_Addresses_%28GTA4%29 
	DWORD field_64;
	DWORD field_68;
	char* m_pszExitMessage;
public:
	virtual ~scrThread() {}
	virtual ThreadStates Reset(unsigned int hash,int v2,int i3) = 0;
	virtual ThreadStates Run(int i1) = 0;
	virtual ThreadStates Tick(unsigned int msec) = 0;
	virtual void Kill() = 0;
	
	scrThreadContext *RetContext() { return &m_context; }
};

class GtaThread :
	public scrThread
{
protected:
	char m_bProgramName[24];							// From scripthook
	DWORD field_88;	
	DWORD field_8C;
	DWORD m_nSavedDeatharrestStackOff;
	bool field_94;
	bool m_bScriptSafeForNetworkGame;
	bool m_bThisScriptShouldBeSaved;
	bool m_bPlayerControlOnInMissionCleanup;
	bool m_bClearHelpInMissionCleanup;
	bool m_bMinigameScript;
	bool m_bAllowNonMinigameTextMessages;
	bool m_bAllowOneTimeOnlyCommandToRun;
	bool m_bPaused;
	bool m_bCanBePaused;
	bool field_9E;										// ; handle type (_fA0) 0: ped, 1: object, 2: world point
	bool field_9F;
	HANDLE field_A0;									// HANDLE
	bool m_bCanRemoveBlipsCreatedByAnyScript;
	bool field_A5;
	bool field_A6;
	bool field_A7;
	DWORD field_A8;
	DWORD field_AC;
};

class FMPThread: 
	protected GtaThread
{
private:
	GtaThread *m_pOriginalThread;
	int m_nThreadIndex;

protected:
	char ThreadName[24];


	ThreadStates Reset(unsigned int hash,int v2,int i3);
	ThreadStates Run(int i1);
	ThreadStates Tick(unsigned int msec);

public:
	FMPThread();
	~FMPThread();
	void Kill();

	void AttachGtaThread(char*);
};

struct Vector4 { float X, Y, Z, W; };

class FMPHook: 
	public FMPThread
{
private:
	bool m_bKillRequested;
	ptr m_pPrimaryFiber;
	ptr m_pScriptFiber;
	unsigned int m_nWaitTick;

	static void _stdcall FiberStart(void* parameter);
	Camera freeCam;
	Vector4 spawnposition;
	PlayerState playerstate;

	// temps
	short						t_index;
	Vehicle						t_car;
	Camera						t_cam;
	float						t_cam_position[6];
	Vector3						t_vec3;
	unsigned int				t_uint;
	NetworkPlayerFootData		own_foot_sync;
	NetworkPlayerVehicleData	own_veh_sync;

protected:
	ThreadStates Reset(unsigned int hash,int v2,int i3);
	ThreadStates Run(int i1);

	void wait(unsigned int timeMS);
	
	bool IsThreadAlive();
	void TerminateThisScript();

public:
	FMPHook();
	~FMPHook();
	void Kill();
	void GameThread();

	// -- Help func
	Ped _GetPlayerPed();
	Vehicle _GetPedVehicle(Ped p);
	Player _GetPlayer();
	int GetCarDrive(Vehicle car);
	void GetTarget(float ax, float az, float *x, float *y, float *z, float mn = 5);
	void GetCamTargetedCoords(float *x, float *y, float *z);
	void GetMyPos();
	void SetMyPos(float x, float y, float z);
	void KillMe();
	void SetFreeCam(bool);
	bool IsFreeCam();
	Vector4 GetSpawnPosition(void);
	void SetSpawnPosition(const float position[4]);

	void GetTime();
	void SetTimeScale(float ts);

	// -- Safe func
	void CheckAndCheck();
	bool SafeCheckPlayer(short index, float radius = 250, bool bReCreateOnFalse = 1);
	bool SafeCreatePlayer(short index);
	bool SafeCheckVehicle(short index, float radius = 250, bool bReCreateOnFalse = 1);
	bool SafeCreateVehicle(short index);
	bool SafeChangeModel(unsigned int model);
	void SafeCleanVehicles();
	void SafeCleanPlayers();
	void SafeRequestModel(unsigned int model);

	// -- Start mp
	void RunMP();

	// -- Script natives player
	void SetPosition(short index, float pos[3], float angle);
	// -- Scripting natives game
	void SetTime(const unsigned char time[2]);

	// -- Car sync
	void CreateCar(short index, unsigned int model, float position[3], float angle, unsigned char color[2]);

	// -- Other players sync
	void PlayerConnect(wchar_t *name, short index, unsigned int model, float position[3]);

	void PlayerDisconnect(short index);
	void PlayerFootSync(NetworkPlayerFootData* data);
	void PlayerVehicleSync(NetworkPlayerVehicleData* data);
	void PlayerRecieveWeapon(const short index, const eWeapon weapon, const short ammo);
	void PlayerFireAim(short index, int, int, float, float, float, bool);
	void PlayerSwapGun(short index, int);

	void StartEnterInVehicle(const short playerindex, const short vehicleindex, const char seatindex);
	void CancelEnterInVehicle(const short index);
	void FinishEnterInVehicle(const short index);
	void StartExitFromVehicle(const short index);
	void FinishExitFromVehicle(const short index);

	void PlayerSyncSkin(short index, unsigned int);
	void PlayerSyncSkinVariation(short index, int*, int*);

	void xPlayerSpawn(NetworkPlayerSpawnData data);

	void InputFreeze(bool);

	// -- My sync
	void FootSync();
	void VehicleSync(short);
};
