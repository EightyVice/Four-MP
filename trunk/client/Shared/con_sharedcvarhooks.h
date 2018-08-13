/// \file
/// \brief Header file that describes the four-mp console variable hooks.
/// \details This file describes only hook callbacks. They all have syntax:
/// void func(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
/// \author FaTony

#pragma once

#include "..\..\Shared\Console\ConVar.h"

void ConVarHookName(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);