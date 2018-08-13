/// \file
/// \brief Header file that describes the Squirrel console natives.
/// \details This file describes only callbacks. They all have syntax:
/// void func(HSQUIRRELVM v);
/// \author FaTony

#pragma once

#include "../sq/squirrel.h"

/// \brief Prints a string of text to the server console.
void sq_PrintToServer(HSQUIRRELVM v, const SQChar *string, ...);

/// \brief Creates a console variable and returns the handle to it.
void sq_CreateConVar(HSQUIRRELVM v);

/// \brief Returns the handle to the console variable and reserves it by the virtual machine.
void sq_FindConVar(HSQUIRRELVM v);

/// \brief Resets the console variable to its default value.
void sq_ResetConVar(HSQUIRRELVM v);

/// \brief Returns the name of a console variable.
void sq_GetConVarName(HSQUIRRELVM v);

/// \brief Returns the value of a console variable.
void sq_GetConVarFloat(HSQUIRRELVM v);

/// \brief Returns the value of a console variable.
void sq_GetConVarInt(HSQUIRRELVM v);

/// \brief Returns the value of a console variable.
void sq_GetConVarString(HSQUIRRELVM v);

/// \brief Returns the bitstring of flags on a console variable.
void sq_GetConVarFlags(HSQUIRRELVM v);

/// \brief Returns the specified bound of a console variable.
void sq_GetConVarBoundFloat(HSQUIRRELVM v);

/// \brief Returns the specified bound of a console variable.
void sq_GetConVarBoundInt(HSQUIRRELVM v);

/// \brief Sets the value of a console variable.
void sq_SetConVarFloat(HSQUIRRELVM v);

/// \brief Sets the value of a console variable.
void sq_SetConVarInt(HSQUIRRELVM v);

/// \brief Sets the value of a console variable.
void sq_SetConVarString(HSQUIRRELVM v);

/// \brief Sets the bitstring of flags on a console variable.
void sq_SetConVarFlags(HSQUIRRELVM v);

/// \brief Sets the specified bound of a console variable.
void sq_SetConVarBoundFloat(HSQUIRRELVM v);

/// \brief Sets the specified bound of a console variable.
void sq_SetConVarBoundInt(HSQUIRRELVM v);

/// \brief Creates a server-only console command.
void sq_RegServerCmd(HSQUIRRELVM v);

/// \brief Returns the number of arguments from the current console command.
void sq_GetCmdArgs(HSQUIRRELVM v);

/// \brief Returns the entire command argument string in one lump from the current console command.
void sq_GetCmdArgsAsString(HSQUIRRELVM v);

/// \brief Returns a command argument type given its index, from the current console command.
void sq_GetCmdArgType(HSQUIRRELVM v);

/// \brief Returns a command argument given its index, from the current console command.
void sq_GetCmdArgString(HSQUIRRELVM v);

/// \brief Returns a command argument given its index, from the current console command.
void sq_GetCmdArgInt(HSQUIRRELVM v);

/// \brief Returns a command argument given its index, from the current console command.
void sq_GetCmdArgFloat(HSQUIRRELVM v);

/// \brief Executes a server command as if it were on the server console.
void sq_ServerCommand(HSQUIRRELVM v);

void RegConsoleSQFunc(SQVM * v);