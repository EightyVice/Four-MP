#include <stdio.h>
#include "CNetwork.h"
#include "log/log.h"

CNetwork::CNetwork()
{
	m_pNet = NULL;
	m_pNet = RakNetworkFactory::GetRakPeerInterface();
	SocketDescriptor socketDescriptor(0,0);
	m_pNet->Startup(1, 1, &socketDescriptor, 1);
}

CNetwork::~CNetwork()
{
	if (m_pNet)
	{
		m_pNet->Shutdown(100,0);
		RakNetworkFactory::DestroyRakPeerInterface(m_pNet);
	}
}

bool CNetwork::Connect(const char * pszServer, const unsigned short iPort, const char * pszPassword)
{
	m_serverAddress.SetBinaryAddress(pszServer);
	m_serverAddress.port = iPort;

	return m_pNet->Connect(pszServer, iPort, pszPassword, strlen(pszPassword));
}

bool CNetwork::IsReady()
{
	return this->m_pNet != NULL;
}

bool CNetwork::IsConnected()
{
	return m_pNet->IsConnected(m_serverAddress);
}

template <typename DATATYPE>
bool CNetwork::Send(const DATATYPE * pData, const NetworkData::eTypes iType, const char PackPriority)
{
	if(!pData) return false;

	int iSize = sizeof(DATATYPE);
	if(iSize == 4) Log::Warning("Send %d: sizeof(pData) == 4", iType);

    char * pszData = new char[iSize + 3];
    pszData[0] = (char)FMP_PACKET_SIGNATURE;
    *(short*)(pszData + 1) = iType;
    memcpy(pszData + 3, pData, iSize);

	m_pNet->Send(pszData, iSize + 3, (PacketPriority)PackPriority, RELIABLE_ORDERED, NULL, m_serverAddress, false);

	delete pszData;

	return true;
}

bool CNetwork::SendConnect(const wchar_t * pszNick, const unsigned int dwGame)
{
	NetworkData::Connect * pConnect = new NetworkData::Connect;
	pConnect->game = dwGame;
	wcscpy(pConnect->nick, pszNick);
	pConnect->version = FMP_NETWORK_VERSION;
	bool bResult = this->Send(pConnect, NetworkData::NetworkConnect, 1);
	delete pConnect;
	return bResult;
}

bool CNetwork::Ping(const char * pszServer, const unsigned short iPort)
{
	return m_pNet->Ping(pszServer, iPort, false);
}

void CNetwork::Tick()
{
	static Packet * pPack;
	for (pPack = m_pNet->Receive(); pPack; m_pNet->DeallocatePacket(pPack), pPack = m_pNet->Receive())
	{
		switch(pPack->data[0])
		{
		case FMP_PACKET_SIGNATURE:
		{
			this->HandlePacket(pPack->data + 1, pPack->length - 1, pPack->systemAddress); 
		} break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			Log::Info(L"Connection accepted. Sending client info...");
			this->SendConnect(L"Player1", 0x1070);
		} break;
		case ID_ALREADY_CONNECTED:
		{
			Log::Info(L"Already connected");
		} break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		{
			Log::Info(L"No free connections");
		} break;
		case ID_DISCONNECTION_NOTIFICATION:
		{
			Log::Info(L"You have been kicked from the server.");
		} break;
		case ID_CONNECTION_LOST:
		{
			Log::Info(L"Lost connection to the server.");
		} break;
		case ID_CONNECTION_BANNED:
		{
			Log::Info(L"You are banned from the server.");
		} break;
		case ID_INVALID_PASSWORD:
		{
			Log::Info(L"Invalid password");
		} break;
		case ID_CONNECTION_ATTEMPT_FAILED:
		{
			Log::Info(L"Connection failed");
		} break;
		case ID_PONG:
		{
			Log::Info(L"RakNet: Pong");

			//RakNetTime time, dataLength;
			//RakNet::BitStream pong( pPack->data+1, sizeof(RakNetTime), false);
			//pong.Read(time);
			//dataLength = pPack->length - sizeof(unsigned char) - sizeof(RakNetTime);
			//unsigned int ping = (unsigned int)(RakNet::GetTime()-time);

			//Log::Debug(L"Ping %s is %d (time %d)"  pPack->systemAddress.ToString(), ping, time);
		} break;
		default:
		{
			Log::Info(L"RakNet: Unknown message (0x%x)", pPack->data[0]);
		} break;
		}
	}
}

void CNetwork::HandlePacket(const unsigned char * pData, const unsigned int dwLength, const SystemAddress saAddr)
{
	short sType = *(short *)(pData);
	switch(sType)
	{
	case NetworkData::NetworkConnectResult:
		{

		} break;
	case NetworkData::NetworkDisconnect:
		{

		} break;
	default:
		{
			Log::Warning("Unknown packet %d (Length: %d) from %s", sType, dwLength, saAddr.ToString());
		} break;
	}
}