/// \file
/// \brief Header file that describes the IPluginHandlerInterface class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "../../Shared/Console/ConVar.h"
#include "IPluginInterface.h"

/// \brief A plugin handler interface.
/// \details It declares all host functions that plugins can directly call. Most of them
/// takes pointer to the plugin as argument, use "this".
/// \author FaTony

class IPluginHandlerInterface
{
public:
	//------------------------------------------------------------------------------------
	// Handles
	//------------------------------------------------------------------------------------

	/// \brief Releases all handle types reserved by a plugin.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \return No return.
	virtual void ReleaseAllHandleTypes(const IPluginInterface *plugin) = 0;

	/// \brief Reserves an empty handle type and retieves it to a plugin.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[out] index Index of the handle type.
	/// \return True on success, false otherwise.
	virtual bool RequestNewHandleType(const IPluginInterface *plugin, unsigned short &index) = 0;

	/// \brief Releases handle type that was reserved by a plugin.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] index Index of the handle type.
	/// \return True on success, false otherwise.
	virtual bool ReleaseHandleType(const IPluginInterface *plugin, const unsigned short &index) = 0;

	//------------------------------------------------------------------------------------
	// Console
	//------------------------------------------------------------------------------------

	/// \brief Prints a string of text to the server console.
	/// \param[in] string Format-control string.
	/// \param[in] ... Optional arguments.
	/// \return No return.
	virtual void PrintToServer(const wchar_t *string, ...) = 0;

	/// \brief Creates a console variable and returns the handle to it.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] name Name of the console variable.
	/// \param[in] defaultvalue Default value of the console variable.
	/// \param[in] description Optional description of the console variable.
	/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \param[in] hasMin Optional boolean that determines if the console variable has a minimum value.
	/// \param[in] min Minimum value that the console variable can have if hasMin is true.
	/// \param[in] hasMax Optional boolean that determines if the console variable has a maximum value.
	/// \param[in] max Maximum value that the console variable can have if hasMax is true.
	/// \return Handle to the console variable on success, INVALID_HANDLE otherwise.
	virtual int CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const float defaultvalue, const wchar_t *description = L"", const int flags = 0, const bool hasMin = false, const float min = 0.0, const bool hasMax = false, const float max = 0.0) = 0;

	/// \brief Creates a console variable and returns the handle to it.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] name Name of the console variable.
	/// \param[in] defaultvalue Default value of the console variable.
	/// \param[in] description Optional description of the console variable.
	/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \param[in] hasMin Optional boolean that determines if the console variable has a minimum value.
	/// \param[in] min Minimum value that the console variable can have if hasMin is true.
	/// \param[in] hasMax Optional boolean that determines if the console variable has a maximum value.
	/// \param[in] max Maximum value that the console variable can have if hasMax is true.
	/// \return Handle to the console variable on success, INVALID_HANDLE otherwise.
	virtual int CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const int defaultvalue, const wchar_t *description = L"", const int flags = 0, const bool hasMin = false, const int min = 0, const bool hasMax = false, const int max = 0) = 0;

	/// \brief Creates a console variable and returns the handle to it.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] name Name of the console variable.
	/// \param[in] defaultvalue Default value of the console variable.
	/// \param[in] description Optional description of the console variable.
	/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \return Handle to the console variable on success, INVALID_HANDLE otherwise.
	virtual int CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const wchar_t *defaultvalue, const wchar_t *description = L"", const int flags = 0) = 0;

	/// \brief Returns the handle to the console variable and reserves it by the plugin.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] name Name of the console variable to search for.
	/// \return Handle index on success, INVALID_HANDLE otherwise.
	virtual int FindConVar(const IPluginInterface *plugin, const wchar_t *name) = 0;

	/// \brief Resets the console variable to its default value.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \return True on success, false otherwise.
	virtual bool ResetConVar(const IPluginInterface *plugin, const int handle) = 0;

	/// \brief Returns the name of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \return Name on success, NULL otherwise.
	virtual wchar_t *GetConVarName(const IPluginInterface *plugin, const int handle) = 0;

	/// \brief Retrieves the value of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the value in.
	/// \return True on success, false otherwise.
	virtual bool GetConVarValue(const IPluginInterface *plugin, const int handle, float &value) = 0;

	/// \brief Retrieves the value of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the value in.
	/// \return True on success, false otherwise.
	virtual bool GetConVarValue(const IPluginInterface *plugin, const int handle, int &value) = 0;

	/// \brief Retrieves the value of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the value in.
	/// \return True on success, false otherwise.
	virtual bool GetConVarValue(const IPluginInterface *plugin, const int handle, wchar_t *&value) = 0;

	/// \brief Retrieves the bitstring of flags on a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] flags Buffer to store the flags in.
	/// \return True on success, false otherwise.
	virtual bool GetConVarFlags(const IPluginInterface *plugin, const int handle, int &flags) = 0;

	/// \brief Retrieves the specified bound of a console variable. 
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of bound to retrieve.
	/// \param[out] bound Buffer to store the bound value in.
	/// \return True on success, false otherwise.
	virtual bool GetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, float &bound) = 0;

	/// \brief Retrieves the specified bound of a console variable. 
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of bound to retrieve.
	/// \param[out] bound Buffer to store the bound value in.
	/// \return True on success, false otherwise.
	virtual bool GetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, int &bound) = 0;

	/// \brief Sets the value of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] value The value to set.
	/// \return True on success, false otherwise.
	virtual bool SetConVarValue(const IPluginInterface *plugin, const int handle, const float value) = 0;

	/// \brief Sets the value of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] value The value to set.
	/// \return True on success, false otherwise.
	virtual bool SetConVarValue(const IPluginInterface *plugin, const int handle, const int value) = 0;

	/// \brief Sets the value of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] value The value to set.
	/// \return True on success, false otherwise.
	virtual bool SetConVarValue(const IPluginInterface *plugin, const int handle, const wchar_t *value) = 0;

	/// \brief Sets the bitstring of flags on a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] flags A bitstring containing the FCVAR_* flags to enable.
	/// \return True on success, false otherwise.
	virtual bool SetConVarFlags(const IPluginInterface *plugin, const int handle, const int flags) = 0;

	/// \brief Sets the specified bound of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of the bound to set.
	/// \param[in] set True to set, false to remove.
	/// \param[out] bound Value of the bound to set.
	/// \return True on success, false otherwise.
	virtual bool SetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType, const bool set, const float bound) = 0;

	/// \brief Sets the specified bound of a console variable.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of the bound to set.
	/// \param[in] set True to set, false to remove.
	/// \param[out] bound Value of the bound to set.
	/// \return True on success, false otherwise.
	virtual bool SetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType, const bool set, const int bound) = 0;

	/// \brief Creates a server-only console command.
	/// \param[in] plugin Pointer to the plugin that calls this function.
	/// \param[in] name Name of the console command.
	/// \param[in] callback A function to use as a callback for when the command is invoked.
	/// \param[in] description Optional description of the console command.
	/// \param[in] flags Optional bitstring of flags determining how the console command should be handled. See FCVAR_* constants for more details.
	/// \note Callback should be void func(const unsigned char numargs);
	/// \return No return.
	virtual void RegServerCmd(const IPluginInterface *plugin, const wchar_t *name, void *callback, const wchar_t *description = L"", const int flags = 0) = 0;

	/// \brief Returns the number of arguments from the current console command.
	/// \return Number of arguments from the current console command.
	virtual unsigned char GetCmdArgs(void) = 0;

	/// \brief Retrieves the entire command argument string in one lump from the current console command.
	/// \return Arguments string on success, NULL otherwise.
	virtual wchar_t *GetCmdArgString(void) = 0;

	/// \brief Retrieves a command argument type given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] type Buffer to use for storing the type.
	/// \return True on success, false otherwise.
	virtual bool GetCmdArgType(const unsigned char argnum, ConVarType &type) = 0;

	/// \brief Retrieves a command argument given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] arg Buffer to use for storing the value.
	/// \return True on success, false otherwise.
	virtual bool GetCmdArg(const unsigned char argnum, wchar_t *&arg) = 0;

	/// \brief Retrieves a command argument given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] arg Buffer to use for storing the value.
	/// \return True on success, false otherwise.
	virtual bool GetCmdArg(const unsigned char argnum, int &arg) = 0;

	/// \brief Retrieves a command argument given its index, from the current console command.
	/// \param[in] argnum Argument number to retrieve.
	/// \param[out] arg Buffer to use for storing the value.
	/// \return True on success, false otherwise.
	virtual bool GetCmdArg(const unsigned char argnum, float &arg) = 0;

	/// \brief Executes a server command as if it were on the server console.
	/// \param[in] string String to execute.
	/// \note The input string can contain several commands separated by ;.
	/// \return No return.
	virtual void ServerCommand(const wchar_t *string) = 0;
};