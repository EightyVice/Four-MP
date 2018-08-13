/// \file
/// \brief Source file that contains implementation of the core console commands.
/// \details See coreconcommands.h.
/// \author FaTony

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "condefs.h"
#include "common.h"
#include "coreconcommands.h"

using namespace std;

void ConCmdAlias(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(CONSTRING("Current alias commands:"));
		conchar *aliasstring;
		conchar *tempstring;
		for (unsigned short i = 0; i < concore->symbolbuffersize; i++)
		{
			if (concore->symbolbuffer[i].type == ConsoleCore::ConsoleSymbolTypeConAlias)
			{
				tempstring = concore->symbolbuffer[i].ptr->conalias->GetName();
				size_t length = con_scprintf(CONSTRING("%s :"), tempstring) + 1;
				aliasstring = (conchar *)calloc(length, sizeof(conchar));
				con_sprintf(aliasstring, length, CONSTRING("%s :")), tempstring);
				free(tempstring);
				tempstring = concore->symbolbuffer[i].ptr->conalias->GetDescription();
				length = con_scprintf(CONSTRING("%s %s"), aliasstring, tempstring) + 1;
				ResizeBuffer<conchar *>(aliasstring, length);
				con_sprintf(aliasstring, length, CONSTRING("%s %s")), aliasstring, tempstring);
				free(tempstring);
				concore->Output(aliasstring);
				free(aliasstring);
			}
		}
		return;
	}
	conchar *name;
	if (!concore->GetCmdArg(1, name))
	{
		return;
	}
	conchar *commandstring;
	if (!concore->GetCmdArg(2, commandstring))
	{
		concore->AddConAlias(name);
	}
	concore->AddConAlias(name, commandstring);
}

void ConCmdCvarlist(ConsoleCore *concore, const unsigned char numargs)
{
	bool search = false;
	conchar *searchstring;
	if (numargs > 0)
	{
		if (concore->GetCmdArg(1, searchstring))
		{
			search = true;
		}
	}
	concore->Output(CONSTRING("cvar list\n--------------"));
	unsigned short numfound = 0;
	unsigned char numcmds;
	conchar *symbolstring;
	conchar *tempstring;
	for (unsigned short i = 0; i < concore->symbolbuffersize; i++)
	{
		//TODO: Sort alphabetically
		if (concore->symbolbuffer[i].type == ConsoleCore::ConsoleSymbolTypeConCmd)
		{
			numcmds = concore->symbolbuffer[i].numcmds;
		}
		else
		{
			numcmds = 1;
		}
		for (unsigned char j = 0; j < numcmds; j++)
		{
			size_t length = con_strlen(concore->symbolbuffer[i].name) + 3;
			symbolstring = (conchar *)calloc(length, sizeof(conchar));
			con_sprintf(symbolstring, length, CONSTRING("%s	:")), concore->symbolbuffer[i].name);
			switch (concore->symbolbuffer[i].type)
			{
			case ConsoleCore::ConsoleSymbolTypeConVar:
				{
					concore->symbolbuffer[i].ptr->convar->GetValue(tempstring);
					length = con_scprintf(CONSTRING("%s %s	:"), symbolstring, tempstring) + 1;
					ResizeBuffer<conchar *>(symbolstring, length);
					con_sprintf(symbolstring, length, CONSTRING("%s %s	:")), symbolstring, tempstring);
					//TODO: flags
					length = con_strlen(symbolstring) + 3;
					ResizeBuffer<conchar *>(symbolstring, length);
					con_sprintf(symbolstring, length, CONSTRING("%s	:")), symbolstring);
					//TODO: flags
					free(tempstring);
					tempstring = concore->symbolbuffer[i].ptr->convar->GetDescription();
					length = con_scprintf(CONSTRING("%s %s"), symbolstring, tempstring) + 1;
					ResizeBuffer<conchar *>(symbolstring, length);
					con_sprintf(symbolstring, length, CONSTRING("%s %s")), symbolstring, tempstring);
					free(tempstring);
					concore->Output(symbolstring);
					break;
				}
			case ConsoleCore::ConsoleSymbolTypeConCmd:
				{
					length = con_strlen(symbolstring) + 7;
					ResizeBuffer<conchar *>(symbolstring, length);
					con_sprintf(symbolstring, length, CONSTRING("%s cmd	:")), symbolstring);
					//TODO: flags
					length = con_strlen(symbolstring) + 3;
					ResizeBuffer<conchar *>(symbolstring, length);
					con_sprintf(symbolstring, length, CONSTRING("%s	:")), symbolstring);
					//TODO: flags
					//free(tempstring);
					tempstring = concore->symbolbuffer[i].ptr[j].concmd->GetDescription();
					length = con_scprintf(CONSTRING("%s %s"), symbolstring, tempstring) + 1;
					ResizeBuffer<conchar *>(symbolstring, length);
					con_sprintf(symbolstring, length, CONSTRING("%s %s")), symbolstring, tempstring);
					free(tempstring);
					concore->Output(symbolstring);
					break;
				}
			case ConsoleCore::ConsoleSymbolTypeConAlias:
				{
					break;
				}
			}
			
			free(symbolstring);
		}
	}
	concore->Output(CONSTRING("--------------\n%d total convars/concommands"), concore->symbolbuffersize);
}

void ConCmdEcho(ConsoleCore *concore, const unsigned char numargs)
{
	conchar *tempstring = concore->GetCmdArgString();
	if (tempstring == NULL)
	{
		return;
	}
	concore->Output(tempstring);
	free(tempstring);
}

void ConCmdExec(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs == 0)
	{
		concore->Output(CONSTRING("Usage: exec <filename>: execute a script file"));
		return;
	}
	conchar *tempstring = concore->GetCmdArgString();
	if (tempstring == NULL)
	{
		concore->Output(CONSTRING("Usage: exec <filename>: execute a script file"));
		return;
	}
	size_t length = con_strlen(tempstring);
	size_t i = 0;
	while ((tempstring[i] != CONSTRING('.')) && (i < length))
	{
		i++;
	}
	conchar *filename;
	if (i == length)
	{
		length = length + 4;
		filename = (conchar *)calloc(length + 1, sizeof(conchar));
		con_sprintf(filename, length + 1, CONSTRING("%s.cfg")), tempstring);
	}
	else
	{
		filename = (conchar *)calloc(length + 1, sizeof(conchar));
		con_strcpy(filename, tempstring);
	}
	conchar *fullpath;
	if (concore->execpath != NULL)
	{
		size_t templength = con_scprintf(CONSTRING("%s%s"), concore->execpath, filename) + 1;
		fullpath = (conchar *)calloc(templength, sizeof(conchar));
		con_sprintf(fullpath, templength, CONSTRING("%s%s")), concore->execpath, filename);
	}
	else
	{
		fullpath = (conchar *)calloc(length + 1, sizeof(conchar));
		con_strcpy(fullpath, filename);
	}
	confstream execfile;
	execfile.open(fullpath, ios::in);
	if (!execfile.is_open())
	{
		concore->Output(CONSTRING("Couldn't exec %s"), tempstring);
		free(tempstring);
		free(fullpath);
		return;
	}
	constring execstring;
	while (getline(execfile, execstring, CONSTRING('\n')))
	{
		concore->InterpretLine(execstring.c_str());
	}
	free(fullpath);
	free(tempstring);
}

void ConCmdFind(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs != 1)
	{
		concore->Output(CONSTRING("Usage: find <string>"));
		return;
	}
	conchar *searchstring = concore->GetCmdArgString();
	if (searchstring == NULL)
	{
		concore->Output(CONSTRING("Usage: find <string>"));
		return;
	}
	unsigned short numsymbols = concore->GetNumberOfConsoleSymbols();
	conchar *tempstring;
	for (unsigned short i = 0; i < numsymbols; i++)
	{
		//TODO: Sort alphabetically
		tempstring = concore->GetConsoleSymbolHelpStringByIndex(i);
		if (con_strstr(tempstring, searchstring) != NULL)
		{
			concore->Output(tempstring);
		}
		free(tempstring);
	}
}

void ConCmdHelp(ConsoleCore *concore, const unsigned char numargs)
{
	if (numargs != 1)
	{
		concore->Output(CONSTRING("Usage: help <cvarname>"));
		return;
	}
	conchar *cvarname;
	if (!concore->GetCmdArg(1, cvarname))
	{
		concore->Output(CONSTRING("Usage: help <cvarname>"));
		free(cvarname);
		return;
	}
	if (!concore->IsConsoleSymbolExist(cvarname))
	{
		concore->Output(CONSTRING("help: no cvar or command named %s"), cvarname);
		free(cvarname);
		return;
	}
	concore->Output(concore->GetConsoleSymbolHelpString(cvarname));
	free(cvarname);
}