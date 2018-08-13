#include <vector>

#include "../../Shared/logging/log.h"
#include "Hook/types.h"
#include "Hook/classes.h"
//#include "Hook\hook.h"
#include "Hook/scripting.h"
#include "functions.h"
#include "../Shared/ClientCore.h"
#include "PlayerManager.h"
#include "VehicleManager.h"
#include "../Shared/NetworkManager.h"

scrThread* GetActiveThread();
void SetActiveThread(scrThread* thread);

extern ClientCore client;
extern FMPHook HOOK;
extern NetworkManager nm;

extern FPlayer gPlayer[MAX_PLAYERS];
extern FVehicle gVehicle[MAX_VEHICLES];

void FMPHook::PlayerConnect(wchar_t *name, short index, unsigned int model, float position[3])
{
	Log::Debug(L"PlayerConnect: Start");
	if(name == 0)
	{
		Log::Error(L"Can't connecting player (Name is bad)");
		return;
	}
	if(index < 0 || index > MAX_PLAYERS)
	{
		Log::Error(L"Can't connecting player (bad index)");
		return;
	}

	Log::Info(L"ConnectInfo: %s %d 0x%x %f %f %f", name, index, model, position[0], position[1], position[2]);
	if(client.GetIndex() == index) // My connect
	{
		Log::Debug(L"Our PlayerConnect");
		wcscpy(gPlayer[index].name, name);
		InputFreeze(0);
		Log::Info(L"Local player %d", Natives::IsThisModelAPed((eModel)model));
		Natives::RequestModel((eModel)model);
		Log::Debug(L"PlayerConnect: RequestModel");
		while(!Natives::HasModelLoaded((eModel)model)) wait(1);
		Log::Debug(L"PlayerConnect: ModelLoaded");
		Natives::ChangePlayerModel(_GetPlayer(), (eModel)model);
		Log::Debug(L"PlayerConnect: ChangeModel");
		Natives::GetPlayerChar(_GetPlayer(), &gPlayer[index].PedID);
		Natives::SetCharCoordinates(gPlayer[index].PedID, position[0], position[1], position[2]);
		Log::Debug(L"PlayerConnect: SetCoords");
		client.SetGameState(GameStateInGame);
		client.SetInputState(InputStateGame);
		SetFreeCam(0);
	}
	else // Other player connect
	{
		Log::Debug(L"Other player connect");
		Natives::RequestModel((eModel)model);
		Log::Debug(L"PlayerConnect: RequestModel");
		while(!Natives::HasModelLoaded((eModel)model)) wait(1);
		Log::Debug(L"PlayerConnect: ModelLoaded");
		Natives::CreateChar(1, (eModel)model, position[0], position[1], position[2], &gPlayer[index].PedID, 1);
		Log::Debug(L"PlayerConnect: CreateChar");
		while(!Natives::DoesCharExist(gPlayer[index].PedID)) wait(1);
		Log::Info(L"MovePlayer %d(%d) = %d", index, Natives::DoesCharExist(gPlayer[index].PedID),gPlayer[index].PedID);
		size_t length = (sizeof(wchar_t) / sizeof(char)) * wcslen(name) + 1;
		char *tempname = (char *)calloc(length, sizeof(char));
		wcstombs(tempname, name, length);
		Natives::GivePedFakeNetworkName(gPlayer[index].PedID, tempname, gPlayer[index].color[1],gPlayer[index].color[2],gPlayer[index].color[3],gPlayer[index].color[0]);
		free(tempname);
		Natives::AddBlipForChar(gPlayer[index].PedID, &gPlayer[index].radarblip);
		Log::Info(L"Player NAME: %s 0x%x%x%x alpha:%x",name, gPlayer[index].color[1],gPlayer[index].color[2],gPlayer[index].color[3],gPlayer[index].color[0]);
		Natives::SetBlockingOfNonTemporaryEvents(gPlayer[index].PedID, 1);
		Natives::SetCharInvincible(gPlayer[index].PedID, 1);
	}

	Log::Debug(L"components");
	Natives::SetCharDefaultComponentVariation( gPlayer[index].PedID );
	Natives::AddArmourToChar(gPlayer[index].PedID, gPlayer[index].armor);
	gPlayer[index].model = model;
	memcpy(gPlayer[index].position, position, sizeof(float) * 3);

	Log::Debug(L"weapons");
	for(int i = 0; i < 8; i++)
	{
		if(gPlayer[index].weapons[i] != 0 && gPlayer[index].ammo[i] > 0)
			Natives::GiveWeaponToChar(gPlayer[index].PedID, (eWeapon)gPlayer[index].weapons[i], gPlayer[index].ammo[i], 0);
	}

	Log::Debug(L"stats");
	wcscpy(gPlayer[index].name, name);
	gPlayer[index].last_active = GetTickCount();
	gPlayer[index].connected = 1;
	Log::Debug(L"PlayerConnect: End");
}

void FMPHook::PlayerFootSync(NetworkPlayerFootData* data)
{
	t_index = data->client;
	
	if(!SafeCheckPlayer(t_index)) 
	{
		Log::Error(L"Unknown player %d", t_index);
		return;
	}

	if(t_index == client.GetIndex())
	{
		Log::Warning(L"wtf? wtf? wtf? wtf? wtf?");
		return;
	}
	else Log::Debug(L"-+-+-+- %d / %d -+-+-+-", t_index, client.GetIndex());

	// read sync
	Natives::SetCharHealth(gPlayer[t_index].PedID,data->health);
	Natives::AddArmourToChar(gPlayer[t_index].PedID,data->armour);
	Natives::GetAmmoInCharWeapon(gPlayer[t_index].PedID,data->weapon,&t_uint);
	if(t_uint != 0) 
	{
		Natives::SetCurrentCharWeapon(gPlayer[t_index].PedID,data->weapon,true);
		Natives::SetAmmoInClip(gPlayer[t_index].PedID,data->weapon,data->ammo);
	}
	else Natives::GiveWeaponToChar(gPlayer[t_index].PedID,data->weapon,data->ammo,false);

	if(data->in_veh)
	{
		if(SafeCheckVehicle(data->veh_id))
			if(!Natives::IsCharInAnyCar(gPlayer[t_index].PedID)) Natives::WarpCharIntoCar(gPlayer[t_index].PedID, gVehicle[data->veh_id].CarID);
		return;
	}
	else
	{
		if(Natives::IsCharInAnyCar(gPlayer[t_index].PedID)) Natives::WarpCharFromCarToCoord(gPlayer[t_index].PedID,data->position[0],data->position[1],data->position[2]);
	}

	// show anim (try...)
	if(data->aim_sync == 2)
	{
		Log::Info(L"[%d foot sync] Char shot from %f,%f,%f to %f,%f,%f",t_index,data->position[0],data->position[1],data->position[2],data->shot_position[0],data->shot_position[1],data->shot_position[2]);
		Natives::TaskShootAtCoord(gPlayer[t_index].PedID,data->shot_position[0],data->shot_position[1],data->shot_position[2],45000, 5);
	}
	else if(data->aim_sync == 1)
	{
		Log::Info(L"[%d foot sync] Char aim from %f,%f,%f to %f,%f,%f",t_index,data->position[0],data->position[1],data->position[2],data->shot_position[0],data->shot_position[1],data->shot_position[2]);
		Natives::TaskAimGunAtCoord(gPlayer[t_index].PedID,data->shot_position[0],data->shot_position[1],data->shot_position[2],45000);
	}
	else 
	{
		// if in vehicle - remove
		if(Natives::IsCharInAnyCar(gPlayer[t_index].PedID)) Natives::WarpCharFromCarToCoord(gPlayer[t_index].PedID,data->position[0],data->position[1],data->position[2]);
		else Natives::SetCharCoordinates(gPlayer[t_index].PedID,data->position[0],data->position[1],data->position[2]);
		Natives::SetCharVelocity(gPlayer[t_index].PedID,data->velocity[0],data->velocity[1],data->velocity[2]);
		Natives::SetCharHeading(gPlayer[t_index].PedID,data->angle);
		
		if((data->is_dunk) && (!Natives::IsCharDucking(gPlayer[t_index].PedID))) Natives::TaskToggleDuck(gPlayer[t_index].PedID,true);
		else if(Natives::IsCharDucking(gPlayer[t_index].PedID)) Natives::TaskToggleDuck(gPlayer[t_index].PedID,false);
		
		if((data->is_jump) && (!Natives::IsCharInAir(gPlayer[t_index].PedID))) Natives::TaskJump(gPlayer[t_index].PedID,true);
		else if(Natives::IsCharInAir(gPlayer[t_index].PedID)) Natives::TaskJump(gPlayer[t_index].PedID,false);
		
		if(data->speed < 3)
		{
			Log::Info(L"[%d foot sync] Char walk from %f,%f,%f to %f,%f,%f",t_index,data->position[0],data->position[1],data->position[2],(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)));
			Natives::TaskGoStraightToCoord(gPlayer[t_index].PedID,(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)),2,45000);   
		}
		else if(data->speed < 5)
		{
			Log::Info(L"[%d foot sync] Char run from %f,%f,%f to %f,%f,%f",t_index,data->position[0],data->position[1],data->position[2],(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)));
			Natives::TaskGoStraightToCoord(gPlayer[t_index].PedID,(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)),3,45000);   
		}
		else
		{
			Log::Info(L"[%d foot sync] Char sprint from %f,%f,%f to %f,%f,%f",t_index,data->position[0],data->position[1],data->position[2],(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)));
			Natives::TaskGoStraightToCoord(gPlayer[t_index].PedID,(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)),4,45000);   
		}
	}
	
	gPlayer[t_index].last_active = GetTickCount();
}

void FMPHook::PlayerVehicleSync(NetworkPlayerVehicleData* data)
{
	t_car = gVehicle[data->v_id].CarID;

	if(!SafeCheckVehicle(data->v_id))
	{
		Log::Warning(L"Vehicle not exist");
		return;
	}

	if(data->v_id == gPlayer[client.GetIndex()].vehicleindex)
	{
		Log::Warning(L"My car");
		return;
	}

	Natives::SetCarCoordinates(t_car, data->position[0],data->position[1],data->position[2]);
	Natives::SetCarHealth(t_car, data->v_health);
	Natives::SetEngineHealth(t_car, data->v_e_health);
	Natives::SwitchCarSiren(t_car, data->siren);
	Natives::SetVehicleQuaternion(t_car, data->qua[0], data->qua[1], data->qua[2], data->qua[3]);

	bool closeall = 1;
	for(char door_id = 0; door_id < 6; door_id++)
	{
		if(data->door_open[door_id] == 1) Natives::ControlCarDoor(t_car, (eVehicleDoor)door_id, 1, data->door_angle[door_id]);
		else Natives::ControlCarDoor(t_car, (eVehicleDoor)door_id, 0, data->door_angle[door_id]);

		if(data->door_open[door_id] != 0) closeall = 0;

		if(data->door_damaged[door_id]) Natives::BreakCarDoor(t_car, (eVehicleDoor)door_id, 0);
	}

	if(closeall) Natives::CloseAllCarDoors(t_car);

	for(char tyre_id = 0; tyre_id < 8; tyre_id++)
		if(data->is_tyre_burst[tyre_id]) Natives::BurstCarTyre(t_car, (eVehicleTyre)tyre_id);

	if(data->is_dead) Natives::ExplodeCar(t_car, 1, 0);

	// show drive (try...)
	if(data->driver >= 0 && data->driver < MAX_PLAYERS && gPlayer[data->driver].connected == 1)
		if(SafeCheckPlayer(data->driver))
			Natives::TaskCarDriveToCoord(gPlayer[data->driver].PedID,t_car,(data->position[0] + (data->velocity[0] * 10 * data->speed)),(data->position[1] + (data->velocity[1] * 10 * data->speed)),(data->position[2] + (data->velocity[2] * 10 * data->speed)),data->speed,1,1,1,1,45000);

	Log::Info(L"[%d vehicle sync] Vehicle drive from %f,%f,%f to %f,%f,%f",t_index,data->position[0],data->position[1],data->position[2],(data->position[0] + (data->velocity[0] * 10)),(data->position[1] + (data->velocity[1] * 10)),(data->position[2] + (data->velocity[2] * 10)));

	gVehicle[data->v_id].angle = data->angle;
	gVehicle[data->v_id].sirenon = data->siren;
	gVehicle[data->v_id].is_dead = data->is_dead;
	gVehicle[data->v_id].health = data->v_health;
	gVehicle[data->v_id].enginehealth = data->v_e_health;
	memcpy(gVehicle[data->v_id].position, data->position, sizeof(float)*3);
	memcpy(gVehicle[data->v_id].velocity, data->velocity, sizeof(float)*3);
	memcpy(gVehicle[data->v_id].qua, data->qua, sizeof(float)*4);
	memcpy(gVehicle[data->v_id].doorexists, data->door_damaged, sizeof(char)*6);
	memcpy(gVehicle[data->v_id].doorangle, data->door_angle, sizeof(char)*6);
	memcpy(gVehicle[data->v_id].is_tyre_burst, data->is_tyre_burst, sizeof(char)*8);
	memcpy(gVehicle[data->v_id].dooropen, data->door_open, sizeof(char)*6);

	gPlayer[t_index].last_active = GetTickCount();
}

void FMPHook::PlayerDisconnect(short index)
{
	if(index == client.GetIndex())
	{
		SafeCleanPlayers();
		SafeCleanVehicles();

		client.SetIndex(-1);

		client.SetGameState(GameStateOffline);
		client.SetInputState(InputStateGui);
		return;
	}

	if(!SafeCheckPlayer(index)) return;

	Log::Info(L"DELETE CHAR %d", index);
	Natives::RemoveBlip(gPlayer[index].radarblip);
	Natives::DeleteChar(&gPlayer[index].PedID);
	gPlayer[index].connected = 0;
}

void FMPHook::StartEnterInVehicle(const short playerindex, const short vehicleindex, const char seatindex)
{
	if(!SafeCheckPlayer(playerindex)) return;
	if(!SafeCheckVehicle(vehicleindex)) return;

	if(seatindex == 0) Natives::TaskEnterCarAsDriver(gPlayer[playerindex].PedID, gVehicle[vehicleindex].CarID, -1);
	else if(seatindex > 0) Natives::TaskEnterCarAsPassenger(gPlayer[playerindex].PedID, gVehicle[vehicleindex].CarID, -1, seatindex - 1);
	gPlayer[playerindex].vehicleindex = vehicleindex;
	gPlayer[playerindex].seatindex = seatindex;
}

void FMPHook::CancelEnterInVehicle(const short index)
{
	if(!SafeCheckPlayer(index)) return;

	Log::Info(L"CancelEnterInVehicle %d", index);
	Natives::ClearCharTasks(gPlayer[index].PedID);
	gPlayer[index].vehicleindex = -1;
}

void FMPHook::FinishEnterInVehicle(const short index)
{
	if(!SafeCheckPlayer(index)) return;

	if(gPlayer[index].seatindex == 0) Natives::WarpCharIntoCar(gPlayer[index].PedID, gVehicle[gPlayer[index].vehicleindex].CarID);
	else if(gPlayer[index].seatindex > 0) Natives::WarpCharIntoCarAsPassenger(gPlayer[index].PedID, gVehicle[gPlayer[index].vehicleindex].CarID, gPlayer[index].seatindex - 1);
}

void FMPHook::StartExitFromVehicle(const short index)
{
	if(!SafeCheckPlayer(index)) return;
	if(!SafeCheckVehicle(gPlayer[index].vehicleindex)) return;

	Log::Info(L"StartExitFromVehicle %d", index);
	Natives::TaskLeaveAnyCar(gPlayer[index].PedID);
}

void FMPHook::FinishExitFromVehicle(const short index)
{
	if(!SafeCheckPlayer(index)) return;

	Log::Info(L"FinishExitFromVehicle %d", index);
	
	Natives::SetCharCoordinates(gPlayer[index].PedID, gPlayer[index].position[0], gPlayer[index].position[1], gPlayer[index].position[2]);
	gPlayer[index].vehicleindex = INVALID_VEHICLE_INDEX;
}

void FMPHook::PlayerRecieveWeapon(const short index, const eWeapon weapon, const short ammo)
{
	Log::Debug(L"Recieving weapon %d %d", weapon, ammo);
	if(!SafeCheckPlayer(index)) return;
	eWeaponSlot slot;
	switch (weapon)
	{
	case WEAPON_UNARMED:
		{
			return;
			break;
		}
	case WEAPON_BASEBALLBAT:
	case WEAPON_KNIFE:
		{
			slot = WEAPON_SLOT_MELEE;
			break;
		}
	case WEAPON_GRENADE:
	case WEAPON_MOLOTOV:
		{
			slot = WEAPON_SLOT_THROWN;
			break;
		}
	case WEAPON_PISTOL:
	case WEAPON_DEAGLE:
		{
			slot = WEAPON_SLOT_HANDGUN;
			break;
		}
	case WEAPON_SHOTGUN:
	case WEAPON_BARETTA:
		{
			slot = WEAPON_SLOT_SHOTGUN;
			break;
		}
	case WEAPON_MICRO_UZI:
	case WEAPON_MP5:
		{
			slot = WEAPON_SLOT_SMG;
			break;
		}
	case WEAPON_AK47:
	case WEAPON_M4:
		{
			slot = WEAPON_SLOT_RIFLE;
			break;
		}
	case WEAPON_SNIPERRIFLE:
	case WEAPON_M40A1:
		{
			slot = WEAPON_SLOT_SNIPER;
			break;
		}
	case WEAPON_RLAUNCHER:
		{
			slot = WEAPON_SLOT_HEAVY;
			break;
		}
	default:
		{
			return;
			break;
		}
	}
	gPlayer[index].weapons[slot] = weapon;
	gPlayer[index].ammo[slot] = ammo;
	Natives::GiveWeaponToChar(gPlayer[index].PedID, weapon, ammo, 0);
	Natives::SetCharAmmo(gPlayer[index].PedID, weapon, ammo);
	Log::Debug(L"Recieved weapon %d %d", weapon, ammo);
}

void FMPHook::PlayerFireAim(short index, int gun, int time, float x, float y, float z, bool fire)
{
	if(!SafeCheckPlayer(index)) return;

	if(fire)
	{
		Natives::SetCurrentCharWeapon(gPlayer[index].PedID, (eWeapon)gun, 1);
		Natives::TaskShootAtCoord(gPlayer[index].PedID, x, y, z, time, 5);
	}
	else
	{
		Natives::SetCurrentCharWeapon(gPlayer[index].PedID, (eWeapon)gun, 1);
		Natives::TaskAimGunAtCoord(gPlayer[index].PedID, x, y, z, time);
	}
}

void FMPHook::PlayerSwapGun(short index, int gun)
{
	if(!SafeCheckPlayer(index)) return;

	Natives::TaskSwapWeapon(gPlayer[index].PedID, (eWeapon)gun);
}

void FMPHook::SetPosition(short index, float pos[3], float angle)
{
	if(!SafeCheckPlayer(index)) return;

	memcpy(gPlayer[index].position, pos, 3 * sizeof(float));
	gPlayer[index].angle = angle;

	Natives::SetCharCoordinates(gPlayer[index].PedID, pos[0], pos[1], pos[2]);
	Natives::SetCharHeading(gPlayer[index].PedID, angle);
}

void FMPHook::PlayerSyncSkin(short index, unsigned int skin)
{
	if(!SafeCheckPlayer(index)) return;

	Log::Info(L"Player Sync Skin START");
	if(index == client.GetIndex())
	{
		SafeChangeModel(skin);
	}
	else
	{
		Natives::DeleteChar(&gPlayer[index].PedID);
		gPlayer[index].model = skin;
		SafeCreatePlayer(index);
	}
	Log::Info(L"Player Sync Skin END");
}

void FMPHook::PlayerSyncSkinVariation(short index, int sm[11], int st[11])
{
	if(!SafeCheckPlayer(index)) return;

	Log::Info(L"Player Sync Skin Variation START");
	for(int i = 0; i < 11; i++)
		Natives::SetCharComponentVariation(gPlayer[index].PedID, (ePedComponent)i, sm[i], st[i]); 
	Log::Info(L"Player Sync Skin Variantion END");
}

void FMPHook::xPlayerSpawn(NetworkPlayerSpawnData data)
{
	Log::Info(L"Spawn %d (%d)", data.client, client.GetIndex());
	/*if(data.client == client.GetIndex()) 
	{
		Log::Info(L"Its me");
		return;
	}*/
	if(!SafeCheckPlayer(data.client)) 
	{
		return;
	}
	Log::Info(L"Player Spawn START");

	Ped old = gPlayer[data.client].PedID;
	
	SafeRequestModel(data.model);
	if(data.client == client.GetIndex()) 
	{
		Natives::ChangePlayerModel(_GetPlayer(), (eModel)data.model);
		wait(100);
		gPlayer[data.client].PedID = _GetPlayerPed();
		Natives::SetCharCoordinates(_GetPlayerPed(), data.position[0], data.position[1], data.position[2]);
	}
	else
		Natives::CreateChar(1, (eModel)data.model, data.position[0], data.position[1], data.position[2], &gPlayer[data.client].PedID, 1);

	while(!Natives::DoesCharExist(gPlayer[data.client].PedID)) wait(0);

	Natives::SetCharDefaultComponentVariation(gPlayer[data.client].PedID);
	PlayerSyncSkinVariation(data.client, data.compD, data.compT);

	Log::Info(L"Set UP");
	Natives::SetCharHeading(gPlayer[data.client].PedID, data.position[3]);
	Natives::SetCharHealth(gPlayer[data.client].PedID, data.health);
	Natives::AddArmourToChar(gPlayer[data.client].PedID, data.armor);
	Natives::SetCharInvincible(gPlayer[data.client].PedID, 1);
	Natives::SetBlockingOfNonTemporaryEvents(gPlayer[data.client].PedID, 1);
	
	if(data.room != 0) Natives::SetRoomForCharByKey(gPlayer[data.client].PedID, (eInteriorRoomKey)data.room);
	Log::Info(L"Player SPAWN END");
	if(Natives::DoesCharExist(old) && data.client != client.GetIndex()) Natives::DeleteChar(&old);
	Log::Info(L"Player Old Delete END");
}