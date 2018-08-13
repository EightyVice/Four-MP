/// \file
/// \brief Source file that contains implementation of the four-mp client shared console
/// commands.
/// \details See con_sharedcommands.h.
/// \author FaTony

#include <string.h>
#include <stdio.h>

#include "con_sharedcommands.h"
#include "ClientCore.h"
#include "NetworkManager.h"

extern ClientCore client;
extern NetworkManager nm;

void ConCmdConnect(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: connect <server>");
		return;
	}
	wchar_t *tempaddress = concore->GetCmdArgString();
	if (tempaddress == NULL)
	{
		concore->Output(L"Usage: connect <server>");
		return;
	}
	size_t length = (sizeof(wchar_t) / sizeof(char)) * wcslen(tempaddress) + 1;
	char *address = (char *)calloc(length, sizeof(char));
	wcstombs(address, tempaddress, length);
	char *portstart = strrchr(address, ':');
	if (portstart == NULL)
	{
		nm.ConnectToServer(address);
		free(address);
		free(tempaddress);
		return;
	}
	unsigned short port = 7777;
	sscanf(portstart, "%d", port);
	nm.ConnectToServer(address, port);
	free(address);
	free(tempaddress);
	return;
}

void ConCmdQuit(ConsoleCore *concore, const unsigned char numargs)
{
	client.Shutdown();
}