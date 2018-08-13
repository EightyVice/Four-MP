#pragma once

#include "../../Shared/Console/ConVar.h"

class ServerCore
{
public:
	ServerCore(void);
	~ServerCore(void);
	bool Load(void);
	bool IsRunning(void);
	void Tick(void);
	void Unload(void);
	void Shutdown(void);
	void UpdateServerInfo(void);
	bool IsLAN(void);
	bool IsPasswordProtected(void);
	wchar_t *GetHostname(void);
	bool GetComponentSelectStatus(void);
	void EnableComponentSelect(bool enable);
	void GetGameTime(unsigned char (&timebuffer)[2]);
	bool SetGameTime(const unsigned char time[2]);
	void SetCmdChar(char index, wchar_t ch);
	wchar_t GetCmdChars(char index);
	int AddTimer(const wchar_t * callback, int timeout, int param);
	void KillTimer(short timerid);
private:
	bool isrunning;
	short sleepcount;
	unsigned int lastcheck;
	unsigned int lastmasterservercheck;
	wchar_t *hostname;
	unsigned short port;
	bool lan;
	short maxplayers;
	wchar_t *gamemode;
	wchar_t *gamemodename;
	wchar_t *password;
	wchar_t *rconpassword;
	bool componentselect;
	ConVar *componentselectcvar;
	time_t curtime;
	struct GameTime
	{
		short ticksperminute;
		short tickcount;
		unsigned char time[2];
	};
	struct ScriptTimer
	{
		wchar_t callback[256];
		int timeout;
		int param;
		long time;
	};
#define MAX_TIMERS 32
	ScriptTimer scripttimers[MAX_TIMERS];
	GameTime gametime;
	wchar_t cmd_chars[2];
	void IncrementGameTime(void);
	void UpdateCaption(void);
	friend void ConVarHookHostGamemode(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	friend void ConVarHookHostname(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	friend void ConVarHookRconPassword(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	friend void ConVarHookSvComponentselect(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	friend void ConVarHookSvLan(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	friend void ConVarHookSvPassword(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	friend void ConVarHookSvPort(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
};
