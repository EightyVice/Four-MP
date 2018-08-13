/// \file
/// \brief Main header that describes the ConsoleCore class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "condefs.h"
#include "ConVar.h"
#include "ConCmd.h"
#include "ConAlias.h"

/// \brief The main class that handles all logic behind the console.
/// \details Console Core is a system responsible for interpreting text commands. It takes
/// string of text as input and translates it into function calls. It also keeps track of
/// all associated variables and commands and dynamically loads and unloads them. It
/// recieves input as char * and use developer-defined function to output text so any
/// developer can easily code a wrapper around it.
/// \author FaTony

class ConsoleCore
{
public:

	/// \brief Inits the core.
	ConsoleCore(void);

	/// \brief Unloads everything.
	~ConsoleCore(void);

	/// \brief Sets which function the console will use to output text.
	/// \param[in] function Pointer to the function.
	/// \note Function should be void func(const conchar *string); or void func(const conchar *string, ...);
	/// \return No return.
	void SetOutputFunction(void *function);

	/// \brief Sets the path which is used to locate files for the exec command.
	/// \param[in] string Path to use.
	/// \return No return.
	void SetExecPath(const conchar *string);

	/// \brief Registers standard console variables and commands.
	/// \return No return.
	void RegisterStandardLibrary(void);

	/// \brief Outputs text into the outside function.
	/// \param[in] string Format-control string.
	/// \param[in] ... Optional arguments.
	/// \return No return.
	void Output(const conchar *string, ...);

	/// \brief Returns total number of console symbols.
	/// \return Total number of console symbols.
	unsigned short GetNumberOfConsoleSymbols(void);

	/// \brief Checks if console symbol exists
	/// \param[in] name Name of the console symbol.
	/// \return True if the symbol exists, false otherwise.
	bool IsConsoleSymbolExist(const conchar *name); 

	/// \brief Adds console variable into symbol buffer and returns pointer to it.
	/// \param[in] name Name of the console variable.
	/// \param[in] defaultvalue Default value of the console variable.
	/// \param[in] description Optional description of the console variable.
	/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \param[in] hasMin Optional boolean that determines if the console variable has a minimum value.
	/// \param[in] min Minimum value that the console variable can have if hasMin is true.
	/// \param[in] hasMax Optional boolean that determines if the console variable has a maximum value.
	/// \param[in] max Maximum value that the console variable can have if hasMax is true.
	/// \return Pointer to the console variable on success, NULL otherwise.
	ConVar *AddConVar(const conchar *name, const float defaultvalue, const conchar *description = CONSTRING(""), const int flags = 0, const bool hasMin = false, const float min = 0.0, const bool hasMax = false, const float max = 0.0);

	/// \brief Adds console variable into symbol buffer and returns pointer to it.
	/// \param[in] name Name of the console variable.
	/// \param[in] defaultvalue Default value of the console variable.
	/// \param[in] description Optional description of the console variable.
	/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \param[in] hasMin Optional boolean that determines if the console variable has a minimum value.
	/// \param[in] min Minimum value that the console variable can have if hasMin is true.
	/// \param[in] hasMax Optional boolean that determines if the console variable has a maximum value.
	/// \param[in] max Maximum value that the console variable can have if hasMax is true.
	/// \return Pointer to the console variable on success, NULL otherwise.
	ConVar *AddConVar(const conchar *name, const int defaultvalue, const conchar *description = CONSTRING(""), const int flags = 0, const bool hasMin = false, const int min = 0, const bool hasMax = false, const int max = 0);

	/// \brief Adds console variable into symbol buffer and returns pointer to it.
	/// \param[in] name Name of the console variable.
	/// \param[in] defaultvalue Default value of the console variable.
	/// \param[in] description Optional description of the console variable.
	/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \return Pointer to the console variable on success, NULL otherwise.
	ConVar *AddConVar(const conchar *name, const conchar *defaultvalue, const conchar *description = CONSTRING(""), const int flags = 0);

	/// \brief Adds console command into symbol buffer and returns pointer to it.
	/// \param[in] name Name of the console command.
	/// \param[in] callback A function to use as a callback for when the command is invoked.
	/// \param[in] description Optional description of the console command.
	/// \param[in] flags Optional bitstring of flags determining how the console command should be handled. See FCVAR_* constants for more details.
	/// \note Callback should be void func(unsigned char numargs);
	/// \return Pointer to the console command on success, NULL otherwise.
	ConCmd *AddConCmd(const conchar *name, void *callback, const conchar *description = CONSTRING(""), const int flags = 0);

	/// \brief Returns help string of given symbol.
	/// \param[in] name Name of the console symbol to search for.
	/// \return Help string on success, NULL otherwise.
	conchar *GetConsoleSymbolHelpString(const conchar *name);

	/// \brief Returns help string of given symbol index.
	/// \param[in] index Index of the console symbol.
	/// \return Help string on success, NULL otherwise.
	conchar *GetConsoleSymbolHelpStringByIndex(unsigned short index);

	/// \brief Returns the number of arguments from the current console command.
	/// \return Number of arguments from the current console command.
	unsigned char GetCmdArgs(void);

	/// \brief Retrieves the entire command argument string in one lump from the current console command.
	/// \return Arguments string on success, NULL otherwise.
	conchar *GetCmdArgString(void);

	/// \brief Retrieves a command argument type given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] type Buffer to use for storing the type.
	/// \return True on success, false otherwise.
	bool GetCmdArgType(const unsigned char argnum, ConVarType &type);

	/// \brief Retrieves a command argument given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] arg Buffer to use for storing the value.
	/// \return True on success, false otherwise.
	bool GetCmdArg(const unsigned char argnum, conchar *&arg);

	/// \brief Retrieves a command argument given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] arg Buffer to use for storing the value.
	/// \return True on success, false otherwise.
	bool GetCmdArg(const unsigned char argnum, int &arg);

	/// \brief Retrieves a command argument given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] arg Buffer to use for storing the value.
	/// \return True on success, false otherwise.
	bool GetCmdArg(const unsigned char argnum, float &arg);

	//TODO: add ... ?
	/// \brief Interprets line.
	/// \param[in] string Line of text to interpret.
	/// \note The input string can contain several commands separated by ;.
	/// \return No return.
	void InterpretLine(const conchar *string);
private:
	void *outputfunction; ///< Holds the pointer to the function which is used to output text.
	conchar *execpath; ///< Holds the path which is used to locate files for the exec command.

	/// \brief Indicates the type of console symbol.
	enum ConsoleSymbolType
	{
		ConsoleSymbolTypeConVar, ///< Indicates a console variable.
		ConsoleSymbolTypeConCmd, ///< Indicates a console command.
		ConsoleSymbolTypeConAlias ///< Indicates a console alias.
	};

	/// \brief Used to wisely work with console symbol.
	union ConsoleSymbolPtr
	{
		ConVar *convar; ///< Used to work with console variable.
		ConCmd *concmd; ///< Used to work with console command.
		ConAlias *conalias; ///< Used to work with console alias.
	};

	/// \brief Describes a console symbol.
	/// \details Console symbol is a unified structure that console uses to keep track of 
	/// all variables and commands registered to it.
	struct ConsoleSymbol
	{
		conchar *name; ///< Name of the console symbol.
		ConsoleSymbolType type; ///< Type of the console symbol.
		ConsoleSymbolPtr *ptr; ///< Pointer to the underlying class.
		unsigned char numcmds; ///< If console symbol is a console command, this indicates the number of commands that share this symbol's name.
	};
	unsigned short maxsymbolbuffersize; ///< Holds maximum size of the symbol buffer.
	unsigned short symbolbuffersize; ///< Holds current size of the symbol buffer.
	ConsoleSymbol *symbolbuffer; ///< Holds all registered console symbols.
	unsigned char maxhookspercvar; ///< Holds maximum number of hooks per 1 console variable.
	unsigned char maxcmdspersymbol; ///< Holds maximum number of commands per 1 console symbol.
	conchar *commandbuffer; ///< Holds current command string.
	conchar **commandargs; ///< Holds arguments of current command.
	unsigned int argpos; ///< Holds starting index of first argument in the current command.
	unsigned char numargs; ///< Holds number of arguments in the current command.

	/// \brief Adds console alias into symbol buffer.
	/// \param[in] name Name of the console alias.
	/// \param[in] cmdstring A command string that will be interpreted when the alias is invoked.
	/// \return No return.
	void AddConAlias(const conchar *name, const conchar *cmdstring = CONSTRING(""));

	/// \brief Deletes console symbol from symbol buffer by it's index.
	/// \param[in] index Index of the console symbol.
	/// \return True on success, false otherwise.
	bool DeleteConsoleSymbolByIndex(const unsigned short index);

	/// \brief Deletes console variable from symbol buffer
	/// \param[in] name Name of the console variable.
	/// \note This function is used only by ConVar's destructor.
	/// \return No return.
	void DeleteConVar(const conchar *name);

	/// \brief Deletes console command from symbol buffer.
	/// \param[in] name Name of the console command.
	/// \param[in] ptr Pointer to the console command.
	/// \note This function is used only by ConCmd's destructor.
	/// \return No return.
	void DeleteConCmd(const conchar *name, ConCmd *ptr);

	/// \brief Retrieves symbol index by it's name.
	/// \param[in] name Name of the console symbol.
	/// \param[out] index Index of the console symbol.
	/// \return True on success, false otherwise.
	bool GetConsoleSymbolIndex(const conchar *name, unsigned short &index);

	/// \brief Returns help string of given symbol.
	/// \param[in] symbol Console symbol to work with.
	/// \return Help string on success, NULL otherwise.
	conchar *GetHelpString(const ConsoleSymbol *symbol);

	/// \brief Gets command string from multicommand string starting from startindex.
	/// \param[in] string Source input string to search in.
	/// \param[in] startindex Index to start search from.
	/// \return String containing 1 command on success, zero-length string otherwise.
	conchar *GetCommand(const conchar *string, const unsigned int startindex);

	/// \brief Interprets prepared command.
	/// \return False if the command ends in a comment, true otherwise.
	bool InterpretCommand(void);
	friend class ConVar; ///< See ConVar.h
	friend class ConCmd; ///< See ConCmd.h
	friend class ConAlias; ///< See ConAlias.h
	friend void ConCmdAlias(ConsoleCore *concore, const unsigned char numargs); ///< See coreconcommands.h
	friend void ConCmdCvarlist(ConsoleCore *concore, const unsigned char numargs); ///< See coreconcommands.h
	friend void ConCmdExec(ConsoleCore *concore, const unsigned char numargs); ///< See coreconcommands.h
};
