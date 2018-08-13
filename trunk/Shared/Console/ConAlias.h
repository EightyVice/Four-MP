/// \file
/// \brief Header file that describes the ConAlias class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "ConSymbolBase.h"

/// \brief A console alias.
/// \details Represents a user defined macro command that executes several registered ones..
/// \author FaTony

class ConAlias : public ConSymbolBase
{
public:
	/// \brief Constructor.
	/// \param[in] core Pointer to the console core this command should be attached to.
	/// \param[in] aliasname Name of the console alias.
	/// \param[in] cmdstring A command string that will be interpreted when the alias is invoked.
	/// \note Do not explicitly call this function. Use 'alias' command during runtime instead.
	ConAlias(ConsoleCore *core, const conchar *aliasname, const conchar *cmdstring = CONSTRING(""));

	/// \brief Destructor.
	~ConAlias(void);

	/// \brief Sets the command string of the console alias.
	/// \param[in] string A command string that will be interpreted when the alias is invoked.
	/// \return No return.
	void SetCommandString(const conchar *string);

	/// \brief Executes the console alias.
	/// \return No return.
	void Execute(void);
};
