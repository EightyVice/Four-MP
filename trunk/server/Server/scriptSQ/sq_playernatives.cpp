#include <stddef.h>

#include "sq.h"
#include "../PlayerManager.h"
#include "../NetworkManager.h"
#include "../../../Shared/logging/log.h"

extern PlayerManager playm;
extern NetworkManager nm;

void sq_GetPlayerName(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	wchar_t *name = playm.GetPlayerName(index);
	if (name == NULL)
	{
		sq_pushnull(v);
		return;
	}
	sq_pushstring(v, name, -1);
}

void sq_GetPlayerModel(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	int model = playm.GetPlayerModel(index);
	sq_pushinteger(v, model);
}

void sq_GetPlayerPosition(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	float position[3];
	if (!playm.GetPlayerPosition(index, position))
	{
		sq_pushnull(v);
		return;
	}
	sq_newarray(v, 0);
	sq_pushfloat(v, position[0]);
	sq_arrayappend(v, -2);
	sq_pushfloat(v, position[1]);
	sq_arrayappend(v, -2);
	sq_pushfloat(v, position[2]);
	sq_arrayappend(v, -2);
	sq_push(v, -1);
}

void sq_GetPlayerAngle(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	float angle;
	if (!playm.GetPlayerAngle(index, angle))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushfloat(v, angle);
}

void sq_GetPlayerVehicle(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	short vehicleindex = playm.GetPlayerVehicle(index);
	sq_pushinteger(v, vehicleindex);
}

void sq_GetPlayerScore(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	int score;
	if (!playm.GetPlayerScore(index, score))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, score);
}

void sq_GetPlayerHealth(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	unsigned char health;
	if (!playm.GetPlayerHealth(index, health))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, health);
}

void sq_GetPlayerArmor(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	unsigned char armor;
	if (!playm.GetPlayerArmor(index, armor))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, armor);
}

void sq_GetPlayerWantedLevel(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	char wantedlevel = playm.GetPlayerWantedLevel(index);
	sq_pushinteger(v, wantedlevel);
}

void sq_GetPlayerSpawnPosition(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	float position[4];
	if (!playm.GetPlayerSpawnPosition(index, position))
	{
		sq_pushnull(v);
		return;
	}
	sq_newarray(v, 0);
	sq_pushfloat(v, position[0]);
	sq_arrayappend(v, -2);
	sq_pushfloat(v, position[1]);
	sq_arrayappend(v, -2);
	sq_pushfloat(v, position[2]);
	sq_arrayappend(v, -2);
	sq_pushfloat(v, position[3]);
	sq_arrayappend(v, -2);
	sq_push(v, -1);
}

void sq_SetPlayerModel(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	int model;
	sq_getinteger(v, 3, &model);
	sq_pushbool(v, playm.SetPlayerModel(index, model));
}

void sq_GivePlayerWeapon(HSQUIRRELVM v) 
{
	int index;
	sq_getinteger(v, 2, &index);
	int weapon;
	int ammo;
	sq_getinteger(v, 3, &weapon);
	sq_getinteger(v, 4, &ammo);
	sq_pushbool(v, playm.GivePlayerWeapon(index, (eWeapon)weapon, ammo));
}

void sq_SetPlayerSpawnPosition(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	float position[4];
	sq_getfloat(v, 3, &position[0]);
	sq_getfloat(v, 4, &position[1]);
	sq_getfloat(v, 5, &position[2]);
	sq_getfloat(v, 6, &position[3]);

	sq_pushbool(v, playm.SetPlayerSpawnPosition(index, position));
}

void sq_SetPlayerPos(HSQUIRRELVM v)
{
	int index;
	sq_getinteger(v, 2, &index);
	float position[3];
	sq_getfloat(v, 3, &position[0]);
	sq_getfloat(v, 4, &position[1]);
	sq_getfloat(v, 5, &position[2]);

	sq_pushbool(v, playm.SetPlayerPosition(index, position));
}

void sq_Kick(HSQUIRRELVM v)
{
	short index;
	sq_getinteger(v, 2, (SQInteger*)&index);
	nm.KickPlayer(index);
}

void sq_Ban(HSQUIRRELVM v)
{
	short index;
	sq_getinteger(v, 2, (SQInteger*)&index);
	nm.BanPlayer(index);
}

void sq_ReloadBanList(HSQUIRRELVM v)
{
	nm.ReloadBanList();
}

void sq_ClearBanList(HSQUIRRELVM v)
{
	nm.ClearBanList();
}

void RegPlayerSQFunc(SQVM * v)
{
	register_global_func(v, (SQFUNCTION)sq_GetPlayerName, L"GetPlayerName");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerModel, L"GetPlayerModel");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerPosition, L"GetPlayerPosition");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerAngle, L"GetPlayerAngle");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerScore, L"GetPlayerScore");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerHealth, L"GetPlayerHealth");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerArmor, L"GetPlayerArmor");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerWantedLevel, L"GetPlayerWantedLevel");
	register_global_func(v, (SQFUNCTION)sq_GetPlayerSpawnPosition, L"GetPlayerSpawnPosition");
	register_global_func(v, (SQFUNCTION)sq_SetPlayerModel, L"SetPlayerModel");
	register_global_func(v, (SQFUNCTION)sq_GivePlayerWeapon, L"GivePlayerWeapon");
	register_global_func(v, (SQFUNCTION)sq_SetPlayerSpawnPosition, L"SetPlayerSpawnPosition");
	register_global_func(v, (SQFUNCTION)sq_SetPlayerPos, L"SetPlayerPos");

	register_global_func(v, (SQFUNCTION)sq_Kick, L"Kick");
	register_global_func(v, (SQFUNCTION)sq_Ban, L"Ban");
	register_global_func(v, (SQFUNCTION)sq_ReloadBanList, L"ReloadBanList");
	register_global_func(v, (SQFUNCTION)sq_ClearBanList, L"ClearBanList");
}