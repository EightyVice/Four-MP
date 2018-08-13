/// \file
/// \brief Source file that contains implementation of the CoreHandleTypesManager class.
/// \details See class description.
/// \author FaTony

#include <stdlib.h>
#include <string.h>

#include "CoreHandleTypesManager.h"
#include "../../Shared/Console/common.h"
#include "HandleManager.h"
#include "VirtualMachineManager.h"

extern HandleManager hm;
extern ConsoleCore concore;
extern VirtualMachineManager vmm;

CoreHandleTypesManager::CoreHandleTypesManager(void)
{
	maxcommandbuffersize = 65535;
	commandbuffersize = 0;
}

CoreHandleTypesManager::~CoreHandleTypesManager(void)
{
	for (unsigned short i = 0; i < commandbuffersize; i++)
	{
		free(commandbuffer[i].callback);
	}
}

bool CoreHandleTypesManager::CloseHandle(const int handle)
{
	if ((handle < 0) || (handle >= hm.handlebuffersize))
	{
		return false;
	}
	if (hm.handlebuffer[handle] == NULL)
	{
		return false;
	}
	if (hm.handlebuffer[handle]->numowners != 0)
	{
		return false;
	}
	if (hm.handlebuffer[handle]->type >= NUM_CORE_HANDLE_TYPES)
	{
		return false;
	}
	switch (hm.handlebuffer[handle]->type)
	{
	case HandleTypeConVar:
		{
			delete ((ConVar *)hm.handlebuffer[handle]->ptr);
			break;
		}
	case HandleTypeConCmd:
		{
			delete ((ConCmd *)hm.handlebuffer[handle]->ptr);
			break;
		}
	}
	return true;
}

int CoreHandleTypesManager::FindConVar(const short owner, const wchar_t *name)
{
	if ((owner < 0) || (owner >= hm.countbuffersize))
	{
		return INVALID_HANDLE;
	}
	if (name == NULL)
	{
		return INVALID_HANDLE;
	}
	wchar_t *cvarname;
	for (int i = 0; i < hm.handlebuffersize; i++)
	{
		if ((hm.handlebuffer[i] != NULL) && (hm.handlebuffer[i]->type == HandleTypeConVar))
		{
			cvarname = ((ConVar *)hm.handlebuffer[i]->ptr)->GetName();
			if (wcscmp(cvarname, name) == 0)
			{
				free(cvarname);
				if (!hm.AddHandleOwner(i, owner))
				{
					return INVALID_HANDLE;
				}
				return i;
			}
			free(cvarname);
		}
	}
	return INVALID_HANDLE;
}

bool CoreHandleTypesManager::ResetConVar(const short owner, const int handle)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	((ConVar *)hm.handlebuffer[handle]->ptr)->Reset();
	return true;
}

wchar_t *CoreHandleTypesManager::GetConVarName(const short owner, const int handle)
{
	if (!this->CheckConVar(owner, handle))
	{
		return NULL;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->GetName();
}

bool CoreHandleTypesManager::GetConVarValue(const short owner, const int handle, float &value)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->GetValue(value);
}

bool CoreHandleTypesManager::GetConVarValue(const short owner, const int handle, int &value)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->GetValue(value);
}

bool CoreHandleTypesManager::GetConVarValue(const short owner, const int handle, wchar_t *&value)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->GetValue(value);
}

bool CoreHandleTypesManager::GetConVarFlags(const short owner, const int handle, int &flags)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	flags = ((ConVar *)hm.handlebuffer[handle]->ptr)->GetFlags();
	return true;
}

bool CoreHandleTypesManager::GetConVarBound(const short owner, const int handle, const ConVarBoundType type, float &bound)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->GetBound(type, bound);
}

bool CoreHandleTypesManager::GetConVarBound(const short owner, const int handle, const ConVarBoundType type, int &bound)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->GetBound(type, bound);
}

bool CoreHandleTypesManager::SetConVarValue(const short owner, const int handle, const float value)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->SetValue(value);
}

bool CoreHandleTypesManager::SetConVarValue(const short owner, const int handle, const int value)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->SetValue(value);
}

bool CoreHandleTypesManager::SetConVarValue(const short owner, const int handle, const wchar_t *value)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->SetValue(value);
}

bool CoreHandleTypesManager::SetConVarFlags(const short owner, const int handle, const int flags)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	((ConVar *)hm.handlebuffer[handle]->ptr)->SetFlags(flags);
	return true;
}

bool CoreHandleTypesManager::SetConVarBound(const short owner, const int handle, const ConVarBoundType type, const bool set, const float bound)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->SetBound(type, set, bound);
}

bool CoreHandleTypesManager::SetConVarBound(const short owner, const int handle, const ConVarBoundType type, const bool set, const int bound)
{
	if (!this->CheckConVar(owner, handle))
	{
		return false;
	}
	return ((ConVar *)hm.handlebuffer[handle]->ptr)->SetBound(type, set, bound);
}

bool CoreHandleTypesManager::AddDynamicCommand(const short owner, const wchar_t *callback, const ConCmd *ptr)
{
	if (ptr == NULL)
	{
		return false;
	}
	if (callback == NULL)
	{
		return false;
	}
	if ((owner < 0) || (owner >= hm.maxcountbuffersize))
	{
		return false;
	}
	if (commandbuffersize == maxcommandbuffersize)
	{
		return false;
	}
	int handle = hm.FindHandle(ptr);
	if (handle != INVALID_HANDLE)
	{
		return false;
	}
	handle = hm.AddNewHandle(owner, HandleTypeConCmd, (void *)ptr);
	if (handle == INVALID_HANDLE)
	{
		return false;
	}
	if (!ResizeBuffer<DynamicCommand *>(commandbuffer, commandbuffersize + 1))
	{
		return false;
	}
	commandbuffer[commandbuffersize].index = handle;
	commandbuffer[commandbuffersize].callback = (wchar_t *)calloc(wcslen(callback) + 1, sizeof(wchar_t));
	wcscpy(commandbuffer[commandbuffersize].callback, callback);
	commandbuffersize++;
	return true;
}

int *CoreHandleTypesManager::GetDynamicCommandHandles(const wchar_t *name, unsigned char &numcmds)
{
	if (name == NULL)
	{
		return NULL;
	}
	numcmds = 0;
	int *handles = NULL;
	wchar_t *cmdname;
	for (unsigned short i = 0; i < commandbuffersize; i++)
	{
		cmdname = ((ConCmd *)hm.handlebuffer[commandbuffer[i].index]->ptr)->GetName();
		if (wcscmp(cmdname, name) == 0)
		{
			if (!ResizeBuffer<int *>(handles, numcmds + 1))
			{
				return NULL;
			}
			handles[numcmds] = commandbuffer[i].index;
			numcmds++;
		}
		free(cmdname);
	}
	if (numcmds == 0)
	{
		return NULL;
	}
	return handles;
}

bool CoreHandleTypesManager::DeleteDynamicCommand(const int handle)
{
	if ((handle < 0) || (handle >= hm.handlebuffersize))
	{
		return false;
	}
	for (unsigned short i = 0; i < commandbuffersize; i++)
	{
		if (commandbuffer[i].index == handle)
		{
			free(commandbuffer[i].callback);
			return true;
		}
	}
	return false;
}

bool CoreHandleTypesManager::ExecuteDynamicCommand(const int handle, const unsigned char numargs)
{
	if ((handle < 0) || (handle >= hm.handlebuffersize))
	{
		return false;
	}
	wchar_t *callback = this->GetDynamicCommandCallback(handle);
	if (callback == NULL)
	{
		return false;
	}
	for (short i = 0; i < hm.handlebuffer[handle]->numowners; i++)
	{
		if ((hm.handlebuffer[handle]->owner[i] > 0) && (hm.handlebuffer[handle]->owner[i] < hm.pluginowneroffset))
		{
			vmm.FireCommandCallback(hm.handlebuffer[handle]->owner[i] - 1, callback, numargs);
		}
		else if (hm.handlebuffer[handle]->owner[i] >= hm.pluginowneroffset)
		{
			//Redirect to PluginManager;
		}
	}
	free(callback);
	return true;
}

bool CoreHandleTypesManager::CheckConVar(const short owner, const int handle)
{
	if ((owner < 0) || (owner >= hm.countbuffersize))
	{
		return false;
	}
	if ((handle < 0) || (handle >= hm.handlebuffersize))
	{
		return false;
	}
	if (hm.handlebuffer[handle] == NULL)
	{
		return false;
	}
	if (hm.handlebuffer[handle]->type != HandleTypeConVar)
	{
		return false;
	}
	if (!hm.IsHandleOwned(handle, owner))
	{
		return false;
	}
	return true;
}

wchar_t *CoreHandleTypesManager::GetDynamicCommandCallback(const int handle)
{
	if ((handle < 0) || (handle >= hm.handlebuffersize))
	{
		return NULL;
	}
	for (unsigned short i = 0; i < commandbuffersize; i++)
	{
		if (commandbuffer[i].index == handle)
		{
			wchar_t *callback = (wchar_t *)calloc(wcslen(commandbuffer[i].callback) + 1, sizeof(wchar_t));
			wcscpy(callback, commandbuffer[i].callback);
			return callback;
		}
	}
	return NULL;
}