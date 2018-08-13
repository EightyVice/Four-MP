/*
*	Created:			28.10.09
*	Created by:			WNeZRoS
*	Last Modifed:		-
*/

#include "../sq/squirrel.h"

#include "sq_callbacks.h"
#include "sq_consolenatives.h"
#include "sq_gamenatives.h"
#include "sq_playernatives.h"
#include "sq_uinatives.h"
#include "sq_vehiclenatives.h"
#include "sq_vmfunc.h"
#include "sq_filenatives.h"


// SQ Script Functions
void sq_addPlayerClass(HSQUIRRELVM v);
void sq_enableComponentSelect(HSQUIRRELVM v);

SQInteger sq_SetTimer(SQVM *v);
SQInteger sq_KillTimer(SQVM *v);

void RegSQFunc(SQVM * v);