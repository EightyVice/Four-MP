/// \file
/// \brief Source file that contains implementation of the ConAlias class.
/// \details See class description.
/// \author FaTony

#include <string.h>

#include "ConAlias.h"
#include "common.h"
#include "ConsoleCore.h"

ConAlias::ConAlias(ConsoleCore *core, const conchar *aliasname, const conchar *cmdstring)
{
	this->Init(core, aliasname, cmdstring);
}

ConAlias::~ConAlias(void)
{
	this->Uninit();
}

void ConAlias::SetCommandString(const conchar *string)
{
	ResizeBuffer<conchar *>(description, con_strlen(string) + 1);
	con_strcpy(description, string);
}

void ConAlias::Execute(void)
{
	concore->InterpretLine(description);
}