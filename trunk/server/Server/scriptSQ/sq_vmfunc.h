#include "../sq/squirrel.h"

// SQ Functions
SQInteger register_global_func(HSQUIRRELVM v, SQFUNCTION f, const wchar_t *fname);

/// \brief Sets the virtual machine name.
void sq_SetScriptName(HSQUIRRELVM v);

/// \brief Sets the virtual machine version.
void sq_SetScriptVersion(HSQUIRRELVM v);

/// \brief Sets the virtual machine author.
void sq_SetScriptAuthor(HSQUIRRELVM v);

void RegVMSQFunc(SQVM * v);