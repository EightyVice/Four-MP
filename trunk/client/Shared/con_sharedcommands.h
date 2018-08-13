/// \file
/// \brief Header file that describes the four-mp client shared console commands.
/// \details This file describes only command callbacks. They all have syntax:
/// void func(const ConsoleCore *concore, const unsigned char numargs);
/// \author FaTony

#pragma once

#include "..\..\Shared\Console\ConsoleCore.h"

/// \brief Connect to specified server.
void ConCmdConnect(ConsoleCore *concore, const unsigned char numargs);

/// \brief Exit the engine.
void ConCmdQuit(ConsoleCore *concore, const unsigned char numargs);