#pragma once

#include "GtaEnums.h"
#include "Limits.h"
#include "ClientDefines.h"

#define PROTOCOL_VERSION 18
#define FMP_PACKET_SIGNATURE 255

enum NetworkPackType
{
	NetworkPackNull,
	NetworkPackPlayerConnection,
	NetworkPackPlayerConnectionRequest,
	NetworkPackPlayerConnectionError,
	NetworkPackPlayerConnectionConfirmation,
	NetworkPackPlayerInfo,
	NetworkPackPlayerDisconnection,
	NetworkPackGameTimeChange,
	NetworkPackPlayerFullUpdate,
	NetworkPackVehicleFullUpdate,
	NetworkPackPlayerFootSync,
	NetworkPackPlayerVehicleSync,
	NetworkPackPlayerStartEntranceInVehicle,
	NetworkPackPlayerCancelEntranceInVehicle,
	NetworkPackPlayerFinishEntranceInVehicle,
	NetworkPackPlayerStartExitFromVehicle,
	NetworkPackPlayerFinishExitFromVehicle,
	NetworkPackPlayerWeaponGift,
	NetworkPackPlayerSpawnPositionChange,
	NetworkPackPlayerSpawn,
	NetworkPackPlayerModelChange,
	NetworkPackPlayerComponentsChange,
	NetworkPackPlayerChat,
	NetworkPackNewVehicle,
	NetworkPackPlayerPosition
};

enum NetworkPlayerConnectionError
{
	NetworkPlayerConnectionErrorServerFull,
	NetworkPlayerConnectionErrorInvalidProtocol,
	NetworkPlayerConnectionErrorInvalidName,
	NetworkPlayerConnectionErrorBanned,
	NetworkPlayerConnectionErrorInvalidAuth,
	NetworkPlayerConnectionErrorAlreadyConnected,
	NetworkPlayerConnectionErrorAllocationError,
	NetworkPlayerConnectionErrorScriptLock
};

#pragma pack(push, 1)
struct NetworkPlayerConnectionRequestData
{
	short protocol;
	wchar_t name[MAX_CLIENT_NAME_LENGTH];
	unsigned int sessionkey;
	int fmpid;
};

struct NetworkPlayerConnectionErrorData
{
	NetworkPlayerConnectionError error;
};

struct NetworkPlayerInfoData
{
	short index;
	unsigned int sessionkey;
};

struct NetworkPlayerConnectionConfirmationData
{
	short client;
};

struct NetworkPlayerDisconnectionData
{
	short client;
};

struct NetworkPlayerCheckData
{
	short client;
};

struct NetworkGameTimeChangeData
{
	unsigned char time[2];
};

struct NetworkPlayerFullUpdateData
{
	short index;
	wchar_t name[MAX_CLIENT_NAME_LENGTH];
	unsigned int model;
	float position[3];
	float angle;
	short vehicleindex;
	char seatindex;
	int score;
	unsigned char health;
	unsigned char armor;
	int room;
	eWeapon weapons[8];
	short ammo[8];
	unsigned char color[4];
};

struct NetworkPlayerFootData
{
	short			client;
	float			position[3];
	float			velocity[3];
	//int				keys[3];
	float			angle;
	float			speed;
	unsigned int	health;
	unsigned int	armour;
	eWeapon			weapon;
	unsigned int	ammo;
	char			is_dunk;
	char			is_jump;
	char			aim_sync;
	char			shot_time;
	float			shot_position[3];
	char			in_veh;
	short			veh_id;
};

struct NetworkPlayerVehicleData
{
	short			driver;
	float			position[3];
	float			velocity[3];
	//int				keys[3];
	float			qua[4];
	float			angle;
	float			door_angle[6];
	char			door_open[6];
	float			speed;
	//unsigned int	health;
	//unsigned int	armour;
	unsigned int	v_health;
	unsigned int	v_e_health;
	int				v_id;
	char			siren;
	char			is_tyre_burst[8];
	char			door_damaged[6];	
	char			is_dead;
};


struct NetworkPlayerStartEntranceInVehicleData
{
	short client;
	short vehicleindex;
	char seatindex;
};

struct NetworkPlayerCancelEntranceInVehicleData
{
	short client;
};

struct NetworkPlayerFinishEntranceInVehicleData
{
	short client;
};

struct NetworkPlayerStartExitFromVehicleData
{
	short client;
};

struct NetworkPlayerFinishExitFromVehicleData
{
	short client;
};

struct NetworkPlayerWeaponGiftData
{
	short client;
	eWeapon weapon;
	short ammo;
};

struct NetworkPlayerFireData
{
	short client;
	float position[3];
	eWeapon weapon;
	int time;
	short target;
	unsigned char health;
	unsigned char armor;
};

struct NetworkPlayerAimData
{
	short client;
	float position[3];
	eWeapon weapon;
	int time;
};

struct NetworkPlayerWeaponChangeData
{
	short client;
	eWeapon weapon;
};

struct NetworkPlayerHealthAndArmorChangeData
{
	short client;
	unsigned char health;
	unsigned char armor;
};

struct NetworkPlayerSpawnPositionChangeData
{
	float position[4];
};

struct NetworkPlayerSpawnRequestData
{
	short client;
};

struct NetworkPlayerSpawnData
{
	short client;
	unsigned int model;
	float position[4];
	int room;
	int compT[11];
	int compD[11];
	unsigned char health;
	unsigned char armor;
};

struct NetworkPlayerModelChangeData
{
	short client;
	unsigned int model;
};

struct NetworkPlayerComponentsChangeData
{
	short client;
	int compD[11];
	int compT[11];
};

struct NetworkPlayerChatData
{
	short client;
	wchar_t message[MAX_CHAT_MESSAGE_LENGTH];
};

struct NetworkVehicleFullUpdateData
{
	short index;
	unsigned int model;
	float position[3];
	float angle;
	unsigned char color[2];
};

struct NetworkPlayerPositionData
{
	short client;
	float pos[3];
	float angle;
};

#pragma pack(pop)