/// \file
/// \brief Header file that describes the ConVar class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "ConSymbolBase.h"

/// \brief Indicates the type of console variable.
enum ConVarType
{
	ConVarTypeFloat, ///< Indicates floating point value.
	ConVarTypeInt, ///< Indicates integer value.
	ConVarTypeString ///< Indicates string value.
};

/// \brief Indicates the type of console variable bound.
enum ConVarBoundType
{
	ConVarBoundLower, ///< Indicates lower bound.
	ConVarBoundUpper ///< Indicates upper bound.
};

/// \brief A console variable. It can store 1 simple value.
/// \details A console variable is designed to hold either float, integer or string value.
/// It can be used to simplify interface between the user and program. Developers can
/// design their software that relies on console variables and users can easily
/// configure it through the console.
/// \author FaTony

class ConVar : public ConSymbolBase
{
public:
	/// \brief Constructor for the console variable with default floating point value.
	/// \param[in] core Pointer to the console core this variable should be attached to.
	/// \param[in] cvarname Name of the console variable.
	/// \param[in] defvalue Default value of the console variable.
	/// \param[in] desc Optional description of the console variable.
	/// \param[in] cvarflags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \param[in] hasMin Optional boolean that determines if the console variable has a minimum value.
	/// \param[in] min Minimum value that the console variable can have if hasMin is true.
	/// \param[in] hasMax Optional boolean that determines if the console variable has a maximum value.
	/// \param[in] max Maximum value that the console variable can have if hasMax is true.
	/// \note Do not explicitly call this function. Use ConsoleCore::AddConVar() instead.
	ConVar(ConsoleCore *core, const conchar *cvarname, const float defvalue, const conchar *desc = CONSTRING(""), const int cvarflags = 0, const bool hasMin = false, const float min = 0.0, const bool hasMax = false, const float max = 0.0);

	/// \brief Constructor for the console variable with default integer value.
	/// \param[in] core Pointer to the console core this variable should be attached to.
	/// \param[in] cvarname Name of the console variable.
	/// \param[in] defvalue Default value of the console variable.
	/// \param[in] desc Optional description of the console variable.
	/// \param[in] cvarflags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \param[in] hasMin Optional boolean that determines if the console variable has a minimum value.
	/// \param[in] min Minimum value that the console variable can have if hasMin is true.
	/// \param[in] hasMax Optional boolean that determines if the console variable has a maximum value.
	/// \param[in] max Maximum value that the console variable can have if hasMax is true.
	/// \note Do not explicitly call this function. Use ConsoleCore::AddConVar() instead.
	ConVar(ConsoleCore *core, const conchar *cvarname, const int defvalue, const conchar *desc = CONSTRING(""), const int cvarflags = 0, const bool hasMin = false, const int min = 0, const bool hasMax = false, const int max = 0);

	/// \brief Constructor for the console variable with default string value.
	/// \param[in] core Pointer to the console core this variable should be attached to.
	/// \param[in] cvarname Name of the console variable.
	/// \param[in] defvalue Default value of the console variable.
	/// \param[in] desc Optional description of the console variable.
	/// \param[in] cvarflags Optional bitstring of flags determining how the console variable should be handled. See FCVAR_* constants for more details.
	/// \note Do not explicitly call this function. Use ConsoleCore::AddConVar() instead.
	ConVar(ConsoleCore *core, const conchar *cvarname, const conchar *defvalue, const conchar *desc = CONSTRING(""), const int cvarflags = 0);

	/// \brief Unloads all resources and removes console variable from the console core.
	~ConVar(void);

	/// \brief Resets console variable to the default value.
	/// \return No return.
	void Reset(void);

	/// \brief Returns current type of the console variable.
	/// \return Current type of the console variable.
	ConVarType GetType(void);

	/// \brief Returns default type of the console variable.
	/// \return Default type of the console variable.
	ConVarType GetDefaultType(void);

	/// \brief Retrieves a value of the console variable.
	/// \param[out] val Buffer which write value to.
	/// \return True on success, false otherwise.
	bool GetValue(float &val);

	/// \brief Retrieves a value of the console variable.
	/// \param[out] val Buffer which write value to.
	/// \return True on success, false otherwise.
	bool GetValue(int &val);

	/// \brief Retrieves a value of the console variable.
	/// \param[out] val Buffer which write value to.
	/// \return True on success, false otherwise.
	bool GetValue(conchar *&val);

	/// \brief Retrieves a default value of the console variable.
	/// \param[out] val Buffer which write default value to.
	/// \return True on success, false otherwise.
	bool GetDefaultValue(float &val);

	/// \brief Retrieves a default value of the console variable.
	/// \param[out] val Buffer which write default value to.
	/// \return True on success, false otherwise.
	bool GetDefaultValue(int &val);

	/// \brief Retrieves a default value of the console variable.
	/// \param[out] val Buffer which write default value to.
	/// \return True on success, false otherwise.
	bool GetDefaultValue(conchar *&val);

	/// \brief Sets the value of the console variable.
	/// \param[in] val Value of the console variable.
	/// \return True on success, false otherwise.
	bool SetValue(const float val);

	/// \brief Sets the value of the console variable.
	/// \param[in] val Value of the console variable.
	/// \return True on success, false otherwise.
	bool SetValue(const int val);

	/// \brief Sets the value of the console variable.
	/// \param[in] val Value of the console variable.
	/// \return True on success, false otherwise.
	bool SetValue(const conchar *val);

	/// \brief Retrieves a bound of the console variable.
	/// \param[in] type Type of the bound.
	/// \param[out] bound Buffer which write bound to.
	/// \return True on success, false otherwise.
	bool GetBound(ConVarBoundType type, float &bound);

	/// \brief Retrieves a bound of the console variable.
	/// \param[in] type Type of the bound.
	/// \param[out] bound Buffer which write bound to.
	/// \return True on success, false otherwise.
	bool GetBound(ConVarBoundType type, int &bound);

	/// \brief Sets the bound of the console variable.
	/// \param[in] type Type of the bound.
	/// \param[in] set True to set, false to remove.
	/// \param[in] bound Value of the bound.
	/// \return True on success, false otherwise.
	bool SetBound(ConVarBoundType type, const bool set, const float bound);

	/// \brief Sets the bound of the console variable.
	/// \param[in] type Type of the bound.
	/// \param[in] set True to set, false to remove.
	/// \param[in] bound Value of the bound.
	/// \return True on success, false otherwise.
	bool SetBound(ConVarBoundType type, const bool set, const int bound);

	/// \brief Hooks the console variable change.
	/// \param[in] callback Pointer to the function to call on change.
	/// \note Function must be void func(ConVar *convar, const ConVarType oldtype, void *oldvalue, const ConVarType newtype, void *newvalue);
	/// \return True on success, false otherwise.
	bool HookChange(void *callback);

	/// \brief Unhooks the console variable change.
	/// \param[in] callback Pointer to the function to unhook.
	/// \return True on success, false otherwise.
	bool UnhookChange(const void *callback);
private:
	/// \brief Used to wisely work with console variable value.
	union ConVarValueUnion
	{
		float f; ///< Floating point value.
		int i; ///< Integer value.
		conchar *s; ///< String value.
	};

	/// \brief Describes the value of console variable.
	struct ConVarValue
	{
		ConVarType type; ///< Holds the type of console variable.
		ConVarValueUnion value; ///< Holds the value of console variable.
	};

	/// \brief Describes the bound of the console variable.
	struct ConVarBound
	{
		bool exist; ///< True if the bound exist, false otherwise.
		ConVarType type; ///< Holds the type of the bound.
		ConVarValueUnion value; ///< holds the value of the bound.
	};
	ConVarValue value; ///< Holds current value of the console variable.
	ConVarValue defaultvalue; ///< Holds default value of the console variable.
	ConVarBound minimum; ///< Holds minimum bound of the console variable.
	ConVarBound maximum; ///< Holds maximum bound of the console variable.
	unsigned char hookbuffersize; ///< Holds the current hook buffer size.
	void **hookbuffer; ///< Holds the pointers to the functions which will be called when the console variable value changes.

	/// \brief Fires all change hooks.
	/// \param[in] val Old value of the console variable.
	/// \return No return.
	void FireChangeHook(const float val);

	/// \brief Fires all change hooks.
	/// \param[in] val Old value of the console variable.
	/// \return No return.
	void FireChangeHook(const int val);

	/// \brief Fires all change hooks.
	/// \param[in] val Old value of the console variable.
	/// \return No return.
	void FireChangeHook(const conchar *val);
};
