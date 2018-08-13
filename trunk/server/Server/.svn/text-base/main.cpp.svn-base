/*
*	Created:			28.10.09
*	Created by:			WNeZRoS
*	Last Modifed:		-
*/

#pragma comment (lib ,"squirrel.lib")
#pragma comment (lib ,"sqstdlib.lib")

#include "ServerCore.h"
#include "../../Shared/logging/log.h"
#include "../../Shared/logging/logFile.h"
#include "../../Shared/logging/logStd.h"
#include "HandleManager.h"
#include "CoreHandleTypesManager.h"
#include "../../Shared/Console/ConsoleCore.h"
#include "../../Shared/Console/ConsoleScreen.h"
#include "MasterServerManager.h"
#include "NetworkManager.h"
#include "PluginManager.h"
#include "VirtualMachineManager.h"
#include "PlayerManager.h"
#include "VehicleManager.h"

ServerCore server;
LogFile logfile(L"server.log");
LogStd logserver;
CoreHandleTypesManager chtm;
ConsoleCore concore;
ConsoleScreen conscreen(&concore);
PlayerManager playm;
MasterServerManager msm;
NetworkManager nm;
VirtualMachineManager vmm;
PluginManager plugm;
HandleManager hm;
VehicleManager vm;

int main()
{
	if (!server.Load())
	{
		return 1;
	}
	while (server.IsRunning())
	{
		server.Tick();
	}
	server.Unload();
	return 0;
}