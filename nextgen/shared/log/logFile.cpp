#include "logFile.h"

LogFile::LogFile(const char * pszFileName)
{
	InitializeCriticalSection(&critSect);

	char fileName[256];
	sprintf(fileName, "%s.txt", pszFileName);
	char tryID = 0;

	fileHandle = fopen(fileName, "a");
	while(!fileHandle)
	{
		if(tryID == 255) exit(1);

		tryID++;
		sprintf(fileName, "%s_%d.txt", pszFileName, tryID);
		fileHandle = fopen(fileName, "a");
	}

	if(fileHandle)
	{
		GetLocalTime(&time);

		fwprintf(fileHandle, L"================================================\n Log stated at %02d.%02d.%04d %02d:%02d:%02d\n", 
			time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond);
		fflush(fileHandle);

		Log::AddLogger(this);
	}
}

LogFile::~LogFile()
{
	if(fileHandle) fclose(fileHandle);
	DeleteCriticalSection(&critSect);
}

void LogFile::Log(const wchar_t *type, const wchar_t *string, char *arglist)
{
	if(!fileHandle) return;
	EnterCriticalSection(&critSect);

	GetLocalTime(&time);
	if(wcslen(type) > 0)
		fwprintf(fileHandle, L"[%02d:%02d:%02d.%03d] %s: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, type);
	else
		fwprintf(fileHandle, L"[%02d:%02d:%02d.%03d]: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	vfwprintf(fileHandle, string, arglist);
	fwprintf(fileHandle, L"\n");
	fflush(fileHandle);

	LeaveCriticalSection(&critSect);
}

void LogFile::Log(const char *type, const char *string, char *arglist)
{
	if(!fileHandle) return;
	EnterCriticalSection(&critSect);

	GetLocalTime(&time);
	if(strlen(type) > 0)
		fprintf(fileHandle, "[%02d:%02d:%02d.%03d] %s: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, type);
	else
		fprintf(fileHandle, "[%02d:%02d:%02d.%03d]: ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	vfprintf(fileHandle, string, arglist);
	fprintf(fileHandle, "\n");
	fflush(fileHandle);

	LeaveCriticalSection(&critSect);
}