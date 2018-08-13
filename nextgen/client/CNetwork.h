#pragma once
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

	bool Connect(const char * pszServer, const unsigned short iPort, const char * pszPassword = NULL);
	bool Ping(const char * pszServer, const unsigned short iPort);

	void Tick();
	bool IsReady();
	bool IsConnected();

	bool SendConnect(const wchar_t * pszNick, const unsigned int dwGame);


private:
	RakPeerInterface * m_pNet;
	SystemAddress m_serverAddress;

	void HandlePacket(const unsigned char * pData, const unsigned int dwLength, const SystemAddress saAddr);

	template <typename DATATYPE>
	bool Send(const DATATYPE * pData, const NetworkData::eTypes iType, const char PackPriority = 2);
};