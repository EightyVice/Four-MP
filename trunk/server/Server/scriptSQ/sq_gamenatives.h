#pragma once

#include "../sq/squirrel.h"

void sq_GetGameTime(HSQUIRRELVM v);
void sq_SetGameTime(HSQUIRRELVM v);

void RegGameSQFunc(SQVM * v);