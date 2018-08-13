// ConsoleClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Shared/ClientCore.h"
#include "../../Shared/Console/ConsoleCore.h"
#include "../../Shared/Console/ConsoleScreen.h"
#include "../Shared/NetworkManager.h"

#include "../../Shared/logging/log.h"
#include "../../Shared/logging/logFile.h"
#include "../../Shared/logging/logStd.h"

ClientCore client;
ConsoleCore concore;
ConsoleScreen conscreen(&concore);
NetworkManager nm;

LogFile logfile(L"log.txt");
LogStd logclient;

int _tmain(int argc, _TCHAR* argv[])
{
	Log::SetState( LOG_INFO|LOG_ERROR|LOG_WARNING|LOG_DEBUG );
	Log::AddLogger(&logfile);
	Log::AddLogger(&logclient);

	if (!client.Load())
	{
		return 1;
	}
	while (client.IsRunning())
	{
		client.Tick();
	}
	client.Unload();
	return 0;
}

