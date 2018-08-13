/// \file
/// \brief Source file that contains implementation of the four-mp console variable hooks.
/// \details See con_fmpcvarhooks.h.
/// \author FaTony

#include <string.h>
#include <stdlib.h>

#include "con_fmpcvarhooks.h"

#include "ServerCore.h"
#include "../../Shared/Console/common.h"
#include "NetworkManager.h"

extern ServerCore server;
extern NetworkManager nm;

void ConVarHookHostGamemode(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype == ConVarTypeString)
	{
		ResizeBuffer<conchar *>(server.gamemode, con_strlen((conchar *)newvalue) + 1);
		con_strcpy(server.gamemode, (conchar *)newvalue);
		return;
	}
	conchar *value;
	if (!convar->GetValue(value))
	{
		return;
	}
	ResizeBuffer<conchar *>(server.gamemode, con_strlen(value) + 1);
	con_strcpy(server.gamemode, value);
	free(value);
}

void ConVarHookHostname(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype == ConVarTypeString)
	{
		ResizeBuffer<conchar *>(server.hostname, con_strlen((conchar *)newvalue) + 1);
		con_strcpy(server.hostname, (conchar *)newvalue);
		if (server.isrunning)
		{
			server.UpdateServerInfo();
		}
		return;
	}
	conchar *value;
	if (!convar->GetValue(value))
	{
		return;
	}
	ResizeBuffer<conchar *>(server.hostname, con_strlen(value) + 1);
	con_strcpy(server.hostname, value);
	free(value);
	if (server.isrunning)
	{
		server.UpdateServerInfo();
	}
}

void ConVarHookRconPassword(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype == ConVarTypeString)
	{
		ResizeBuffer<conchar *>(server.rconpassword, con_strlen((conchar *)newvalue) + 1);
		con_strcpy(server.rconpassword, (conchar *)newvalue);
		return;
	}
	conchar *value;
	if (!convar->GetValue(value))
	{
		return;
	}
	ResizeBuffer<conchar *>(server.rconpassword, con_strlen(value) + 1);
	con_strcpy(server.rconpassword, value);
	free(value);
}

void ConVarHookSvComponentselect(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype != ConVarTypeInt)
	{
		return;
	}
	server.componentselect = *(int *)newvalue;
}
void ConVarHookSvLan(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype != ConVarTypeInt)
	{
		return;
	}
	server.lan = *(int *)newvalue;
}

void ConVarHookSvPassword(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype == ConVarTypeString)
	{
		ResizeBuffer<conchar *>(server.password, con_strlen((conchar *)newvalue) + 1);
		con_strcpy(server.password, (conchar *)newvalue);
		if (server.isrunning)
		{
			server.UpdateServerInfo();
		}
		return;
	}
	conchar *value;
	if (!convar->GetValue(value))
	{
		return;
	}
	ResizeBuffer<conchar *>(server.password, con_strlen(value) + 1);
	con_strcpy(server.password, value);
	free(value);
	if (server.isrunning)
	{
		server.UpdateServerInfo();
	}
}

void ConVarHookSvPort(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype != ConVarTypeInt)
	{
		return;
	}
	server.port = *(int *)newvalue;
}