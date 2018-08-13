#pragma once

#include <windows.h>
#include "../../Shared/RakNet/RakNetTypes.h"
#include "../../Shared/Network/NetworkProtocol.h"

class RakPeerInterface;

class NetworkManager
{
public:
	NetworkManager(void);
	~NetworkManager(void);
	void Load(void);
	void Tick(void);
	void Unload(void);
	void Ping(const char *hostname, const unsigned short port = 7777);
	void ConnectToServer(const char *hostname = "", const unsigned short port = 7777);

	void SendClientConnectionRequest(void);
	void SendPlayerFootSync(NetworkPlayerFootData data);
	void SendPlayerVehicleSync(NetworkPlayerVehicleData data);

	void SendPlayerStartEntranceInVehicle(void);
	void SendPlayerCancelEntranceInVehicle(void);
	void SendPlayerFinishEntranceInVehicle(void);
	void SendPlayerStartExitFromVehicle(void);
	void SendPlayerFinishExitFromVehicle(void);
	void SendPlayerSpawnRequest(void);
	void SendPlayerModelChange(void);
	void SendPlayerComponentsChange(void);
	void SendPlayerChat(const wchar_t *message);
	
private:

	SystemAddress serveraddress;
	RakPeerInterface *net;
	char *buff;
	short loaded;

	void HandleOurPacket(unsigned char *, unsigned int length, SystemAddress sa);
	template <typename DATATYPE>
	void SendDataToServer(const DATATYPE * data, const NetworkPackType type, const char pp = 2);
};
