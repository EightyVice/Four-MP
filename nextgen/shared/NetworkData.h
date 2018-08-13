#pragma once

#define FMP_PACKET_SIGNATURE 0xFF
#define FMP_NETWORK_VERSION 100

namespace NetworkData
{
	enum eTypes
	{
		NetworkConnect,
		NetworkConnectResult,
		NetworkDisconnect,
	};

	enum eConnectResult
	{
		CR_OK,
		CR_NOFREESLOTS,
		CR_BANNED,
		CR_SCRIPTKICK,
		CR_OLDFMP,
	};

	struct Connect
	{
		wchar_t nick[32];
		short version;
		unsigned int game;
	};

	struct ConnectResult
	{
		char result;
		short id;
	};

	struct Disconnect
	{
		short id;
	};
};