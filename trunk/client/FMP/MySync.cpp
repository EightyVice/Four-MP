/****************************************************************
Syncronizashion this player
(c) WNeZRoS 2009
*****************************************************************/

#include <math.h>

#include "../../Shared/logging/log.h"
#include "../Shared/ClientCore.h"
#include "Hook\classes.h"
#include "Hook\scripting.h"
#include "functions.h"

#include "PlayerManager.h"
#include "VehicleManager.h"
#include "../Shared/NetworkManager.h"

extern ClientCore client;
extern NetworkManager nm;

extern FPlayer gPlayer[MAX_PLAYERS];
extern FVehicle gVehicle[MAX_VEHICLES];

void FMPHook::FootSync()
{
	if(client.GetIndex() < 0 || !Natives::DoesCharExist(gPlayer[client.GetIndex()].PedID)) 
	{
		Natives::GetPlayerChar(_GetPlayer(), &gPlayer[client.GetIndex()].PedID);
		return;
	}
	// write info in our temp sync struct
	Natives::GetCharCoordinates(gPlayer[client.GetIndex()].PedID, &own_foot_sync.position[0],&own_foot_sync.position[1],&own_foot_sync.position[2]);
	own_foot_sync.position[2] -= 1.0; // z correction
	Natives::GetCharVelocity(gPlayer[client.GetIndex()].PedID, &own_foot_sync.velocity[0],&own_foot_sync.velocity[1],&own_foot_sync.velocity[2]);
	Natives::GetCharHeading(gPlayer[client.GetIndex()].PedID, &own_foot_sync.angle);
	Natives::GetCharHealth(gPlayer[client.GetIndex()].PedID, &own_foot_sync.health);
	Natives::GetCharArmour(gPlayer[client.GetIndex()].PedID, &own_foot_sync.armour);
	Natives::GetCharSpeed(gPlayer[client.GetIndex()].PedID, &own_foot_sync.speed);
	Natives::GetCurrentCharWeapon(gPlayer[client.GetIndex()].PedID, &own_foot_sync.weapon);
	if(own_foot_sync.weapon != WEAPON_UNARMED) Natives::GetAmmoInCharWeapon(gPlayer[client.GetIndex()].PedID, own_foot_sync.weapon, &own_foot_sync.ammo);
	else own_foot_sync.ammo = 0;
	own_foot_sync.is_dunk = Natives::IsCharDucking(gPlayer[client.GetIndex()].PedID);
	own_foot_sync.is_jump = Natives::IsCharInAir(gPlayer[client.GetIndex()].PedID);

	if(Natives::IsCharInAnyCar(gPlayer[client.GetIndex()].PedID))
	{
		own_foot_sync.in_veh = 1;
		Natives::GetCarCharIsUsing(gPlayer[client.GetIndex()].PedID, &t_car);
		own_foot_sync.veh_id = GetPlayerCar(t_car);
		gPlayer[client.GetIndex()].vehicleindex = own_foot_sync.veh_id;
	}
	else
	{
		own_foot_sync.in_veh = 0;
		own_foot_sync.veh_id = -1;
		gPlayer[client.GetIndex()].vehicleindex = own_foot_sync.veh_id;
	}

	if(Natives::IsControlPressed(0, 137)) // Fire
	{
		own_foot_sync.shot_time = GetTickCount() - gPlayer[client.GetIndex()].last_active;

		/*Natives::GetGameCam(&t_cam);
		Natives::GetCamRot(t_cam, &t_cam_position[0],&t_cam_position[1],&t_cam_position[2]);
		GetTarget(t_cam_position[0],t_cam_position[2], &t_cam_position[3], &t_cam_position[4], &t_cam_position[5], 5);
		Natives::GetCamPos(t_cam, &t_cam_position[0],&t_cam_position[1],&t_cam_position[2]);
		t_cam_position[0] += t_cam_position[3];
		t_cam_position[1] += t_cam_position[4];
		t_cam_position[2] += t_cam_position[5];*/
		GetCamTargetedCoords(&own_foot_sync.shot_position[0], &own_foot_sync.shot_position[1], &own_foot_sync.shot_position[2]);

		own_foot_sync.aim_sync = 2; // fire id
	}
	else if(Natives::IsControlPressed(0, 138)) // Aim
	{
		own_foot_sync.shot_time = GetTickCount() - gPlayer[client.GetIndex()].last_active;

		/*Natives::GetGameCam(&t_cam);
		Natives::GetCamRot(t_cam, &t_cam_position[0],&t_cam_position[1],&t_cam_position[2]);
		GetTarget(t_cam_position[0],t_cam_position[2], &t_cam_position[3], &t_cam_position[4], &t_cam_position[5], 5);
		Natives::GetCamPos(t_cam, &t_cam_position[0],&t_cam_position[1],&t_cam_position[2]);
		t_cam_position[0] += t_cam_position[3];
		t_cam_position[1] += t_cam_position[4];
		t_cam_position[2] += t_cam_position[5];*/
		GetCamTargetedCoords(&own_foot_sync.shot_position[0], &own_foot_sync.shot_position[1], &own_foot_sync.shot_position[2]);

		own_foot_sync.aim_sync = 1; // aim id
	}
	else own_foot_sync.aim_sync = 0;
	// send sync to server
	nm.SendPlayerFootSync(own_foot_sync);
}

char VehicleCmp(FVehicle *a, NetworkPlayerVehicleData *b)
{
	if(!IntRange(a->health, b->v_health, 5)) return 1;
	if(!IntRange(a->enginehealth, b->v_e_health, 5)) return 2;
	if(a->sirenon != b->siren) return 3;
	if(!FloatRange(a->angle, b->angle, 0.5f)) return 4;
	if(!FloatRange(a->position[0], b->position[0], 0.5f)) return 5;
	if(!FloatRange(a->position[1], b->position[1], 0.5f)) return 6; 
	if(!FloatRange(a->position[2], b->position[2], 0.5f)) return 7;
	if(!FloatRange(a->doorangle[0], b->door_angle[0], 0.5f)) return 8;
	if(!FloatRange(a->doorangle[1], b->door_angle[1], 0.5f)) return 9;
	if(!FloatRange(a->doorangle[2], b->door_angle[2], 0.5f)) return 10;
	if(!FloatRange(a->doorangle[3], b->door_angle[3], 0.5f)) return 11;
	if(!FloatRange(a->doorangle[4], b->door_angle[4], 0.5f)) return 12;
	if(!FloatRange(a->doorangle[5], b->door_angle[5], 0.5f)) return 13;
	if(!FloatRange(a->qua[0], b->qua[0], 0.5f)) return 14;
	if(!FloatRange(a->qua[1], b->qua[1], 0.5f)) return 15;
	if(!FloatRange(a->qua[2], b->qua[2], 0.5f)) return 16;
	if(!FloatRange(a->qua[3], b->qua[3], 0.5f)) return 17;
	if(!FloatRange(a->angle, b->angle, 0.5f)) return 18;
	if(a->is_dead != b->is_dead) return 19;
	if(memcmp(a->doorexists, b->door_damaged, sizeof(char)*6) != 0) return 20;
	if(memcmp(a->dooropen, b->door_open, sizeof(char)*6) != 0) return 21;
	if(memcmp(a->is_tyre_burst, b->is_tyre_burst, sizeof(char)*9) != 0) return 22;

	return 0;
}

void FMPHook::VehicleSync(short car)
{
	if(client.GetIndex() < 0 || !Natives::DoesCharExist(gPlayer[client.GetIndex()].PedID)) 
	{
		Natives::GetPlayerChar(_GetPlayer(), &gPlayer[client.GetIndex()].PedID);
		return;
	}

	if(!SafeCheckVehicle(car))
	{
		Log::Warning(L"Vehicle not exist");
		return;
	}

	memset(&own_veh_sync, 0, sizeof(NetworkPlayerVehicleData));

	t_car = gVehicle[car].CarID;
	own_veh_sync.v_id = car;

	Ped x_ped;
	Natives::GetDriverOfCar(t_car, &x_ped);

	if(!Natives::DoesCharExist(x_ped) || x_ped == 0)
		own_veh_sync.driver = -1;
	else if(car == gPlayer[client.GetIndex()].vehicleindex)
		own_veh_sync.driver = 1;
	else 
	{
		Log::Warning(L"Car with driver");
		return;
	}

	float tx, ty, tz;
	Natives::GetCarCoordinates(t_car, &tx, &ty, &tz);
	//Log::Debug(L"COORDS: %f %f %f", tx, ty, tz);
	own_veh_sync.position[0] = tx;
	own_veh_sync.position[1] = ty;
	own_veh_sync.position[2] = tz;
	//Log::Debug(L"COORDS S: %f %f %f", own_veh_sync.position[0], own_veh_sync.position[1], own_veh_sync.position[2]);
	Natives::GetCarSpeedVector(t_car,&t_vec3,false);
	own_veh_sync.velocity[0] = t_vec3.X;
	own_veh_sync.velocity[1] = t_vec3.Y;
	own_veh_sync.velocity[2] = t_vec3.Z;
	Natives::GetCarSpeed(t_car,&own_veh_sync.speed);
	Natives::GetCarHealth(t_car, &own_veh_sync.v_health);
	own_veh_sync.v_e_health = Natives::GetEngineHealth(t_car);
	own_veh_sync.siren = Natives::IsCarSirenOn(t_car);
	Natives::GetVehicleQuaternion(t_car,&own_veh_sync.qua[0],&own_veh_sync.qua[1],&own_veh_sync.qua[2],&own_veh_sync.qua[3]);
	Natives::GetCarHeading(t_car, &own_veh_sync.angle);

	own_veh_sync.is_dead = Natives::IsCarDead(t_car);

	for(char door_id = 0; door_id < 6; door_id++)
	{
		own_veh_sync.door_open[door_id] = Natives::IsCarDoorFullyOpen(t_car, (eVehicleDoor)door_id);
		Natives::GetDoorAngleRatio(t_car, (eVehicleDoor)door_id, &own_veh_sync.door_angle[door_id]);
		own_veh_sync.door_damaged[door_id] = Natives::IsCarDoorDamaged(t_car, (eVehicleDoor)door_id);
	}

	for(char tyre_id = 0; tyre_id < 8; tyre_id++)
		own_veh_sync.is_tyre_burst[tyre_id] = Natives::IsCarTyreBurst(t_car, (eVehicleTyre)tyre_id);

	if(VehicleCmp(&gVehicle[car], &own_veh_sync) == 0) return;
	else Log::Debug(L"Car %d[%d] ok (Send data to server)", car, gPlayer[client.GetIndex()].vehicleindex);
	
	gVehicle[car].angle = own_veh_sync.angle;
	gVehicle[car].sirenon = own_veh_sync.siren;
	gVehicle[car].is_dead = own_veh_sync.is_dead;
	gVehicle[car].health = own_veh_sync.v_health;
	gVehicle[car].enginehealth = own_veh_sync.v_e_health;
	memcpy(gVehicle[car].position, own_veh_sync.position, sizeof(float)*3);
	memcpy(gVehicle[car].velocity, own_veh_sync.velocity, sizeof(float)*3);
	memcpy(gVehicle[car].qua, own_veh_sync.qua, sizeof(float)*4);
	memcpy(gVehicle[car].doorexists, own_veh_sync.door_damaged, sizeof(char)*6);
	memcpy(gVehicle[car].doorangle, own_veh_sync.door_angle, sizeof(char)*6);
	memcpy(gVehicle[car].is_tyre_burst, own_veh_sync.is_tyre_burst, sizeof(char)*8);
	memcpy(gVehicle[car].dooropen, own_veh_sync.door_open, sizeof(char)*6);

	// send sync to server
	nm.SendPlayerVehicleSync(own_veh_sync);
}