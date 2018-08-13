/// \file
/// \brief Source file that contains implementation of the four-mp console commands.
/// \details See con_fmpcommands.h.
/// \author FaTony

#include "con_fmpcommands.h"
#include "ServerCore.h"
#include "CoreHandleTypesManager.h"
#include "PluginManager.h"
#include "VirtualMachineManager.h"

extern ServerCore server;
extern CoreHandleTypesManager chtm;
extern PluginManager plugm;
extern VirtualMachineManager vmm;

void ConCmdDynamic(ConsoleCore *concore, const unsigned char numargs)
{
	conchar *cmdname;
	if (!concore->GetCmdArg(0, cmdname))
	{
		return;
	}
	unsigned char numcmds;
	int *indexes = chtm.GetDynamicCommandHandles(cmdname, numcmds);
	if (indexes == NULL)
	{
		concore->Output(L"Unknown command \"%s\"", cmdname);
		free(cmdname);
		return;
	}
	for (unsigned char i = 0; i < numcmds; i++)
	{
		if (!chtm.ExecuteDynamicCommand(indexes[i], numargs))
		{
			concore->Output(L"Unknown command \"%s\"", cmdname);
		}
	}
	free(cmdname);
}

void ConCmdFsList(ConsoleCore *concore, const unsigned char numargs)
{
	concore->Output(L"Loaded filterscripts:\n---------------------");
	wchar_t *string;
	unsigned char max = vmm.GetVirtualMachineBufferSize();
	for (unsigned char i = 0; i < max; i++)
	{
		string = vmm.GetVirtualMachineInfoString(i);
		if (string != NULL)
		{
			concore->Output(string);
		}
	}
	concore->Output(L"---------------------");
}

void ConCmdFsLoad(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: fs_load <filename>");
		return;
	}
	conchar *name;
	if (!concore->GetCmdArg(1, name))
	{
		concore->Output(L"Usage: fs_load <filename>");
		return;
	}
	if (!vmm.LoadFilterScript(name))
	{
		concore->Output(L"Unable to load filterscript \"%s\"", name);
		return;
	}
	concore->Output(L"Filterscript \"%s\" has been loaded successfully", name);
	free(name);
}

void ConCmdFsLoadAll(ConsoleCore *concore, const unsigned char numargs)
{
	vmm.LoadFilterScripts();
	concore->Output(L"Loaded all filterscripts");
}

void ConCmdFsPause(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: fs_pause <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: fs_pause <index>");
		return;
	}
	if (!vmm.PauseVirtualMachine(index))
	{

		concore->Output(L"Unable to pause filterscript \"%d\"", index);
		return;
	}
	concore->Output(L"Filterscript \"%d\" disabled", index);
}

void ConCmdFsPauseAll(ConsoleCore *concore, const unsigned char numargs)
{
	vmm.PauseVirtualMachines();
	concore->Output(L"Filterscripts disabled");
}

void ConCmdFsReload(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: fs_reload <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: fs_reload <index>");
		return;
	}
	if (index == 0)
	{
		concore->Output(L"Can't reload gamemode");
		return;
	}
	if (!vmm.ReloadFilterScript(index))
	{

		concore->Output(L"Unable to reload filterscript \"%d\"", index);
		return;
	}
	concore->Output(L"Filterscript \"%d\" has been reloaded successfully", index);
}

void ConCmdFsReloadAll(ConsoleCore *concore, const unsigned char numargs)
{
	vmm.ReloadFilterScripts();
	concore->Output(L"Reloaded all filterscripts");
}

void ConCmdFsUnload(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: fs_unload <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: fs_unload <index>");
		return;
	}
	if (index == 0)
	{
		concore->Output(L"Can't unload gamemode");
		return;
	}
	if (!vmm.UnloadFilterScript(index))
	{
		concore->Output(L"Unable to unload filterscript \"%d\", not found", index);
		return;
	}
	concore->Output(L"Filterscript \"%d\" has been unloaded successfully", index);
}

void ConCmdFsUnloadAll(ConsoleCore *concore, const unsigned char numargs)
{
	vmm.UnloadFilterScripts();
	concore->Output(L"Unloaded all filterscripts");
}

void ConCmdFsUnpause(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: fs_unpause <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: fs_unpause <index>");
		return;
	}
	if (!vmm.UnpauseVirtualMachine(index))
	{
		concore->Output(L"Unable to unpause filterscript \"%d\"", index);
		return;
	}
	concore->Output(L"Filterscript \"%d\" enabled", index);
}

void ConCmdFsUnpauseAll(ConsoleCore *concore, const unsigned char numargs)
{
	vmm.UnpauseVirtualMachines();
	concore->Output(L"Filterscripts enabled");
}

void ConCmdPluginList(ConsoleCore *concore, const unsigned char numargs)
{
	concore->Output(L"Loaded plugins:\n---------------------");
	wchar_t *string;
	unsigned char max = plugm.GetPluginBufferSize();
	for (unsigned char i = 0; i < max; i++)
	{
		string = plugm.GetPluginInfoString(i);
		if (string != NULL)
		{
			concore->Output(string);
		}
	}
	concore->Output(L"---------------------");
}

void ConCmdPluginLoad(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: plugin_load <filename>");
		return;
	}
	conchar *name;
	if (!concore->GetCmdArg(1, name))
	{
		concore->Output(L"Usage: plugin_load <filename>");
		return;
	}
	if (!plugm.LoadPlugin(name))
	{
		concore->Output(L"Unable to load plugin \"%s\"", name);
		return;
	}
	concore->Output(L"Plugin \"%s\" has been loaded successfully", name);
	free(name);
}

void ConCmdPluginLoadAll(ConsoleCore *concore, const unsigned char numargs)
{
	plugm.LoadPlugins();
	concore->Output(L"Loaded all plugins");
}

void ConCmdPluginPause(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: plugin_pause <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: plugin_pause <index>");
		return;
	}
	if (!plugm.PausePlugin(index))
	{

		concore->Output(L"Unable to pause plugin \"%d\"", index);
		return;
	}
	concore->Output(L"Plugin \"%d\" disabled", index);
}

void ConCmdPluginPauseAll(ConsoleCore *concore, const unsigned char numargs)
{
	plugm.PausePlugins();
	concore->Output(L"Plugins disabled");
}

void ConCmdPluginReload(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: plugin_reload <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: plugin_reload <index>");
		return;
	}
	if (!plugm.ReloadPlugin(index))
	{
		concore->Output(L"Unable to reload plugin \"%d\"", index);
		return;
	}
	concore->Output(L"Plugin \"%d\" has been reloaded successfully", index);
}

void ConCmdPluginReloadAll(ConsoleCore *concore, const unsigned char numargs)
{
	plugm.ReloadPlugins();
	concore->Output(L"Reloaded all plugins");
}

void ConCmdPluginUnload(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: plugin_unload <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: plugin_unload <index>");
		return;
	}
	if (!plugm.UnloadPlugin(index))
	{

		concore->Output(L"Unable to unload plugin \"%d\", not found", index);
		return;
	}
	concore->Output(L"Plugin \"%d\" has been unloaded successfully", index);
}

void ConCmdPluginUnloadAll(ConsoleCore *concore, const unsigned char numargs)
{
	plugm.UnloadPlugins();
	concore->Output(L"Unloaded all plugins");
}

void ConCmdPluginUnpause(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(L"Usage: plugin_unpause <index>");
		return;
	}
	int index;
	if (!concore->GetCmdArg(1, index))
	{
		concore->Output(L"Usage: plugin_unpause <index>");
		return;
	}
	if (!plugm.UnpausePlugin(index))
	{

		concore->Output(L"Unable to unpause plugin \"%d\"", index);
		return;
	}
	concore->Output(L"Plugin \"%d\" enabled", index);
}

void ConCmdPluginUnpauseAll(ConsoleCore *concore, const unsigned char numargs)
{
	plugm.UnpausePlugins();
	concore->Output(L"Plugins enabled");
}

void ConCmdQuit(ConsoleCore *concore, const unsigned char numargs)
{
	server.Shutdown();
}