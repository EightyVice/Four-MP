/// \file
/// \brief Source file that contains implementation of the Plugin class.
/// \details See class description.

#include "Plugin.h"

Plugin plugin; ///< Main instance of the plugin.
IPluginInterface *pluginptr = &plugin; ///< Pointer to the instance. Used by host.

Plugin::Plugin(void)
{
}

Plugin::~Plugin(void)
{
}

void Plugin::OnPluginLoad(void)
{
	//Your code here
	server->PrintToServer(L"HELLO WORLD!");
}

void Plugin::OnPluginUnload(void)
{
	//Your code here
}