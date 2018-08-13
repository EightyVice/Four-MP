#include "../../Shared/RakNet/RakNetworkFactory.h"
#include "../../Shared/RakNet/RakPeerInterface.h"
#include "../../Shared/RakNet/TCPInterface.h"
#include "../../Shared/RakNet/HTTPConnection.h"
#include "../../Shared/RakNet/RakString.h"
#include "../../Shared/RakNet/MessageIdentifiers.h"
#include "../../Shared/RakNet/GetTime.h"

#include "MasterServerManager.h"
#include "../../Shared/logging/log.h"

using namespace std;
using namespace RakNet;

MasterServerManager::MasterServerManager(void)
{
	isloaded = false;
}

MasterServerManager::~MasterServerManager(void)
{
	if (isloaded)
	{
		free(http);
		free(tcp);
	}
}

bool MasterServerManager::Init(void)
{
	if (isloaded)
	{
		return false;
	}
	tcp = RakNet::OP_NEW<TCPInterface>(__FILE__,__LINE__);
	http = RakNet::OP_NEW<HTTPConnection>(__FILE__,__LINE__);

	tcp->Start(0, 64);
	http->Init(tcp, MASTER_HOST);

	state = MSS_NONE;
	isloaded = true;
	return true;
}

bool MasterServerManager::RegisterServer(const unsigned short port, const wchar_t *name, const wchar_t *mode, const wchar_t *loc, const short maxpl, const bool password)
{
	if(http->IsBusy()) return 0;

	char *urlname = this->URLEncode(name);
	char *urlmode = this->URLEncode(mode);
	char *urlloc = this->URLEncode(loc);
	RakString data("port=%d&name=%s&mode=%s&loc=%s&maxpl=%d&password=%d&t=add", port, urlname, urlmode, urlloc, maxpl, password);
	free(urlname);
	free(urlmode);
	free(urlloc);

	http->Post(RakString("%s%s", MASTER_PATH, "list.php").C_String(), data);
	state = MSS_WAIT_SERVER_ADD;

	RakNetTimeMS endTime=RakNet::GetTimeMS() + 10000;
	while(RakNet::GetTimeMS() < endTime && !(state == MSS_NONE || state == MSS_ERROR))
	{
		Process();
	}

	if(state != MSS_NONE)
	{
		state = MSS_NONE;
		return 0;
	}

	return 1;
}

bool MasterServerManager::QueryUserCheck(const int fmpid, const char *ip, const unsigned int sessionkey)
{
	if(http->IsBusy()) return 0;

	RakString data = RakString("fmpid=%d&ip=%s&seskey=%d&t=check", fmpid, 
		RakString(ip).URLEncode().C_String(), sessionkey);

	http->Post(RakString("%s%s", MASTER_PATH, "login.php").C_String(), data);
	state = MSS_WAIT_USER_CHECK;

	RakNetTimeMS endTime=RakNet::GetTimeMS() + 10000;
	while(RakNet::GetTimeMS() < endTime && !(state == MSS_NONE || state == MSS_ERROR))
	{
		Process();
	}

	if(state != MSS_NONE)
	{
		state = MSS_NONE;
		return 0;
	}

	return 1;
}

bool MasterServerManager::QueryClanCheck(const int fmpid, const wchar_t *clan)
{
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MasterServerManager::ReadPacket(const RakString data)
{
	switch(state)
	{
	case MSS_WAIT_SERVER_ADD: 
		{
			if(data.C_String()[1] == 'O') state = MSS_NONE;
			else state = MSS_ERROR;
		} break;
	case MSS_WAIT_USER_CHECK: 
		{
			if(data.C_String()[1] == 'O') state = MSS_NONE;
			else state = MSS_ERROR;
		} break;
	case MSS_WAIT_CLAN_CHECK:
		{
			Log::Debug(L"%S\n", data.C_String());

			if(data.C_String()[1] == 'O') state = MSS_NONE;
			else state = MSS_ERROR;
		} break;
	default: Log::Warning(L"Recieved unknown packet from the master server."); break;
	}
}

void MasterServerManager::Process(void)
{
	if(!tcp) return;

	Packet *packet = tcp->Receive();
	if(packet) 
	{
		http->ProcessTCPPacket(packet);
		tcp->DeallocatePacket(packet);
	}
	if(http->HasRead())
	{
		int code;
		RakNet::RakString data;
		if(http->HasBadResponse(&code, &data))
			Log::Error(L"Master server error %d: %S", code, data.C_String());
		else
			ReadPacket(http->Read());
	}

	http->Update();
}

char *MasterServerManager::URLEncode(const wchar_t *string)
{
	if (string == NULL)
	{
		return NULL;
	}
	size_t length = (sizeof(wchar_t) / sizeof(char)) * wcslen(string) + 1;
	char *tempstring = (char *)calloc(length, sizeof(char));
	wcstombs(tempstring, string, length);
	RakNet::RakString tempstring2 = RakNet::RakString(tempstring).URLEncode();
	char *tempstring3 = (char *)calloc(strlen(tempstring2.C_String()) + 1, sizeof(char));
	strcpy(tempstring3, tempstring2.C_String());
	free(tempstring);
	return tempstring3;
}