#pragma once
#include "log.h"
#include "../../Shared/Console/ConsoleScreen.h"

class LogFile : public Logger
{
public:
	LogFile(wchar_t*);
	~LogFile();

	virtual void Log(const wchar_t *type, const wchar_t *string, char*);
private:
	CRITICAL_SECTION critSect;
	FILE * fileHandle;
};
