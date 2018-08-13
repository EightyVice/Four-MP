/// \file
/// \brief Source file that contains implementation of the PluginManager class.
/// \details See class description.
/// \author FaTony

#include <stdio.h>
#include <string.h>
#include <io.h>

#include "PluginManager.h"
#include "../../Shared/Console/common.h"
#include "../../Shared/logging/log.h"
#include "HandleManager.h"
#include "CoreHandleTypesManager.h"
#include "../../Shared/Console/ConsoleCore.h"
#include "VirtualMachineManager.h"

extern HandleManager hm;
extern CoreHandleTypesManager chtm;
extern ConsoleCore concore;
extern PluginManager plugm;
extern VirtualMachineManager vmm;

PluginManager::PluginManager(void)
{
	handleowneroffset = 1 + vmm.GetMaxVirtualMachineBufferSize();
	maxpluginbuffersize = 8;
	pluginbuffersize = 0;
	ph = new PluginHandler;
}

PluginManager::~PluginManager(void)
{
	this->UnloadPlugins();
	free(pluginbuffer);
	delete ph;
}

unsigned char PluginManager::GetMaxPluginBufferSize(void)
{
	return maxpluginbuffersize;
}

unsigned char PluginManager::GetPluginBufferSize(void)
{
	return pluginbuffersize;
}

void PluginManager::LoadPlugins(void)
{
	if (_waccess(L"plugins", 0) == -1)
	{
		_wmkdir(L"plugins");
		return;
	}
	intptr_t ptr;
	_wfinddata64i32_t data;
	ptr = _wfindfirst(L"plugins\\*.dll", &data);
	if (ptr == -1)
	{
		return;
	}
	int continuesearch = 0;
	unsigned char slots = this->GetNumberOfFreePluginSlots();
	unsigned char i = 0;
	while ((continuesearch == 0) && (i < slots))
	{
		if ((!this->IsPluginLoaded(data.name)) && (this->LoadPlugin(data.name)))
		{
			i++;
		}
		continuesearch = _wfindnext(ptr, &data);
	}
	_findclose(ptr);
}

void PluginManager::UnloadPlugins(void)
{
	for (unsigned char i = 0; i < pluginbuffersize; i++)
	{
		if (pluginbuffer[i] != NULL)
		{
			this->UnloadPlugin(i);
		}
	}
}

void PluginManager::ReloadPlugins(void)
{
	for (unsigned char i = 0; i < pluginbuffersize; i++)
	{
		if (pluginbuffer[i] != NULL)
		{
			this->ReloadPlugin(i);
		}
	}
}

void PluginManager::PausePlugins(void)
{
	for (unsigned char i = 0; i < pluginbuffersize; i++)
	{
		if (pluginbuffer[i] != NULL)
		{
			this->PausePlugin(i);
		}
	}
}

void PluginManager::UnpausePlugins(void)
{
	for (unsigned char i = 0; i < pluginbuffersize; i++)
	{
		if (pluginbuffer[i] != NULL)
		{
			this->UnpausePlugin(i);
		}
	}
}

bool PluginManager::IsPluginLoaded(const wchar_t *string)
{
	size_t length = wcslen(string) + 8;
	wchar_t *plugin = (wchar_t *)calloc(length, sizeof(wchar_t));
	swprintf(plugin, length, L"plugins/%s", string);
	for (unsigned char i = 0; i < pluginbuffersize; i++)
	{
		if ((pluginbuffer[i] != NULL) && (wcscmp(pluginbuffer[i]->filename, plugin) == 0))
		{
			return true;
		}
	}
	return false;
}

bool PluginManager::LoadPlugin(const wchar_t *string)
{
	unsigned char index;
	if (!this->GetPluginFreeSlot(index))
	{
		return false;
	}
	size_t length = wcslen(string) + 9;
	wchar_t *plugin = (wchar_t *)calloc(length, sizeof(wchar_t));
	swprintf(plugin, length, L"plugins\\%s", string);
	return this->LoadPluginInternal(index, plugin);
}

bool PluginManager::UnloadPlugin(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return false;
	}
	if (pluginbuffer[index] == NULL)
	{
		return false;
	}
	this->OnPluginUnload(index);
	pluginbuffer[index]->paused = false;
	FreeLibrary(pluginbuffer[index]->module);
	free(pluginbuffer[index]->filename);
	delete pluginbuffer[index];
	pluginbuffer[index] = NULL;
	hm.CloseAllHandles(handleowneroffset + index);
	hm.ReleaseAllHandleTypes(index);
	return true;
}

bool PluginManager::ReloadPlugin(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return false;
	}
	if (pluginbuffer[index] == NULL)
	{
		return false;
	}
	wchar_t *filename = (wchar_t *)calloc(wcslen(pluginbuffer[index]->filename) + 1, sizeof(wchar_t));
	wcscpy(filename, pluginbuffer[index]->filename);
	if (!this->UnloadPlugin(index))
	{
		return false;
	}
	if (!this->LoadPluginInternal(index, filename))
	{
		return false;
	}
	return true;
}

bool PluginManager::PausePlugin(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return false;
	}
	if (pluginbuffer[index] == NULL)
	{
		return false;
	}
	if (pluginbuffer[index]->paused)
	{
		return false;
	}
	pluginbuffer[index]->paused = true;
	return true;
}

bool PluginManager::UnpausePlugin(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return false;
	}
	if (pluginbuffer[index] == NULL)
	{
		return false;
	}
	if (!pluginbuffer[index]->paused)
	{
		return false;
	}
	pluginbuffer[index]->paused = false;
	return true;
}

wchar_t *PluginManager::GetPluginInfoString(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return NULL;
	}
	if (pluginbuffer[index] == NULL)
	{
		return NULL;
	}
	wchar_t *string;
	wchar_t *name = pluginbuffer[index]->ptr->GetName();
	wchar_t *version = pluginbuffer[index]->ptr->GetVersion();
	wchar_t *author = pluginbuffer[index]->ptr->GetAuthor();
	if (!pluginbuffer[index]->paused)
	{
		int length = _scwprintf(L"%d \"%s\" (%s) by %s", index, name, version, author) + 1;
		string = (wchar_t *)calloc(length, sizeof(wchar_t));
		swprintf(string, length, L"%d \"%s\" (%s) by %s", index, name, version, author);
	}
	else
	{
		int length = _scwprintf(L"%d (Paused) \"%s\" (%s) by %s", index, name, version, author) + 1;
		string = (wchar_t *)calloc(length, sizeof(wchar_t));
		swprintf(string, length, L"%d (Paused) \"%s\" (%s) by %s", index, name, version, author);
	}
	return string;
}

IPluginHandlerInterface *PluginManager::GetPluginHandler(void)
{
	return ph;
}

bool PluginManager::LoadPluginInternal(const unsigned char index, const wchar_t *string)
{
	if (index >= maxpluginbuffersize)
	{
		return false;
	}
	if (index >= pluginbuffersize)
	{
		if (pluginbuffersize == maxpluginbuffersize)
		{
			return false;
		}
		if (!ResizeBuffer<Plugin **>(pluginbuffer, index + 1))
		{
			return false;
		}
		pluginbuffer[index] = NULL;
		pluginbuffersize = index + 1;
	}
	if (pluginbuffer[index] != NULL)
	{
		return false;
	}
	pluginbuffer[index] = new Plugin;
	pluginbuffer[index]->module = LoadLibrary(string);
	if (pluginbuffer[index]->module == NULL)
	{
		delete pluginbuffer[index];
		pluginbuffer[index] = NULL;
		return false;
	}
	typedef IPluginInterface *(*GetPluginFunctionType)();
	GetPluginFunctionType GetPluginFunction = NULL;
	GetPluginFunction = (GetPluginFunctionType)GetProcAddress(pluginbuffer[index]->module, "GetPlugin");
	if (GetPluginFunction == NULL)
	{
		FreeLibrary(pluginbuffer[index]->module);
		delete pluginbuffer[index];
		pluginbuffer[index] = NULL;
		return false;
	}
	pluginbuffer[index]->ptr = GetPluginFunction();
	if (!pluginbuffer[index]->ptr->AttachToServer())
	{
		FreeLibrary(pluginbuffer[index]->module);
		delete pluginbuffer[index];
		pluginbuffer[index] = NULL;
		return false;
	}
	pluginbuffer[index]->paused = false;
	pluginbuffer[index]->filename = (wchar_t *)calloc(wcslen(string) + 1, sizeof(wchar_t));
	wcscpy(pluginbuffer[index]->filename, string);
	this->OnPluginLoad(index);
	return true;
}

unsigned char PluginManager::GetNumberOfFreePluginSlots(void)
{
	unsigned char slots = 0;
	for (unsigned char i = 0; i < pluginbuffersize; i++)
	{
		if (pluginbuffer[i] == NULL)
		{
			slots++;
		}
	}
	slots = maxpluginbuffersize - pluginbuffersize + slots;
	return slots;
}

bool PluginManager::GetPluginFreeSlot(unsigned char &index)
{
	for (index = 0; index < pluginbuffersize; index++)
	{
		if (pluginbuffer[index] == NULL)
		{
			return true;
		}
	}
	if (pluginbuffersize == maxpluginbuffersize)
	{
		return false;
	}
	return true;
}

bool PluginManager::FindPlugin(const IPluginInterface *plugin, unsigned char &index)
{
	for (index = 0; index < pluginbuffersize; index++)
	{
		if ((pluginbuffer[index] != NULL) && (pluginbuffer[index]->ptr == plugin))
		{
			return true;
		}
	}
	return false;
}

void PluginManager::OnPluginLoad(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return;
	}
	if (pluginbuffer[index] == NULL)
	{
		return;
	}
	pluginbuffer[index]->ptr->OnPluginLoad();
}

void PluginManager::OnPluginUnload(const unsigned char index)
{
	if (index >= pluginbuffersize)
	{
		return;
	}
	if (pluginbuffer[index] == NULL)
	{
		return;
	}
	pluginbuffer[index]->ptr->OnPluginUnload();
}

/// \brief Returns the pointer to the plugin handler interface.
/// \note Used by plugins.
/// \return Pointer to the plugin handler interface.
extern "C" __declspec(dllexport) IPluginHandlerInterface *GetPluginHandler(void)
{
	return plugm.GetPluginHandler();
}

PluginManager::PluginHandler::PluginHandler(void)
{
}

PluginManager::PluginHandler::~PluginHandler(void)
{
}

void PluginManager::PluginHandler::ReleaseAllHandleTypes(const IPluginInterface *plugin)
{
	unsigned char index;
	if (!plugm.FindPlugin(plugin, index))
	{
		return;
	}
	hm.ReleaseAllHandleTypes(index);
}

bool PluginManager::PluginHandler::RequestNewHandleType(const IPluginInterface *plugin, unsigned short &index)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	if (!hm.RequestNewHandleType(pluginindex, index))
	{
		return false;
	}
	return true;
}

bool PluginManager::PluginHandler::ReleaseHandleType(const IPluginInterface *plugin, const unsigned short &index)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	if (!hm.ReleaseHandleType(pluginindex, index))
	{
		return false;
	}
	return true;
}

void PluginManager::PluginHandler::PrintToServer(const wchar_t *string, ...)
{
	va_list arglist; 
    va_start(arglist, string);
	wchar_t *tempstring = (wchar_t *)calloc(_vscwprintf(string, arglist) + 1, sizeof(wchar_t));
	vswprintf(tempstring, string, arglist);
	Log::Info(tempstring);
	free(tempstring);
	va_end(arglist);
}

int PluginManager::PluginHandler::CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const float defaultvalue, const wchar_t *description, const int flags, const bool hasMin, const float min, const bool hasMax, const float max)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return INVALID_HANDLE;
	}
	return hm.AddNewHandle(plugm.handleowneroffset + pluginindex, HandleTypeConVar, concore.AddConVar(name, defaultvalue, description, flags, hasMin, min, hasMax, max));
}

int PluginManager::PluginHandler::CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const int defaultvalue, const wchar_t *description, const int flags, const bool hasMin, const int min, const bool hasMax, const int max)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return INVALID_HANDLE;
	}
	return hm.AddNewHandle(plugm.handleowneroffset + pluginindex, HandleTypeConVar, concore.AddConVar(name, defaultvalue, description, flags, hasMin, min, hasMax, max));
}

int PluginManager::PluginHandler::CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const wchar_t *defaultvalue, const wchar_t *description, const int flags)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return INVALID_HANDLE;
	}
	return hm.AddNewHandle(plugm.handleowneroffset + pluginindex, HandleTypeConVar, concore.AddConVar(name, defaultvalue, description, flags));
}

int PluginManager::PluginHandler::FindConVar(const IPluginInterface *plugin, const wchar_t *name)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return INVALID_HANDLE;
	}
	return chtm.FindConVar(plugm.handleowneroffset + pluginindex, name);
}

bool PluginManager::PluginHandler::ResetConVar(const IPluginInterface *plugin, const int handle)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.ResetConVar(plugm.handleowneroffset + pluginindex, handle);
}

wchar_t *PluginManager::PluginHandler::GetConVarName(const IPluginInterface *plugin, const int handle)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return NULL;
	}
	return chtm.GetConVarName(plugm.handleowneroffset + pluginindex, handle);
}

bool PluginManager::PluginHandler::GetConVarValue(const IPluginInterface *plugin, const int handle, float &value)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.GetConVarValue(plugm.handleowneroffset + pluginindex, handle, value);
}

bool PluginManager::PluginHandler::GetConVarValue(const IPluginInterface *plugin, const int handle, int &value)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.GetConVarValue(plugm.handleowneroffset + pluginindex, handle, value);
}

bool PluginManager::PluginHandler::GetConVarValue(const IPluginInterface *plugin, const int handle, wchar_t *&value)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.GetConVarValue(plugm.handleowneroffset + pluginindex, handle, value);
}

bool PluginManager::PluginHandler::GetConVarFlags(const IPluginInterface *plugin, const int handle, int &flags)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.GetConVarFlags(plugm.handleowneroffset + pluginindex, handle, flags);
}

bool PluginManager::PluginHandler::GetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, float &bound)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.GetConVarBound(plugm.handleowneroffset + pluginindex, handle, type, bound);
}

bool PluginManager::PluginHandler::GetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, int &bound)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.GetConVarBound(plugm.handleowneroffset + pluginindex, handle, type, bound);
}

bool PluginManager::PluginHandler::SetConVarValue(const IPluginInterface *plugin, const int handle, const float value)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.SetConVarValue(plugm.handleowneroffset + pluginindex, handle, value);
}

bool PluginManager::PluginHandler::SetConVarValue(const IPluginInterface *plugin, const int handle, const int value)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.SetConVarValue(plugm.handleowneroffset + pluginindex, handle, value);
}

bool PluginManager::PluginHandler::SetConVarValue(const IPluginInterface *plugin, const int handle, const wchar_t *value)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.SetConVarValue(plugm.handleowneroffset + pluginindex, handle, value);
}

bool PluginManager::PluginHandler::SetConVarFlags(const IPluginInterface *plugin, const int handle, const int flags)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.SetConVarFlags(plugm.handleowneroffset + pluginindex, handle, flags);
}

bool PluginManager::PluginHandler::SetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, const bool set, const float bound)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.SetConVarBound(plugm.handleowneroffset + pluginindex, handle, type, set, bound);
}

bool PluginManager::PluginHandler::SetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, const bool set, const int bound)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return false;
	}
	return chtm.SetConVarBound(plugm.handleowneroffset + pluginindex, handle, type, set, bound);
}

void PluginManager::PluginHandler::RegServerCmd(const IPluginInterface *plugin, const wchar_t *name, void *callback, const wchar_t *description, const int flags)
{
	unsigned char pluginindex;
	if (!plugm.FindPlugin(plugin, pluginindex))
	{
		return;
	}
	hm.AddNewHandle(plugm.handleowneroffset + pluginindex, HandleTypeConCmd, concore.AddConCmd(name, callback, description, flags));
}

unsigned char PluginManager::PluginHandler::GetCmdArgs(void)
{
	return concore.GetCmdArgs();
}

wchar_t *PluginManager::PluginHandler::GetCmdArgString(void)
{
	return concore.GetCmdArgString();
}

bool PluginManager::PluginHandler::GetCmdArgType(const unsigned char argnum, ConVarType &type)
{
	return concore.GetCmdArgType(argnum, type);
}

bool PluginManager::PluginHandler::GetCmdArg(const unsigned char argnum, wchar_t *&arg)
{
	return concore.GetCmdArg(argnum, arg);
}

bool PluginManager::PluginHandler::GetCmdArg(const unsigned char argnum, int &arg)
{
	return concore.GetCmdArg(argnum, arg);
}

bool PluginManager::PluginHandler::GetCmdArg(const unsigned char argnum, float &arg)
{
	return concore.GetCmdArg(argnum, arg);
}

void PluginManager::PluginHandler::ServerCommand(const wchar_t *string)
{
	concore.InterpretLine(string);
}