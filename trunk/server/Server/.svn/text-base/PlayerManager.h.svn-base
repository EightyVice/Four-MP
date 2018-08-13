#pragma once

#include "../../Shared/Network/ClientDefines.h"
#include "../../Shared/Network/PlayerDefines.h"
#include "../../Shared/Network/GtaEnums.h"

class PlayerManager
{
public:
	PlayerManager(void);
	~PlayerManager(void);
	short GetMaxPlayers(void);
	short GetNumberOfPlayers(void);
	wchar_t *GetPlayerName(const short index);
	unsigned int GetPlayerModel(const short index);
	bool GetPlayerPosition(const short index, float (&postion)[3]);
	bool GetPlayerAngle(const short index, float &angle);
	short GetPlayerVehicle(const short index);
	bool GetPlayerScore(const short index, int &score);
	bool GetPlayerHealth(const short index, unsigned char &health);
	bool GetPlayerArmor(const short index, unsigned char &armor);
	char GetPlayerWantedLevel(const short index);
	bool GetPlayerColor(const short index, unsigned char (&color)[4]);
	bool GetPlayerSpawnPosition(const short index, float (&position)[4]);
	unsigned char GetNumberOfPlayerClasses(void);

	bool GivePlayerWeapon(const short index, const eWeapon weapon, const unsigned short ammo);

	bool IsServerFull(void);
	bool IsPlayerConnected(const short index);

	bool SetPlayerModel(const short index, const unsigned int model);
	bool SetPlayerPosition(const short index, const float position[3]);
	bool SetPlayerSpawnPosition(const short index, const float position[4]);
	
	bool AddPlayerClass(const unsigned int model, const float position[3], const float angle, const char weapons[8], const short ammo[8], unsigned char &index);
	bool GetPlayerClassData(const unsigned char index, unsigned int &model, float (&position)[3], float &angle, char (&weapons)[8], short (&ammo)[8]);
private:
	struct Player
	{
		wchar_t name[MAX_CLIENT_NAME_LENGTH]; ///< Holds the name of the player.
		unsigned char classindex; ///< Holds the index of the player's class.
		unsigned int model; ///< Holds the model hash of the player.
		float position[3]; ///< Holds the position of the player.
		float angle; ///< Holds the angle of the player.
		bool isducking; ///< Holds true if the player is ducking and false otherwise.
		char currentweapon;
		eWeapon weapons[8];
		short ammo[8];
		char animation[128];
		PlayerState state; ///< Holds the state of the player.
		short vehicleindex; ///< Holds the index of the vehicle the player is in.
		char seatindex; ///< Holds the index of the seat of the vehicle the player is in.
		int score; /// Holds the score of the player.
		unsigned char health; ///< Holds the health of the player. 200 mean full health, 99 or lower - dead.
		unsigned char armor; ///< Holds the armor of the player. 0 means no armor, 100 - full.
		char wanted_level; ///< Holds the wanted level of the player.
		bool edSprint, edLockon, edDoDriveBy, edUseCover, edConrol, edFreeze; // enable / disable
		int room;
		unsigned char color[4]; ///< Holds the color of the player.
		int compT[11], compD[11];
		float spawnposition[4];
		bool isDead;
	};
	short maxplayerbuffersize;
	short playerbuffersize;
	short numplayers;
	Player **playerbuffer;
	struct PlayerClass
	{
		unsigned int model;
		float position[3];
		float angle;
		char weapons[8];
		short ammo[8];
	};
	unsigned char maxclassbuffersize;
	unsigned char classbuffersize;
	PlayerClass **classbuffer;
	bool RegisterNewPlayer(const short index, wchar_t (&name)[MAX_CLIENT_NAME_LENGTH]);
	short GetPlayerFreeSlot(void);
	bool AssignPlayerName(wchar_t (&name)[MAX_CLIENT_NAME_LENGTH]);
	bool GetClassFreeSlot(unsigned char &index);
	friend class NetworkManager;
};
