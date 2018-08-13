/// \file
/// \brief Header file that describes the NetworkManager class.
/// \details See class description.
/// \author WNeZRoS, FaTony

#pragma once

#include <vector>
#include "../../Shared/RakNet/RakNetTypes.h"
#include "../../Shared/RakNet/MessageIdentifiers.h"
#include "../../Shared/Network/GtaEnums.h"
#include "../../Shared/Network/NetworkProtocol.h"

class RakPeerInterface;

/// \brief A network manager. It handles all network traffic.
/// \details TODO:
/// \author WNeZRoS, FaTony

class NetworkManager 
{
public:
	NetworkManager(void);
	~NetworkManager(void);
	void Load(short maxclients, unsigned short port);
	void Tick(void);
	void Unload(void);
	void CheckClients(void);
	void UpdateServerInfo(void);

	void KickPlayer(short index);
	void BanPlayer(short index);
	void ClearBanList();
	void ReloadBanList();
	void LoadBanList();

	bool SendGameTimeChangeToAll(const unsigned char time[2]);
	bool SendPlayerModelChangeToAll(const short index);
	bool SendPlayerWeaponGiftToAll(const short index, const eWeaponSlot slot);
	bool SendPlayerSpawnPositionChange(const short index);
	bool SendNewVehicleInfoToAll(const short index);
	bool SendPlayerPosition(const short index, const float pos[3], const float angle);
	void SendChatMessageToOne(short index, const wchar_t * msg);
	void SendChatMessageToAll(const wchar_t * msg);

private:
	unsigned short serverport;
	RakPeerInterface *net;
	std::vector<wchar_t*> badnick;

	struct Client
	{
		SystemAddress address;
	};

	short maxclientbuffersize;
	short clientbuffersize;
	Client **clientbuffer;

	void HandleOurPacket(unsigned char *, unsigned int length, SystemAddress sa);

	bool CheckClientName(const wchar_t name[MAX_CLIENT_NAME_LENGTH]);
	short RegisterNewClient(const SystemAddress address);
	void HandleClientDisconnection(const SystemAddress address, const DefaultMessageIDTypes type = ID_INTERNAL_PING);
	short GetClientIndex(const SystemAddress address);
	short GetClientFreeSlot(void);
	void SendConnectionError(const SystemAddress address, const NetworkPlayerConnectionError error);
	NetworkPlayerFullUpdateData *GetPlayerFullUpdateData(const short index);
	NetworkVehicleFullUpdateData *GetVehicleFullUpdateData(const short index);

	void HandleClientConnectionRequest(NetworkPlayerConnectionRequestData *data, const SystemAddress sa);
	void HandleClientConnectionConfirmation(NetworkPlayerConnectionConfirmationData *data, const SystemAddress sa);
	void HandlePlayerFootSync(NetworkPlayerFootData *data, const SystemAddress sa);
	void HandlePlayerVehicleSync(NetworkPlayerVehicleData *data, const SystemAddress sa);
	void HandlePlayerStartEntranceInVehicle(NetworkPlayerStartEntranceInVehicleData *data, const SystemAddress sa);
	void HandlePlayerCancelEntranceInVehicle(NetworkPlayerCancelEntranceInVehicleData *data, const SystemAddress sa);
	void HandlePlayerFinishEntranceInVehicle(NetworkPlayerFinishEntranceInVehicleData *data, const SystemAddress sa);
	void HandlePlayerStartExitFromVehicle(NetworkPlayerStartExitFromVehicleData *data, const SystemAddress sa);
	void HandlePlayerFinishExitFromVehicle(NetworkPlayerFinishExitFromVehicleData *data, const SystemAddress sa);
	void HandlePlayerSpawnRequest(NetworkPlayerSpawnRequestData *data, const SystemAddress sa);
	void HandlePlayerModelChange(NetworkPlayerModelChangeData *data, const SystemAddress sa);
	void HandlePlayerComponentsChange(NetworkPlayerComponentsChangeData *data, const SystemAddress sa);
	void HandlePlayerChat(NetworkPlayerChatData *data, const SystemAddress sa);

	template <typename DATATYPE>
	void SendDataToAll(const DATATYPE * data, const NetworkPackType type, const char pp = 2);

	template <typename DATATYPE>
	bool SendDataToOne(const short index, const DATATYPE * data, const NetworkPackType type, const char pp = 2);

	template <typename DATATYPE>
	void SendDataToAllExceptOne(const short index, const DATATYPE * data, const NetworkPackType type, const char pp = 2);

	template <typename DATATYPE>
	bool SendDataTo(const DATATYPE * data, const NetworkPackType type, const SystemAddress addr, const char pp = 2);
};
