/// \file
/// \brief Header file that describes the CoreHandleTypesManager class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "../../Shared/Console/ConsoleCore.h"

/// \brief Indicates a type of the handle.
enum CoreHandleType
{
	HandleTypeConVar, ///< Indicates a console variable.
	HandleTypeConCmd ///< Indicates a console command.
};

#define NUM_CORE_HANDLE_TYPES 2 ///< Number of core handle types.

/// \brief A core handle types manager. It works with built-in handle types.
/// \details HandleManager is designed as a complete system that works with abstract data.
/// It doesn't know what type of data it works with. Core handle types manager is what
/// know which data it operates on - built-in (core) handle types. Since it has direct
/// access to the handle buffer, it works faster than asking HandleManager.
/// \author FaTony

class CoreHandleTypesManager
{
public:
	/// \brief Constructor.
	CoreHandleTypesManager(void);

	/// \brief Destructor.
	~CoreHandleTypesManager(void);

	/// \brief Wisely closes the given handle since the HandleManager doesn't know what data it operates on.
	/// \param[in] handle Index of the handle.
	/// \return True on success, false otherwise.
	bool CloseHandle(const int handle);

	/// \brief Returns the handle to the console variable and reserves it by the owner.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] name Name of the console variable to search for.
	/// \return Handle index on success, INVALID_HANDLE otherwise.
	int FindConVar(const short owner, const wchar_t *name);

	/// \brief Resets the console variable to its default value.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \return True on success, false otherwise.
	bool ResetConVar(const short owner, const int handle);

	/// \brief Returns the name of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \return Name on success, NULL otherwise.
	wchar_t *GetConVarName(const short owner, const int handle);

	/// \brief Retrieves the value of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the value in.
	/// \return True on success, false otherwise.
	bool GetConVarValue(const short owner, const int handle, float &value);

	/// \brief Retrieves the value of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the value in.
	/// \return True on success, false otherwise.
	bool GetConVarValue(const short owner, const int handle, int &value);

	/// \brief Retrieves the value of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the value in.
	/// \return True on success, false otherwise.
	bool GetConVarValue(const short owner, const int handle, wchar_t *&value);

	/// \brief Retrieves the bitstring of flags on a console variable. 
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[out] value Buffer to store the flags in.
	/// \return True on success, false otherwise.
	bool GetConVarFlags(const short owner, const int handle, int &flags);

	/// \brief Retrieves the specified bound of a console variable. 
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of bound to retrieve.
	/// \param[out] bound Buffer to store the bound value in.
	/// \return True on success, false otherwise.
	bool GetConVarBound(const short owner, const int handle, const ConVarBoundType type, float &bound);

	/// \brief Retrieves the specified bound of a console variable. 
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of bound to retrieve.
	/// \param[out] bound Buffer to store the bound value in.
	/// \return True on success, false otherwise.
	bool GetConVarBound(const short owner, const int handle, const ConVarBoundType type, int &bound);

	/// \brief Sets the value of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] value The value to set.
	/// \return True on success, false otherwise.
	bool SetConVarValue(const short owner, const int handle, const float value);

	/// \brief Sets the value of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] value The value to set.
	/// \return True on success, false otherwise.
	bool SetConVarValue(const short owner, const int handle, const int value);

	/// \brief Sets the value of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] value The value to set.
	/// \return True on success, false otherwise.
	bool SetConVarValue(const short owner, const int handle, const wchar_t *value);

	/// \brief Sets the bitstring of flags on a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] flags A bitstring containing the FCVAR_* flags to enable.
	/// \return True on success, false otherwise.
	bool SetConVarFlags(const short owner, const int handle, const int flags);

	/// \brief Sets the specified bound of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of the bound to set.
	/// \param[in] set True to set, false to remove.
	/// \param[out] bound Value of the bound to set.
	/// \return True on success, false otherwise.
	bool SetConVarBound(const short owner, const int handle, const ConVarBoundType type, const bool set, const float bound);

	/// \brief Sets the specified bound of a console variable.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Handle to the console variable.
	/// \param[in] type Type of the bound to set.
	/// \param[in] set True to set, false to remove.
	/// \param[out] bound Value of the bound to set.
	/// \return True on success, false otherwise.
	bool SetConVarBound(const short owner, const int handle, const ConVarBoundType type, const bool set, const int bound);

	/// \brief Adds a dynamic command.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] callback Name of the callback that will be called during the execution of the command.
	/// \param[in] ptr Pointer to the console command that will be associated with this dynamic command.
	/// \return True on success, false otherwise.
	bool AddDynamicCommand(const short owner, const wchar_t *callback, const ConCmd *ptr);

	/// \brief Returns the handle indexes of a dynamic command.
	/// \param[in] name Name of the command to search for.
	/// \param[out] numcmds Number of commands found.
	/// \return An array of handles on success, NULL otherwise.
	int *GetDynamicCommandHandles(const wchar_t *name, unsigned char &numcmds);

	/// \brief Deletes the dynamic command by the given handle index.
	/// \param[in] handle Index of the handle.
	/// \return True on success, false otherwise.
	bool DeleteDynamicCommand(const int handle);

	/// \brief Executes the dynamic command by the given handle index.
	/// \param[in] handle Index of the handle.
	/// \param[in] numargs Number of arguments to pass.
	/// \return True on success, false otherwise.
	bool ExecuteDynamicCommand(const int handle, const unsigned char numargs);
private:
	/// \brief Describes a dynamic command. It is console command that was created by a filterscript.
	struct DynamicCommand
	{
		int index; ///< Holds the handle index of the current dynamic command.
		wchar_t *callback; //Holds the callback of the current dynamic command.
	};
	DynamicCommand *commandbuffer; ///< Holds all additional data needed by the dynamic commands.
	unsigned short maxcommandbuffersize; ///< Holds the maximum size of the dynamic commands buffer.
	unsigned short commandbuffersize; ///< Holds the current size of the dynamic commands buffer.
	
	/// \brief Checks if the given handle is a ConVar and owned by the given owner.
	/// \param[in] owner Index of the owner.
	/// \param[in] handle Index of the handle.
	/// \return True on success, false otherwise.
	bool CheckConVar(const short owner, const int handle);

	/// \brief Retrieves the callback of the given handle index.
	/// \param[in] handle Index of the handle.
	/// \return Callback string on success, NULL otherwise.
	wchar_t *GetDynamicCommandCallback(const int handle);
};
