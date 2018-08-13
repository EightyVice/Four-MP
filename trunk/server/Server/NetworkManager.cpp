#include "../../Shared/RakNet/RakPeerInterface.h"
#include "../../Shared/RakNet/RakNetworkFactory.h"

#include "NetworkManager.h"
#include "../../Shared/Console/common.h"
#include "../../Shared/logging/log.h"
#include "ServerCore.h"
#include "MasterServerManager.h"
#include "VirtualMachineManager.h"
#include "PlayerManager.h"
#include "VehicleManager.h"

extern ServerCore server;
extern MasterServerManager msm;
extern VirtualMachineManager vmm;
extern PlayerManager playm;
extern VehicleManager vm;

NetworkManager::NetworkManager(void)
{
	net = NULL;
	maxclientbuffersize = playm.GetMaxPlayers();
	clientbuffer = NULL;
	clientbuffersize = 0;
}

NetworkManager::~NetworkManager(void)
{
	if (net != NULL)
	{
		net->Shutdown(100,0);
		RakNetworkFactory::DestroyRakPeerInterface(net);
	}
	if (clientbuffer != NULL)
	{
		for (short i = 0; i < clientbuffersize; i++)
		{
			if (clientbuffer[i] != NULL)
			{
				delete clientbuffer[i];
			}
		}
		free(clientbuffer);
	}
}

void NetworkManager::Load(const short maxclients, const unsigned short port)
{
	net = RakNetworkFactory::GetRakPeerInterface();
	SocketDescriptor s(port, 0);
	net->SetMaximumIncomingConnections(maxclients);
	net->Startup(maxclients, 1, &s, 1);
	this->LoadBanList();
}

void NetworkManager::Tick(void)
{
	static Packet *pack;
	for (pack = net->Receive(); pack; net->DeallocatePacket(pack), pack = net->Receive())
	{
		switch (pack->data[0])
		{
		case FMP_PACKET_SIGNATURE:
			{
				HandleOurPacket(pack->data + 1, pack->length, pack->systemAddress);
			} break;
		case ID_CONNECTION_REQUEST:
			{
				Log::Debug(L"New connection request");
			} break;
		case ID_NEW_INCOMING_CONNECTION:
			{
				Log::Debug(L"New connection from %S:%d", pack->systemAddress.ToString(0), pack->systemAddress.port);
			} break;
		case ID_DISCONNECTION_NOTIFICATION:
			{
				this->HandleClientDisconnection(pack->systemAddress);
			} break;
		case ID_CONNECTION_LOST:
			{
				this->HandleClientDisconnection(pack->systemAddress);
			} break;
		}
	}
}

void NetworkManager::Unload(void)
{
	if (net != NULL)
	{
		net->Shutdown(100,0);
		RakNetworkFactory::DestroyRakPeerInterface(net);
		net = NULL;
	}
	if (clientbuffer != NULL)
	{
		for (short i = 0; i < clientbuffersize; i++)
		{
			if (clientbuffer[i] != NULL)
			{
				delete clientbuffer[i];
				clientbuffer[i] = NULL;
			}
		}
		free(clientbuffer);
		clientbuffer = NULL;
	}
}

void NetworkManager::CheckClients(void)
{
	//this->SendDataToAll("&NetworkManager::RecieveCheck", );
}

void NetworkManager::UpdateServerInfo(void)
{
	wchar_t *hostname = server.GetHostname();
	wchar_t *gamemode = vmm.GetGameModeName();
	int length = _scwprintf(L"%s%c%s%c%s%c%d%c%d%c%d%c%s%c", hostname, 1, gamemode, 1, L"World", 1, playm.numplayers, 1, playm.maxplayerbuffersize, 1, server.IsPasswordProtected(), 1, L"", 1);
	wchar_t *tempstring = (wchar_t *)calloc(length + 1, sizeof(wchar_t));
	swprintf(tempstring, length + 1, L"%s%c%s%c%s%c%d%c%d%c%d%c%s%c", hostname, 1, gamemode, 1, L"World", 1, playm.numplayers, 1, playm.maxplayerbuffersize, 1, server.IsPasswordProtected(), 1, L"", 1);
	length = (sizeof(wchar_t) / sizeof(char)) * length + 1;
	char *info = (char *)calloc(length, sizeof(char));
	wcstombs(info, tempstring, length);
	net->SetOfflinePingResponse(info, length);
	delete hostname;
	delete gamemode;
	delete info;
}

void NetworkManager::HandleOurPacket(unsigned char * pack, unsigned int length, SystemAddress sa)
{
	short type = *(short*)pack;

	switch(type)
	{
	case NetworkPackPlayerConnectionRequest:
		{
			NetworkPlayerConnectionRequestData data = *(NetworkPlayerConnectionRequestData*)(pack+2);
			this->HandleClientConnectionRequest(&data, sa);
		} break;
	case NetworkPackPlayerConnectionConfirmation:
		{
			NetworkPlayerConnectionConfirmationData data = *(NetworkPlayerConnectionConfirmationData*)(pack+2);
			this->HandleClientConnectionConfirmation(&data, sa);
		} break;
	case NetworkPackPlayerFootSync:
		{
			NetworkPlayerFootData data = *(NetworkPlayerFootData*)(pack+2);
			this->HandlePlayerFootSync(&data, sa);
		} break;
	case NetworkPackPlayerVehicleSync:
		{
			NetworkPlayerVehicleData data = *(NetworkPlayerVehicleData*)(pack+2);
			this->HandlePlayerVehicleSync(&data, sa);
		} break;
	case NetworkPackPlayerStartEntranceInVehicle:
		{
			NetworkPlayerStartEntranceInVehicleData data = *(NetworkPlayerStartEntranceInVehicleData*)(pack+2);
			this->HandlePlayerStartEntranceInVehicle(&data, sa);
		} break;
	case NetworkPackPlayerCancelEntranceInVehicle:
		{
			NetworkPlayerCancelEntranceInVehicleData data = *(NetworkPlayerCancelEntranceInVehicleData*)(pack+2);
			this->HandlePlayerCancelEntranceInVehicle(&data, sa);
		} break;
	case NetworkPackPlayerFinishEntranceInVehicle:
		{
			NetworkPlayerFinishEntranceInVehicleData data = *(NetworkPlayerFinishEntranceInVehicleData*)(pack+2);
			this->HandlePlayerFinishEntranceInVehicle(&data, sa);
		} break;
	case NetworkPackPlayerStartExitFromVehicle:
		{
			NetworkPlayerStartExitFromVehicleData data = *(NetworkPlayerStartExitFromVehicleData*)(pack+2);
			this->HandlePlayerStartExitFromVehicle(&data, sa);
		} break;
	case NetworkPackPlayerFinishExitFromVehicle:
		{
			NetworkPlayerFinishExitFromVehicleData data = *(NetworkPlayerFinishExitFromVehicleData*)(pack+2);
			this->HandlePlayerFinishExitFromVehicle(&data, sa);
		} break;
	case NetworkPackPlayerSpawn:
		{
			NetworkPlayerSpawnRequestData data = *(NetworkPlayerSpawnRequestData*)(pack+2);
			this->HandlePlayerSpawnRequest(&data, sa);
		} break;
	case NetworkPackPlayerModelChange:
		{
			NetworkPlayerModelChangeData data = *(NetworkPlayerModelChangeData*)(pack+2);
			this->HandlePlayerModelChange(&data, sa);
		} break;
	case NetworkPackPlayerComponentsChange:
		{
			NetworkPlayerComponentsChangeData data = *(NetworkPlayerComponentsChangeData*)(pack+2);
			this->HandlePlayerComponentsChange(&data, sa);
		} break;
	case NetworkPackPlayerChat:
		{
			NetworkPlayerChatData data = *(NetworkPlayerChatData*)(pack+2);
			this->HandlePlayerChat(&data, sa);
		} break;
	}
}

void NetworkManager::HandleClientConnectionRequest(NetworkPlayerConnectionRequestData *data, const SystemAddress sa)
{
	if (playm.IsServerFull())
	{
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorServerFull);
		net->CloseConnection(sa, true);
		return;
	}
	if (data->protocol != PROTOCOL_VERSION)
	{
		Log::Error(L"Client has different protocol version.");
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorInvalidProtocol);
		net->CloseConnection(sa, true);
		return;
	}
	if (wcslen(data->name) == 0)
	{
		Log::Error(L"Client has invalid name.");
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorInvalidName);
		net->CloseConnection(sa, true);
		return;
	}
	for(int i = 0; i != badnick.size(); i++)
	{
		if(wcscmp(badnick[i], data->name) == 0)
		{
			Log::Error(L"Client banned.");
			net->AddToBanList(sa.ToString(0));
			this->SendConnectionError(sa, NetworkPlayerConnectionErrorBanned);
			net->CloseConnection(sa, true);
			return;
			break;
		}
	}
	if (!server.IsLAN())
	{
		if(!msm.QueryUserCheck(data->fmpid, sa.ToString(0), data->sessionkey))
		{
			Log::Error(L"Client has failed to pass an authentication.");
			this->SendConnectionError(sa, NetworkPlayerConnectionErrorInvalidAuth);
			net->CloseConnection(sa, true);
			return;
		}
	}
	else
	{
		// TODO: Offline name check
	}

	short client = this->GetClientIndex(sa);
	if (client != INVALID_PLAYER_INDEX)
	{
		Log::Error(L"Player %s has tried to connect twice.", playm.playerbuffer[client]->name);
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorAlreadyConnected);
		net->CloseConnection(sa, true);
		return;
	}
	client = this->RegisterNewClient(sa);
	if (client == INVALID_PLAYER_INDEX)
	{
		Log::Error(L"Unable to register new client.");
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorAllocationError);
		net->CloseConnection(sa, true);
		return;
	}
	if (!vmm.OnPlayerConnect(client, data->name))
	{
		Log::Warning(L"Server script has disabled new client.");
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorScriptLock);
		net->CloseConnection(sa, true);
		delete clientbuffer[client];
		clientbuffer[client] = NULL;
		return;
	}
	if (!playm.RegisterNewPlayer(client, data->name))
	{
		Log::Error(L"Unable to register new client.");
		this->SendConnectionError(sa, NetworkPlayerConnectionErrorAllocationError);
		net->CloseConnection(sa, true);
		delete clientbuffer[client];
		clientbuffer[client] = NULL;
		return;
	}
	Log::Info(L"Player %s[%d] connected", playm.playerbuffer[client]->name, client);
	NetworkPlayerInfoData infodata;
	infodata.index = client;
	infodata.sessionkey = data->sessionkey;
	this->SendDataToOne(client, &infodata, NetworkPackPlayerInfo, 1);
}

void NetworkManager::HandleClientConnectionConfirmation(NetworkPlayerConnectionConfirmationData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	NetworkGameTimeChangeData timedata;
	server.GetGameTime(timedata.time);
	this->SendDataToOne(client, &timedata, NetworkPackGameTimeChange, 2);
	NetworkPlayerFullUpdateData *playerdata;
	//TODO: Optimize using currently connected players, not buffer size.
	for (short i = 0; i < clientbuffersize; i++)
	{
		if (i != data->client)
		{
			playerdata = this->GetPlayerFullUpdateData(i);
			if (playerdata != NULL)
			{
				this->SendDataToOne(client, playerdata, NetworkPackPlayerFullUpdate, 1);
				delete playerdata;
			}
		}
	}
	NetworkVehicleFullUpdateData *vehicledata;
	for (short i = 0; i < vm.vehiclebuffersize; i++)
	{
		vehicledata = this->GetVehicleFullUpdateData(i);
		if (vehicledata != NULL)
		{
			this->SendDataToOne(client, vehicledata, NetworkPackVehicleFullUpdate, 1);
			delete vehicledata;
		}
	}
	playerdata = this->GetPlayerFullUpdateData(data->client);
	if (playerdata == NULL)
	{
		Log::Error(L"Unable to read player data.");
		this->SendConnectionError(clientbuffer[data->client]->address, NetworkPlayerConnectionErrorAllocationError);
		net->CloseConnection(clientbuffer[data->client]->address, true);
		delete clientbuffer[data->client];
		clientbuffer[data->client] = NULL;
		return;
	}
	this->SendDataToAll(playerdata, NetworkPackPlayerConnection, 1);
	delete playerdata;
	server.UpdateServerInfo();

	vmm.OnPlayerSpawn(data->client);

	NetworkPlayerSpawnData data2;
	data2.armor = playm.playerbuffer[data->client]->armor;
	data2.health = playm.playerbuffer[data->client]->health;
	data2.model = playm.playerbuffer[data->client]->model;
	memcpy(data2.position, playm.playerbuffer[data->client]->spawnposition, sizeof(float) * 4);
	data2.room = playm.playerbuffer[data->client]->room;
	memcpy(data2.compD, playm.playerbuffer[data->client]->compD, sizeof(int) * 11);
	memcpy(data2.compT, playm.playerbuffer[data->client]->compT, sizeof(int) * 11);
	data2.client = data->client;
	this->SendDataToAll(&data2, NetworkPackPlayerSpawn, 1);
}

void NetworkManager::HandlePlayerFootSync(NetworkPlayerFootData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}

	if ((data->health >= 100) && playm.playerbuffer[client]->isDead)
	{
		playm.playerbuffer[client]->health = data->health;
		playm.playerbuffer[client]->armor = data->armour;
		vmm.OnPlayerSpawn(client);
		playm.playerbuffer[client]->isDead = false;
	}
	else // already death
	{
		playm.playerbuffer[client]->health = data->health;
		playm.playerbuffer[client]->armor = data->armour;
	}
	if (data->health < 100 && !playm.playerbuffer[client]->isDead)
	{
		vmm.OnPlayerDeath(client, INVALID_PLAYER_INDEX, 46);
		playm.playerbuffer[client]->isDead = true;
	}
	//PrintToServer(L"Foot %d to %f %f %f", client, data->position[0], data->position[1], data->position[2]);
	memcpy(playm.playerbuffer[client]->position, data->position, sizeof(float) * 3);
	playm.playerbuffer[client]->angle = data->angle;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerFootSync, 1);
}

void NetworkManager::HandlePlayerVehicleSync(NetworkPlayerVehicleData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	if(data->driver == 1) data->driver = client;

	vm.SetVehiclePositionInternal(data->v_id, data->position);
	vm.SetVehicleAngleInternal(data->v_id, data->angle);

	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerVehicleSync, 1);
}

void NetworkManager::HandlePlayerStartEntranceInVehicle(NetworkPlayerStartEntranceInVehicleData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((data->client < 0) || (data->client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[data->client] == NULL)
	{
		return;
	}
	if (playm.playerbuffer[data->client]->state != PlayerStateOnFoot)
	{
		return;
	}
	if ((data->vehicleindex < 0) || (data->vehicleindex >= vm.vehiclebuffersize))
	{
		return;
	}
	if (vm.vehiclebuffer[data->vehicleindex] == NULL)
	{
		return;
	}
	if (data->seatindex < 0)
	{
		return;
	}
	playm.playerbuffer[data->client]->state = PlayerStateEnteringVehicle;
	playm.playerbuffer[data->client]->vehicleindex = data->vehicleindex;
	playm.playerbuffer[data->client]->seatindex = data->seatindex;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerStartEntranceInVehicle);
}

void NetworkManager::HandlePlayerCancelEntranceInVehicle(NetworkPlayerCancelEntranceInVehicleData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((data->client < 0) || (data->client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[data->client] == NULL)
	{
		return;
	}
	if (playm.playerbuffer[data->client]->state != PlayerStateEnteringVehicle)
	{
		return;
	}
	playm.playerbuffer[data->client]->state = PlayerStateOnFoot;
	playm.playerbuffer[data->client]->vehicleindex = INVALID_VEHICLE_INDEX;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerCancelEntranceInVehicle);
}

void NetworkManager::HandlePlayerFinishEntranceInVehicle(NetworkPlayerFinishEntranceInVehicleData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((data->client < 0) || (data->client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[data->client] == NULL)
	{
		return;
	}
	if (playm.playerbuffer[data->client]->state != PlayerStateEnteringVehicle)
	{
		return;
	}
	playm.playerbuffer[data->client]->state = PlayerStateInVehicle;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerFinishEntranceInVehicle);
}

void NetworkManager::HandlePlayerStartExitFromVehicle(NetworkPlayerStartExitFromVehicleData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}
	if (playm.playerbuffer[client]->state != PlayerStateInVehicle)
	{
		return;
	}
	playm.playerbuffer[client]->state = PlayerStateExitingVehicle;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerStartExitFromVehicle);
}

void NetworkManager::HandlePlayerFinishExitFromVehicle(NetworkPlayerFinishExitFromVehicleData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}
	if (playm.playerbuffer[client]->state != PlayerStateExitingVehicle)
	{
		return;
	}
	playm.playerbuffer[client]->state = PlayerStateOnFoot;
	playm.playerbuffer[client]->vehicleindex = INVALID_VEHICLE_INDEX;
	playm.playerbuffer[client]->seatindex = INVALID_VEHICLE_INDEX;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerFinishExitFromVehicle);
}

void NetworkManager::HandlePlayerSpawnRequest(NetworkPlayerSpawnRequestData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}
	NetworkPlayerSpawnData data2;
	playm.playerbuffer[client]->armor = 0;
	playm.playerbuffer[client]->health = 200;
	playm.playerbuffer[client]->room = 0;
	vmm.OnPlayerSpawn(client);
	data2.armor = playm.playerbuffer[client]->armor;
	data2.health = playm.playerbuffer[client]->health;
	data2.model = playm.playerbuffer[client]->model;
	memcpy(data2.position, playm.playerbuffer[client]->spawnposition, sizeof(float) * 4);
	data2.room = playm.playerbuffer[client]->room;
	memcpy(data2.compD, playm.playerbuffer[client]->compD, sizeof(int) * 11);
	memcpy(data2.compT, playm.playerbuffer[client]->compT, sizeof(int) * 11);
	data2.client = client;
	this->SendDataToAll(&data2, NetworkPackPlayerSpawn, 1);

	NetworkGameTimeChangeData timedata;
	server.GetGameTime(timedata.time);
	this->SendDataToOne(client, &timedata, NetworkPackGameTimeChange);
}

void NetworkManager::HandlePlayerModelChange(NetworkPlayerModelChangeData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}
	playm.playerbuffer[client]->model = data->model;
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerModelChange, 1);
}

void NetworkManager::HandlePlayerComponentsChange(NetworkPlayerComponentsChangeData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;

	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}
	memcpy(playm.playerbuffer[client]->compD, data->compD, sizeof(int) * 11);
	memcpy(playm.playerbuffer[client]->compT, data->compT, sizeof(int) * 11);
	this->SendDataToAllExceptOne(client, data, NetworkPackPlayerComponentsChange);
}

void NetworkManager::HandlePlayerChat(NetworkPlayerChatData *data, const SystemAddress sa)
{
	short client = this->GetClientIndex(sa);
	if (client == INVALID_PLAYER_INDEX) return;
	data->client = client;

	if(wcslen(data->message) == 0) return;

	for(char i = 1; i != wcslen(data->message); i++)
	{
		if(data->message[i] < 32) data->message[i] = L' ';
	}

	if(data->message[0] == server.GetCmdChars(0) || data->message[0] == server.GetCmdChars(1))
	{
		char offset = 0;
		for(char i = 1; i != wcslen(data->message); i++)
		{
			if(data->message[i] == L' ') { offset = i; data->message[i] = 0; break; }
		}
		if(offset == 1) return;

		vmm.OnPlayerCommandText(client, data->message + 1, data->message + offset + 1);
		return;
	}
	else
	{
		if (!vmm.OnPlayerText(client, data->message))
		{
			return;
		}
	}
	wchar_t tempstring[MAX_CHAT_MESSAGE_LENGTH];
	_snwprintf(tempstring, MAX_CHAT_MESSAGE_LENGTH, L"%s: %s", playm.playerbuffer[data->client]->name, data->message);
	tempstring[MAX_CHAT_MESSAGE_LENGTH-1] = L'\0';
	Log::Info(tempstring);
	wcscpy(data->message, tempstring);
	this->SendDataToAll(data, NetworkPackPlayerChat);
}

short NetworkManager::RegisterNewClient(const SystemAddress address)
{
	short index = this->GetClientFreeSlot();
	if (index == INVALID_PLAYER_INDEX)
	{
		return INVALID_PLAYER_INDEX;
	}
	if (index >= clientbuffersize)
	{
		if (clientbuffersize == maxclientbuffersize)
		{
			return INVALID_PLAYER_INDEX;
		}
		if (!ResizeBuffer<Client **>(clientbuffer, index + 1))
		{
			return INVALID_PLAYER_INDEX;
		}
		clientbuffer[index] = NULL;
		clientbuffersize = index + 1;
	}
	clientbuffer[index] = new Client;
	clientbuffer[index]->address = address;
	return index;
}

void NetworkManager::HandleClientDisconnection(const SystemAddress address, const DefaultMessageIDTypes type)
{
	short client = this->GetClientIndex(address);
	if (client == INVALID_PLAYER_INDEX)
	{
		return;
	}
	if ((client < 0) || (client >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[client] == NULL)
	{
		return;
	}
	vmm.OnPlayerDisconnect(client);
	Log::Info(L"Player %s disconnected", playm.playerbuffer[client]->name);
	delete playm.playerbuffer[client];
	playm.playerbuffer[client] = NULL;
	playm.numplayers--;
	if ((client < 0) && (client >= clientbuffersize))
	{
		return;
	}
	if (clientbuffer[client] == NULL)
	{
		return;
	}
	delete clientbuffer[client];
	clientbuffer[client] = NULL;
	NetworkPlayerDisconnectionData data;
	data.client = client;
	this->SendDataToAll(&data, NetworkPackPlayerDisconnection, 1);
	server.UpdateServerInfo();
}

short NetworkManager::GetClientIndex(const SystemAddress address)
{
	//TODO: Optimize using currently connected players, not buffer size.
	for (short index = 0; index < clientbuffersize; index++)
	{
		if ((clientbuffer[index] != NULL) && (clientbuffer[index]->address == address))
		{
			return index;
		}
	}
	return INVALID_PLAYER_INDEX;
}

short NetworkManager::GetClientFreeSlot(void)
{
	short index;
	for (index = 0; index < clientbuffersize; index++)
	{
		if (clientbuffer[index] == NULL)
		{
			return index;
		}
	}
	if (clientbuffersize == maxclientbuffersize)
	{
		return INVALID_PLAYER_INDEX;
	}
	return index;
}


NetworkPlayerFullUpdateData *NetworkManager::GetPlayerFullUpdateData(const short index)
{
	if ((index < 0) || (index >= clientbuffersize))
	{
		return NULL;
	}
	if (clientbuffer[index] == NULL)
	{
		return NULL;
	}
	if ((index < 0) || (index >= playm.playerbuffersize))
	{
		return NULL;
	}
	if (playm.playerbuffer[index] == NULL)
	{
		return NULL;
	}
	NetworkPlayerFullUpdateData *data = (NetworkPlayerFullUpdateData*)new char[sizeof(NetworkPlayerFullUpdateData)];
	data->index = index;
	wcscpy(data->name, playm.playerbuffer[index]->name);
	data->model = playm.playerbuffer[index]->model;
	memcpy(data->position, playm.playerbuffer[index]->position, sizeof(float) * 3);
	data->angle = playm.playerbuffer[index]->angle;
	data->vehicleindex = playm.playerbuffer[index]->vehicleindex;
	data->seatindex = playm.playerbuffer[index]->seatindex;
	data->score = playm.playerbuffer[index]->score;
	data->health = playm.playerbuffer[index]->health;
	data->armor = playm.playerbuffer[index]->armor;
	data->room = playm.playerbuffer[index]->room;
	memcpy(data->weapons, playm.playerbuffer[index]->weapons, sizeof(char) * 8);
	memcpy(data->ammo, playm.playerbuffer[index]->ammo, sizeof(short) * 8);
	memcpy(data->color, playm.playerbuffer[index]->color, sizeof(unsigned char) * 4);
	return data;
}

NetworkVehicleFullUpdateData *NetworkManager::GetVehicleFullUpdateData(const short index)
{
	if ((index < 0) || (index >= vm.vehiclebuffersize))
	{
		return NULL;
	}
	if (vm.vehiclebuffer[index] == NULL)
	{
		return NULL;
	}
	NetworkVehicleFullUpdateData *data = (NetworkVehicleFullUpdateData *)new char[sizeof(NetworkVehicleFullUpdateData)];
	data->index = index;
	data->model = vm.vehiclebuffer[index]->model;
	memcpy(data->position, vm.vehiclebuffer[index]->position, sizeof(float) * 3);
	data->angle = vm.vehiclebuffer[index]->angle[1];
	memcpy(data->color, vm.vehiclebuffer[index]->color, sizeof(unsigned char) * 2);
	return data;
}

void NetworkManager::KickPlayer(const short index)
{
	if ((index < 0) || (index >= clientbuffersize))
	{
		return;
	}
	if (clientbuffer[index] == NULL)
	{
		return;
	}
	if ((index < 0) || (index >= playm.playerbuffersize))
	{
		return;
	}
	if (playm.playerbuffer[index] == NULL)
	{
		return;
	}

	net->CloseConnection(clientbuffer[index]->address, true);

	delete playm.playerbuffer[index];
	playm.playerbuffer[index] = NULL;
	playm.numplayers--;

	delete clientbuffer[index];
	clientbuffer[index] = NULL;
}

void NetworkManager::BanPlayer(const short index)
{
	if ((index < 0) || (index >= clientbuffersize))
	{
		return;
	}
	if (clientbuffer[index] == NULL)
	{
		return;
	}

	net->AddToBanList(clientbuffer[index]->address.ToString(0));
	badnick.push_back(playm.GetPlayerName(index));
	
	FILE * banlist = fopen("ban.list", "a");
	if(banlist) 
	{
		fwprintf(banlist, L"%s\t%s\n", playm.GetPlayerName(index), clientbuffer[index]->address.ToString(0));	
		fclose(banlist);
	}
	this->KickPlayer(index);
}

void NetworkManager::ClearBanList()
{
	net->ClearBanList();
	badnick.clear();

	FILE * banlist = fopen("ban.list", "w");
	if(banlist) fclose(banlist);
}

void NetworkManager::ReloadBanList()
{
	net->ClearBanList();
	badnick.clear();
	this->LoadBanList();
}

void NetworkManager::LoadBanList()
{
	FILE * banlist = fopen("ban.list", "r");
	if(banlist)
	{
		int idx = 0;
		wchar_t nick[32];
		char ip[32];

		while(!feof(banlist))
		{
			fwscanf(banlist, L"%s\t%s\n", &nick, &ip);
			net->AddToBanList(ip);
			badnick.push_back(nick);
		}
		fclose(banlist);
	}
}

/*************************************************************************************************************************
**																														**
**					NetworkManager Send functions																		**
**																														**
*************************************************************************************************************************/

bool NetworkManager::SendGameTimeChangeToAll(const unsigned char time[2])
{
	NetworkGameTimeChangeData data;
	memcpy(data.time, time, sizeof(unsigned char) * 2);
	this->SendDataToAll(&data, NetworkPackGameTimeChange);
	return true;
}

bool NetworkManager::SendPlayerModelChangeToAll(const short index)
{
	if ((index < 0) || (index >= playm.playerbuffersize))
	{
		return false;
	}
	if (playm.playerbuffer[index] == NULL)
	{
		return false;
	}
	NetworkPlayerModelChangeData data;
	data.client = index;
	data.model = playm.playerbuffer[index]->model;
	this->SendDataToAll(&data, NetworkPackPlayerModelChange, 1);
	return true;
}

bool NetworkManager::SendPlayerWeaponGiftToAll(const short index, const eWeaponSlot slot)
{
	if ((index < 0) || (index >= playm.playerbuffersize))
	{
		return false;
	}
	if (playm.playerbuffer[index] == NULL)
	{
		return false;
	}
	if (playm.playerbuffer[index]->ammo[slot] == 0)
	{
		return false;
	}
	NetworkPlayerWeaponGiftData data;
	data.client = index;
	data.weapon = playm.playerbuffer[index]->weapons[slot];
	data.ammo = playm.playerbuffer[index]->ammo[slot];
	this->SendDataToAll(&data, NetworkPackPlayerWeaponGift, 2);
	return true;
}

bool NetworkManager::SendPlayerSpawnPositionChange(const short index)
{
	if ((index < 0) || (index >= playm.playerbuffersize))
	{
		return false;
	}
	if (playm.playerbuffer[index] == NULL)
	{
		return false;
	}
	NetworkPlayerSpawnPositionChangeData data;
	memcpy(data.position, playm.playerbuffer[index]->spawnposition, sizeof(float) * 4);
	return this->SendDataToOne(index, &data, NetworkPackPlayerSpawnPositionChange, 1);
}

bool NetworkManager::SendNewVehicleInfoToAll(const short index)
{
	if ((index < 0) || (index >= vm.vehiclebuffersize))
	{
		return false;
	}
	if (vm.vehiclebuffer[index] == NULL)
	{
		return false;
	}
	NetworkVehicleFullUpdateData data;
	data.index = index;
	data.model = vm.vehiclebuffer[index]->model;
	data.position[0] = vm.vehiclebuffer[index]->position[0];
	data.position[1] = vm.vehiclebuffer[index]->position[1];
	data.position[2] = vm.vehiclebuffer[index]->position[2];
	data.angle = vm.vehiclebuffer[index]->angle[1];
	data.color[0] = vm.vehiclebuffer[index]->color[0];
	data.color[1] = vm.vehiclebuffer[index]->color[2];

	this->SendDataToAll(&data, NetworkPackNewVehicle, 1);
	return true;
}

bool NetworkManager::SendPlayerPosition(const short index, const float pos[3], const float angle)
{
	//TODO: Redo.
	NetworkPlayerPositionData data;
	data.client = index;
	memcpy(data.pos, pos, 3 * sizeof(float));
	data.angle = angle;

	this->SendDataToAll(&data, NetworkPackPlayerPosition, 1);
	return true;
}

void NetworkManager::SendConnectionError(const SystemAddress address, const NetworkPlayerConnectionError error)
{
	NetworkPlayerConnectionErrorData data;
	data.error = error;
	this->SendDataTo(&data, NetworkPackPlayerConnectionError, address, 1);
}

void NetworkManager::SendChatMessageToOne(short index, const wchar_t * msg)
{
	NetworkPlayerChatData data;
	data.client = -1;
	wcscpy(data.message, msg);
	this->SendDataToOne(index, &data, NetworkPackPlayerChat);
}

void NetworkManager::SendChatMessageToAll(const wchar_t * msg)
{
	NetworkPlayerChatData data;
	data.client = -1;
	wcscpy(data.message, msg);
	this->SendDataToAll(&data, NetworkPackPlayerChat);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename DATATYPE>
void NetworkManager::SendDataToAll(const DATATYPE * data, const NetworkPackType type, const char pp)
{
	//TODO: Optimize using currently connected players, not buffer size.
	int size = sizeof(DATATYPE);
	char * pack = new char[3 + size];
	pack[0] = FMP_PACKET_SIGNATURE;
	*(short*)(pack + 1) = type;
	memcpy(pack + 3, data, size);

	for (short i = 0; i < clientbuffersize; i++)
	{
		if (clientbuffer[i] != NULL)
		{
			net->Send(pack, size + 3, (PacketPriority)pp, RELIABLE_ORDERED, NULL, clientbuffer[i]->address, false);
		}
	}
}

template <typename DATATYPE>
bool NetworkManager::SendDataToOne(const short index, const DATATYPE *data, const NetworkPackType type, const char pp)
{
	if((index < 0) && (index >= clientbuffersize))
	{
		return false;
	}
	if (clientbuffer[index] == NULL)
	{
		return false;
	}

	if(sizeof(DATATYPE) == 4)
	{
		Log::Debug(L"Bad data at %d", type);
	}

	int size = sizeof(DATATYPE);
	char * pack = new char[3 + size];
	pack[0] = FMP_PACKET_SIGNATURE;
	*(short*)(pack + 1) = type;
	memcpy(pack + 3, data, size);

	return net->Send(pack, size + 3, (PacketPriority)pp, RELIABLE_ORDERED, NULL, clientbuffer[index]->address, false);
}

template <typename DATATYPE>
void NetworkManager::SendDataToAllExceptOne(const short index, const DATATYPE *data, const NetworkPackType type, const char pp)
{
	//TODO: Optimize using currently connected players, not buffer size.
	int size = sizeof(DATATYPE);
	char * pack = new char[3 + size];
	pack[0] = FMP_PACKET_SIGNATURE;
	*(short*)(pack + 1) = type;
	memcpy(pack + 3, data, size);

	for (unsigned char i = 0; i < clientbuffersize; i++)
	{
		if ((i != index) && (clientbuffer[i] != NULL))
		{
			net->Send(pack, size + 3, (PacketPriority)pp, RELIABLE_ORDERED, NULL, clientbuffer[i]->address, false);
		}
	}
}

template <typename DATATYPE>
bool NetworkManager::SendDataTo(const DATATYPE *data, const NetworkPackType type, const SystemAddress addr, const char pp)
{
	int size = sizeof(DATATYPE);
	char * pack = new char[3 + size];
	pack[0] = FMP_PACKET_SIGNATURE;
	*(short*)(pack + 1) = type;
	memcpy(pack + 3, data, size);

	return net->Send(pack, size + 3, (PacketPriority)pp, RELIABLE_ORDERED, NULL, addr, false);
}