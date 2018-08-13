#include <time.h>

#include "ServerCore.h"
#include "../../Shared/logging/log.h"
#include "../../Shared/logging/logFile.h"
#include "../../Shared/logging/logStd.h"
#include "HandleManager.h"
#include "CoreHandleTypesManager.h"
#include "../../Shared/Console/ConsoleCore.h"
#include "../../Shared/Console/ConsoleScreen.h"
#include "../../Shared/Console/coreconcommands.h"
#include "con_fmpcvarhooks.h"
#include "con_fmpcommands.h"
#include "MasterServerManager.h"
#include "NetworkManager.h"
#include "PluginManager.h"
#include "VirtualMachineManager.h"
#include "PlayerManager.h"

#define SERVER_TICKRATE 10

extern LogFile logfile;
extern LogStd logserver;
extern HandleManager hm;
extern ConsoleCore concore;
extern ConsoleScreen conscreen;
extern MasterServerManager msm;
extern NetworkManager nm;
extern PluginManager plugm;
extern VirtualMachineManager vmm;
extern PlayerManager playm;

long msec_time()
{
#ifdef _WIN32
	return GetTickCount();
#else
	struct timeval tv;
	if(gettimeofday(&tv, NULL) != 0) return 0;

	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
}

ServerCore::ServerCore(void)
{
	isrunning = false;
	sleepcount = 100;
	lastcheck = 0;
	hostname = NULL;
	port = 7777;
	lan = 1;
	gamemode = NULL;
	password = NULL;
	rconpassword = NULL;
	componentselect = false;
	componentselectcvar = NULL;
	gametime.ticksperminute = 20;
	gametime.tickcount = 0;
	gametime.time[0] = 0;
	gametime.time[1] = 0;
	cmd_chars[0] = L'/';
	cmd_chars[1] = 0;

	memset(&scripttimers, 0, sizeof(ScriptTimer)*MAX_TIMERS);
}

ServerCore::~ServerCore(void)
{
	if (hostname)
	{
		free(hostname);
	}
	if (gamemode)
	{
		free(gamemode);
	}
	if (password)
	{
		free(password);
	}
	if (rconpassword)
	{
		free(rconpassword);
	}
}

bool ServerCore::Load(void)
{
	Log::SetState( LOG_INFO|LOG_ERROR|LOG_WARNING|LOG_DEBUG );
	Log::AddLogger(&logfile);
	Log::AddLogger(&logserver);
	concore.SetOutputFunction(Log::Info);
	concore.SetExecPath(L"cfg/");
	conscreen.SetCaption(L"FOUR-MP");
	//Core console functions
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"alias", ConCmdAlias, L"Alias a command.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"cvarlist", ConCmdCvarlist, L"Show the list of convars/concommands.", 0));
	hm.AddNewHandle(0, HandleTypeConVar, concore.AddConVar(L"developer", 0, L"Show developer messages.", 0, true, 0, true, 2));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"echo", ConCmdEcho, L"Echo text to console.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"exec", ConCmdExec, L"Execute script file.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"find", ConCmdFind, L"Find concommands with the specified string in their name/help text.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"help", ConCmdHelp, L"Find help about a convar/concommand.", 0));
	// FMP console functions
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"exit", ConCmdQuit, L"Exit the engine.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_list", ConCmdFsList, L"Prints details about loaded gamemode/filterscripts.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_load", ConCmdFsLoad, L"fs_load <filename> : loads a filterscript", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_load_all", ConCmdFsLoadAll, L"Loads all filterscripts", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_pause", ConCmdFsPause, L"fs_pause <index> : pauses a loaded filterscript", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_pause_all", ConCmdFsPauseAll, L"Pauses all loaded filterscripts", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_reload", ConCmdFsReload, L"fs_reload <index> : reloads a filterscript", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_reload_all", ConCmdFsReloadAll, L"Reloads all filterscripts", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_unload", ConCmdFsUnload, L"fs_unload <index> : unloads a filterscript", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_unload_all", ConCmdFsUnloadAll, L"Unloads all filterscripts", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_unpause", ConCmdFsUnpause, L"fs_unpause <index> : unpauses a loaded filterscript", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"fs_unpause_all", ConCmdFsUnpauseAll, L"Unpauses all disabled filterscripts", 0));
	ConVar *gamemodecvar = concore.AddConVar(L"host_gamemode", L"", L"Current gamemode name.", 0);
	gamemodecvar->HookChange(ConVarHookHostGamemode);
	hm.AddNewHandle(0, HandleTypeConVar, gamemodecvar);
	ConVar *hostnamecvar = concore.AddConVar(L"hostname", L"", L"Hostname for server.", 0);
	hostnamecvar->HookChange(ConVarHookHostname);
	hm.AddNewHandle(0, HandleTypeConVar, hostnamecvar);
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_list", ConCmdPluginList, L"Prints details about loaded plugins.", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_load", ConCmdPluginLoad, L"plugin_load <filename> : loads a plugin", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_load_all", ConCmdPluginLoadAll, L"Loads all plugins", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_pause", ConCmdPluginPause, L"plugin_pause <index> : pauses a loaded plugin", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_pause_all", ConCmdPluginPauseAll, L"Pauses all loaded plugins", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_reload", ConCmdPluginReload, L"fs_reload <index> : reloads a plugin", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_reload_all", ConCmdPluginReloadAll, L"Reloads all plugins", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_unload", ConCmdPluginUnload, L"fs_unload <index> : unloads a plugin", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_unload_all", ConCmdPluginUnloadAll, L"Unloads all plugins", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_unpause", ConCmdPluginUnpause, L"fs_unpause <index> : unpauses a loaded plugin", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"plugin_unpause_all", ConCmdPluginUnpauseAll, L"Unpauses all disabled plugins", 0));
	hm.AddNewHandle(0, HandleTypeConCmd, concore.AddConCmd(L"quit", ConCmdQuit, L"Exit the engine.", 0));
	ConVar *rconpasswordcvar = concore.AddConVar(L"rcon_password", L"", L"Remote console password.", 0);
	rconpasswordcvar->HookChange(ConVarHookRconPassword);
	hm.AddNewHandle(0, HandleTypeConVar, rconpasswordcvar);
	componentselectcvar = concore.AddConVar(L"sv_componentselect", 0, L"Enables component select", 0, true, 0, true, 1);
	componentselectcvar->HookChange(ConVarHookSvComponentselect);
	hm.AddNewHandle(0, HandleTypeConVar, componentselectcvar);
	ConVar *lancvar = concore.AddConVar(L"sv_lan", 1, L"Server is a lan server (no heartbeat, no authentication, no non-class C addresses).", 0, true, 0, true, 1);
	lancvar->HookChange(ConVarHookSvLan);
	hm.AddNewHandle(0, HandleTypeConVar, lancvar);
	ConVar *passwordcvar = concore.AddConVar(L"sv_password", L"", L"Server password for entry into multiplayer games", 0);
	passwordcvar->HookChange(ConVarHookSvPassword);
	hm.AddNewHandle(0, HandleTypeConVar, passwordcvar);
	ConVar *portcvar = concore.AddConVar(L"sv_port", 7777, L"Server port.", 0, true, 0, true, 65535);
	portcvar->HookChange(ConVarHookSvPort);
	hm.AddNewHandle(0, HandleTypeConVar, portcvar);
	Log::Void(L"FOUR-MP. Copyright 2009-2010 Four-mp team.");
	concore.InterpretLine(L"exec server.cfg");
	sleepcount = 1000 / SERVER_TICKRATE;
	gametime.ticksperminute = SERVER_TICKRATE * 2;
	nm.Load(playm.GetMaxPlayers(), port);
	maxplayers = playm.GetMaxPlayers();
	plugm.LoadPlugins();
	vmm.LoadFilterScripts();
	if (!vmm.LoadGameMode(gamemode))
	{
		Log::Error(L"Can't load gamemode.");
		return false;
	}
	gamemodename = vmm.GetGameModeName();
	if (!lan)
	{
		msm.Init();
	}
	this->UpdateServerInfo();
	this->UpdateCaption();
	isrunning = true;
	Log::Debug(L"Started");
	return true;
}

bool ServerCore::IsRunning(void)
{
	return isrunning;
}
void ServerCore::Tick(void)
{
	conscreen.CheckUserInput();
	nm.Tick();
	gametime.tickcount++;

	curtime = time(0);

	if (gametime.tickcount == gametime.ticksperminute)
	{
		gametime.tickcount = 0;
		this->IncrementGameTime();
		this->UpdateCaption();
	}
	if(curtime - lastcheck >= 30000)
	{
		lastcheck = curtime;
		nm.CheckClients();
	}
	if (!lan)
	{
		if (curtime - lastmasterservercheck >= 3600000)
		{
			lastmasterservercheck = curtime;
			if (!msm.RegisterServer(port, hostname, gamemodename, L"World", maxplayers, password))
			{
				Log::Warning(L"Unable to register server.");
			}
		}
	}
	long curmtime = msec_time();
	for(int i = 0; i < MAX_TIMERS; i++)
	{
		if(scripttimers[i].timeout > 0)
		{
			if(curmtime >= scripttimers[i].time)
			{
				if(!vmm.CallSomeCallback(scripttimers[i].callback, scripttimers[i].param))
				{
					KillTimer(i);
				}
				else
					scripttimers[i].time = curmtime + scripttimers[i].timeout;
			}
		}
	}
	Sleep(sleepcount);
}

void ServerCore::Unload(void)
{
	//TODO:
	//1. Politely kick all players.
	//2. Destroy all vehicles.
	vmm.UnloadGameMode(); //3. Unload all virtual machines.
	vmm.UnloadFilterScripts(); //3. Unload all virtual machines.
	plugm.UnloadPlugins(); //4. Unload all plugins.
	nm.Unload();
	//5. Clean up all remaining data - destructors.
}

void ServerCore::Shutdown(void)
{
	isrunning = false;
}

void ServerCore::UpdateServerInfo(void)
{
	if (!lan)
	{
		if (!msm.RegisterServer(port, hostname, gamemodename, L"World", maxplayers, password))
		{
			Log::Warning(L"Unable to register server.");
		}
		lastmasterservercheck = time(0);
	}
	nm.UpdateServerInfo();
}

bool ServerCore::IsLAN(void)
{
	return lan;
}

bool ServerCore::IsPasswordProtected(void)
{
	if (password == NULL)
	{
		return false;
	}
	return true;
}

wchar_t *ServerCore::GetHostname(void)
{
	if (hostname == NULL)
	{
		return NULL;
	}
	wchar_t *tempstring = (wchar_t *)calloc(wcslen(hostname) + 1, sizeof(wchar_t));
	wcscpy(tempstring, hostname);
	return tempstring;
}

bool ServerCore::GetComponentSelectStatus(void)
{
	return componentselect;
}

void ServerCore::EnableComponentSelect(bool enable)
{
	componentselect = enable;
	componentselectcvar->SetValue(enable);
}

void ServerCore::GetGameTime(unsigned char (&time)[2])
{
	memcpy(time, &gametime.time, sizeof(unsigned char) * 2);
}

bool ServerCore::SetGameTime(const unsigned char time[2])
{
	if ((time[0] >= 24) || (time[1] >= 60))
	{
		return false;
	}
	memcpy(gametime.time, time, sizeof(unsigned char) * 2);
	nm.SendGameTimeChangeToAll(gametime.time);
	return true;
}

void ServerCore::SetCmdChar(char index, wchar_t ch)
{
	if(index < 0 || index > 1) return;
	cmd_chars[index] = ch;
}
wchar_t ServerCore::GetCmdChars(char index)
{
	if(index < 0 || index > 1) return 0;
	return cmd_chars[index];
}

void ServerCore::IncrementGameTime(void)
{
	gametime.time[1]++;
	if (gametime.time[1] == 60)
	{
		gametime.time[1] = 0;
		gametime.time[0]++;
		if (gametime.time[0] == 24)
		{
			gametime.time[0] = 0;
		}
	}
}

void ServerCore::UpdateCaption(void)
{
	wchar_t caption[81];
	swprintf(caption, 81, L"FOUR-MP %02d / %02d %-58.58s %02d:%02d", playm.GetNumberOfPlayers(), playm.GetMaxPlayers(), gamemodename, gametime.time[0], gametime.time[1]);
	conscreen.SetCaption(caption);
}

int ServerCore::AddTimer(const wchar_t * callback, int timeout, int param)
{
	int i;
	for(i = 0; i < MAX_TIMERS; i++)
	{
		if(scripttimers[i].timeout <= 0) break;
	}
	wcscpy(scripttimers[i].callback, callback);
	scripttimers[i].param = param;
	scripttimers[i].timeout = timeout;
	scripttimers[i].time = msec_time() + timeout;
	return i;
}
void ServerCore::KillTimer(short timerid)
{
	memset(&scripttimers[timerid], 0, sizeof(ScriptTimer));
	Log::Info(L"Kill %d", timerid);
}