#include <windows.h>
#include <stdarg.h>
#include <vector>

#include "log.h"

class critical_section
{
	CRITICAL_SECTION _cs;
public:
	critical_section() { InitializeCriticalSection(&_cs); }
	~critical_section() { DeleteCriticalSection(&_cs); }

	void Enter() { EnterCriticalSection(&_cs); }
	void Leave() { LeaveCriticalSection(&_cs); }
};

namespace Log
{
	critical_section critSect;
	std::vector<Logger*> logging;
	bool b_Debug = 1;
	bool b_Info = 1;
	bool b_Error = 1;
	bool b_Warning = 1;
	bool b_Logging = 1;

	void SetState(unsigned int state)
	{
		b_Debug = 0;
		b_Info = 0;
		b_Error = 0;
		b_Warning = 0;

		while(state > 0)
		{
			if(state >= LOG_WARNING)
			{
				b_Warning = 1;
				state -= LOG_WARNING;
			}
			if(state >= LOG_ERROR)
			{
				b_Error = 1;
				state -= LOG_ERROR;
			}
			if(state >= LOG_INFO)
			{
				b_Info = 1;
				state -= LOG_INFO;
			}
			if(state >= LOG_DEBUG)
			{
				b_Debug = 1;
				state -= LOG_DEBUG;
			}
			if(state >= LOG_ON)
			{
				b_Logging = 1;
				state -= LOG_ON;
			}
		}

		b_Logging = b_Logging || b_Debug || b_Info || b_Error || b_Warning;
	}

	void AddLogger(Logger* iLog)
	{
		logging.push_back(iLog);
	}

	void Log::Debug(const wchar_t *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Debug) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(L"Debug", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Info(const wchar_t *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Info) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(L"Info", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Error(const wchar_t *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Error) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(L"Error", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Warning(const wchar_t *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Warning) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(L"Warning", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Other(const wchar_t *type, const wchar_t *string, ...)
	{
		if(logging.size() == 0 || !b_Logging) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(type, string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Void(const wchar_t *string, ...)
	{
		if(logging.size() == 0 || !b_Logging) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(L"", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}

	void Log::Debug(const char *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Debug) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log("Debug", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Info(const char *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Info) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log("Info", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Error(const char *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Error) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log("Error", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Warning(const char *string, ...)
	{
		if(logging.size() == 0 || !b_Logging || !b_Warning) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log("Warning", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Other(const char *type, const char *string, ...)
	{
		if(logging.size() == 0 || !b_Logging) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log(type, string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
	void Void(const char *string, ...)
	{
		if(logging.size() == 0 || !b_Logging) return;

		critSect.Enter();
		va_list arglist;
		va_start(arglist, string);
		for(int i = 0; i < (int)logging.size(); i++)
			if(logging[i]) logging[i]->Log("", string, arglist);
		va_end(arglist);
		critSect.Leave();
	}
};
