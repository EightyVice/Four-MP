#include "logStd.h"

LogStd::LogStd()
{
	GetLocalTime(&time);

	printf("Log stated at %02d.%02d.%04d %02d:%02d:%02d\n", 
		time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond);
}

LogStd::~LogStd()
{
}

void LogStd::Log(const wchar_t *type, const wchar_t *string, char *arglist)
{
	GetLocalTime(&time);
	if(wcslen(type) > 0)
		wprintf(L"[%02d:%02d:%02d.%03d] %s: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, type);
	else
		wprintf(L"[%02d:%02d:%02d.%03d]: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	vwprintf(string, arglist);
	wprintf(L"\n");
}

void LogStd::Log(const char *type, const char *string, char *arglist)
{
	GetLocalTime(&time);
	if(strlen(type) > 0)
		printf("[%02d:%02d:%02d.%03d] %s: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, type);
	else
		printf("[%02d:%02d:%02d.%03d]: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	vprintf(string, arglist);
	printf("\n");
}