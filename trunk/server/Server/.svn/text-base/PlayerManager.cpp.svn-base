#include <stdlib.h>
#include <stdio.h>

#include "PlayerManager.h"
#include "../../Shared/Console/common.h"
#include "../../Shared/logging/log.h"
#include "NetworkManager.h"
#include "VirtualMachineManager.h"
#include "VehicleManager.h"

extern NetworkManager nm;
extern VirtualMachineManager vmm;
extern VehicleManager vm;

PlayerManager::PlayerManager(void)
{
	maxplayerbuffersize = 32;
	maxclassbuffersize = 64;
	playerbuffer = NULL;
	classbuffer = NULL;
	playerbuffersize = 0;
	classbuffersize = 0;
}

PlayerManager::~PlayerManager(void)
{
	if (playerbuffer != NULL)
	{
		for (short i = 0; i < playerbuffersize; i++)
		{
			if (playerbuffer[i] != NULL)
			{
				delete playerbuffer[i];
			}
		}
	}
	if (classbuffer != NULL)
	{
		for (unsigned char i = 0; i < classbuffersize; i++)
		{
			if (classbuffer[i] != NULL)
			{
				delete classbuffer[i];
			}
		}
	}
}

short PlayerManager::GetMaxPlayers(void)
{
	return maxplayerbuffersize;
}

short PlayerManager::GetNumberOfPlayers(void)
{
	return numplayers;
}

bool PlayerManager::IsServerFull(void)
{
	if (playerbuffersize < maxplayerbuffersize)
	{
		return false;
	}
	for (unsigned char i = 0; i < playerbuffersize; i++)
	{
		if (playerbuffer[i] == NULL)
		{
			return false;
		}
	}
	return true;
}

bool PlayerManager::IsPlayerConnected(const short index)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	return true;
}

wchar_t *PlayerManager::GetPlayerName(const short index)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return NULL;
	}
	if (playerbuffer[index] == NULL)
	{
		return NULL;
	}
	wchar_t *tempstring = (wchar_t *)calloc(wcslen(playerbuffer[index]->name) + 1, sizeof(wchar_t));
	wcscpy(tempstring, playerbuffer[index]->name);
	return tempstring;
}

unsigned int PlayerManager::GetPlayerModel(const short index)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return INVALID_PLAYER_MODEL;
	}
	if (playerbuffer[index] == NULL)
	{
		return INVALID_PLAYER_MODEL;
	}
	return playerbuffer[index]->model;
}

bool PlayerManager::GetPlayerPosition(const short index, float (&position)[3])
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	memcpy(position, playerbuffer[index]->position, sizeof(float) * 3);
	return true;
}

bool PlayerManager::GetPlayerAngle(const short index, float &angle)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	angle = playerbuffer[index]->angle;
	return true;
}

short PlayerManager::GetPlayerVehicle(const short index)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return INVALID_VEHICLE_INDEX;
	}
	if (playerbuffer[index] == NULL)
	{
		return INVALID_VEHICLE_INDEX;
	}
	return playerbuffer[index]->vehicleindex;
}

bool PlayerManager::GetPlayerScore(const short index, int &score)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	score = playerbuffer[index]->score;
	return true;
}

bool PlayerManager::GetPlayerHealth(const short index, unsigned char &health)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	health = playerbuffer[index]->health;
	return true;
}

bool PlayerManager::GetPlayerArmor(const short index, unsigned char &armor)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	armor = playerbuffer[index]->armor;
	return true;
}

char PlayerManager::GetPlayerWantedLevel(const short index)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return INVALID_PLAYER_WANTED_LEVEL;
	}
	if (playerbuffer[index] == NULL)
	{
		return INVALID_PLAYER_WANTED_LEVEL;
	}
	return playerbuffer[index]->wanted_level;
}

bool PlayerManager::GetPlayerColor(const short index, unsigned char (&color)[4])
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	memcpy(color, playerbuffer[index]->color, sizeof(unsigned char) * 4);
	return true;
}

bool PlayerManager::GetPlayerSpawnPosition(const short index, float (&position)[4])
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	memcpy(position, playerbuffer[index]->spawnposition, sizeof(float) * 4);
	return true;
}

bool PlayerManager::SetPlayerModel(const short index, const unsigned int model)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	playerbuffer[index]->model = model;
	return nm.SendPlayerModelChangeToAll(index);
}

bool PlayerManager::SetPlayerPosition(const short index, const float position[3])
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	memcpy(playerbuffer[index]->position, position, sizeof(float) * 3);
	nm.SendPlayerPosition(index, position, playerbuffer[index]->angle);
	return true;
}

bool PlayerManager::GivePlayerWeapon(const short index, const eWeapon weapon, const unsigned short ammo)
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	if (playerbuffer[index]->health < 100)
	{
		return false;
	}
	if (ammo == 0)
	{
		return true;
	}
	eWeaponSlot slot;
	switch (weapon)
	{
	case WEAPON_UNARMED:
		{
			return true;
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
			return false;
			break;
		}
	}
	playerbuffer[index]->weapons[slot] = weapon;
	if (ammo >= MaxAmmoPerWeaponSlot[slot])
	{
		playerbuffer[index]->ammo[slot] = MaxAmmoPerWeaponSlot[slot];
	}
	else if ((playerbuffer[index]->ammo[slot] + ammo ) >= MaxAmmoPerWeaponSlot[slot])
	{
		playerbuffer[index]->ammo[slot] = MaxAmmoPerWeaponSlot[slot];
	}
	else
	{
		playerbuffer[index]->ammo[slot] = playerbuffer[index]->ammo[slot] + ammo;
	}
	return nm.SendPlayerWeaponGiftToAll(index, slot);
}

bool PlayerManager::SetPlayerSpawnPosition(const short index, const float position[4])
{
	if ((index < 0) || (index >= playerbuffersize))
	{
		return false;
	}
	if (playerbuffer[index] == NULL)
	{
		return false;
	}
	memcpy(playerbuffer[index]->spawnposition, position, 4 * sizeof(float));
	return nm.SendPlayerSpawnPositionChange(index);
}

unsigned char PlayerManager::GetNumberOfPlayerClasses(void)
{
	unsigned char numclasses = 0;
	for (unsigned char i = 0; i < classbuffersize; i++)
	{
		if (classbuffer[i] != NULL)
		{
			numclasses++;
		}
	}
	return numclasses;
}

bool PlayerManager::AddPlayerClass(const unsigned int model, const float position[3], const float angle, const char weapons[8], const short ammo[8], unsigned char &index)
{
	if (!this->GetClassFreeSlot(index))
	{
		Log::Warning(L"Unable to add player class. No free slots.");
		return false;
	}
	if (index >= classbuffersize)
	{
		if (classbuffersize == maxclassbuffersize)
		{
			return false;
		}
		if (!ResizeBuffer<PlayerClass **>(classbuffer, index + 1))
		{
			return false;
		}
		classbuffer[index] = NULL;
		classbuffersize = index + 1;
	}
	classbuffer[index] = new PlayerClass;
	classbuffer[index]->model = model;
	classbuffer[index]->position[0] = position[0];
	classbuffer[index]->position[1] = position[1];
	classbuffer[index]->position[2] = position[2];
	classbuffer[index]->angle = angle;
	classbuffer[index]->weapons[0] = weapons[0];
	classbuffer[index]->weapons[1] = weapons[1];
	classbuffer[index]->weapons[2] = weapons[2];
	classbuffer[index]->weapons[3] = weapons[3];
	classbuffer[index]->weapons[4] = weapons[4];
	classbuffer[index]->weapons[5] = weapons[5];
	classbuffer[index]->weapons[6] = weapons[6];
	classbuffer[index]->weapons[7] = weapons[7];
	classbuffer[index]->ammo[0] = ammo[0];
	classbuffer[index]->ammo[1] = ammo[1];
	classbuffer[index]->ammo[2] = ammo[2];
	classbuffer[index]->ammo[3] = ammo[3];
	classbuffer[index]->ammo[4] = ammo[4];
	classbuffer[index]->ammo[5] = ammo[5];
	classbuffer[index]->ammo[6] = ammo[6];
	classbuffer[index]->ammo[7] = ammo[7];
	//TODO: sync it? Does classes even sync?
	return true;
}

bool PlayerManager::GetPlayerClassData(const unsigned char index, unsigned int &model, float (&position)[3], float &angle, char (&weapons)[8], short (&ammo)[8])
{
	if (index >= classbuffersize)
	{
		return false;
	}
	if (classbuffer[index] == NULL)
	{
		return false;
	}
	model = classbuffer[index]->model;
	position[0] = classbuffer[index]->position[0];
	position[1] = classbuffer[index]->position[1];
	position[2] = classbuffer[index]->position[2];
	angle = classbuffer[index]->angle;
	weapons[0] = classbuffer[index]->weapons[0];
	weapons[1] = classbuffer[index]->weapons[1];
	weapons[2] = classbuffer[index]->weapons[2];
	weapons[3] = classbuffer[index]->weapons[3];
	weapons[4] = classbuffer[index]->weapons[4];
	weapons[5] = classbuffer[index]->weapons[5];
	weapons[6] = classbuffer[index]->weapons[6];
	weapons[7] = classbuffer[index]->weapons[7];
	ammo[0] = classbuffer[index]->ammo[0];
	ammo[1] = classbuffer[index]->ammo[1];
	ammo[2] = classbuffer[index]->ammo[2];
	ammo[3] = classbuffer[index]->ammo[3];
	ammo[4] = classbuffer[index]->ammo[4];
	ammo[5] = classbuffer[index]->ammo[5];
	ammo[6] = classbuffer[index]->ammo[6];
	ammo[7] = classbuffer[index]->ammo[7];
	return true;
}

bool PlayerManager::RegisterNewPlayer(const short index, wchar_t (&name)[MAX_CLIENT_NAME_LENGTH])
{
	if ((index < 0) || (index >= maxplayerbuffersize))
	{
		return false;
	}
	if (index >= playerbuffersize)
	{
		if (playerbuffersize == maxplayerbuffersize)
		{
			return false;
		}
		if (!ResizeBuffer<Player **>(playerbuffer, index + 1))
		{
			return false;
		}
		playerbuffer[index] = NULL;
		playerbuffersize = index + 1;
	}
	if (playerbuffer[index] != NULL)
	{
		return false;
	}
	if (!this->AssignPlayerName(name))
	{
		return false;
	}
	playerbuffer[index] = new Player;
	wcscpy(playerbuffer[index]->name, name);
	playerbuffer[index]->classindex = 0;
	playerbuffer[index]->model = DEFAULT_PLAYER_MODEL;
	playerbuffer[index]->position[0] = DEFAULT_PLAYER_X;
	playerbuffer[index]->position[1] = DEFAULT_PLAYER_Y;
	playerbuffer[index]->position[2] = DEFAULT_PLAYER_Z;
	playerbuffer[index]->angle = 0.0;
	playerbuffer[index]->isducking = false;
	for(unsigned char i = 0; i < 8; i++)
	{
		playerbuffer[index]->weapons[i] = WEAPON_UNARMED;
		playerbuffer[index]->ammo[i] = 0;
	}
	playerbuffer[index]->animation[0] = 0;
	playerbuffer[index]->state = PlayerStateOnFoot;
	playerbuffer[index]->vehicleindex = INVALID_VEHICLE_INDEX;
	playerbuffer[index]->seatindex = INVALID_PLAYER_SEAT_INDEX;
	playerbuffer[index]->score = 0;
	playerbuffer[index]->health = 200;
	playerbuffer[index]->armor = 0;
	playerbuffer[index]->wanted_level = 0;
	playerbuffer[index]->edSprint = 1;
	playerbuffer[index]->edLockon = 1;
	playerbuffer[index]->edDoDriveBy = 1;
	playerbuffer[index]->edUseCover = 1;
	playerbuffer[index]->edConrol = 1;
	playerbuffer[index]->edFreeze = 0;
	playerbuffer[index]->room = 0;
	playerbuffer[index]->color[0] = 0xFF;
	playerbuffer[index]->color[1] = 0xFF;
	playerbuffer[index]->color[2] = 0x00;
	playerbuffer[index]->color[3] = 0x00;
	playerbuffer[index]->spawnposition[0] = DEFAULT_PLAYER_X;
	playerbuffer[index]->spawnposition[1] = DEFAULT_PLAYER_Y;
	playerbuffer[index]->spawnposition[2] = DEFAULT_PLAYER_Z;
	playerbuffer[index]->spawnposition[3] = 0;
	playerbuffer[index]->currentweapon = 0;
	numplayers++;
	return true;
}

short PlayerManager::GetPlayerFreeSlot(void)
{
	short index;
	for (index = 0; index < playerbuffersize; index++)
	{
		if (playerbuffer[index] == NULL)
		{
			return index;
		}
	}
	if (playerbuffersize == maxplayerbuffersize)
	{
		return INVALID_PLAYER_INDEX;
	}
	return index;
}

bool PlayerManager::AssignPlayerName(wchar_t (&name)[MAX_CLIENT_NAME_LENGTH])
{
	if (wcslen(name) == 0)
	{
		wcscpy(name, L"unnamed");
		if (!this->AssignPlayerName(name))
		{
			return false;
		}
		return true;
	}
	bool stop;
	short j = 1;
	wchar_t tempname[MAX_CLIENT_NAME_LENGTH];
	wcsncpy(tempname, name, MAX_CLIENT_NAME_LENGTH - 1);
	tempname[MAX_CLIENT_NAME_LENGTH-1] = L'\0';
	do
	{
		stop = true;
		for (short i = 0; i < playerbuffersize; i++)
		{
			if ((playerbuffer[i] != NULL) && (wcscmp(playerbuffer[i]->name, tempname) == 0))
			{
				stop = false;
				_snwprintf(tempname, MAX_CLIENT_NAME_LENGTH - 1, L"(%d)%s", j, name);
				tempname[MAX_CLIENT_NAME_LENGTH-1] = L'\0';
				j++;
			}
		}
	} while (!stop);
	wcscpy(name, tempname);
	return true;
}

bool PlayerManager::GetClassFreeSlot(unsigned char &index)
{
	for (index = 0; index < classbuffersize; index++)
	{
		if (classbuffer[index] == NULL)
		{
			return true;
		}
	}
	if (classbuffersize == maxclassbuffersize)
	{
		return false;
	}
	return true;
}