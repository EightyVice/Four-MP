/*
*	Created:			26.10.09
*	Created by:			009 & WNeZRoS
*	Last Modifed:		28.10.09
*/
// --------------------------------------------------
// includes
// --------------------------------------------------
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <math.h>
#include <vector>
// our includes

#include "../../Shared/logging/log.h"
#include "../../Shared/logging/logFile.h"
#include "Hook\types.h"
#include "Hook\classes.h"
#include "Hook\hook.h"
#include "Hook\scripting.h"
#include "functions.h"
#include "../Shared/ClientCore.h"
#include "PlayerManager.h"
#include "VehicleManager.h"
#include "../Shared/NetworkManager.h"
#include "masterserver.h"
#include "Check\check.h"
#include "..\..\Shared\Console\ConsoleCore.h"
#include "d3d9/d3d9hook.h"
#include "d3d9/gui.h"
#include "ConsoleWindow.h"
#include "ChatManager.h"

/* ----------------------------------------------------------------------------------------------------- */
/*                                     Потоки для работы с игрой                                         */
/* ----------------------------------------------------------------------------------------------------- */
ClientCore client;
FMPHook HOOK;
HANDLE MainThreadHandle;

ConsoleCore concore;
NetworkManager nm;
LogFile fileLogger(L"FMP/log.txt");

FMPGUI Gui;
ConsoleWindow conwindow;
ChatManager chat;

bool cheats = 0;

FPlayer gPlayer[MAX_PLAYERS];
FVehicle gVehicle[MAX_VEHICLES];

void patchCode();
extern DWORD dwGameVersion;


/* ----------------------------------------------------------------------------------------------------- */
/*                                           F U N C T I O N S                                           */
/* ----------------------------------------------------------------------------------------------------- */

bool FMPHook::IsFreeCam()
{
	return Natives::DoesCamExist(freeCam);
}

void FMPHook::SetFreeCam(bool on)
{
	/*[INFO] Camera: {-646.000000f, -711.000000f, 68.000000f, 0.000000f, 0.000000f, -104.999893f};
	[INFO] Camera: {-182.000000f, 158.000000f, 119.000000f, -17.999989f, -0.000000f, 20.000170f};
	[INFO] Camera: {747.000000f, 221.000000f, 68.000000f, -9.999971f, -0.000000f, 63.000130f};
	[INFO] Camera: {1481.000000f, 439.000000f, 102.000000f, -26.999943f, -0.000000f, 1.000075f};
	[INFO] Camera: {2789.000000f, 483.000000f, 52.000000f, -16.999884f, -1.000004f, 103.000015f};*/

	if(!on) 
	{
		Natives::ActivateScriptedCams(0, 0);
		Natives::DisplayHUD(1);
		Natives::DisplayRadar(1);

		if(!Natives::DoesCamExist(freeCam))
		{
			Log::Error(L"Cam does exist");
			return;
		}
		Natives::SetCamActive(freeCam, 0);
		Natives::SetCamPropagate(freeCam, 0);
		Natives::DestroyCam(freeCam);
	}
	else if(on)
	{
		if(!Natives::DoesCamExist(freeCam))
			Natives::CreateCam(14, &freeCam);

		while(!Natives::DoesCamExist(freeCam)) wait(0);

		unsigned int time = Natives::GetHoursOfDay();

		if(time >= 0 && time < 5)
		{
			Natives::SetCamPos(freeCam, -646, -711, 68);
			Natives::SetCamRot(freeCam, 0, 0, -105);
		}
		else if(time >= 5 && time < 10)
		{
			Natives::SetCamPos(freeCam, -182, 158, 119);
			Natives::SetCamRot(freeCam, -18, 0, 20);
		}
		else if(time >= 10 && time < 15)
		{
			Natives::SetCamPos(freeCam, 747, 221, 68);
			Natives::SetCamRot(freeCam, -10, 0, 63);
		}
		else if(time >= 15 && time < 20)
		{
			Natives::SetCamPos(freeCam, 1481, 439, 102);
			Natives::SetCamRot(freeCam, -27, 0, 1);
		}
		else
		{
			Natives::SetCamPos(freeCam, 2789, 483, 52);
			Natives::SetCamRot(freeCam, -17, -1, 103);
		}

		Natives::SetCamPropagate(freeCam, 1);
		Natives::SetCamActive(freeCam, 1);
		Natives::ActivateScriptedCams(1, 1);
		Natives::DisplayHUD(0);
		Natives::DisplayRadar(0);
	}
}

Vector4 FMPHook::GetSpawnPosition(void)
{
	return spawnposition;
}

void FMPHook::SetSpawnPosition(const float position[4])
{
	spawnposition.X = position[0];
	spawnposition.Y = position[1];
	spawnposition.Z = position[2];
	spawnposition.W = position[3];
}

void FMPHook::CreateCar(short index, unsigned int model, float position[3], float angle, unsigned char color[2])
{
	Log::Info(L"CREATE CAR %d", index);
	Natives::RequestModel((eModel)model);
	while(!Natives::HasModelLoaded((eModel)model)) wait(0);
	Log::Info(L"Model LOADED");
	Natives::CreateCar(model, position[0], position[1], position[2], &gVehicle[index].CarID, 1);
	Natives::SetCarHeading(gVehicle[index].CarID, angle);
	gVehicle[index].exist = 1;
	gVehicle[index].model = model;
	memcpy(gVehicle[index].position, position, sizeof(float) * 3);
	gVehicle[index].angle = angle;
	memcpy(gVehicle[index].color, color, sizeof(unsigned char) * 2);
}

Ped FMPHook::_GetPlayerPed()
{
	Ped Player;
	Natives::GetPlayerChar(Natives::ConvertIntToPlayerIndex(Natives::GetPlayerId()), &Player);
	return Player;
}

Player FMPHook::_GetPlayer()
{
	unsigned int uint = Natives::GetPlayerId();
	Player pl = Natives::ConvertIntToPlayerIndex(uint);
	return pl;
}

Vehicle FMPHook::_GetPedVehicle(Ped p)
{
	Vehicle car;
	Natives::GetCarCharIsUsing(p, &car);
	return car;
}

void FMPHook::InputFreeze(bool e)
{
	Natives::SetPlayerControl(Natives::ConvertIntToPlayerIndex(Natives::GetPlayerId()), !e);
}

bool FMPHook::SafeCreatePlayer(short index)
{
	Log::Info(L"SafeCreatePlayer requested");

	if(gPlayer[index].connected == 0) 
	{
		Log::Warning(L"Haven't player data for create");
		return 0;
	}

	if(client.GetIndex() == index)
	{
		Log::Warning(L"Is a local player");
		return 0;
	}

	if(Natives::DoesCharExist(gPlayer[index].PedID))
	{
		Log::Warning(L"Char already exist");
		return 0;
	}
	
	if(!Natives::IsThisModelAPed((eModel)gPlayer[index].model))
	{
		Log::Warning(L"This model not a ped");
		return 0;
	}

	if(gPlayer[index].name == 0 || wcslen(gPlayer[index].name) == 0)
	{
		Log::Warning(L"Player haven't name");
		return 0;
	}

	Natives::RequestModel((eModel)gPlayer[index].model);
	while(!Natives::HasModelLoaded((eModel)gPlayer[index].model)) wait(0);

	Natives::CreateChar(1, (eModel)gPlayer[index].model, gPlayer[index].position[0], gPlayer[index].position[1], 
		gPlayer[index].position[2], &gPlayer[index].PedID, 1);

	while(!Natives::DoesCharExist(gPlayer[index].PedID)) wait(0);

	size_t length = (sizeof(wchar_t) / sizeof(char)) * wcslen(gPlayer[index].name) + 1;
	char *tempname = (char *)calloc(length, sizeof(char));
	wcstombs(tempname, gPlayer[index].name, length);
	Natives::GivePedFakeNetworkName(gPlayer[index].PedID, tempname, gPlayer[index].color[1],gPlayer[index].color[2],gPlayer[index].color[3],gPlayer[index].color[0]);
	free(tempname);
	Natives::SetBlockingOfNonTemporaryEvents(gPlayer[index].PedID, 1);
	Natives::SetCharInvincible(gPlayer[index].PedID, 1);

	Natives::SetCharHealth( gPlayer[index].PedID, gPlayer[index].health );
	Natives::SetCharDefaultComponentVariation( gPlayer[index].PedID );
	Natives::AddArmourToChar(gPlayer[index].PedID, gPlayer[index].armor);

	if(gPlayer[index].vehicleindex != -1)
	{
		if(gVehicle[gPlayer[index].vehicleindex].exist == 0)
		{
			Log::Warning(L"Player car not register");
			return 0;
		}
		if(!Natives::DoesVehicleExist( gVehicle[gPlayer[index].vehicleindex].CarID ))
		{
			Log::Warning(L"Player car not created");
			return 0;
		}

		if(gPlayer[index].seatindex == -1) Natives::TaskEnterCarAsDriver(gPlayer[index].PedID, gVehicle[gPlayer[index].vehicleindex].CarID, 0);
		else Natives::TaskEnterCarAsPassenger(gPlayer[index].PedID, gVehicle[gPlayer[index].vehicleindex].CarID, 0, gPlayer[index].seatindex);
	}

	for(int i = 0; i < 8; i++)
	{
		if(gPlayer[index].weapons[i] != 0 && gPlayer[index].ammo[i] > 0)
			Natives::GiveWeaponToChar(gPlayer[index].PedID, (eWeapon)gPlayer[index].weapons[i], gPlayer[index].ammo[i], 0);
	}

	return Natives::DoesCharExist( gPlayer[index].PedID );
}

bool FMPHook::SafeCheckPlayer(short index, float radius, bool bReCreateOnFalse)
{
	if(gPlayer[index].connected == 0) 
	{
		Log::Error(L"Player not connected");
		return 0;
	}
	if(!Natives::DoesCharExist(gPlayer[index].PedID))
	{
		if (index == client.GetIndex())
		{
			Log::Warning(L"Outdated player ped data. Updating...");
			Natives::GetPlayerChar(_GetPlayer(), &gPlayer[client.GetIndex()].PedID);
			return 1;
		}
		else
		{
			if(!FloatRange(gPlayer[index].position[0], gPlayer[client.GetIndex()].position[0], radius)) return 0;
			if(!FloatRange(gPlayer[index].position[1], gPlayer[client.GetIndex()].position[1], radius)) return 0;
			if(!FloatRange(gPlayer[index].position[2], gPlayer[client.GetIndex()].position[2], radius)) return 0;

			Log::Error(L"Player doesn't exist");
			if(bReCreateOnFalse) return SafeCreatePlayer(index);
			return 0;
		}
	}

	return 1;
}

bool FMPHook::SafeCreateVehicle(short index)
{
	Log::Info(L"SafeCreateVehicle requested");

	if(gVehicle[index].exist == 0) 
	{
		Log::Warning(L"Haven't vehicle data for create");
		return 0;
	}

	if(Natives::DoesVehicleExist(gVehicle[index].CarID))
	{
		Log::Warning(L"Vehicle already exist");
		return 0;
	}
	
	if(!Natives::IsThisModelAVehicle((eModel)gVehicle[index].model))
	{
		Log::Warning(L"This model not a vehicle");
		return 0;
	}

	Natives::RequestModel((eModel)gVehicle[index].model);
	while(!Natives::HasModelLoaded((eModel)gVehicle[index].model)) wait(0);

	Natives::CreateCar(gVehicle[index].model, gVehicle[index].position[0], gVehicle[index].position[1], gVehicle[index].position[2], &gVehicle[index].CarID, 1);

	while(!Natives::DoesVehicleExist(gVehicle[index].CarID)) wait(0);

	Natives::SetCarHeading(gVehicle[index].CarID, gVehicle[index].angle);
	Natives::SetCarHealth(gVehicle[index].CarID, gVehicle[index].health);
	Natives::SetEngineHealth(gVehicle[index].CarID, gVehicle[index].enginehealth);
	Natives::SetExtraCarColours(gVehicle[index].CarID, gVehicle[index].color[2], gVehicle[index].color[3]);
	Natives::ChangeCarColour(gVehicle[index].CarID, gVehicle[index].color[0], gVehicle[index].color[1]);

	for(int i = 0; i < 6; i++)
		if(gVehicle[index].doorexists[i] == 0)
			Natives::BreakCarDoor(gVehicle[index].CarID, (eVehicleDoor)i, 0);

	for(int i = 0; i < 6; i++)
		Natives::ControlCarDoor(gVehicle[index].CarID, (eVehicleDoor)i, gVehicle[index].doorlock[i], gVehicle[index].doorangle[i]);

	for(int i = 0; i < 5; i++)
		if(gVehicle[index].doorlock[i])
			Natives::LockCarDoors(gVehicle[index].CarID, (eVehicleDoorLock)i);

	return Natives::DoesVehicleExist( gVehicle[index].CarID );
}

bool FMPHook::SafeCheckVehicle(short index, float radius, bool bReCreateOnFalse)
{
	if(gVehicle[index].exist == 0) 
	{
		Log::Warning(L"Vehicle not created");
		return 0;
	}
	if(!Natives::DoesVehicleExist(gVehicle[index].CarID))
	{
		if(!FloatRange(gVehicle[index].position[0], gPlayer[client.GetIndex()].position[0], radius)) return 0;
		if(!FloatRange(gVehicle[index].position[1], gPlayer[client.GetIndex()].position[1], radius)) return 0;
		if(!FloatRange(gVehicle[index].position[2], gPlayer[client.GetIndex()].position[2], radius)) return 0;

		Log::Warning(L"Vehicle doesn't exist");
		if(bReCreateOnFalse) return SafeCreateVehicle(index);
		return 0;
	}

	return 1;
}

bool FMPHook::SafeChangeModel(unsigned int model)
{
	Natives::RequestModel((eModel)model);
	while(!Natives::HasModelLoaded((eModel)model)) wait(0);
	Natives::ChangePlayerModel(_GetPlayer(), (eModel)model);

	return 1;
}

void FMPHook::SafeCleanPlayers()
{
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(!gPlayer[i].connected) continue;
		if(i == client.GetIndex()) continue;

		if(Natives::DoesCharExist(gPlayer[i].PedID))
			Natives::DeleteChar(&gPlayer[i].PedID);
	}

	memset(gPlayer, 0, sizeof(FPlayer) * MAX_PLAYERS);
}

void FMPHook::SafeCleanVehicles()
{
	for(int i = 0; i < MAX_VEHICLES; i++)
	{
		if(!gVehicle[i].exist) continue;
		if(Natives::DoesVehicleExist(gVehicle[i].CarID))
			Natives::DeleteCar(&gVehicle[i].CarID);
	}

	memset(gVehicle, 0, sizeof(FVehicle) * MAX_VEHICLES);
}

void FMPHook::SafeRequestModel(unsigned int model)
{
	Natives::RequestModel((eModel)model);
	while(!Natives::HasModelLoaded((eModel)model)) wait(0);
}

void FMPHook::CheckAndCheck()
{
	for(short i = 0; i < MAX_VEHICLES; i++)
		if(gVehicle[i].exist)
			if(!Natives::DoesVehicleExist( gVehicle[i].CarID ))
			{
				Log::Warning(L"Check: Car not exist");
				SafeCreateVehicle(i);
			}

	for(short i = 0; i < MAX_PLAYERS; i++)
		if(gPlayer[i].connected)
			if(!Natives::DoesCharExist( gPlayer[i].PedID ))
			{
				Log::Warning(L"Check: Char not exist");
				SafeCreatePlayer(i);
			}
}

void FMPHook::RunMP()
{
	Log::Info(L"Starting up multiplayer mode.");

	Natives::AllowThisScriptToBePaused(0);
	Natives::ThisScriptShouldBeSaved();

	Natives::SetPedNonCreationArea(-3000, -3000, -3000, 3000, 3000, 3000);

	Natives::AllowEmergencyServices(0);
	//Natives::SetPedDensityMultiplier(0);
	//Natives::SetCarDensityMultiplier(0);
	Natives::DisableCarGenerators(1);
	//DisableCarGeneratorsWithHeli(1);
	Natives::SetNoResprays(1);
	Natives::SwitchAmbientPlanes(0);
	Natives::SwitchArrowAboveBlippedPickups(0);
	Natives::SwitchRandomBoats(0);
	Natives::SwitchRandomTrains(0);
	Natives::SwitchGarbageTrucks(0);

	Natives::SetSleepModeActive(1);
	
	Natives::SetIntStat(STAT_ISLANDS_UNLOCKED, 100);
	Natives::SetIntStat(STAT_ACTIVITIES_WITH_BRUCIE, 0);
	Natives::SetIntStat(STAT_ACTIVITIES_WITH_ROMAN, 0);
	Natives::SetIntStat(STAT_MISSIONS_ATTEMPTED, 0);
	Natives::SetIntStat(STAT_MISSIONS_FAILED, 0);
	Natives::SetIntStat(STAT_MISSIONS_PASSED, 0);

	Natives::SetIntStat(STAT_STUNT_JUMPS_COMPLETED, 50);
	Natives::SetIntStat(STAT_ACTIVITIES_WITH_JACOB, 0);
	Natives::SetIntStat(STAT_ACTIVITIES_WITH_DWAYNE, 0);
	Natives::SetIntStat(STAT_ACTIVITIES_WITH_PACKIE, 0);
	Natives::SetIntStat(STAT_PIGEONS_EXTERMINATED, 200);
	Natives::SetIntStat(STAT_PROGRESS_WITH_DENISE, 0);
	Natives::SetIntStat(STAT_PROGRESS_WITH_MICHELLE, 0);
	Natives::SetIntStat(STAT_PROGRESS_WITH_HELENA, 0);
	Natives::SetIntStat(STAT_PROGRESS_WITH_BARBARA, 0);
	Natives::SetIntStat(STAT_PROGRESS_WITH_KATIE, 0);
	Natives::SetIntStat(STAT_PROGRESS_WITH_MILLIE, 0);
	
	Natives::SetFloatStat(STAT_TOTAL_PROGRESS, 100);
	Natives::SetFloatStat(STAT_ROMAN_LIKE, 100);
	Natives::SetFloatStat(STAT_ROMAN_RESPECT, 100);
	Natives::SetFloatStat(STAT_ROMAN_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_JACOB_LIKE, 100);
	Natives::SetFloatStat(STAT_JACOB_RESPECT, 100);
	Natives::SetFloatStat(STAT_JACOB_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_FAUSTIN_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_MANNY_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_ELIZABETA_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_DWAYNE_LIKE, 100);
	Natives::SetFloatStat(STAT_DWAYNE_RESPECT, 100);
	Natives::SetFloatStat(STAT_DWAYNE_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_BRUCIE_LIKE, 100);
	Natives::SetFloatStat(STAT_BRUCIE_RESPECT, 100);
	Natives::SetFloatStat(STAT_BRUCIE_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_PLAYBOY_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_ULPC_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_PACKIE_LIKE, 100);
	Natives::SetFloatStat(STAT_PACKIE_RESPECT, 100);
	Natives::SetFloatStat(STAT_PACKIE_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_RAY_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_GERRY_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_BERNIE_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_BELL_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_GAMBETTI_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_JIMMY_MISSION_PROGRESS, 100);
	Natives::SetFloatStat(STAT_CARMEN_ORTIZ_FONDNESS, 100);
	Natives::SetFloatStat(STAT_CARMEN_TRUST, 100);
	Natives::SetFloatStat(STAT_ALEX_CHILTON_FONDNESS, 100);
	Natives::SetFloatStat(STAT_ALEX_TRUST, 100);
	Natives::SetFloatStat(STAT_KIKI_JENKINS_FONDNESS, 100);
	Natives::SetFloatStat(STAT_KIKI_TRUST, 100);
	Natives::SetFloatStat(STAT_MICHELLE_FONDNESS, 100);
	Natives::SetFloatStat(STAT_MICHELLE_TRUST, 100);
	Natives::SetFloatStat(STAT_KATE_FONDNESS, 100);
	Natives::SetFloatStat(STAT_KATE_TRUST, 100);
	Natives::SetFloatStat(STAT_GAME_PROGRESS, 100);
	
	Natives::TerminateAllScriptsWithThisName("startup");
	Natives::TerminateAllScriptsWithThisName("initial");
	Natives::TerminateAllScriptsWithThisName("main");
	Natives::TerminateAllScriptsWithThisName("carwash");
	Natives::TerminateAllScriptsWithThisName("stunt");
	Natives::TerminateAllScriptsWithThisName("spcellphone");
	Natives::TerminateAllScriptsWithThisName("spcellphonemain");
	Natives::TerminateAllScriptsWithThisName("computermain");
	Natives::TerminateAllScriptsWithThisName("copbootsearch");
	Natives::TerminateAllScriptsWithThisName("emergencycall");

	Natives::TerminateAllScriptsWithThisName("taxi_trigger");
	Natives::TerminateAllScriptsWithThisName("internet_dating");
	Natives::TerminateAllScriptsWithThisName("speechControl");
	Natives::TerminateAllScriptsWithThisName("statTracker");
	Natives::TerminateAllScriptsWithThisName("happyTShirt");
	Natives::TerminateAllScriptsWithThisName("storyTimer");
	Natives::TerminateAllScriptsWithThisName("mpTutorialLauncher");
	Natives::TerminateAllScriptsWithThisName("sixAxisTutLauncher"); 

	/*Natives::TerminateAllScriptsWithThisName("empiredown");
	Natives::TerminateAllScriptsWithThisName("foodserver");
	Natives::TerminateAllScriptsWithThisName("garbage_trucks");
	Natives::TerminateAllScriptsWithThisName("vendor");
	Natives::TerminateAllScriptsWithThisName("nutvendor");
	Natives::TerminateAllScriptsWithThisName("ambairpotarea");
	Natives::TerminateAllScriptsWithThisName("ambatmq");
	Natives::TerminateAllScriptsWithThisName("ambbar");
	Natives::TerminateAllScriptsWithThisName("ambbarrier");
	Natives::TerminateAllScriptsWithThisName("ambbeggar");
	Natives::TerminateAllScriptsWithThisName("ambblkhawk");
	Natives::TerminateAllScriptsWithThisName("ambbouncer");
	Natives::TerminateAllScriptsWithThisName("ambbridgepatrol");
	Natives::TerminateAllScriptsWithThisName("ambbusker");
	Natives::TerminateAllScriptsWithThisName("ambcabaret");
	Natives::TerminateAllScriptsWithThisName("ambcargoholddoors");
	Natives::TerminateAllScriptsWithThisName("ambchurchdoors");
	Natives::TerminateAllScriptsWithThisName("ambclublights");
	Natives::TerminateAllScriptsWithThisName("ambcomedyclub");
	Natives::TerminateAllScriptsWithThisName("ambcontrolloader");
	Natives::TerminateAllScriptsWithThisName("ambcontrolmain");
	Natives::TerminateAllScriptsWithThisName("ambdealer");
	Natives::TerminateAllScriptsWithThisName("ambfloater");
	Natives::TerminateAllScriptsWithThisName("ambgerry3doorlock");
	Natives::TerminateAllScriptsWithThisName("ambhelicopter");
	Natives::TerminateAllScriptsWithThisName("ambhomelandcordon");
	Natives::TerminateAllScriptsWithThisName("ambhomelandfed");
	Natives::TerminateAllScriptsWithThisName("ambhomelandsirens");
	Natives::TerminateAllScriptsWithThisName("ambhotel");
	Natives::TerminateAllScriptsWithThisName("ambinternetcafe");
	Natives::TerminateAllScriptsWithThisName("ambjerseydocksgates");
	Natives::TerminateAllScriptsWithThisName("ambjimslocks");
	Natives::TerminateAllScriptsWithThisName("ambliftdoors");
	Natives::TerminateAllScriptsWithThisName("ambnightclubext");
	Natives::TerminateAllScriptsWithThisName("ambpimpnpros");
	Natives::TerminateAllScriptsWithThisName("ambpoledancer");
	Natives::TerminateAllScriptsWithThisName("ambpolrdblk");
	Natives::TerminateAllScriptsWithThisName("ambpreacher");
	Natives::TerminateAllScriptsWithThisName("ambsavebed");
	Natives::TerminateAllScriptsWithThisName("ambshowroom");
	Natives::TerminateAllScriptsWithThisName("ambstripclub");
	Natives::TerminateAllScriptsWithThisName("ambtaxdpt");
	Natives::TerminateAllScriptsWithThisName("ambtaxihail");
	Natives::TerminateAllScriptsWithThisName("ambtoiletdoors");
	Natives::TerminateAllScriptsWithThisName("ambtunnelcops");
	Natives::TerminateAllScriptsWithThisName("ambtv");
	Natives::TerminateAllScriptsWithThisName("ambunarea");
	Natives::TerminateAllScriptsWithThisName("ambwardrobe");
	Natives::TerminateAllScriptsWithThisName("ambwindowlift");*/
	
	
	Natives::ClearAreaOfChars(0,0,0, 2000);
	//ClearAreaOfCops(0,0,0, 2000);

	Ped Player;
	Natives::GetPlayerChar(Natives::ConvertIntToPlayerIndex(Natives::GetPlayerId()), &Player);
	Natives::RemoveAllCharWeapons(Player);
	Natives::AddArmourToChar(Player, -1000);
	Natives::SetCharMoney(Player, 0);
	Natives::SetTimeOfDay(0,0);
	Natives::ForceWeatherNow((eWeather)1);
	Natives::SetMaxWantedLevel(0);

	unsigned int score = 0;
	Natives::StoreScore( _GetPlayer(), &score );
	Natives::AddScore( _GetPlayer(), -score );

	Log::Info(L"Multiplayer mode started.");
}

void FMPHook::GameThread()
{
	Log::Debug(L"GameThread");
	client.Load();
	InputFreeze(1);

	RunMP();
	SetFreeCam(1);

	while(IsThreadAlive() && client.IsRunning())
	{
		client.Tick();
		GameState state = client.GetGameState();
		switch (state)
		{
		case GameStateOffline:
			{
				SetFreeCam(1);
				if(GetAsyncKeyState(112) != 0)
				{
					Log::Debug(L"Player: 0x%x %d", _GetPlayer(), Natives::PlayerHasChar(_GetPlayer()));
					Log::Debug(L"%d %d %d %d %d", Natives::IsScreenFadedIn(), Natives::IsScreenFadedOut(), Natives::IsScreenFading(),
						Natives::IsScreenFadingIn(), Natives::IsScreenFadingOut());
				}
				break;
			}
		case GameStateConnecting:
			{
				break;
			}
		case GameStateInGame:
			{

				//if(GetTickCount() - LastUpdate > 60*1000)
				//{
				//	// Disconnect: Not info from server
				//	Natives::PrintStringWithLiteralStringNow("STRING", "SERVER NOT SEND INFO TO YOU", 5000, 1);
				//}

				CheckAndCheck();
				
				for(int i = 0; i < MAX_VEHICLES; i++) if(gVehicle[i].exist) VehicleSync(i);
				FootSync();
				
				gPlayer[client.GetIndex()].last_active = GetTickCount();
				break;
			}
		}
		wait(100);
	}
	client.Unload();
	Log::Debug(L"Exit GameThread");
}

void FMPHook::SetTime(const unsigned char time[2])
{
	Natives::SetTimeOfDay(time[0], time[1]);
}

void FMPHook::GetMyPos()
{
	float x, y, z;
	Natives::GetCharCoordinates(_GetPlayerPed(), &x, &y, &z);
	Log::Info(L"MY POS (%f; %f; %f)", x, y, z);
}

void FMPHook::SetMyPos(float x, float y, float z)
{
	Natives::SetCharCoordinates(_GetPlayerPed(), x, y, z);
}

void FMPHook::KillMe()
{
	Natives::SetCharHealth(_GetPlayerPed(), 0);
}

void FMPHook::GetTime()
{
	unsigned int h = 0, m = 0;
	Natives::GetTimeOfDay(&h, &m);
	Log::Info(L"TIME: %d:%d = %d", h, m, GetTickCount());
}

void FMPHook::SetTimeScale(float ts)
{
	Natives::SetTimeScale(ts);
}

void GetMyPos(ConsoleCore *concore, const unsigned char numargs)
{
	HOOK.GetMyPos();
}

void SetMyPos(ConsoleCore *concore, const unsigned char numargs)
{
	if(numargs < 3) return;

	float x, y, z;
	wchar_t *tmp;
	concore->GetCmdArg(1, tmp);
	x = _wtof(tmp);
	free(tmp);
	concore->GetCmdArg(2, tmp);
	y = _wtof(tmp);
	free(tmp);
	concore->GetCmdArg(3, tmp);
	z = _wtof(tmp);
	free(tmp);
	HOOK.SetMyPos(x, y, z);
}

void KillMe(ConsoleCore *concore, const unsigned char numargs)
{
	HOOK.KillMe();
}

void GetTime(ConsoleCore *concore, const unsigned char numargs)
{
	HOOK.GetTime();
}

void SetTS(ConsoleCore *concore, const unsigned char numargs)
{
	wchar_t *tmp;
	concore->GetCmdArg(1, tmp);

	HOOK.SetTimeScale(_wtof(tmp));
	free(tmp);
}

void MainThread(void* dummy)
{
	Log::Debug(L"MainThread (0x%x)", dwLoadOffset);

	concore.AddConCmd(L"getmypos", GetMyPos);
	concore.AddConCmd(L"getpos", GetMyPos);
	concore.AddConCmd(L"teleport", SetMyPos);
	concore.AddConCmd(L"kill", KillMe);
	concore.AddConCmd(L"time", GetTime);
	concore.AddConCmd(L"ts", SetTS);

	memset(&gPlayer, 0, sizeof(FPlayer) * MAX_PLAYERS);
	memset(&gVehicle, 0, sizeof(FVehicle) * MAX_VEHICLES);

	Sleep(10000);
	HOOK.AttachGtaThread("FOURMP");
	Log::Debug(L"Attached");

	CloseHandle(MainThreadHandle);
	MainThreadHandle = NULL;
}

/*void ALLOCATE_SCRIPT_TO_OBJECT(char *script, int model, int unk1, float unk2, int unk3)
{
	Log::Debug(L"ALLOCATE_SCRIPT_TO_OBJECT");
	Log::Debug(L"('%s', 0x%x, %d, %f, %d)", script, model, unk1, unk2, unk3);
}

void ALLOCATE_SCRIPT_TO_RANDOM_PED(char *script, int model, int unk1, int unk2)
{
	Log::Debug(L"ALLOCATE_SCRIPT_TO_RANDOM_PED");
	Log::Debug(L"('%s', 0x%x, %d, %d)", script, model, unk1, unk2);
}*/

int sub_A002B0(void * th, char *script, int a3, int a4, int a5, int a6, int a7, int a8)
{
	Log::Debug(L"> sub_A002B0 (%s)", script);
	return 1;
}

int sub_A00350(char *script, int a2, int a3)
{
	Log::Debug(L"> sub_A00350 (%s)", script);
	return 1;
}

bool IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE()
{
	Log::Debug(L"> IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE");
	return 0;
}

bool IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(int a1)
{
	Log::Debug(L"> IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE");
	Log::Debug(L">>> (%d)", a1);
	return 0;
}

void REGISTER_WORLD_POINT_SCRIPT_BRAIN(char *script, float unk1)
{
	Log::Debug(L"REGISTER_WORLD_POINT_SCRIPT_BRAIN");
	Log::Debug(L"%s with %f", script, unk1);
}

Vector4 GetSpawnPos(Vector4 *pos, float angle, Vector4 *result) //8E6840
{
	memcpy(pos, &HOOK.GetSpawnPosition(), sizeof(Vector4));
	return *pos; //return *result;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) 
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hModule);

		Log::SetState( LOG_INFO|LOG_ERROR|LOG_WARNING|LOG_DEBUG );
		Log::AddLogger( &fileLogger );
		Log::AddLogger( &conwindow );

		concore.RegisterStandardLibrary();

		patchCode();
		GetAddresses(dwGameVersion);

		if(dwGameVersion >= 0x1050 && dwGameVersion <= 0x1070)
		{
			Log::Info(L"Skipping main menu");
			JmpHook(CGAME_PROCESS_SLEEP, CGAME_PROCESS_START_GAME);

			/*JmpHook(0xB5DC50+dwLoadOffset, (DWORD)ALLOCATE_SCRIPT_TO_OBJECT);
			JmpHook(0xB5DC00+dwLoadOffset, (DWORD)ALLOCATE_SCRIPT_TO_RANDOM_PED);
			JmpHook(0xB5DCC0+dwLoadOffset, (DWORD)REGISTER_WORLD_POINT_SCRIPT_BRAIN);*/

			JmpHook(ADDRESS_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE, (DWORD)IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE);
			JmpHook(ADDRESS_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE, (DWORD)IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE);
			JmpHook(ADDRESS_REGISTER_WORLD_POINT_SCRIPT_BRAIN, (DWORD)REGISTER_WORLD_POINT_SCRIPT_BRAIN);
			JmpHook(ADDRESS_GET_SPAWN_POS, (DWORD)GetSpawnPos);
			SetString(GAME_NAME,"GTA IV: FOUR-MP");
			SetString(ADDRESS_STR_POPCYCLE_DAT, "FMP/popcycle.dat");

			Log::Debug(L"Set DX9 Hook");
			DetourFunc((BYTE*)ADDRESS_CREATE_DEVICE,(BYTE*)hkDirect3DCreate9, 5);

			Log::Debug(L"Set script hook");
			DWORD threadId = 0; 
			MainThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&MainThread, 0, 0, (LPDWORD)&threadId);
		}
		else
			Log::Info(L"This version not supported (%x)", dwGameVersion);
	}
	else if(ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		client.Shutdown();

		if(MainThreadHandle != NULL)
		{
			TerminateThread(MainThreadHandle, 1);
			CloseHandle(MainThreadHandle);
		}
		Log::Debug(L"EXIT FMP");
	}
	return TRUE;
}