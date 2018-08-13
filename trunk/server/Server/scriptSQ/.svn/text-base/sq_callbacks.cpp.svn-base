/// \file
/// \brief Source file that contains implementation of the Squirrel callbacks.
/// \details See sq_callbacks.h.
/// \author WNeZRoS, FaTony

#include "sq_callbacks.h"

void sc_OnGameModeInit(HSQUIRRELVM v)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnGameModeInit"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_call(v, 1, 0, 1);
	}
	sq_settop(v, top);
}

void sc_OnGameModeExit(HSQUIRRELVM v)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnGameModeExit"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_call(v, 1, 0, 1);
	}
	sq_settop(v, top);
}

void sc_OnFilterScriptInit(HSQUIRRELVM v)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnFilterScriptInit"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_call(v, 1, 0, 1);
	}
	sq_settop(v, top);
}

void sc_OnFilterScriptExit(HSQUIRRELVM v)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnFilterScriptExit"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_call(v, 1, 0, 1);
	}
	sq_settop(v, top);
}

bool sc_OnPlayerConnect(HSQUIRRELVM v, const short index, const wchar_t *name)
{
	int result = 1;
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerConnect"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, index);
		sq_pushstring(v, name, -1);
		if (SQ_FAILED(sq_call(v, 3, 1, 1)))
		{
			return true;
		}
		sq_getinteger(v, sq_gettop(v), &result);
	}
	sq_settop(v, top);
	return result;
}

void sc_OnPlayerDisconnect(HSQUIRRELVM v, const short index)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerDisconnect"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, index);
		sq_call(v, 2, 0, 1);
	}
	sq_settop(v, top);
}

void sc_OnPlayerSpawn(HSQUIRRELVM v, const short index)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerSpawn"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, index);
		sq_call(v, 2, 0, 1);
	}
	sq_settop(v, top);
}

void sc_OnPlayerDeath(HSQUIRRELVM v, const short playerindex, const short killerindex, const char reason)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerDeath"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, playerindex);
		sq_pushinteger(v, killerindex);
		sq_pushinteger(v, reason);
		sq_call(v, 4, 0, 1);
	}
	sq_settop(v, top);
}

bool sc_OnPlayerText(HSQUIRRELVM v, const short index, const wchar_t *text)
{
	int result = 1;
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerText"), -1);
	if(SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, index);
		sq_pushstring(v, text, -1);
		sq_call(v, 3, 1, 1);
		sq_getinteger(v, sq_gettop(v), &result);
	}
	sq_settop(v, top);
	return result != 0;
}

bool sc_OnPlayerCommandText(HSQUIRRELVM v, const short index, const wchar_t * cmd, const wchar_t *params)
{
	int result = 1;
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerCommandText"), -1);
	if(SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, index);
		sq_pushstring(v, cmd, -1);
		sq_pushstring(v, params, -1);
		sq_call(v, 4, 1, 1);
		sq_getinteger(v, sq_gettop(v), &result);
	}
	sq_settop(v, top);
	return result != 0;
}

void sc_CommandCallback(HSQUIRRELVM v, const wchar_t *callback, const unsigned char numargs)
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, callback, -1);
	if(SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, numargs);
		sq_call(v, 2, 0, 1);
	}
	sq_settop(v, top);
}

void sc_OnPlayerShoot(HSQUIRRELVM v, const short index, float shoot[3])
{
	int top = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, _SC("OnPlayerShoot"), -1);
	if(SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, index);
		sq_pushfloat(v, shoot[0]);
		sq_pushfloat(v, shoot[1]);
		sq_pushfloat(v, shoot[2]);
		sq_call(v, 5, 0, 1);
	}
	sq_settop(v, top);
}

bool sc_CallSomeCallback(HSQUIRRELVM v, const wchar_t *callback, const int param)
{
	int top = sq_gettop(v);
	int result = 0;
	sq_pushroottable(v);

	sq_pushstring(v, callback, -1);
	if(SQ_SUCCEEDED(sq_get(v, -2))) {
		sq_pushroottable(v);
		sq_pushinteger(v, param);
		sq_call(v, 2, 1, 1);
		sq_getinteger(v, sq_gettop(v), &result);
	}
	sq_settop(v, top);
	return result == 1;
}