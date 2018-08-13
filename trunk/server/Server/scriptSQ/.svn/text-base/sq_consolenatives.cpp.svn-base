/// \file
/// \brief Source file that contains implementation of the callbacks for the Squirrel console natives.
/// \details See sq_consolenatives.h.
/// \author FaTony

#include <stdio.h>
#include <stdarg.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "sq.h"
#include "../../../Shared/logging/log.h"
#include "../HandleManager.h"
#include "../CoreHandleTypesManager.h"
#include "../../../Shared/Console/ConsoleCore.h"
#include "../con_fmpcommands.h"
#include "../VirtualMachineManager.h"

extern HandleManager hm;
extern CoreHandleTypesManager chtm;
extern ConsoleCore concore;
extern VirtualMachineManager vmm;

// функция печати - PrintToServer(string)
void sq_PrintToServer(HSQUIRRELVM v, const SQChar *string, ...)
{
	va_list arglist;
    va_start(arglist, string);
	wchar_t *tempstring = (wchar_t *)calloc(_vscwprintf(string, arglist) + 1, sizeof(wchar_t));
	vswprintf(tempstring, string, arglist);
	Log::Info(tempstring);
	free(tempstring);
    va_end(arglist);
}

void sq_CreateConVar(HSQUIRRELVM v)
{
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushinteger(v, INVALID_HANDLE);
		return;
	}
	int args = sq_gettop(v);
	if (args < 2)
	{
		sq_pushinteger(v, INVALID_HANDLE);
		return;
	}
	const wchar_t *name;
	const wchar_t *description;
	int flags = 0;
	sq_getstring(v, 2, &name);
	if (args >= 3)
	{
		sq_getstring(v, 4, &description);
	}
	if (args >= 4)
	{
		sq_getinteger(v, 5, &flags);
	}
	switch (sq_gettype(v, 2))
	{
	case OT_STRING:
		{
			const wchar_t *value;
			sq_getstring(v, 3, &value);
			sq_pushinteger(v, hm.AddNewHandle(index + 1, HandleTypeConVar, concore.AddConVar(name, value, description, flags)));
			return;
			break;
		}
	case OT_INTEGER:
		{
			int value;
			bool hasMin = false;
			int min = 0;
			bool hasMax = false;
			int max = 0;
			sq_getinteger(v, 3, &value);
			if (args >= 6)
			{
				sq_getbool(v, 6, (SQBool *)&hasMin);
				sq_getinteger(v, 7, &min);
			}
			if (args >= 8)
			{
				sq_getbool(v, 6, (SQBool *)&hasMax);
				sq_getinteger(v, 7, &max);
			}
			sq_pushinteger(v, hm.AddNewHandle(index + 1, HandleTypeConVar, concore.AddConVar(name, value, description, flags, hasMin, min, hasMax, max)));
			return;
			break;
		}
	case OT_FLOAT:
		{
			float value;
			bool hasMin = false;
			float min = 0;
			bool hasMax = false;
			float max = 0;
			sq_getfloat(v, 3, &value);
			if (args >= 6)
			{
				sq_getbool(v, 6, (SQBool *)&hasMin);
				sq_getfloat(v, 7, &min);
			}
			if (args >= 8)
			{
				sq_getbool(v, 6, (SQBool *)&hasMax);
				sq_getfloat(v, 7, &max);
			}
			sq_pushinteger(v, hm.AddNewHandle(index + 1, HandleTypeConVar, concore.AddConVar(name, value, description, flags, hasMin, min, hasMax, max)));
			return;
			break;
		}
	}
}

void sq_FindConVar(HSQUIRRELVM v)
{
	const wchar_t *name;
	sq_getstring(v, 2, &name);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushinteger(v, INVALID_HANDLE);
		return;
	}
	sq_pushinteger(v, chtm.FindConVar(index + 1, name));
}

void sq_ResetConVar(HSQUIRRELVM v)
{
	int handle;
	sq_getinteger(v, 2, &handle);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, chtm.ResetConVar(index + 1, handle));
}

void sq_GetConVarName(HSQUIRRELVM v)
{
	int handle;
	sq_getinteger(v, 2, &handle);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	wchar_t *name = chtm.GetConVarName(index + 1, handle);
	if (name == NULL)
	{
		sq_pushnull(v);
		return;
	}
	sq_pushstring(v, name, -1);
	free(name);
}

void sq_GetConVarFloat(HSQUIRRELVM v)
{
	int handle;
	float value;
	sq_getinteger(v, 2, &handle);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	if (!chtm.GetConVarValue(index + 1, handle, value))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushfloat(v, value);
}

void sq_GetConVarInt(HSQUIRRELVM v)
{
	int handle;
	int value;
	sq_getinteger(v, 2, &handle);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	if (!chtm.GetConVarValue(index + 1, handle, value))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, value);
}

void sq_GetConVarString(HSQUIRRELVM v)
{
	int handle;
	wchar_t *value;
	sq_getinteger(v, 2, &handle);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	if (!chtm.GetConVarValue(index + 1, handle, value))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushstring(v, value, -1);
	free(value);
}

void sq_GetConVarFlags(HSQUIRRELVM v)
{
	int handle;
	int flags;
	sq_getinteger(v, 2, &handle);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	if (!chtm.GetConVarFlags(index + 1, handle, flags))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, flags);
}

void sq_GetConVarBoundFloat(HSQUIRRELVM v)
{
	int handle;
	int type;
	float bound;
	sq_getinteger(v, 2, &handle);
	sq_getinteger(v, 3, &type);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	if (!chtm.GetConVarBound(index + 1, handle, (ConVarBoundType)type, bound))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushfloat(v, bound);
}

void sq_GetConVarBoundInt(HSQUIRRELVM v)
{
	int handle;
	int type;
	int bound;
	sq_getinteger(v, 2, &handle);
	sq_getinteger(v, 3, &type);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushnull(v);
		return;
	}
	if (!chtm.GetConVarBound(index + 1, handle, (ConVarBoundType)type, bound))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, bound);
}

void sq_SetConVarFloat(HSQUIRRELVM v)
{
	int handle;
	float value;
	sq_getinteger(v, 2, &handle);
	sq_getfloat(v, 3, &value);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	if (!chtm.SetConVarValue(index + 1, handle, value))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, true);
}

void sq_SetConVarInt(HSQUIRRELVM v)
{
	int handle;
	int value;
	sq_getinteger(v, 2, &handle);
	sq_getinteger(v, 3, &value);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	if (!chtm.SetConVarValue(index + 1, handle, value))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, true);
}

void sq_SetConVarString(HSQUIRRELVM v)
{
	int handle;
	const wchar_t *value;
	sq_getinteger(v, 2, &handle);
	sq_getstring(v, 3, &value);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	if (!chtm.SetConVarValue(index + 1, handle, value))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, true);
}

void sq_SetConVarFlags(HSQUIRRELVM v)
{
	int handle;
	int flags;
	sq_getinteger(v, 2, &handle);
	sq_getinteger(v, 3, &flags);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	if (!chtm.SetConVarFlags(index + 1, handle, flags))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, true);
}

void sq_SetConVarBoundFloat(HSQUIRRELVM v)
{
	int handle;
	int type;
	unsigned int set;
	float bound;
	sq_getinteger(v, 2, &handle);
	sq_getinteger(v, 3, &type);
	sq_getbool(v, 4, &set);
	sq_getfloat(v, 5, &bound);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	if (!chtm.SetConVarBound(index + 1, handle, (ConVarBoundType)type, (bool)set, bound))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, true);
}

void sq_SetConVarBoundInt(HSQUIRRELVM v)
{
	int handle;
	int type;
	unsigned int set;
	int bound;
	sq_getinteger(v, 2, &handle);
	sq_getinteger(v, 3, &type);
	sq_getbool(v, 4, &set);
	sq_getinteger(v, 5, &bound);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		sq_pushbool(v, false);
		return;
	}
	if (!chtm.SetConVarBound(index + 1, handle, (ConVarBoundType)type, (bool)set, bound))
	{
		sq_pushbool(v, false);
		return;
	}
	sq_pushbool(v, true);
}

void sq_RegServerCmd(HSQUIRRELVM v)
{
	const wchar_t *name;
	const wchar_t *callback;
	const wchar_t *description;
	int flags;
	sq_getstring(v, 2, &name);
	sq_getstring(v, 3, &callback);
	sq_getstring(v, 4, &description);
	sq_getinteger(v, 5, &flags);
	unsigned char index;
	if (!vmm.FindVirtualMachine(&v, index))
	{
		return;
	}
	chtm.AddDynamicCommand(index + 1, callback, concore.AddConCmd(name, ConCmdDynamic, description, flags));
}

void sq_GetCmdArgs(HSQUIRRELVM v)
{
	sq_pushinteger(v, concore.GetCmdArgs());
}

void sq_GetCmdArgsAsString(HSQUIRRELVM v)
{
	wchar_t *arg = concore.GetCmdArgString();
	if (arg == NULL)
	{
		sq_pushnull(v);
		return;
	}
	sq_pushstring(v, arg, -1);
}

void sq_GetCmdArgType(HSQUIRRELVM v)
{
	int argnum;
	ConVarType type;
	sq_getinteger(v, 2, &argnum);
	if (!concore.GetCmdArgType(argnum, type))
	{
		sq_pushnull(v);
		return;
	}
	switch (type)
	{
	case ConVarTypeFloat:
		{
			sq_pushinteger(v, 0);
			break;
		}
	case ConVarTypeInt:
		{
			sq_pushinteger(v, 1);
			break;
		}
	case ConVarTypeString:
		{
			sq_pushinteger(v, 2);
			break;
		}
	}
}

void sq_GetCmdArgString(HSQUIRRELVM v)
{
	int argnum;
	wchar_t *arg;
	sq_getinteger(v, 2, &argnum);
	if (!concore.GetCmdArg(argnum, arg))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushstring(v, arg, -1);
}

void sq_GetCmdArgInt(HSQUIRRELVM v)
{
	int argnum;
	int arg;
	sq_getinteger(v, 2, &argnum);
	if (!concore.GetCmdArg(argnum, arg))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, arg);
}

void sq_GetCmdArgFloat(HSQUIRRELVM v)
{
	int argnum;
	float arg;
	sq_getinteger(v, 2, &argnum);
	if (!concore.GetCmdArg(argnum, arg))
	{
		sq_pushnull(v);
		return;
	}
	sq_pushfloat(v, arg);
}

void sq_ServerCommand(HSQUIRRELVM v)
{
	const wchar_t *cmdstring;
	sq_getstring(v, 2, &cmdstring);
	concore.InterpretLine(cmdstring);
}

void RegConsoleSQFunc(SQVM * v)
{
	register_global_func(v, (SQFUNCTION)sq_CreateConVar, L"CreateConVar");
	register_global_func(v, (SQFUNCTION)sq_FindConVar, L"FindConVar");
	register_global_func(v, (SQFUNCTION)sq_ResetConVar, L"ResetConVar");
	register_global_func(v, (SQFUNCTION)sq_GetConVarName, L"GetConVarName");
	register_global_func(v, (SQFUNCTION)sq_GetConVarFloat, L"GetConVarFloat");
	register_global_func(v, (SQFUNCTION)sq_GetConVarInt, L"GetConVarInt");
	register_global_func(v, (SQFUNCTION)sq_GetConVarString, L"GetConVarString");
	register_global_func(v, (SQFUNCTION)sq_GetConVarFlags, L"GetConVarFlags");
	register_global_func(v, (SQFUNCTION)sq_GetConVarBoundFloat, L"GetConVarBoundFloat");
	register_global_func(v, (SQFUNCTION)sq_GetConVarBoundInt, L"GetConVarBoundInt");
	register_global_func(v, (SQFUNCTION)sq_SetConVarFloat, L"SetConVarFloat");
	register_global_func(v, (SQFUNCTION)sq_SetConVarInt, L"SetConVarInt");
	register_global_func(v, (SQFUNCTION)sq_SetConVarString, L"SetConVarString");
	register_global_func(v, (SQFUNCTION)sq_SetConVarFlags, L"SetConVarFlags");
	register_global_func(v, (SQFUNCTION)sq_SetConVarBoundFloat, L"SetConVarBoundFloat");
	register_global_func(v, (SQFUNCTION)sq_SetConVarBoundInt, L"SetConVarBoundInt");
	register_global_func(v, (SQFUNCTION)sq_RegServerCmd, L"RegServerCmd");
	register_global_func(v, (SQFUNCTION)sq_GetCmdArgs, L"GetCmdArgs");
	register_global_func(v, (SQFUNCTION)sq_GetCmdArgsAsString, L"GetCmdArgsAsString");
	register_global_func(v, (SQFUNCTION)sq_GetCmdArgType, L"GetCmdArgType");
	register_global_func(v, (SQFUNCTION)sq_GetCmdArgString, L"GetCmdArgString");
	register_global_func(v, (SQFUNCTION)sq_GetCmdArgInt, L"GetCmdArgInt");
	register_global_func(v, (SQFUNCTION)sq_GetCmdArgFloat, L"GetCmdArgFloat");
	register_global_func(v, (SQFUNCTION)sq_ServerCommand, L"ServerCommand");
}