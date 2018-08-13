/// \file
/// \brief Header file that describes the VirtualMachineManager class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "sq/squirrel.h"

/// \brief A virtual machine manager. It handles all I/O between scripting languages and
/// other modules.
/// \details Virtual machine manager is designed to create convenient abstraction layer.
/// It transforms language specific calls into unified format allowing virtually unlimited
/// number of different languages to be implemented into a single server and work 
/// together. The main idea is to have limited number of language-independent virtual
/// machines: one for the always changing gamemode and other for always-on filterscripts.
/// All virtual machines can be called through the single interface. Each call is 
/// internally converted into the language specific one.
/// \author FaTony. Wrapped around initial WNeZRoS' code.

class VirtualMachineManager
{
public:
	/// \brief Constructor.
	VirtualMachineManager(void);

	/// \brief Destructor.
	~VirtualMachineManager(void);

	/// \brief Checks if the game mode is loaded.
	/// \return True if game mode is loaded, false otherwise.
	bool IsGameModeLoaded(void);

	/// \brief Loads the game mode.
	/// \param[in] string Filename of the game mode.
	/// \return True on success, false otherwise.
	bool LoadGameMode(const wchar_t *string);

	/// \brief Unloads the game mode.
	/// \return True on success, false otherwise.
	bool UnloadGameMode(void);

	/// \brief Returns the game mode name.
	/// \return Game mode name on success, NULL otherwise.
	wchar_t *GetGameModeName(void);

	/// \brief Returns the maximum virtual machine buffer size.
	/// \return Maximum virtual machine buffer size.
	unsigned char GetMaxVirtualMachineBufferSize(void);

	/// \brief Returns the current virtual machine buffer size.
	/// \return Current virtual machine buffer size.
	unsigned char GetVirtualMachineBufferSize(void);

	/// \brief Loads all filterscripts.
	/// \return No return.
	void LoadFilterScripts(void);

	/// \brief Unloads all filterscripts.
	/// \return No return.
	void UnloadFilterScripts(void);

	/// \brief Reloads all filterscripts.
	/// \return No return.
	void ReloadFilterScripts(void);

	/// \brief Pauses all virtual machines.
	/// \return No return.
	void PauseVirtualMachines(void);

	/// \brief Unpauses all virtual machines.
	/// \return No return.
	void UnpauseVirtualMachines(void);

	/// \brief Checks if the specified filterscript is loaded.
	/// \param[in] string Filename of the filterscript.
	/// \return True if the filterscript is loaded, false otherwise.
	bool IsFilterScriptLoaded(const wchar_t *string);

	/// \brief Loads a filterscript.
	/// \param[in] string Filename of the filterscript.
	/// \return True on success, false otherwise.
	bool LoadFilterScript(const wchar_t *string);

	/// \brief Unloads a filterscript.
	/// \param[in] index Index of the filterscript.
	/// \return True on success, false otherwise.
	bool UnloadFilterScript(const unsigned char index);

	/// \brief Reloads a filterscript.
	/// \param[in] index Index of the filterscript.
	/// \return True on success, false otherwise.
	bool ReloadFilterScript(const unsigned char index);

	/// \brief Pauses a virtual machine.
	/// \param[in] index Index of the virtual machine.
	/// \return True on success, false otherwise.
	bool PauseVirtualMachine(const unsigned char index);

	/// \brief Unpauses a virtual machine.
	/// \param[in] index Index of the virtual machine.
	/// \return True on success, false otherwise.
	bool UnpauseVirtualMachine(const unsigned char index);

	/// \brief Returns the virtual machine info string.
	/// \param[in] index Index of the virtual machine.
	/// \return Info string on success, NULL otherwise.
	wchar_t *GetVirtualMachineInfoString(const unsigned char index);

	/// \brief Retrieves the virtual machine index by the given pointer.
	/// \param[in] v Pointer to the virtual machine.
	/// \param[out] index Index of the virtual machine.
	/// \note Used only by squirrel natives.
	/// \return True on success, false otherwise.
	bool FindVirtualMachine(const HSQUIRRELVM *v, unsigned char &index);

	//------------------------------------------------------------------------------------
	// Natives below this line
	//------------------------------------------------------------------------------------

	/// \brief Sets the virtual machine name.
	/// \param[in] index Index of the virtual machine.
	/// \param[in] string Name to set.
	/// \return No return.
	void SetVirtualMachineName(const unsigned char index, const wchar_t *string);

	/// \brief Sets the virtual machine version.
	/// \param[in] index Index of the virtual machine.
	/// \param[in] string Version to set.
	/// \return No return.
	void SetVirtualMachineVersion(const unsigned char index, const wchar_t *string);

	/// \brief Sets the virtual machine author.
	/// \param[in] v Pointer to the virtual machine that calls this function.
	/// \param[in] string Author to set.
	/// \return No return.
	void SetVirtualMachineAuthor(const unsigned char index, const wchar_t *string);

	//------------------------------------------------------------------------------------
	// Callbacks below this line
	//------------------------------------------------------------------------------------

	/// \brief Called when a player connects the server.
	/// \param[in] index Index of the player.
	/// \param[in] name Name of the player.
	/// \return True if we let the player to connect, false otherwise.
	bool OnPlayerConnect(const short index, const wchar_t *name);

	/// \brief Called when a player is disconnecting from the server.
	/// \param[in] index Index of the player.
	/// \return No return.
	void OnPlayerDisconnect(const short index);

	/// \brief Called when a player is spawning.
	/// \param[in] playerindex Index of the player.
	/// \return No return.
	void OnPlayerSpawn(const short playerindex);

	/// \brief Called when a player dies.
	/// \param[in] playerindex Index of the player who have died.
	/// \param[in] killerindex Index of the killer, INVALID_PLAYER_INDEX otherwise.
	/// \param[in] reason Reason of the death. //TODO: Should this be enum?
	/// \return No return.
	void OnPlayerDeath(const short playerindex, const short killerindex, const char reason);

	///
	///
	///
	///
	bool OnPlayerText(const short playerindex, const wchar_t *data);

	bool OnPlayerCommandText(const short playerindex, const wchar_t *cmd, const wchar_t *data);

	bool CallSomeCallback(const wchar_t *callback, const int param);

	/// \brief Fires a dynamic command callback.
	/// \param[in] index Index of the virtual machine.
	/// \param[in] callback Name of the callback to call.
	/// \param[in] numargs Number of arguments to pass.
	/// \return No return.
	void FireCommandCallback(const unsigned char index, const wchar_t *callback, const unsigned char numargs);
private:
	/// \brief Indicates the language of a virtual machine.
	enum VirtualMachineLanguage
	{
		VMLanguageSquirrel ///< Indicates the Squirrel.
		//VMLanguagePawn
		//VMLanguageLua
	};
	/// \brief Used to wisely work with the virtual machine.
	union VirtualMachinePtr
	{
		HSQUIRRELVM *squirrel; ///< Squirrel virtual machine.
		//AMX *amx;
		//Lua
	};
	/// \brief Describes the virtual machine.
	struct VirtualMachine
	{
		bool paused; ///< Holds true if the virtual machine is paused, false otherwise.
		wchar_t *name; ///< Holds the name of the virtual machine.
		wchar_t *version; ///< Holds the version of the virtual machine.
		wchar_t *author; ///< Holds the author of the virtual machine.
		VirtualMachineLanguage lang; ///< Holds the language of the virtual machine.
		VirtualMachinePtr ptr; ///< Holds the pointer to the language specific virtual machine.
		wchar_t *filename; ///< Holds the filename of the virtual machine.
	};
	unsigned char maxvmbuffersize; ///< Holds the maximum size of the virtual machine buffer.
	unsigned char vmbuffersize; ///< Holds the current size of the virtual machine buffer.
	VirtualMachine **vmbuffer; ///< Virtual machine buffer. 0 - game mode, (1...maxvmbuffersize - 1) - filterscripts

	/// \brief Loads a filterscript into the specified index.
	/// \param[in] index Index of the virtual machine.
	/// \param[in] string Filename of the filterscript.
	/// \return True on success, false otherwise.
	bool LoadFilterScriptInternal(const unsigned char index, const wchar_t *string);

	/// \brief Loads a virtual machine into the specified index.
	/// \param[in] index Index of the virtual machine.
	/// \param[in] string Filename of the filterscript.
	/// \return True on success, false otherwise.
	bool LoadVirtualMachine(const unsigned char index, const wchar_t *string);

	/// \brief Unloads a virtual machine.
	/// \param[in] index Index of the virtual machine.
	/// \return True on success, false otherwise.
	bool UnloadVirtualMachine(const unsigned char index);

	/// \brief Returns the number of free filterscript slots.
	/// \return Number of free filterscript slots.
	unsigned char GetNumberOfFreeFilterScriptSlots(void);

	/// \brief Retrieves the free filterscript slot.
	/// \param[out] index Buffer to store the slot in.
	/// \return True on success, false otherwise.
	bool GetFilterScriptFreeSlot(unsigned char &index);

	/// \brief Called when the game mode starts.
	/// \return No return.
	void OnGameModeInit(void);

	/// \brief Called when the game mode ends.
	/// \return No return.
	void OnGameModeExit(void);

	/// \brief Called when the filterscript is loaded.
	/// \param[in] index Index of the filterscript.
	/// \return No return.
	void OnFilterScriptInit(const unsigned char index);

	/// \brief Called when the filterscript is unloaded.
	/// \param[in] index Index of the filterscript.
	/// \return No return.
	void OnFilterScriptExit(const unsigned char index);
};
