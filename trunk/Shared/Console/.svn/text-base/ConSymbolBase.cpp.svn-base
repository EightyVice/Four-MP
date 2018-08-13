/// \file
/// \brief Source file that contains implementation of the ConSymbolBase class.
/// \details See class description.
/// \author FaTony

#include <stdlib.h>
#include <string.h>

#include "ConSymbolBase.h"

ConSymbolBase::ConSymbolBase(void)
{
}

ConSymbolBase::~ConSymbolBase(void)
{
}

conchar *ConSymbolBase::GetName(void)
{
	conchar *tempname = (conchar *)calloc(con_strlen(name) + 1, sizeof(conchar));
	con_strcpy(tempname, name);
	return tempname;
}

conchar *ConSymbolBase::GetDescription(void)
{
	conchar *tempdescription = (conchar *)calloc(con_strlen(description) + 1, sizeof(conchar));
	con_strcpy(tempdescription, description);
	return tempdescription;
}

int ConSymbolBase::GetFlags(void)
{
	return flags;
}

void ConSymbolBase::SetFlags(const int f)
{
	flags = f;
}

void ConSymbolBase::Init(ConsoleCore *core, const conchar *symbolname, const conchar *desc, const int symbolflags)
{
	concore = core;
	name = (conchar *)calloc(con_strlen(symbolname) + 1, sizeof(conchar));
	con_strcpy(name, symbolname);
	description = (conchar *)calloc(con_strlen(desc) + 1, sizeof(conchar));
	con_strcpy(description, desc);
	flags = symbolflags;
}

void ConSymbolBase::Uninit(void)
{
	free(name);
	free(description);
}
