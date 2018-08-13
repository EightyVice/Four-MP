#include "../../Shared/RakNet/RakPeerInterface.h"
#include "../../Shared/RakNet/RakNetworkFactory.h"
#include "../../Shared/RakNet/MessageIdentifiers.h"
#include "../../Shared/RakNet/GetTime.h"
#include "../../Shared/RakNet/BitStream.h"

#include "NetworkManager.h"
#include "ClientCore.h"
#include "../../Shared/Console/common.h"
#include "../../Shared/logging/log.h"
#if defined (FMP_CLIENT)
#include "../FMP/Hook/classes.h"
#include "../FMP/PlayerManager.h"
#include "../FMP/VehicleManager.h"
#include "../FMP/masterserver.h"
#include "../FMP/d3d9/gui.h"
#include "../FMP/ChatManager.h"
#elif defined (FMP_CONSOLE_CLIENT)
#include "../../Shared/Console/ConsoleScreen.h"
#endif

extern ClientCore client;
#if defined (FMP_CLIENT)
extern FMPHook HOOK;
extern FMPGUI Gui;
extern ChatManager chat;

extern FPlayer gPlayer[MAX_PLAYERS];
extern FVehicle gVehicle[MAX_VEHICLES];
#endif

NetworkManager::NetworkManager(void)
{
	net = NULL;
}

NetworkManager::~NetworkManager(void)
{
	if (net)
	{
		net->Shutdown(100,0);
		RakNetworkFactory::DestroyRakPeerInterface(net);
	}
}

void NetworkManager::Load(void)
{
	net = RakNetworkFactory::GetRakPeerInterface();
	SocketDescriptor socketDescriptor(0,0);
	net->Startup(1, 1, &socketDescriptor, 1);
}

void NetworkManager::Tick(void)
{
	static Packet *pack;
	for (pack = net->Receive(); pack; net->DeallocatePacket(pack), pack = net->Receive())
	{
		Log::Debug(L"%02X %02X %02X %02X %02X %02X", pack->data[0], pack->data[1], pack->data[2], pack->data[3], pack->data[4], pack->data[5]); 
		switch(pack->data[0])
		{
		case FMP_PACKET_SIGNATURE:
			{
				HandleOurPacket(pack->data + 1, pack->length - 1, pack->systemAddress);	
			} break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				Log::Info(L"Connection accepted. Sending client info...");
				this->SendClientConnectionRequest();
			} break;
		case ID_ALREADY_CONNECTED:
			{
				Log::Info(L"Already connected");
				//clientstate.game = GameStateInGame;
			} break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			{
				Log::Info(L"No free connections");
				client.SetGameState(GameStateOffline);
			} break;
		case ID_DISCONNECTION_NOTIFICATION:
			{
				Log::Info(L"You have been kicked from the server.");
#ifdef FMP_CLIENT 
				HOOK.PlayerDisconnect(client.GetIndex());
#endif
				client.SetGameState(GameStateOffline);
			} break;
		case ID_CONNECTION_LOST:
			{
				Log::Info(L"Lost connection to the server.");
#ifdef FMP_CLIENT
				HOOK.PlayerDisconnect(client.GetIndex());
#endif
				client.SetGameState(GameStateOffline);
			} break;
		case ID_CONNECTION_BANNED:
			{
				Log::Info(L"You are banned from the server.");
				client.SetGameState(GameStateOffline);
				client.SetGameState(GameStateOffline);
			} break;
		case ID_INVALID_PASSWORD:
			{
				Log::Info(L"Invalid password");
				client.SetGameState(GameStateOffline);
			} break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			{
				Log::Info(L"Connection failed");
				client.SetGameState(GameStateOffline);
#ifdef FMP_CLIENT
				wchar_t str[128];
				swprintf(str, L"Can't connect to %S", pack->systemAddress.ToString());
				Gui.Message(str);
#endif
			} break;
		case ID_PONG:
			{
#if defined (FMP_CLIENT)
				Log::Info(L"RakNet: Pong");
				RakNetTime time, dataLength;
				RakNet::BitStream pong( pack->data+1, sizeof(RakNetTime), false);
				pong.Read(time);
				dataLength = pack->length - sizeof(unsigned char) - sizeof(RakNetTime);
				Log::Debug(L"Create tmp info");
				ServerInfo *tmp_msi = new ServerInfo;
				tmp_msi->ping = (unsigned int)(RakNet::GetTime()-time);

				Log::Debug(L"ID_PONG from SystemAddress:%u:%u.", pack->systemAddress.binaryAddress, pack->systemAddress.port);
				Log::Debug(L"Time is %i",time);
				Log::Debug(L"Ping is %i", tmp_msi->ping);
				Log::Debug(L"Data is %i bytes long.", dataLength);

				if (dataLength > 0)
				{
					char tempname[256];
					char tempmode[128];
					char temploc[128];
					char tempclan[128];
					unsigned char *data = pack->data+sizeof(unsigned char)+sizeof(RakNetTime);
					sscanf((char*)data, "%[^\1]\1%[^\1]\1%[^\1]\1%d\1%d\1%d\1%[^\1]\1\0", &tempname, &tempmode, &temploc, 
					&tmp_msi->players, &tmp_msi->maxplayers, &tmp_msi->password, &tempclan);
					mbstowcs(tmp_msi->name, tempname, 128);
					mbstowcs(tmp_msi->mode, tempmode, 64);
					mbstowcs(tmp_msi->loc, temploc, 64);
					mbstowcs(tmp_msi->clan, tempclan, 64);
				}
				strcpy_s(tmp_msi->ip, 64, pack->systemAddress.ToString(0));
				tmp_msi->port = pack->systemAddress.port;
				Gui.UpdateServer(tmp_msi);
#endif
			} break;
		default:
			{
				Log::Info(L"RakNet: Unknown message (0x%x)", pack->data[0]);
			} break;
		}
	}
}

void NetworkManager::HandleOurPacket(unsigned char * pack, unsigned int length, SystemAddress sa)
{
	short type = *(short*)pack;

	Log::Debug(L"Type %d - Length %d", type, length);

	switch (type)
	{
	case NetworkPackPlayerConnection:
		{
			NetworkPlayerFullUpdateData data = *(NetworkPlayerFullUpdateData*)(pack + 2);

#if defined (FMP_CLIENT)
			Log::Info(L"New player connection. Name is %s", data.name);
			gPlayer[data.index].model = data.model;
			memcpy(gPlayer[data.index].position, data.position, sizeof(float) * 3);
			gPlayer[data.index].angle = data.angle;
			gPlayer[data.index].vehicleindex = data.vehicleindex;
			gPlayer[data.index].seatindex = data.seatindex;
			gPlayer[data.index].score = data.score;
			gPlayer[data.index].health = data.health;
			gPlayer[data.index].armor = data.armor;
			gPlayer[data.index].room = data.room;
			memcpy(gPlayer[data.index].weapons, data.weapons, sizeof(char) * 8);
			memcpy(gPlayer[data.index].ammo, data.ammo, sizeof(short) * 8);
			memcpy(gPlayer[data.index].color, data.color, sizeof(unsigned char) * 4);

			HOOK.PlayerConnect(data.name, data.index, gPlayer[data.index].model, gPlayer[data.index].position);
#endif
		} break;
	case NetworkPackPlayerConnectionError:
		{
			NetworkPlayerConnectionErrorData data = *(NetworkPlayerConnectionErrorData*)(pack + 2);

			switch (data.error)
			{
			case NetworkPlayerConnectionErrorServerFull:
				{
					Log::Info(L"Connection error: Server is full.");
				} break;
			case NetworkPlayerConnectionErrorInvalidProtocol:
				{
					Log::Info(L"Connection error: Server is using different protocol.");
				} break;
			case NetworkPlayerConnectionErrorInvalidName:
				{
					Log::Info(L"Connection error: Invalid user name.");
				} break;
			case NetworkPlayerConnectionErrorBanned:
				{
					Log::Info(L"Connection error: Banned.");
				} break;
			case NetworkPlayerConnectionErrorInvalidAuth:
				{
					Log::Info(L"Connection error: You have failed to pass an authentication.");
				} break;
			case NetworkPlayerConnectionErrorAlreadyConnected:
				{
					Log::Info(L"Connection error: You are already connected.");
				} break;
			case NetworkPlayerConnectionErrorAllocationError:
				{
					Log::Info(L"Connection error: Server was unable to allocate player resources.");
				} break;
			case NetworkPlayerConnectionErrorScriptLock:
				{
					Log::Info(L"Connection error: Connection has been refused by a server script.");
				} break;
			}
		} break;
	case NetworkPackPlayerInfo:
		{
			NetworkPlayerInfoData data = *(NetworkPlayerInfoData*)(pack + 2);

			if (data.sessionkey != client.GetSessionKey())
			{
				return;
			}
			client.SetIndex(data.index);

			NetworkPlayerConnectionConfirmationData data2;
			this->SendDataToServer(&data2, NetworkPackPlayerConnectionConfirmation, 1);
		} break;
	case NetworkPackPlayerDisconnection:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerDisconnectionData data = *(NetworkPlayerDisconnectionData*)(pack + 2);
			HOOK.PlayerDisconnect(data.client);
#endif
		} break;
	case NetworkPackGameTimeChange:
		{
#if defined (FMP_CLIENT)
			NetworkGameTimeChangeData data = *(NetworkGameTimeChangeData*)(pack + 2);
			HOOK.SetTime(data.time);
#endif
		} break;
	case NetworkPackPlayerFullUpdate:
		{
			NetworkPlayerFullUpdateData data = *(NetworkPlayerFullUpdateData*)(pack + 2);
#if defined (FMP_CLIENT)
			//TODO: Do NOT load at connect, redo the whole thing.
			gPlayer[data.index].model = data.model;
			memcpy(gPlayer[data.index].position, data.position, sizeof(float) * 3);
			gPlayer[data.index].angle = data.angle;
			gPlayer[data.index].vehicleindex = data.vehicleindex;
			gPlayer[data.index].seatindex = data.seatindex;
			gPlayer[data.index].score = data.score;
			gPlayer[data.index].health = data.health;
			gPlayer[data.index].armor = data.armor;
			gPlayer[data.index].room = data.room;
			memcpy(gPlayer[data.index].weapons, data.weapons, sizeof(char) * 8);
			memcpy(gPlayer[data.index].ammo, data.ammo, sizeof(short) * 8);
			memcpy(gPlayer[data.index].color, data.color, sizeof(unsigned char) * 4);

			Log::Info(L"Recieving player full update. Name is %s", data.name);
			HOOK.PlayerConnect(data.name, data.index, gPlayer[data.index].model, gPlayer[data.index].position);
#elif defined (FMP_CONSOLE_CLIENT)
			Log::Info(L"Recieving player full update. Name is %s", data.name);
#endif
		} break;
	case NetworkPackVehicleFullUpdate:
		{
#if defined (FMP_CLIENT)
			NetworkVehicleFullUpdateData data = *(NetworkVehicleFullUpdateData*)(pack + 2);
			
			//TODO: Do NOT load at connect, redo the whole thing.
			HOOK.CreateCar(data.index, data.model, data.position, data.angle, data.color);
#endif
		} break;
	case NetworkPackPlayerFootSync:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerFootData data = *(NetworkPlayerFootData*)(pack + 2);
			Log::Debug(L"Foot %d", data.client);
			HOOK.PlayerFootSync(&data);
#endif
		} break;
	case NetworkPackPlayerVehicleSync:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerVehicleData data = *(NetworkPlayerVehicleData*)(pack + 2);
			HOOK.PlayerVehicleSync(&data);
#endif
		} break;
	case NetworkPackPlayerStartEntranceInVehicle:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerStartEntranceInVehicleData data = *(NetworkPlayerStartEntranceInVehicleData*)(pack + 2);
			HOOK.StartEnterInVehicle(data.client, data.vehicleindex, data.seatindex);
#endif
		} break;
	case NetworkPackPlayerCancelEntranceInVehicle:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerCancelEntranceInVehicleData data = *(NetworkPlayerCancelEntranceInVehicleData*)(pack + 2);
			HOOK.CancelEnterInVehicle(data.client);
#endif
		} break;
	case NetworkPackPlayerFinishEntranceInVehicle:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerFinishEntranceInVehicleData data = *(NetworkPlayerFinishEntranceInVehicleData*)(pack + 2);
			HOOK.FinishEnterInVehicle(data.client);
#endif
		} break;
	case NetworkPackPlayerStartExitFromVehicle:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerStartExitFromVehicleData data = *(NetworkPlayerStartExitFromVehicleData*)(pack + 2);
			HOOK.StartExitFromVehicle(data.client);
#endif
		} break;
	case NetworkPackPlayerFinishExitFromVehicle:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerFinishExitFromVehicleData data = *(NetworkPlayerFinishExitFromVehicleData*)(pack + 2);
			HOOK.FinishExitFromVehicle(data.client);
#endif
		} break;
	case NetworkPackPlayerWeaponGift:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerWeaponGiftData data = *(NetworkPlayerWeaponGiftData*)(pack + 2);
			HOOK.PlayerRecieveWeapon(data.client, data.weapon, data.ammo);
#endif
		} break;
	case NetworkPackPlayerSpawnPositionChange:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerSpawnPositionChangeData data = *(NetworkPlayerSpawnPositionChangeData*)(pack + 2);
			HOOK.SetSpawnPosition(data.position);
#endif
		} break;
	case NetworkPackPlayerSpawn:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerSpawnData data = *(NetworkPlayerSpawnData*)(pack + 2);

			Log::Info(L"Setup player spawn info %d", data.client);
			gPlayer[data.client].model = data.model;
			memcpy(&gPlayer[data.client].compD, &data.compD, 11 * sizeof(int));
			memcpy(&gPlayer[data.client].compT, &data.compT, 11 * sizeof(int));
			gPlayer[data.client].armor = data.armor;
			gPlayer[data.client].health = data.health;
			gPlayer[data.client].room = data.room;
			HOOK.xPlayerSpawn(data);
#endif
		} break;
	case NetworkPackPlayerModelChange:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerModelChangeData data = *(NetworkPlayerModelChangeData*)(pack + 2);
			HOOK.PlayerSyncSkin(data.client, data.model);
#endif
		} break;
	case NetworkPackPlayerComponentsChange:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerComponentsChangeData data = *(NetworkPlayerComponentsChangeData*)(pack + 2);
			HOOK.PlayerSyncSkinVariation(data.client, data.compD, data.compT);
#endif
		} break;
	case NetworkPackPlayerChat:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerChatData data = *(NetworkPlayerChatData*)(pack + 2);
			Log::Info(L"MSG: %s", data.message);
			chat.AddChatMessage(data.message);
#endif
		} break;
	case NetworkPackNewVehicle:
		{
#if defined (FMP_CLIENT)
			NetworkVehicleFullUpdateData data = *(NetworkVehicleFullUpdateData*)(pack + 2);
			HOOK.CreateCar(data.index, data.model, data.position, data.angle, data.color);
#endif
		} break;
	case NetworkPackPlayerPosition:
		{
#if defined (FMP_CLIENT)
			NetworkPlayerPositionData data = *(NetworkPlayerPositionData*)(pack + 2);
			HOOK.SetPosition(data.client, data.pos, data.angle);
#endif
		} break;
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
}

void NetworkManager::Ping(const char *hostname, const unsigned short port)
{
	net->Ping(hostname, port, false);
}

void NetworkManager::ConnectToServer(const char *hostname, const unsigned short port)
{
//#if defined (FMP_CLIENT)
	Log::Info(L"Connecting to server...");
	GameState state = client.GetGameState();
	if(state == GameStateOffline)
	{
		net->Connect(hostname, port, 0, 0, 0);
		serveraddress.SetBinaryAddress(hostname);
		serveraddress.port = port;
	}
	else if(state == GameStateConnecting)
	{
		net->Connect(serveraddress.ToString(0), serveraddress.port, 0, 0, 0);
	}
	client.SetGameState(GameStateConnecting);
/*#elif defined (FMP_CONSOLE_CLIENT)
	PrintToConsole(L"Connecting to server...");
	net->Connect(hostname, port, 0, 0, 0);
	serveraddress.SetBinaryAddress(hostname);
	serveraddress.port = port;
#endif*/
}

void NetworkManager::SendClientConnectionRequest(void)
{
	NetworkPlayerConnectionRequestData data;
	data.protocol = PROTOCOL_VERSION;
	wchar_t *name = client.GetName();
	wcscpy(data.name, name);
	free(name);
	data.sessionkey = client.GetSessionKey();
	data.fmpid = client.GetFMPID();
	this->SendDataToServer(&data, NetworkPackPlayerConnectionRequest, 1);
}

void NetworkManager::SendPlayerFootSync(NetworkPlayerFootData data)
{
	this->SendDataToServer(&data, NetworkPackPlayerFootSync, 1);
}

void NetworkManager::SendPlayerVehicleSync(NetworkPlayerVehicleData data)
{
	this->SendDataToServer(&data, NetworkPackPlayerVehicleSync, 1);
}

void NetworkManager::SendPlayerStartEntranceInVehicle(void)
{
	NetworkPlayerStartEntranceInVehicleData data;
#if defined (FMP_CLIENT)
	data.vehicleindex = gPlayer[client.GetIndex()].vehicleindex;
	data.seatindex = gPlayer[client.GetIndex()].seatindex;
#endif
	this->SendDataToServer(&data, NetworkPackPlayerStartEntranceInVehicle);
}

void NetworkManager::SendPlayerCancelEntranceInVehicle(void)
{
	NetworkPlayerCancelEntranceInVehicleData data;
	this->SendDataToServer(&data, NetworkPackPlayerCancelEntranceInVehicle);
}

void NetworkManager::SendPlayerFinishEntranceInVehicle(void)
{
	NetworkPlayerFinishEntranceInVehicleData data;
	this->SendDataToServer(&data, NetworkPackPlayerFinishEntranceInVehicle);
}

void NetworkManager::SendPlayerStartExitFromVehicle(void)
{
	NetworkPlayerStartExitFromVehicleData data;
	this->SendDataToServer(&data, NetworkPackPlayerStartExitFromVehicle);
}

void NetworkManager::SendPlayerFinishExitFromVehicle(void)
{
	NetworkPlayerFinishExitFromVehicleData data;
	this->SendDataToServer(&data, NetworkPackPlayerFinishExitFromVehicle);
}

void NetworkManager::SendPlayerSpawnRequest(void)
{
	NetworkPlayerSpawnRequestData data;
	this->SendDataToServer(&data, NetworkPackPlayerSpawn);
}

void NetworkManager::SendPlayerModelChange(void)
{
	NetworkPlayerModelChangeData data;
#if defined (FMP_CLIENT)
	data.model = gPlayer[client.GetIndex()].model;
#endif
	this->SendDataToServer(&data, NetworkPackPlayerModelChange);
}

void NetworkManager::SendPlayerComponentsChange(void)
{
	NetworkPlayerComponentsChangeData data;
#if defined (FMP_CLIENT)
	memcpy(data.compD, gPlayer[client.GetIndex()].compD, sizeof(int) * 11);
	memcpy(data.compT, gPlayer[client.GetIndex()].compT, sizeof(int) * 11);
#endif
	this->SendDataToServer(&data, NetworkPackPlayerComponentsChange);
}

void NetworkManager::SendPlayerChat(const wchar_t *message)
{
	if (message == NULL)
	{
		return;
	}
	NetworkPlayerChatData data;
#if defined (FMP_CLIENT)
	wcscpy(data.message, message);
#endif
	this->SendDataToServer(&data, NetworkPackPlayerChat, 1);
}

template <typename DATATYPE>
void NetworkManager::SendDataToServer(const DATATYPE * data, const NetworkPackType type, const char pp)
{
	int size = sizeof(DATATYPE);
	char * pack = new char[3 + size];
	pack[0] = (char)FMP_PACKET_SIGNATURE;
	*(short*)(pack + 1) = type;
	memcpy(pack + 3, data, size);

	net->Send(pack, size + 3, (PacketPriority)pp, RELIABLE_ORDERED, NULL, serveraddress, false);
}