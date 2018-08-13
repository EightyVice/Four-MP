#pragma once

#include "../../Shared/Console/ConVar.h"
#include "../../Shared/Network/Limits.h"
#include "../../Shared/Network/ClientDefines.h"
#define MAX_PATH 260

/// \brief Indicates the global state of the game.
enum GameState
{
	GameStateLoading, ///< Indicates that client is loading.
	GameStateOffline, ///< Indicates that client is offline.
	GameStateUnloading, ///< Indicates that client is unloading.
	GameStateConnecting, ///< Indicates that client is connecting to the server.
	GameStateInGame, ///< Indicates that client is connected to the server and is playing.
	GameStateSkinSelect, ///< Indicates that client is connected to the server and is choosing their skin.
	GameStateComponentSelect ///< Indicates that client is connected to the server and is choosing their components (clothes).
};

#if defined (FMP_CLIENT)
/// \brief Indicates the target that all keyboard and mouse input is redirected to.
enum InputState
{
	InputStateGame, ///< Indicates that all input is going into the game itself.
	InputStateChat, ///< Indicates that all input is going into the chat.
	InputStateGui ///< Indicates that all input is going into the GUI.
};
#endif

class ClientCore
{
public:
	ClientCore(void);
	~ClientCore(void);
	bool Load(void);
	bool IsRunning(void);
	void Tick(void);
	void Unload(void);
	void Shutdown(void);
	GameState GetGameState(void);
	wchar_t *GetName(void);
	short GetIndex(void);
	unsigned int GetSessionKey(void);
	int GetFMPID();
	bool SetGameState(const GameState state);
	bool SetName(const wchar_t name[MAX_CLIENT_NAME_LENGTH]);
	bool SetIndex(const short i);
	void SetSessionKey(unsigned int key);
	void SetFMPID(int);
	wchar_t *GetPath();
	void GetPath(const wchar_t *file, wchar_t *path);
#if defined (FMP_CLIENT)
	InputState GetInputState(void);
	bool SetInputState(const InputState state);
#endif
private:
	GameState gamestate; ///< Holds the current game state.
	wchar_t name[MAX_CLIENT_NAME_LENGTH]; ///< Holds the desired client name (May be overriden by the server).
	ConVar *namecvar; ///< Holds the pointer to the console variable that holds the desired client name.
	short index; ///< Holds the client's index while connected to the server, -1 (should be #define) otherwise.
	unsigned int sessionkey; ///< Holds the unique session key of the client. Used in rare cases to identify it.
	int fmpid;
	wchar_t PathToClient[MAX_PATH];
	friend void ConVarHookName(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
#if defined (FMP_CLIENT)
	InputState inputstate; ///< Holds the current input target.
#endif
};
