#pragma once

#include "../sq/squirrel.h"

SQInteger sq_fopen(SQVM *v);
SQInteger sq_fclose(SQVM *v);
SQInteger sq_feof(SQVM *v);
SQInteger sq_fprint(SQVM *v);
SQInteger sq_fputs(SQVM *v);
SQInteger sq_fgets(SQVM *v);
SQInteger sq_fread(SQVM *v);
SQInteger sq_fwrite(SQVM *v);
SQInteger sq_fseek(SQVM *v);
SQInteger sq_ftell(SQVM *v);
SQInteger sq_access(SQVM *v);
SQInteger sq_remove(SQVM *v);
SQInteger sq_rename(SQVM *v);

void RegFileSQFunc(SQVM * v);