#pragma once
#include <vector>
#include "../main.h"
#include "RakNet/RakPeerInterface.h"
#include "RakNet/RakNetworkFactory.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/MessageIdentifiers.h"
#include "NetworkData.h"

class CNetwork
{
public:
	CNetwork();
	~CNetwork();

	bool Load(const unsigned short iPort, const unsigned short iMaxPlayers);
	bool Unload();

	void Tick();
	bool IsReady();

	void CloseConnection(const SystemAddress addr);
	void AddToBanList(const SystemAddress addr, wchar_t * pszNick);
	void ClearBanList();
	void ReloadBanList();
	void LoadBanList();

	bool SendClientConnect(const short iID, const char iResult, const SystemAddress saAddr);
	bool SendClientDisconnect(const short iID);

private:
	RakPeerInterface * m_pNet;
	std::vector<wchar_t *> m_vBadNick;
	SystemAddress * m_pPlayerAddress;
	short iMaxPlayers;

	void HandlePacket(const unsigned char * pData, const unsigned int dwLength, const SystemAddress saAddr);

	void HandleConnect(const NetworkData::Connect * pData, const unsigned int dwLength, const SystemAddress saAddr); 
	void HandleDisconnection(const SystemAddress saAddr);

	short GetFreeClientId();
	short GetIdFromAddress(SystemAddress saAddr);

	template <typename DATATYPE> 
	bool SendTo(const short iPlayer, const DATATYPE * pData, const NetworkData::eTypes iType, const char PackPriority = 2);
	template <typename DATATYPE> 
	bool SendToAll(const DATATYPE * pData, const NetworkData::eTypes iType, const short iExceptPlayer = -1, const char PackPriority = 2);
	template <typename DATATYPE> 
	bool SendTo(const SystemAddress sysAddr, const DATATYPE * pData, const NetworkData::eTypes iType, const char PackPriority = 2);
};