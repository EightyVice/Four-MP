#include <stdio.h>
#include <time.h>

#include "LogStd.h"
#include "../../Shared/Console/ConsoleScreen.h"

extern ConsoleScreen conscreen;

LogStd::LogStd()
{
	
}

LogStd::~LogStd()
{
	
}

void LogStd::Log(const wchar_t *type, const wchar_t *string, char *arglist)
{
	wchar_t * timestring = new wchar_t[128];
	time_t now;
	time(&now);
	wcsftime(timestring, 128, L"[%H:%M:%S]", localtime(&now));

	int sub = wcslen(type) + 3 + wcslen(timestring);
	int length = _vscwprintf(string, arglist) + 1;
	wchar_t *tempstring = (wchar_t *)calloc(length + sub, sizeof(wchar_t));

	if(wcslen(type) == 0) { sub -= 2; swprintf(tempstring, sub+2, L"%s ", timestring); }
	else swprintf(tempstring, sub+1, L"%s %s: ", timestring, type);
	vswprintf(tempstring+sub, length, string, arglist); 
	conscreen.Print(tempstring);

	delete tempstring;
	delete timestring;
}