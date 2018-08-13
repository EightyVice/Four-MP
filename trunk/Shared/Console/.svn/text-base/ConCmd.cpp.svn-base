/// \file
/// \brief Source file that contains implementation of the ConCmd class.
/// \details See class description.
/// \author FaTony

#include <stdlib.h>
#include <string.h>

#include "ConCmd.h"
#include "ConsoleCore.h"

ConCmd::ConCmd(ConsoleCore *core, const conchar *cmdname, void *callback, const conchar *desc, const int cmdflags)
{
	this->Init(core, cmdname, desc, cmdflags);
	handler = callback;
}

ConCmd::~ConCmd(void)
{
	concore->DeleteConCmd(this->name, this);
	this->Uninit();
}

void ConCmd::Execute(void)
{
	unsigned char numargs = concore->GetCmdArgs();
	((void (*) (const ConsoleCore *, const unsigned char))handler)(concore, numargs);
}
