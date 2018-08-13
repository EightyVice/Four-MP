#pragma once
#include "log.h"
#include <stdio.h>
#include <windows.h>

class LogStd : public Logger
{
public:
	LogStd();
	~LogStd();

	virtual void Log(const wchar_t *type, const wchar_t *string, char*);
	virtual void Log(const char *type, const char *string, char*);
private:
	SYSTEMTIME time;
};
