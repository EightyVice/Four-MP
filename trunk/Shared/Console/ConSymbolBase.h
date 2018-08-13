/// \file
/// \brief Header file that describes the ConSymbolBase class.
/// \details See class description.
/// \author FaTony
#pragma once

#include "condefs.h"

#define FCVAR_NONE				0	///< No flags.
#define FCVAR_UNREGISTERED		(1<<0)	///< If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY	(1<<1)	///< Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL			(1<<2)	///< Defined by the game DLL.
#define FCVAR_CLIENTDLL			(1<<3)  ///< Defined by the client DLL.
#define FCVAR_HIDDEN			(1<<4)	///< Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.
#define FCVAR_PROTECTED			(1<<5)  ///< It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value.
#define FCVAR_SPONLY			(1<<6)  ///< This cvar cannot be changed by clients connected to a multiplayer server.
#define	FCVAR_ARCHIVE			(1<<7)	///< Set to cause it to be saved to vars.rc.
#define	FCVAR_NOTIFY			(1<<8)	///< Notifies players when changed.
#define	FCVAR_USERINFO			(1<<9)	///< Changes the client's info string.
#define FCVAR_PRINTABLEONLY		(1<<10) ///< This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED			(1<<11) ///< If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log.
#define FCVAR_NEVER_AS_STRING	(1<<12) ///< Never try to print that cvar.
#define FCVAR_SERVER			(1<<13)	///< Server setting enforced on clients.
#define FCVAR_CHEAT				(1<<14) ///< Only useable in singleplayer / debug / multiplayer & sv_cheats.
#define FCVAR_PLUGIN			(1<<15)	///< Defined by a 3rd party plugin.
#define FCVAR_NOT_CONNECTED		(1<<16)	///< Cvar cannot be changed by a client that is connected to a server.
#define FCVAR_SERVER_CAN_EXECUTE	(1<<17)///< The server is allowed to execute this command on clients.
#define FCVAR_SERVER_CANNOT_QUERY	(1<<18)///< If this is set, then the server is not allowed to query this cvar's value.
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<19)	//

class ConsoleCore;

/// \brief The base class that all other symbols derive from.
/// \details Describes all common properties between symbols i. e. name, description,
/// flags and functions that work with them.
/// \author FaTony

class ConSymbolBase
{
public:
	/// \brief Constructor, unused.
	ConSymbolBase(void);

	/// \brief Destructor, unused.
	~ConSymbolBase(void);

	/// \brief Returns symbol name.
	/// \return Name of the current symbol.
	conchar *GetName(void);

	/// \brief Returns symbol description.
	/// \return Description of the current symbol or zero-length string.
	conchar *GetDescription(void);

	/// \brief Returns symbol flags.
	/// \return Flags of the current symbol.
	int GetFlags(void);

	/// \brief Sets flags of the current symbol.
	/// \param[in] f Bitstring of flags determining how the symbol should be handled. See FCVAR_* constants for more details.
	void SetFlags(const int f);
protected:
	ConsoleCore *concore; ///< Pointer to the console core this symbol belongs to.
	conchar *name; ///< Holds name of the current symbol.
	conchar *description; ///< Holds description of the current symbol.
	int flags; ///< Holds flags of the current symbol.

	/// \brief Initialises all base properties of the current symbol.
	/// \param[in] core The console core this symbol will be attached to.
	/// \param[in] symbolname Name of the symbol.
	/// \param[in] desc Description of the symbol.
	/// \param[in] symbolflags Flags of the symbol.
	/// \note Used by derived classes' constructor.
	/// \return No return.
	void Init(ConsoleCore *core, const conchar *symbolname, const conchar *desc = CONSTRING(""), const int symbolflags = 0);

	/// \brief Frees all dynamically allocated memory of current symbol base.
	/// \note Used by derived classes' destructor.
	/// \return No return.
	void Uninit(void);
};
