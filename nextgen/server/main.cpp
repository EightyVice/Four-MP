#include <stdio.h>
#include "network/CNetwork.h"
#include "main.h"
#include "log/log.h"
#include "log/logFile.h"
#include "log/logStd.h"

CNetwork * pNetwork;

int main(int argc, char *argv[])
{
	LogFile * pLogFile = new LogFile("server_log");
	LogStd * pLogStd = new LogStd();
	Log::AddLogger(pLogFile);
	Log::AddLogger(pLogStd);
	Log::Void("FOUR-MP Server %s loaded", FMP_VERSION);

	// Initialize
	pNetwork = new CNetwork;

	// Work
	while(pNetwork->IsReady())
	{
		pNetwork->Tick();
		Sleep(33);
	}

	// Uninitialize
	delete pNetwork;
	delete pLogFile;
	delete pLogStd;
	return 0;
}