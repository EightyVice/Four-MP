/// \file
/// \brief Header file that describes the ConCmd class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "ConSymbolBase.h"

/// \brief A console command.
/// \details Represents a simple "bridge" between user input and function call.
/// \author FaTony

class ConCmd : public ConSymbolBase
{
public:
	/// \brief Constructor.
	/// \param[in] core Pointer to the console core this command should be attached to.
	/// \param[in] cmdname Name of the console command.
	/// \param[in] callback Callback of the console command.
	/// \param[in] desc Optional description of the console command.
	/// \param[in] cmdflags Optional bitstring of flags determining how the console command should be handled. See FCVAR_* constants for more details.
	/// \note Callback should be void func(unsigned char numargs);
	/// \note Do not explicitly call this function. Use ConsoleCore::AddConCmd() instead.
	ConCmd(ConsoleCore *core, const conchar *cmdname, void *callback, const conchar *desc = CONSTRING(""), const int cmdflags = 0);

	/// \brief Unloads all resources and removes console command from the console core.
	~ConCmd(void);

	/// \brief Executes the console command.
	/// \return No return.
	void Execute(void);
private:
	void *handler; ///< Pointer to the function that will be used as callback.
};
