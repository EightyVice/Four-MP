#include <stdio.h>
#include "CNetwork.h"
#include "log/log.h"

CNetwork::CNetwork()
{
	m_pNet = NULL;
	m_pPlayerAddress = NULL; 
	iMaxPlayers = 0;
}

CNetwork::~CNetwork()
{
	this->Unload();
}

bool CNetwork::Load(const unsigned short iPort, const unsigned short iMaxPlayers)
{
	m_pNet = RakNetworkFactory::GetRakPeerInterface();
	SocketDescriptor s(iPort, 0);
	m_pNet->SetMaximumIncomingConnections(iMaxPlayers);
	m_pNet->Startup(iMaxPlayers, 1, &s, 1);

	m_pPlayerAddress = new SystemAddress[iMaxPlayers];
	memset(m_pPlayerAddress, 0, sizeof(SystemAddress) * iMaxPlayers);

	this->iMaxPlayers = iMaxPlayers;

	this->LoadBanList();
	return true;
}

bool CNetwork::Unload()
{
	if(m_pPlayerAddress) 
	{
		for(int i = 0; i < iMaxPlayers; i++)
			if(m_pPlayerAddress[i].port != 0) this->HandleDisconnection(m_pPlayerAddress[i]);

		delete [] m_pPlayerAddress;
	}
	if (m_pNet)
	{
		m_pNet->Shutdown(100,0);
		RakNetworkFactory::DestroyRakPeerInterface(m_pNet);
	}
	return true;
}

bool CNetwork::IsReady()
{
	return this->m_pNet != NULL;
}

short CNetwork::GetIdFromAddress(SystemAddress saAddr)
{
	for(int i = 0; i < iMaxPlayers; i++)
		if(m_pPlayerAddress[i] == saAddr) return i;

	return -1;
}

short CNetwork::GetFreeClientId()
{
	for(int i = 0; i < iMaxPlayers; i++)
		if(m_pPlayerAddress[i].port == 0) return i;
	return -1;
}

void CNetwork::Tick()
{
	static Packet * pPack;
	for (pPack = m_pNet->Receive(); pPack; m_pNet->DeallocatePacket(pPack), pPack = m_pNet->Receive())
	{
		switch (pPack->data[0])
		{
		case FMP_PACKET_SIGNATURE:
			{
				this->HandlePacket(pPack->data + 1, pPack->length - 1, pPack->systemAddress);
			} break;
		case ID_CONNECTION_REQUEST:
			{
				Log::Debug(L"New connection request");
			} break;
		case ID_NEW_INCOMING_CONNECTION:
			{
				Log::Debug(L"New connection from %S", pPack->systemAddress.ToString(1));
			} break;
		case ID_DISCONNECTION_NOTIFICATION:
			{
				this->HandleDisconnection(pPack->systemAddress);
			} break;
		case ID_CONNECTION_LOST:
			{
				this->HandleDisconnection(pPack->systemAddress);
			} break;
		}
	}
}

void CNetwork::HandlePacket(const unsigned char * pData, const unsigned int dwLength, const SystemAddress saAddr)
{
	short sType = *(short *)(pData);
	switch(sType)
	{
	case NetworkData::NetworkConnect:
		{
			this->HandleConnect((NetworkData::Connect *)(pData + 2), dwLength, saAddr); 
		} break;
	default:
		{
			Log::Warning("Unknown packet %d (Length: %d) from %s", sType, dwLength, saAddr.ToString());
		} break;
	}
}

void CNetwork::HandleConnect(const NetworkData::Connect * pData, const unsigned int dwLength, const SystemAddress saAddr)
{
	if(pData->version < FMP_NETWORK_VERSION)
	{
		this->SendClientConnect(-1, NetworkData::CR_OLDFMP, saAddr);
		return;
	}

	short iID = this->GetIdFromAddress(saAddr);
	if(iID > 0 && iID < iMaxPlayers)
	{
		this->SendClientConnect(iID, NetworkData::CR_OK, saAddr);
		return;
	}
	iID = this->GetFreeClientId();
	if(iID < 0 || iID >= iMaxPlayers)
	{
		this->SendClientConnect(iID, NetworkData::CR_NOFREESLOTS, saAddr);
		return;
	}

	for(int i = 0; i < m_vBadNick.size(); i++)
	{
		if(wcscmp(m_vBadNick.at(i), pData->nick) == 0)
		{
			this->SendClientConnect(iID, NetworkData::CR_BANNED, saAddr);
			return;
		}
	}

	TODO("Nick check");
	TODO("Send to script");

	this->SendClientConnect(iID, NetworkData::CR_OK, saAddr);
}

void CNetwork::HandleDisconnection(const SystemAddress saAddr)
{
	short iID = GetIdFromAddress(saAddr);
	if(iID > 0 && iID < iMaxPlayers)
	{
		this->SendClientDisconnect(iID);
		memset(&m_pPlayerAddress[iID], 0, sizeof(SystemAddress));
	}
}