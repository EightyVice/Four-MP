/// \file
/// \brief Source file that contains implementation of the four-mp console variable hooks.
/// \details See con_fmpcvarhooks.h.
/// \author FaTony

#include <string.h>
#include <stdlib.h>

#include "con_sharedcvarhooks.h"
#include "ClientCore.h"
#include "../../Shared/Network/Limits.h"

extern ClientCore client;

void ConVarHookName(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue)
{
	if (newtype == ConVarTypeString)
	{
		size_t length = wcslen((wchar_t *)newvalue);
		if (length > MAX_CLIENT_NAME_LENGTH - 1)
		{
			wcsncpy(client.name, (wchar_t *)newvalue, MAX_CLIENT_NAME_LENGTH - 1);
			client.name[MAX_CLIENT_NAME_LENGTH-1] = L'\0';
			return;
		}
		wcsncpy(client.name, (wchar_t *)newvalue, length);
		client.name[length] = L'\0';
		return;
	}
	wchar_t *value;
	if (!convar->GetValue(value))
	{
		return;
	}
	size_t length = wcslen(value);
	if (length > MAX_CLIENT_NAME_LENGTH - 1)
	{
		wcsncpy(client.name, value, MAX_CLIENT_NAME_LENGTH - 1);
		client.name[MAX_CLIENT_NAME_LENGTH - 1] = L'\0';
		return;
	}
	wcsncpy(client.name, value, length);
	client.name[length] = '\0';
	free(value);
}