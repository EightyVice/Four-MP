#include "CNetwork.h"

void CNetwork::CloseConnection(const SystemAddress addr)
{
	m_pNet->CloseConnection(addr, true);
}

void CNetwork::AddToBanList(const SystemAddress addr, wchar_t * pszNick)
{
	m_pNet->AddToBanList(addr.ToString(0));
	m_vBadNick.push_back(pszNick);

	FILE * banlist = fopen("ban.list", "a");
	if(banlist)
	{
		fwprintf(banlist, L"%s\t%s\n", pszNick, addr.ToString(0));  
		fclose(banlist);
	}

	this->CloseConnection(addr);
}

void CNetwork::ClearBanList()
{
	m_pNet->ClearBanList();
	m_vBadNick.clear();

	FILE * banlist = fopen("ban.list", "w");
	if(banlist) fclose(banlist);
}

void CNetwork::ReloadBanList()
{
	m_pNet->ClearBanList();
	m_vBadNick.clear();
	this->LoadBanList();
}

void CNetwork::LoadBanList()
{
	FILE * banlist = fopen("ban.list", "r");
	if(banlist)
	{
		while(!feof(banlist))
		{
			wchar_t nick[32];
			char ip[32];
			fwscanf(banlist, L"%s\t%s\n", &nick, &ip);
			m_pNet->AddToBanList(ip);
			m_vBadNick.push_back(nick);
		}
		fclose(banlist);
	}
}
