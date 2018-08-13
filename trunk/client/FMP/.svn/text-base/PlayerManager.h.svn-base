#pragma once

#include "Hook/types.h"
#include "../../Shared/Network/ClientDefines.h"
#include "../../Shared/Network/PlayerDefines.h"

class PlayerManager
{
public:
	PlayerManager(void);
	~PlayerManager(void);
};

struct FPlayer
{
	Ped PedID;
	Blip radarblip;
	bool connected;
	char ip[16];
	unsigned short port;
	wchar_t name[MAX_CLIENT_NAME_LENGTH];
	unsigned int model;
	float position[3];
	float angle;
	int last_active;
	eWeapon currentweapon;
	eWeapon weapons[8];
	short ammo[8];
	char animation[128];
	short vehicleindex;
	char seatindex;
	int score;
	unsigned char health;
	unsigned char armor;
	char wanted_level;
	bool edSprint, edLockon, edDoDriveBy, edUseCover, edConrol, edFreeze; // enable / disable
	bool isaiming; ///< Holds true if the player is aiming.
	bool isducking; ///< Holds true if the player is ducking.
	int room;
	unsigned char color[4];
	int compT[11], compD[11];
};