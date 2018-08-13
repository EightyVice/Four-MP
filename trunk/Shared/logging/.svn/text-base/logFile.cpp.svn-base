#include "logFile.h"
#include <time.h>

LogFile::LogFile(wchar_t * filename)
{
	InitializeCriticalSection(&critSect);
	fileHandle = _wfopen(filename, L"a");
	if(!fileHandle) exit(1);
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
	if(!fileHandle) return;

	wchar_t * tempstring = new wchar_t[128];
	time_t now;
	time(&now);
	wcsftime(tempstring, 128, L"[%d.%m %H:%M:%S]", localtime(&now));
	fputws(tempstring, fileHandle);
	delete tempstring;
 
	if(wcslen(type) > 0)
		fwprintf(fileHandle, L" %s: ", type);
	else
		fwprintf(fileHandle, L": ");
	vfwprintf(fileHandle, string, arglist);
	fwprintf(fileHandle, L"\n");
	fflush(fileHandle);

	LeaveCriticalSection(&critSect);
}