/// \file
/// \brief Header file that describes the Squirrel callbacks.
/// \details These are the functions that host calls from outside.
/// \author WNeZRoS, FaTony

#include "../sq/squirrel.h"

// SQ Callbacks

/// \brief Called when the game mode starts.
void sc_OnGameModeInit(HSQUIRRELVM v);

/// \brief Called when the game mode ends.
void sc_OnGameModeExit(HSQUIRRELVM v);

/// \brief Called when the filterscript is loaded.
void sc_OnFilterScriptInit(HSQUIRRELVM v);

/// \brief Called when the filterscript is unloaded.
void sc_OnFilterScriptExit(HSQUIRRELVM v);

/// \brief Called when a player connects the server.
/// \param[in] index Index of the player.
/// \param[in] name Name of the player.
/// \return True if we let the player to connect, false otherwise.
bool sc_OnPlayerConnect(HSQUIRRELVM v, const short index, const wchar_t *name);

/// \brief Called when a player is disconnecting from the server.
/// \param[in] index Index of the player.
/// \return No return.
void sc_OnPlayerDisconnect(HSQUIRRELVM v, const short index);

/// \brief Called when a player is spawning.
/// \param[in] index Index of the player.
/// \return No return.
void sc_OnPlayerSpawn(HSQUIRRELVM v, const short index);

/// \brief Called when a player dies.
/// \param[in] playerindex Index of the player who have died.
/// \param[in] killerindex Index of the killer, INVALID_PLAYER_INDEX otherwise.
/// \param[in] reason Reason of the death. //TODO: Should this be enum?
/// \return No return.
void sc_OnPlayerDeath(HSQUIRRELVM v, const short playerindex, const short killerindex, const char reason);

/// \brief Called when send message in chat
/// \param[in] index
/// \param[in] text
/// \return Return bool
bool sc_OnPlayerText(HSQUIRRELVM v, const short index, const wchar_t *text);

/// \brief Called when send command in chat
/// \param[in] index
/// \param[in] cmd
/// \param[in] params
/// \return Return bool
bool sc_OnPlayerCommandText(HSQUIRRELVM v, const short index, const wchar_t * cmd, const wchar_t *params);

/// \brief Fires a dynamic command callback.
/// \param[in] callback Name of the callback to call.
/// \param[in] numargs Number of arguments to pass.
/// \return No return.
void sc_CommandCallback(HSQUIRRELVM v, const wchar_t *callback, const unsigned char numargs);

void sc_OnPlayerShoot(HSQUIRRELVM v, const short index, float shoot[3]);
bool sc_CallSomeCallback(HSQUIRRELVM v, const wchar_t *callback, const int param);