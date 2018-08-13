#pragma once
#include <vector>
#include <windows.h>

#define LOG_NONE	0x0
#define LOG_ON		0x1
#define LOG_DEBUG	0x2
#define LOG_INFO	0x4
#define LOG_ERROR	0x8
#define LOG_WARNING 0x10

class Logger
{
public:
	virtual void Log(const wchar_t *type, const wchar_t *string, char*) = 0;
};

class critical_section
{
        CRITICAL_SECTION _cs;
public:
        critical_section() { InitializeCriticalSection(&_cs); }
        ~critical_section() { DeleteCriticalSection(&_cs); }

        void Enter() { EnterCriticalSection(&_cs); }
        void Leave() { LeaveCriticalSection(&_cs); }
};


class Log
{
public:
	static void AddLogger(Logger* iLog);
	static void SetState(unsigned int state);

	static void Debug(const wchar_t *string, ...);
	static void Info(const wchar_t *string, ...);
	static void Error(const wchar_t *string, ...);
	static void Warning(const wchar_t *string, ...);
	static void Other(const wchar_t *type, const wchar_t *string, ...);
	static void Void(const wchar_t *string, ...);
private:
	static critical_section critSect;
	static std::vector<Logger*> logging;
	static bool b_Debug;
	static bool b_Info;
	static bool b_Error;
	static bool b_Warning;
	static bool b_Logging;
};
