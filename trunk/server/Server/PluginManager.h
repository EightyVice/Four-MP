/// \file
/// \brief Header file that describes the PluginManager class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "IPluginHandlerInterface.h"

#ifdef WIN32
#include <windows.h>
#endif

/// \brief A plugin manager. It handles plugin operations.
/// \details Plugins are dynamic libraries written in C++ that get linked to the host at
/// runtime. Plugin manager loads them, link them, calls their functions and handle all
/// their calls to the host.
/// \author FaTony

class PluginManager
{
public:
	/// \brief Constructor. Should be called after VirtualMachineManager.
	PluginManager(void);

	/// \brief Desctructor.
	~PluginManager(void);

	/// \brief Returns the maximum plugin buffer size.
	/// \return Maximum plugin buffer size.
	unsigned char GetMaxPluginBufferSize(void);

	/// \brief Return the current plugin buffer size.
	/// \return Current plugin buffer size.
	unsigned char GetPluginBufferSize(void);

	/// \brief Loads all plugins.
	/// \return No return.
	void LoadPlugins(void);

	/// \brief Unloads all plugins.
	/// \return No return.
	void UnloadPlugins(void);

	/// \brief Reloads all plugins.
	/// \return No return.
	void ReloadPlugins(void);

	/// \brief Pauses all plugins.
	/// \return No return.
	void PausePlugins(void);

	/// \brief Unpauses all plugins.
	/// \return No return.
	void UnpausePlugins(void);

	/// \brief Checks if the plugin is loaded.
	/// \param[in] string Name of the file.
	/// \return True if the plugin is loaded, false otherwise.
	bool IsPluginLoaded(const wchar_t *string);

	/// \brief Loads a plugin.
	/// \param[in] string Name of the file.
	/// \return True on success, false otherwise.
	bool LoadPlugin(const wchar_t *string);

	/// \brief Unloads a plugin.
	/// \param[in] index Index of the plugin.
	/// \return True on success, false otherwise.
	bool UnloadPlugin(const unsigned char index);

	/// \brief Reloads a plugin.
	/// \param[in] index Index of the plugin.
	/// \return True on success, false otherwise.
	bool ReloadPlugin(const unsigned char index);

	/// \brief Pauses a plugin.
	/// \param[in] index Index of the plugin.
	/// \return True on success, false otherwise.
	bool PausePlugin(const unsigned char index);

	/// \brief Unpauses a plugin.
	/// \param[in] index Index of the plugin.
	/// \return True on success, false otherwise.
	bool UnpausePlugin(const unsigned char index);

	/// \brief Returns the plugin info string.
	/// \param[in] index Index of the plugin.
	/// \return Info string on success, NULL otherwise.
	wchar_t *GetPluginInfoString(const unsigned char index);

	/// \brief Returns the pointer to the plugin handler interface.
	/// \note Used by plugins to call the host.
	/// \return Pointer to the plugin handler interface.
	IPluginHandlerInterface *GetPluginHandler(void);
private:
	short handleowneroffset; ///< Holds the offset of the plugins in the handle buffer.
	/// \brief Describes the plugin.
	struct Plugin
	{
		bool paused; ///< Holds true if the plugin is paused, false otherwise.
	#ifdef WIN32
		HMODULE module; ///< Holds Win32-specific module of the plugin.
	#endif
		IPluginInterface *ptr; ///< Holds the pointer to the plugin interface. Used by host to call the plugin functions.
		wchar_t *filename; ///< Holds the name of the plugin file.
	};
	unsigned char maxpluginbuffersize; ///< Holds the maximum size of the plugin buffer.
	unsigned char pluginbuffersize; ///< Holds the current size of the plugin buffer.
	Plugin **pluginbuffer; ///< Holds all plugins.

	/// \brief A plugin handler. It is used by plugins to call the host functions.
	/// \details Since the interaction between the host and plugins is done using
	/// interfaces and plugins only knows it's interface, they can only call the functions
	/// that are implemented in this class. Most of them takes the pointer to the plugin
	/// interface to identify which plugin called them.

	class PluginHandler : public IPluginHandlerInterface
	{
	public:
		/// \brief Constructor. Unused.
		PluginHandler(void);

		/// \brief Destructor. Unused.
		~PluginHandler(void);

		/// \brief Releases all handle types reserved by a plugin.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \return No return.
		virtual void ReleaseAllHandleTypes(const IPluginInterface *plugin);

		/// \brief Reserves an empty handle type and retieves it to a plugin.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[out] index Index of the handle type.
		/// \return True on success, false otherwise.
		virtual bool RequestNewHandleType(const IPluginInterface *plugin, unsigned short &index);

		/// \brief Releases handle type that was reserved by a plugin.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] index Index of the handle type.
		/// \return True on success, false otherwise.
		virtual bool ReleaseHandleType(const IPluginInterface *plugin, const unsigned short &index);

		/// \brief Prints a string of text to the server console.
		/// \param[in] string Format-control string.
		/// \param[in] ... Optional arguments.
		/// \return No return.
		virtual void PrintToServer(const wchar_t *string, ...);

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
		virtual int CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const float defaultvalue, const wchar_t *description = L"", const int flags = 0, const bool hasMin = false, const float min = 0.0, const bool hasMax = false, const float max = 0.0);

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
		virtual int CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const int defaultvalue, const wchar_t *description = L"", const int flags = 0, const bool hasMin = false, const int min = 0, const bool hasMax = false, const int max = 0);

		/// \brief Creates a console variable and returns the handle to it.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] name Name of the console variable.
		/// \param[in] defaultvalue Default value of the console variable.
		/// \param[in] description Optional description of the console variable.
		/// \param[in] flags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
		/// \return Handle to the console variable on success, INVALID_HANDLE otherwise.
		virtual int CreateConVar(const IPluginInterface *plugin, const wchar_t *name, const wchar_t *defaultvalue, const wchar_t *description = L"", const int flags = 0);

		/// \brief Returns the handle to the console variable and reserves it by the plugin.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] name Name of the console variable to search for.
		/// \return Handle index on success, INVALID_HANDLE otherwise.
		virtual int FindConVar(const IPluginInterface *plugin, const wchar_t *name);

		/// \brief Resets the console variable to its default value.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \return True on success, false otherwise.
		virtual bool ResetConVar(const IPluginInterface *plugin, const int handle);

		/// \brief Returns the name of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \return Name on success, NULL otherwise.
		virtual wchar_t *GetConVarName(const IPluginInterface *plugin, const int handle);

		/// \brief Retrieves the value of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[out] value Buffer to store the value in.
		/// \return True on success, false otherwise.
		virtual bool GetConVarValue(const IPluginInterface *plugin, const int handle, float &value);

		/// \brief Retrieves the value of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[out] value Buffer to store the value in.
		/// \return True on success, false otherwise.
		virtual bool GetConVarValue(const IPluginInterface *plugin, const int handle, int &value);

		/// \brief Retrieves the value of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[out] value Buffer to store the value in.
		/// \return True on success, false otherwise.
		virtual bool GetConVarValue(const IPluginInterface *plugin, const int handle, wchar_t *&value);

		/// \brief Retrieves the bitstring of flags on a console variable. 
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[out] flags Buffer to store the flags in.
		/// \return True on success, false otherwise.
		virtual bool GetConVarFlags(const IPluginInterface *plugin, const int handle, int &flags);

		/// \brief Retrieves the specified bound of a console variable. 
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] type Type of bound to retrieve.
		/// \param[out] bound Buffer to store the bound value in.
		/// \return True on success, false otherwise.
		virtual bool GetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, float &bound);

		/// \brief Retrieves the specified bound of a console variable. 
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] type Type of bound to retrieve.
		/// \param[out] bound Buffer to store the bound value in.
		/// \return True on success, false otherwise.
		virtual bool GetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType type, int &bound);

		/// \brief Sets the value of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] value The value to set.
		/// \return True on success, false otherwise.
		virtual bool SetConVarValue(const IPluginInterface *plugin, const int handle, const float value);

		/// \brief Sets the value of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] value The value to set.
		/// \return True on success, false otherwise.
		virtual bool SetConVarValue(const IPluginInterface *plugin, const int handle, const int value);

		/// \brief Sets the value of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] value The value to set.
		/// \return True on success, false otherwise.
		virtual bool SetConVarValue(const IPluginInterface *plugin, const int handle, const wchar_t *value);

		/// \brief Sets the bitstring of flags on a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] flags A bitstring containing the FCVAR_* flags to enable.
		/// \return True on success, false otherwise.
		virtual bool SetConVarFlags(const IPluginInterface *plugin, const int handle, const int flags);

		/// \brief Sets the specified bound of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] type Type of the bound to set.
		/// \param[in] set True to set, false to remove.
		/// \param[out] bound Value of the bound to set.
		/// \return True on success, false otherwise.
		virtual bool SetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType, const bool set, const float bound);

		/// \brief Sets the specified bound of a console variable.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] handle Handle to the console variable.
		/// \param[in] type Type of the bound to set.
		/// \param[in] set True to set, false to remove.
		/// \param[out] bound Value of the bound to set.
		/// \return True on success, false otherwise.
		virtual bool SetConVarBound(const IPluginInterface *plugin, const int handle, const ConVarBoundType, const bool set, const int bound);

		/// \brief Creates a server-only console command.
		/// \param[in] plugin Pointer to the plugin that calls this function.
		/// \param[in] name Name of the console command.
		/// \param[in] callback A function to use as a callback for when the command is invoked.
		/// \param[in] description Optional description of the console command.
		/// \param[in] flags Optional bitstring of flags determining how the console command should be handled. See FCVAR_* constants for more details.
		/// \note Callback should be void func(unsigned char numargs);
		/// \return No return.
		virtual void RegServerCmd(const IPluginInterface *plugin, const wchar_t *name, void *callback, const wchar_t *description = L"", const int flags = 0);

		/// \brief Returns the number of arguments from the current console command.
		/// \return Number of arguments from the current console command.
		virtual unsigned char GetCmdArgs(void);

		/// \brief Retrieves the entire command argument string in one lump from the current console command.
		/// \return Arguments string on success, NULL otherwise.
		virtual wchar_t *GetCmdArgString(void);

		/// \brief Retrieves a command argument type given its index, from the current console command.
		/// \param[in] argnum Argument number to retrieve.
		/// \param[out] type Buffer to use for storing the type.
		/// \return True on success, false otherwise.
		virtual bool GetCmdArgType(const unsigned char argnum, ConVarType &type);

		/// \brief Retrieves a command argument given its index, from the current console command.
		/// \param[in] argnum Argument number to retrieve.
		/// \param[out] arg Buffer to use for storing the value.
		/// \return True on success, false otherwise.
		virtual bool GetCmdArg(const unsigned char argnum, wchar_t *&arg);

		/// \brief Retrieves a command argument given its index, from the current console command.
		/// \param[in] argnum Argument number to retrieve.
		/// \param[out] arg Buffer to use for storing the value.
		/// \return True on success, false otherwise.
		virtual bool GetCmdArg(const unsigned char argnum, int &arg);

		/// \brief Retrieves a command argument given its index, from the current console command.
		/// \param[in] argnum Argument number to retrieve.
		/// \param[out] arg Buffer to use for storing the value.
		/// \return True on success, false otherwise.
		virtual bool GetCmdArg(const unsigned char argnum, float &arg);

		/// \brief Executes a server command as if it were on the server console.
		/// \param[in] string String to execute.
		/// \note The input string can contain several commands separated by ;.
		/// \return No return.
		virtual void ServerCommand(const wchar_t *string);
	};
	IPluginHandlerInterface *ph; ///< Holds the plugin handler that plugins call.

	/// \brief Loads a plugin by given filename to the given index.
	/// \param[in] index Index of the plugin.
	/// \param[in] string Filename of the plugin.
	/// \return True on success, false otherwise.
	bool LoadPluginInternal(const unsigned char index, const wchar_t *string);

	/// \brief Returns the number of free plugin slots.
	/// \return Number of free plugin slots.
	unsigned char GetNumberOfFreePluginSlots(void);

	/// \brief Retrieves the free plugin slot.
	/// \param[out] index Buffer to store the slot in.
	/// \return True on success, false otherwise.
	bool GetPluginFreeSlot(unsigned char &index);

	/// \brief Retrieves the plugin index by the given pointer.
	/// \param[in] plugin Pointer to the plugin interface.
	/// \param[out] index Index of the plugin.
	/// \return True on success, false otherwise.
	bool FindPlugin(const IPluginInterface *plugin, unsigned char &index);

	/// \brief Calls the OnPluginLoad callback in the plugin by the given index.
	/// \param[in] index Index of the plugin.
	/// \return No return.
	void OnPluginLoad(const unsigned char index);

	/// \brief Calls the OnPluginUnload callback in the plugin by the given index.
	/// \param[in] index Index of the plugin.
	/// \return No return.
	void OnPluginUnload(const unsigned char index);
};
