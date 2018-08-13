/// \file
/// \brief Source file that contains implementation of the PluginCore class.
/// \details See class description.

#include "PluginCore.h"
#include "PluginConfig.h"

#ifdef WIN32
#include "windows.h"
#endif

extern IPluginInterface *pluginptr;

/// \brief Return the pointer to the plugin interface.
/// \note Used by the host.
/// \return Pointer to the plugin interface.
extern "C" __declspec(dllexport) IPluginInterface *GetPlugin(void)
{
	return pluginptr;
}

PluginCore::PluginCore(void)
{
	server = NULL;
}

PluginCore::~PluginCore(void)
{
}

bool PluginCore::AttachToServer(void)
{
	typedef IPluginHandlerInterface *(*GetPluginHandlerFunctionType)();
	GetPluginHandlerFunctionType GetPluginHandlerFunction = NULL;
	GetPluginHandlerFunction = (GetPluginHandlerFunctionType)GetProcAddress(GetModuleHandle(NULL), "GetPluginHandler");
	if (GetPluginHandlerFunction == NULL)
	{
		return false;
	}
	server = GetPluginHandlerFunction();
	if (server == NULL)
	{
		return false;
	}
	return true;
}

void PluginCore::OnPluginLoad(void)
{
}

void PluginCore::OnPluginUnload(void)
{
}

wchar_t *PluginCore::GetName(void)
{
	return PLUGIN_NAME;
}

wchar_t *PluginCore::GetVersion(void)
{
	return PLUGIN_VERSION;
}

wchar_t *PluginCore::GetAuthor(void)
{
	return PLUGIN_AUTHOR;
}