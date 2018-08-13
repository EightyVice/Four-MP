/// \file
/// \brief Source file that contains implementation of the ConsoleCore class.
/// \details See class description.
/// \author FaTony

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "common.h"
#include "ConsoleCore.h"
#include "coreconcommands.h"

ConsoleCore::ConsoleCore(void)
{
	outputfunction = NULL;
	execpath = NULL;
	maxsymbolbuffersize = 65535;
	symbolbuffer = NULL;
	symbolbuffersize = 0;
	maxhookspercvar = 255;
	maxcmdspersymbol = 255;
	commandbuffer = NULL;
	commandargs = NULL;
	argpos = 0;
	numargs = 0;
}

ConsoleCore::~ConsoleCore(void)
{
	unsigned short i;
	for (i = 0; i < symbolbuffersize; i++)
	{
		switch (symbolbuffer[0].type)
		{
		case ConsoleSymbolTypeConVar:
			{
				delete symbolbuffer[0].ptr->convar;
				break;
			}
		case ConsoleSymbolTypeConCmd:
			{
				for (unsigned char j = 0; j < symbolbuffer[0].numcmds; j++)
				{
					delete symbolbuffer[0].ptr[0].concmd;
				}
				break;
			}
		case ConsoleSymbolTypeConAlias:
			{
				delete symbolbuffer[0].ptr->conalias;
				break;
			}
		}
	}
	free(symbolbuffer);
	if (commandbuffer != NULL)
	{
		free(commandbuffer);
	}
	if (commandargs != NULL)
	{
		for (i = 0; i <= numargs; i++)
		{
			free(commandargs[i]);
		}
	}
	free(commandargs);
}

void ConsoleCore::SetOutputFunction(void *function)
{
	outputfunction = function;
}

void ConsoleCore::SetExecPath(const conchar *string)
{
	if (string == NULL)
	{
		if (execpath != NULL)
		{
			free(execpath);
			execpath = NULL;
		}
		return;
	}
	execpath = (conchar *)calloc(con_strlen(string) + 1, sizeof(conchar));
	con_strcpy(execpath, string);
}

void ConsoleCore::RegisterStandardLibrary(void)
{
	this->AddConCmd(CONSTRING("alias"), ConCmdAlias, CONSTRING("Alias a command."), 0);
	this->AddConCmd(CONSTRING("cvarlist"), ConCmdCvarlist, CONSTRING("Show the list of convars/concommands."), 0);
	this->AddConVar(CONSTRING("developer"), 0, CONSTRING("Show developer messages."), 0, true, 0, true, 2);
	this->AddConCmd(CONSTRING("echo"), ConCmdEcho, CONSTRING("Echo text to console."), 0);
	this->AddConCmd(CONSTRING("exec"), ConCmdExec, CONSTRING("Execute script file."), 0);
	this->AddConCmd(CONSTRING("find"), ConCmdFind, CONSTRING("Find concommands with the specified string in their name/help text."), 0);
	this->AddConCmd(CONSTRING("help"), ConCmdHelp, CONSTRING("Find help about a convar/concommand."), 0);
}

void ConsoleCore::Output(const conchar *string, ...)
{
	if (outputfunction == NULL)
	{
		return;
	}
	va_list arglist;
	va_start(arglist, string);
	int stringsize = con_vscprintf(string, arglist) + 1;
	conchar *tempstring = (conchar *)calloc(stringsize, sizeof(conchar));
	con_vsprintf(tempstring, stringsize, string, arglist);
	va_end(arglist);
	((void (*) (const conchar *))outputfunction)(tempstring);
	free(tempstring);
}


unsigned short ConsoleCore::GetNumberOfConsoleSymbols(void)
{
	return symbolbuffersize;
}

bool ConsoleCore::IsConsoleSymbolExist(const conchar *name)
{
	if (name == NULL)
	{
		return false;
	}
	for (unsigned short i = 0; i < symbolbuffersize; i++)
	{
		if ((con_strcmp(symbolbuffer[i].name, name)) == 0)
		{
			return true;
		}
	}
	return false;
}

ConVar *ConsoleCore::AddConVar(const conchar *name, const float defaultvalue, const conchar *description, const int flags, const bool hasMin, const float min, const bool hasMax, const float max)
{
	if (name == NULL)
	{
		return NULL;
	}
	if (hasMin && hasMax && (min > max))
	{
		return NULL;
	}
	if (symbolbuffersize == maxsymbolbuffersize)
	{
		return NULL;
	}
	unsigned short index;
	if (this->GetConsoleSymbolIndex(name, index))
	{
		if (symbolbuffer[index].type != ConsoleSymbolTypeConAlias)
		{
			return NULL;
		}
		delete symbolbuffer[index].ptr->conalias;
		symbolbuffer[index].type = ConsoleSymbolTypeConVar;
		symbolbuffer[index].ptr->convar = new ConVar(this, name, defaultvalue, description, flags, hasMin, min, hasMax, max);
		return symbolbuffer[index].ptr->convar;
	}
	if (!ResizeBuffer<ConsoleSymbol *>(symbolbuffer, symbolbuffersize + 1))
	{
		return NULL;
	}
	symbolbuffer[symbolbuffersize].name = (conchar *)calloc(con_strlen(name) + 1, sizeof(conchar));
	con_strcpy(symbolbuffer[symbolbuffersize].name, name);
	symbolbuffer[symbolbuffersize].type = ConsoleSymbolTypeConVar;
	symbolbuffer[symbolbuffersize].ptr = new ConsoleSymbolPtr;
	symbolbuffer[symbolbuffersize].ptr->convar = new ConVar(this, name, defaultvalue, description, flags, hasMin, min, hasMax, max);
	symbolbuffer[symbolbuffersize].numcmds = 0;
	symbolbuffersize++;
	return symbolbuffer[symbolbuffersize-1].ptr->convar;
}

ConVar *ConsoleCore::AddConVar(const conchar *name, const int defaultvalue, const conchar *description, const int flags, const bool hasMin, const int min, const bool hasMax, const int max)
{
	if (name == NULL)
	{
		return NULL;
	}
	if (hasMin && hasMax && (min > max))
	{
		return NULL;
	}
	if (symbolbuffersize == maxsymbolbuffersize)
	{
		return NULL;
	}
	unsigned short index;
	if (this->GetConsoleSymbolIndex(name, index))
	{
		if (symbolbuffer[index].type != ConsoleSymbolTypeConAlias)
		{
			return NULL;
		}
		delete symbolbuffer[index].ptr->conalias;
		symbolbuffer[index].type = ConsoleSymbolTypeConVar;
		symbolbuffer[index].ptr->convar = new ConVar(this, name, defaultvalue, description, flags, hasMin, min, hasMax, max);
		return symbolbuffer[index].ptr->convar;
	}
	if (!ResizeBuffer<ConsoleSymbol *>(symbolbuffer, symbolbuffersize + 1))
	{
		return NULL;
	}
	symbolbuffer[symbolbuffersize].name = (conchar *)calloc(con_strlen(name) + 1, sizeof(conchar));
	con_strcpy(symbolbuffer[symbolbuffersize].name, name);
	symbolbuffer[symbolbuffersize].type = ConsoleSymbolTypeConVar;
	symbolbuffer[symbolbuffersize].ptr = new ConsoleSymbolPtr;
	symbolbuffer[symbolbuffersize].ptr->convar = new ConVar(this, name, defaultvalue, description, flags, hasMin, min, hasMax, max);
	symbolbuffer[symbolbuffersize].numcmds = 0;
	symbolbuffersize++;
	return symbolbuffer[symbolbuffersize-1].ptr->convar;
}

ConVar *ConsoleCore::AddConVar(const conchar *name, const conchar *defaultvalue, const conchar *description, const int flags)
{
	if (name == NULL)
	{
		return NULL;
	}
	if (symbolbuffersize == maxsymbolbuffersize)
	{
		return NULL;
	}
	unsigned short index;
	if (this->GetConsoleSymbolIndex(name, index))
	{
		if (symbolbuffer[index].type != ConsoleSymbolTypeConAlias)
		{
			return NULL;
		}
		delete symbolbuffer[index].ptr->conalias;
		symbolbuffer[index].type = ConsoleSymbolTypeConVar;
		symbolbuffer[index].ptr->convar = new ConVar(this, name, defaultvalue, description, flags);
		return symbolbuffer[index].ptr->convar;
	}
	if (!ResizeBuffer<ConsoleSymbol *>(symbolbuffer, symbolbuffersize + 1))
	{
		return NULL;
	}
	symbolbuffer[symbolbuffersize].name = (conchar *)calloc(con_strlen(name) + 1, sizeof(conchar));
	con_strcpy(symbolbuffer[symbolbuffersize].name, name);
	symbolbuffer[symbolbuffersize].type = ConsoleSymbolTypeConVar;
	symbolbuffer[symbolbuffersize].ptr = new ConsoleSymbolPtr;
	symbolbuffer[symbolbuffersize].ptr->convar = new ConVar(this, name, defaultvalue, description, flags);
	symbolbuffer[symbolbuffersize].numcmds = 0;
	symbolbuffersize++;
	return symbolbuffer[symbolbuffersize-1].ptr->convar;
}

ConCmd *ConsoleCore::AddConCmd(const conchar *name, void *callback, const conchar *description, const int flags)
{
	if (name == NULL)
	{
		return NULL;
	}
	if (callback == NULL)
	{
		return NULL;
	}
	unsigned short index;
	if (this->GetConsoleSymbolIndex(name, index))
	{
		if (symbolbuffer[index].type == ConsoleSymbolTypeConVar)
		{
			return NULL;
		}
		if (symbolbuffer[index].type == ConsoleSymbolTypeConAlias)
		{
			delete symbolbuffer[index].ptr->conalias;
			symbolbuffer[index].type = ConsoleSymbolTypeConCmd;
			symbolbuffer[index].ptr[0].concmd = new ConCmd(this, name, callback, description, flags);
			return symbolbuffer[index].ptr[0].concmd;
		}
		if (symbolbuffer[index].numcmds == maxcmdspersymbol)
		{
			return NULL;
		}
		if (!ResizeBuffer<ConsoleSymbolPtr *>(symbolbuffer[index].ptr, symbolbuffer[index].numcmds + 1))
		{
			return NULL;
		}
		symbolbuffer[index].ptr[symbolbuffer[index].numcmds].concmd = new ConCmd(this, name, callback, description, flags);
		symbolbuffer[index].numcmds++;
		return symbolbuffer[index].ptr[symbolbuffer[index].numcmds-1].concmd;
	}
	if (symbolbuffersize == maxsymbolbuffersize)
	{
		return NULL;
	}
	if (!ResizeBuffer<ConsoleSymbol *>(symbolbuffer, symbolbuffersize + 1))
	{
		return NULL;
	}
	symbolbuffer[symbolbuffersize].name = (conchar *)calloc(con_strlen(name) + 1, sizeof(conchar));
	con_strcpy(symbolbuffer[symbolbuffersize].name, name);
	symbolbuffer[symbolbuffersize].type = ConsoleSymbolTypeConCmd;
	symbolbuffer[symbolbuffersize].ptr = new ConsoleSymbolPtr;
	symbolbuffer[symbolbuffersize].ptr[0].concmd = new ConCmd(this, name, callback, description, flags);
	symbolbuffer[symbolbuffersize].numcmds = 1;
	symbolbuffersize++;
	return symbolbuffer[symbolbuffersize-1].ptr[0].concmd;
}

conchar *ConsoleCore::GetConsoleSymbolHelpString(const conchar *name)
{
	if (name == NULL)
	{
		return NULL;
	}
	unsigned short index;
	if (!this->GetConsoleSymbolIndex(name, index))
	{
		return NULL;
	}
	return this->GetHelpString(&symbolbuffer[index]);
}

conchar *ConsoleCore::GetConsoleSymbolHelpStringByIndex(unsigned short index)
{
	if (index >= symbolbuffersize)
	{
		return NULL;
	}
	return this->GetHelpString(&symbolbuffer[index]);
}

unsigned char ConsoleCore::GetCmdArgs(void)
{
	return numargs;
}

conchar *ConsoleCore::GetCmdArgString(void)
{
	if ((argpos == 0) || (commandbuffer == NULL))
	{
		return NULL;
	}
	conchar *arg = (conchar *)calloc(con_strlen(commandbuffer + argpos) + 1, sizeof(conchar));
	con_strcpy(arg, commandbuffer + argpos);
	return arg;
}

bool ConsoleCore::GetCmdArgType(const unsigned char argnum, ConVarType &type)
{
	if ((argpos == 0) || (commandbuffer == NULL))
	{
		return false;
	}
	if (!((commandargs[argnum][0] == CONSTRING('-')) || ((commandargs[argnum][0] >= 48) && (commandargs[argnum][0] <= 57))))
	{
		type = ConVarTypeString;
		return true;
	}
	unsigned char firstnum = 0;
	if (commandargs[argnum][0] == CONSTRING('-'))
	{
		firstnum = 1;
	}
	size_t length = con_strlen(commandargs[argnum]);
	size_t i = 1;
	bool floatflag = false;
	while (i < length)
	{
		if (!((commandargs[argnum][i] == CONSTRING('.')) || ((commandargs[argnum][i] >= 48) && (commandargs[argnum][i] <= 57))))
		{
			type = ConVarTypeString;
			return true;
		}
		if (commandargs[argnum][i] == CONSTRING('.'))
		{
			if (floatflag)
			{
				type = ConVarTypeString;
				return true;
			}
			floatflag = true;
			if (i == firstnum)
			{
				type = ConVarTypeString;
				return true;
			}
		}
		i++;
	}
	if (floatflag)
	{
		type = ConVarTypeFloat;
		return true;
	}
	type = ConVarTypeInt;
	return true;
}

bool ConsoleCore::GetCmdArg(const unsigned char argnum, conchar *&arg)
{
	if (argnum > numargs)
	{
		return false;
	}
	arg = (conchar *)calloc(con_strlen(commandargs[argnum]) + 1, sizeof(conchar));
	con_strcpy(arg, commandargs[argnum]);
	return true;
}

bool ConsoleCore::GetCmdArg(const unsigned char argnum, int &arg)
{
	if (argnum > numargs)
	{
		return false;
	}
	ConVarType type;
	if ((this->GetCmdArgType(argnum, type)) && (type != ConVarTypeInt))
	{
		return false;
	}
	arg = con_atoi(commandargs[argnum]);
	return true;
}

bool ConsoleCore::GetCmdArg(const unsigned char argnum, float &arg)
{
	if (argnum > numargs)
	{
		return false;
	}
	ConVarType type;
	if ((this->GetCmdArgType(argnum, type)) && (type != ConVarTypeFloat))
	{
		return false;
	}
	arg = (float)con_atof(commandargs[argnum]);
	return true;
}

void ConsoleCore::InterpretLine(const conchar *string)
{
	size_t length = con_strlen(string);
	size_t i = 0;
	while (((string[i] == CONSTRING(' ')) || (string[i] == CONSTRING('"'))) && (i < length))
	{
		i++;
	}
	if (i == length)
	{
		return;
	}
	if ((string[i] == CONSTRING('/')) && (string[i+1] == CONSTRING('/')))
	{
		return;
	}
	bool comment;
	while (i < length)
	{
		commandbuffer = this->GetCommand(string, i);
		i = i + con_strlen(commandbuffer) + 1;
		comment = (!this->InterpretCommand());
		free(commandbuffer);
		commandbuffer = NULL;
		if (comment)
		{
			return;
		}
	}
}

void ConsoleCore::AddConAlias(const conchar *name, const conchar *cmdstring)
{
	if (name == NULL)
	{
		return;
	}
	if (cmdstring == NULL)
	{
		return;
	}
	unsigned short index;
	if (this->GetConsoleSymbolIndex(name, index))
	{
		if (symbolbuffer[index].type != ConsoleSymbolTypeConAlias)
		{
			this->Output(CONSTRING("Cannot redefine registered convars/concommands."));
			return;
		}
		symbolbuffer[index].ptr->conalias->SetCommandString(cmdstring);
		return;
	}
	if (symbolbuffersize == maxsymbolbuffersize)
	{
		return;
	}
	if (!ResizeBuffer<ConsoleSymbol *>(symbolbuffer, symbolbuffersize + 1))
	{
		return;
	}
	symbolbuffer[symbolbuffersize].name = (conchar *)calloc(con_strlen(name) + 1, sizeof(conchar));
	con_strcpy(symbolbuffer[symbolbuffersize].name, name);
	symbolbuffer[symbolbuffersize].type = ConsoleSymbolTypeConAlias;
	symbolbuffer[symbolbuffersize].ptr = new ConsoleSymbolPtr;
	symbolbuffer[symbolbuffersize].ptr->conalias = new ConAlias(this, name, cmdstring);
	symbolbuffer[symbolbuffersize].numcmds = 0;
	symbolbuffersize++;
	return;
}

bool ConsoleCore::DeleteConsoleSymbolByIndex(const unsigned short index)
{
	if (index >= symbolbuffersize)
	{
		return false;
	}
	free(symbolbuffer[index].name);
	for (unsigned short i = index; i < (symbolbuffersize - 1); i++)
	{
		symbolbuffer[i] = symbolbuffer[i+1];
	}
	
	if (!ResizeBuffer<ConsoleSymbol *>(symbolbuffer, symbolbuffersize - 1))
	{
		return false;
	}
	symbolbuffersize--;
	return true;
}

void ConsoleCore::DeleteConVar(const conchar *name)
{
	if (name == NULL)
	{
		return;
	}
	unsigned short index;
	if (!this->GetConsoleSymbolIndex(name, index))
	{
		return;
	}
	if (symbolbuffer[index].type != ConsoleSymbolTypeConVar)
	{
		return;
	}
	if (!this->DeleteConsoleSymbolByIndex(index))
	{
		return;
	}
}

void ConsoleCore::DeleteConCmd(const conchar *name, ConCmd *ptr)
{
	if (name == NULL)
	{
		return;
	}
	if (ptr == NULL)
	{
		return;
	}
	unsigned short index;
	if (!this->GetConsoleSymbolIndex(name, index))
	{
		return;
	}
	if (symbolbuffer[index].type != ConsoleSymbolTypeConCmd)
	{
		return;
	}
	if (symbolbuffer[index].numcmds == 1)
	{
		if (!this->DeleteConsoleSymbolByIndex(index))
		{
			return;
		}
		return;
	}
	for (unsigned char i = 0; i < symbolbuffer[index].numcmds; i++)
	{
		if (symbolbuffer[index].ptr[i].concmd == ptr)
		{
			for (; i < (symbolbuffer[index].numcmds - 1); i++)
			{
				symbolbuffer[index].ptr[i] = symbolbuffer[index].ptr[i+1];
			}
			if (!ResizeBuffer<ConsoleSymbolPtr *>(symbolbuffer[index].ptr, symbolbuffer[index].numcmds - 1))
			{
				return;
			}
			symbolbuffer[index].numcmds--;
			return;
		}
	}
}

bool ConsoleCore::GetConsoleSymbolIndex(const conchar *name, unsigned short &index)
{
	for (index = 0; index < symbolbuffersize; index++)
	{
		if ((con_strcmp(symbolbuffer[index].name, name)) == 0)
		{
			return true;
		}
	}
	return false;
}

conchar *ConsoleCore::GetHelpString(const ConsoleSymbol *symbol)
{
	size_t length = con_strlen(symbol->name) + 3;
	conchar *helpstring = (conchar *)calloc(length, sizeof(conchar));
	con_sprintf(helpstring, length, CONSTRING("\"%s\"")), symbol->name);
	switch (symbol->type)
	{
	case ConsoleSymbolTypeConVar:
		{
			switch (symbol->ptr->convar->GetType())
			{
			case ConVarTypeFloat:
				{
					float value;
					symbol->ptr->convar->GetValue(value);
					length = con_scprintf(CONSTRING("%s = \"%f\""), helpstring, value) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s = \"%f\"")), helpstring, value);
					break;
				}
			case ConVarTypeInt:
				{
					int value;
					symbol->ptr->convar->GetValue(value);
					length = con_scprintf(CONSTRING("%s = \"%d\""), helpstring, value) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s = \"%d\"")), helpstring, value);
					break;
				}
			case ConVarTypeString:
				{
					conchar *value;
					symbol->ptr->convar->GetValue(value);
					length = con_scprintf(CONSTRING("%s = \"%s\""), helpstring, value) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s = \"%s\"")), helpstring, value);
					free(value);
					break;
				}
			}
			switch (symbol->ptr->convar->GetDefaultType())
			{
			case ConVarTypeFloat:
				{
					float value;
					symbol->ptr->convar->GetDefaultValue(value);
					length = con_scprintf(CONSTRING("%s ( def. \"%f\" )"), helpstring, value) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s ( def. \"%f\" )")), helpstring, value);
					if (symbol->ptr->convar->GetBound(ConVarBoundLower, value))
					{
						length = con_scprintf(CONSTRING("%s min. %f"), helpstring, value) + 1;
						ResizeBuffer<conchar *>(helpstring, length);
						con_sprintf(helpstring, length, CONSTRING("%s min. %f")), helpstring, value);
					}
					if (symbol->ptr->convar->GetBound(ConVarBoundUpper, value))
					{
						length = con_scprintf(CONSTRING("%s max. %f"), helpstring, value) + 1;
						ResizeBuffer<conchar *>(helpstring, length);
						con_sprintf(helpstring, length, CONSTRING("%s max. %f")), helpstring, value);
					}
					break;
				}
			case ConVarTypeInt:
				{
					int value;
					symbol->ptr->convar->GetDefaultValue(value);
					length = con_scprintf(CONSTRING("%s ( def. \"%d\" )"), helpstring, value) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s ( def. \"%d\" )")), helpstring, value);
					if (symbol->ptr->convar->GetBound(ConVarBoundLower, value))
					{
						length = con_scprintf(CONSTRING("%s min. %d"), helpstring, value) + 1;
						ResizeBuffer<conchar *>(helpstring, length);
						con_sprintf(helpstring, length, CONSTRING("%s min. %d")), helpstring, value);
					}
					if (symbol->ptr->convar->GetBound(ConVarBoundUpper, value))
					{
						length = con_scprintf(CONSTRING("%s max. %d"), helpstring, value) + 1;
						ResizeBuffer<conchar *>(helpstring, length);
						con_sprintf(helpstring, length, CONSTRING("%s max. %d")), helpstring, value);
					}
					break;
				}
			case ConVarTypeString:
				{
					conchar *value;
					symbol->ptr->convar->GetDefaultValue(value);
					length = con_scprintf(CONSTRING("%s  ( def. \"%s\" )"), helpstring, value) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s  ( def. \"%s\" )")), helpstring, value);
					free(value);
					break;
				}
			}
			if (symbol->ptr->convar->GetFlags() != 0)
			{
				//TODO: flags
			}
			conchar *desc = symbol->ptr->convar->GetDescription();
			if (con_strlen(desc) != 0)
			{
				length = con_scprintf(CONSTRING("%s\n - %s"), helpstring, desc) + 1;
				ResizeBuffer<conchar *>(helpstring, length);
				con_sprintf(helpstring, length, CONSTRING("%s\n - %s")), helpstring, desc);
			}
			free(desc);
			break;
		}
	case ConsoleSymbolTypeConCmd:
		{
			conchar *desc;
			for (unsigned char i = 0; i < symbol->numcmds; i++)
			{
				if (symbol->ptr->convar->GetFlags() != 0)
				{
					//TODO: flags
				}
				desc = symbol->ptr->convar->GetDescription();
				if (con_strlen(desc) != 0)
				{
					length = con_scprintf(CONSTRING("%s\n - %s"), helpstring, desc) + 1;
					ResizeBuffer<conchar *>(helpstring, length);
					con_sprintf(helpstring, length, CONSTRING("%s\n - %s")), helpstring, desc);
				}
				free(desc);
			}
			break;
		}
	case ConsoleSymbolTypeConAlias:
		{
			ResizeBuffer<conchar *>(helpstring, 1);
			helpstring[0] = CONSTRING('\0');
			break;
		}
	}
	return helpstring;
}

conchar *ConsoleCore::GetCommand(const conchar *string, const unsigned int startindex)
{
	size_t length = con_strlen(string);
	size_t i = startindex;
	bool stringargument = false;
	while ((!((string[i] == CONSTRING(';')) && (stringargument == false))) && (i < length))
	{
		if (string[i] == CONSTRING('"'))
		{
			stringargument = !stringargument;
		}
		i++;
	}
	length = i - startindex;
	conchar *cmdstring = (conchar *)calloc(length + 1, sizeof(conchar));
	con_strncpy(cmdstring, string + startindex, length);
	cmdstring[length] = CONSTRING('\0');
	return cmdstring;
}

bool ConsoleCore::InterpretCommand(void)
{
	size_t length = con_strlen(commandbuffer);
	size_t i = 0;
	while (((commandbuffer[i] == CONSTRING(' ')) || (commandbuffer[i] == CONSTRING('"'))) && (i < length))
	{
		i++;
	}
	size_t startindex = i;
	while ((commandbuffer[i] != CONSTRING(' ')) && (i < length))
	{
		i++;
	}
	size_t templength = i - startindex;
	if (templength == 0)
	{
		return true;
	}
	conchar *symbolname = (conchar *)calloc(templength + 1, sizeof(conchar));
	con_strncpy(symbolname, commandbuffer + startindex, templength);
	symbolname[templength] = CONSTRING('\0');
	unsigned short index;
	if (!this->GetConsoleSymbolIndex(symbolname, index))
	{
		this->Output(CONSTRING("Unknown command \"%s\""), symbolname);
		free(symbolname);
		return true;
	}
	if (commandargs != NULL)
	{
		for (unsigned char k = 0; k <= numargs; k++)
		{
			free(commandargs[k]);
			commandargs[k] = NULL;
		}
		free(commandargs);
	}
	commandargs = (conchar **)calloc(1, sizeof(conchar *));
	commandargs[0] = (conchar *)calloc(templength + 1, sizeof(conchar));
	con_strcpy(commandargs[0], symbolname);
	i++;
	unsigned char j = 1;
	bool comment = false;
	while ((i < length) && (!comment))
	{
		if (commandbuffer[i] == CONSTRING(' '))
		{
			i++;
		}
		else if (commandbuffer[i] == CONSTRING('"'))
		{
			startindex = i + 1;
			if (j == 1)
			{
				argpos = startindex;
			}
			i++;
			while ((commandbuffer[i] != CONSTRING('"')) && (i < length))
			{
				i++;
			}
			templength = i - startindex;
			i++;
			ResizeBuffer<conchar **>(commandargs, j + 1);
			commandargs[j] = (conchar *)calloc(templength + 1, sizeof(conchar));
			con_strncpy(commandargs[j], commandbuffer + startindex, templength);
			commandargs[j][templength] = CONSTRING('\0');
			j++;
		}
		else
		{
			startindex = i;
			if (j == 1)
			{
				if ((commandbuffer[i] == CONSTRING('/')) && (commandbuffer[i+1] == CONSTRING('/')))
				{
					comment = true;
				}
				else
				{
					argpos = startindex;
				}
			}
			if (!comment)
			{
				i++;
				while ((commandbuffer[i] != CONSTRING(' ')) && (i < length))
				{
					i++;
				}
				templength = i - startindex;
				ResizeBuffer<conchar **>(commandargs, j + 1);
				commandargs[j] = (conchar *)calloc(templength + 1, sizeof(conchar));
				con_strncpy(commandargs[j], commandbuffer + startindex, templength);
				commandargs[j][templength] = CONSTRING('\0');
				j++;
			}
		}
	}
	numargs = j - 1;
	switch (symbolbuffer[index].type)
	{
	case ConsoleSymbolTypeConVar:
		{
			if (numargs == 0)
			{
				this->Output(this->GetHelpString(&symbolbuffer[index]));
			}
			else if (numargs == 1)
			{
				ConVarType type;
				this->GetCmdArgType(1, type);
				switch (type)
				{
				case ConVarTypeFloat:
					{
						float value;
						this->GetCmdArg(1, value);
						symbolbuffer[index].ptr->convar->SetValue(value);
						break;
					}
				case ConVarTypeInt:
					{
						int value;
						this->GetCmdArg(1, value);
						symbolbuffer[index].ptr->convar->SetValue(value);
						break;
					}
				case ConVarTypeString:
					{
						conchar *value;
						this->GetCmdArg(1, value);
						symbolbuffer[index].ptr->convar->SetValue(value);
						free(value);
						break;
					}
				}
			}
			else
			{
				conchar *arg = this->GetCmdArgString();
				symbolbuffer[index].ptr->convar->SetValue(arg);
			}
			break;
		}
	case ConsoleSymbolTypeConCmd:
		{
			for (j = 0; j < symbolbuffer[index].numcmds; j++)
			{
				symbolbuffer[index].ptr[j].concmd->Execute();
			}
			break;
		}
	case ConsoleSymbolTypeConAlias:
		{
			symbolbuffer[index].ptr->conalias->Execute();
			break;
		}
	}
	free(symbolname);
	if (commandargs != NULL)
	{
		for (i = 0; i <= numargs; i++)
		{
			free(commandargs[i]);
			commandargs[i] = NULL;
		}
		free(commandargs);
	}
	commandargs = NULL;
	argpos = 0;
	numargs = 0;
	return !comment;
}
