/// \file
/// \brief Source file that contains implementation of the ConsoleScreen class.
/// \details See class description.
/// \author FaTony

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#if defined (WIN32)
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#endif

#include "ConsoleScreen.h"
#include "common.h"

ConsoleScreen::ConsoleScreen(ConsoleCore *core)
{
	concore = core;
	maxoutputbuffersize = 1024;
	maxinputbuffersize = 255;
	pagesize = 23;
#if defined (WIN32)
	outputhandle = GetStdHandle(STD_OUTPUT_HANDLE);
#if defined (CONUNICODE)
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
#endif
	caption = (conchar *)calloc(2, sizeof(conchar));
	outputbuffer = (conchar **)calloc(1, sizeof(conchar *));
	outputbuffersize = 0;
	inputbuffer = (conchar **)calloc(1, sizeof(conchar *));
	inputbuffer[0] = (conchar *)calloc(1, sizeof(conchar));
	inputbuffersize = 1;
	inputbufferposition[0] = 0;
	inputbufferposition[1] = 0;
	screenposition = 0;
	this->UpdateScreen();
}

ConsoleScreen::~ConsoleScreen(void)
{
	free(caption);
	unsigned short i;
	for (i = 0; i < outputbuffersize; i++)
	{
		free(outputbuffer[i]);
	}
	free(outputbuffer);
	for (i = 0; i < inputbuffersize; i++)
	{
		free(inputbuffer[i]);
	}
	free(inputbuffer);
}

void ConsoleScreen::SetCaption(const conchar *string)
{
	ResizeBuffer<conchar *>(caption, con_strlen(string) + 1);
	con_strcpy(caption, string);
	this->PrintCaption();
	this->SetFinalCursorPosition();
}

void ConsoleScreen::CheckUserInput(void)
{
	if (_kbhit())
		{
			int ch = con_getch();
			switch (ch)
			{
			case 0: //Control characters
				{
					ch = _getch();
					switch (ch)
					{
					case 59: //F1
						{
							
							break;
						}
					case 60: //F2
						{
							
							break;
						}
					case 61: //F3
						{
							
							break;
						}
					case 62: //F4
						{
							
							break;
						}
					case 63: //F5
						{
							
							break;
						}
					case 64: //F6
						{
							
							break;
						}
					case 65: //F7
						{
							
							break;
						}
					case 66: //F8
						{
							
							break;
						}
					case 67: //F9
						{
							
							break;
						}
					case 68: //F10
						{
							
							break;
						}
					}
					//printf("Control: 0 %d\n", ch);
					break;
				}
			case 224: //Control characters
				{
					ch = con_getch();
					switch (ch)
					{
					case 71: //Home
						{
							
							break;
						}
					case 72: //Up arrow
						{
							this->InputHistoryBack();
							break;
						}
					case 73: //Page up
						{
							this->GoOnePageUp();
							break;
						}
					case 75: //Left arrow
						{
							this->MoveCursorLeft();
							break;
						}
					case 77: //Right arrow
						{
							this->MoveCursorRight();
							break;
						}
					case 79: //End
						{
							
							break;
						}
					case 80: //Down arrow
						{
							this->InputHistoryForward();
							break;
						}
					case 81: //Page down
						{
							this->GoOnePageDown();
							break;
						}
					case 82: //Insert
						{
							
							break;
						}
					case 83: //Delete
						{
							this->DeleteCharInInputBuffer();
							break;
						}
					case 133: //F11
						{
							
							break;
						}
					case 134: //F12
						{
							
							break;
						}
					}
					//printf("Control: 224 %d\n", ch);
					break;
				}
			case 8: //Backspace
				{
					this->BackspaceCharInInputBuffer();
					break;
				}
			case 13: //Enter
				{
					this->AcceptUserInput();
					break;
				}
			default:
				{
					this->AddCharToInputBuffer(ch);
				}
			}
		}
}

void ConsoleScreen::Print(const conchar *string, ...)
{
	va_list arglist;
    va_start(arglist, string);
	int stringsize = con_vscprintf(string, arglist) + 1;
	conchar *tempstring = (conchar *)calloc(stringsize, sizeof(conchar));
	con_vsprintf(tempstring, stringsize, string, arglist);
	va_end(arglist);
	this->WriteToOutputBuffer(tempstring);
	free(tempstring);
	this->PrintOutputPage();
	this->PrintInputLine();
}

void ConsoleScreen::ClearScreen(void)
{
#if defined (WIN32)
	system("cls");
#endif
}

void ConsoleScreen::ClearInputLine(void)
{
	size_t length = con_strlen(inputbuffer[inputbufferposition[0]]);
	this->SetCursorPosition(2, this->GetInputLineScreenPosition());
	for (size_t i = 0; i < length; i++)
	{
		con_printf(CONSTRING(" "));
	}
}

void ConsoleScreen::SetCursorPosition(const unsigned char x, const unsigned char y)
{
#if defined (WIN32)
	COORD coords = {x, y};
	SetConsoleCursorPosition(outputhandle, coords);
#endif
}

unsigned char ConsoleScreen::GetInputLineScreenPosition(void)
{
	if (outputbuffersize < pagesize)
	{
		return outputbuffersize + 1;
	}
	else
	{
		return pagesize + 1;
	}
}

void ConsoleScreen::SetFinalCursorPosition(void)
{
	this->SetCursorPosition((con_strlen(inputbuffer[inputbuffersize-1]) + 2) % 80, this->GetInputLineScreenPosition());
}

void ConsoleScreen::PrintCaption(void)
{
	this->SetCursorPosition(0, 0);
#if defined (WIN32)
	size_t length = con_strlen(caption);
	DWORD temp;
#if defined (CONUNICODE)
	WriteConsoleW(outputhandle, caption, length, &temp, NULL);
#else
	WriteConsoleA(outputhandle, caption, length, &temp, NULL);
#endif
	COORD coords = {0, 0};
	FillConsoleOutputAttribute(outputhandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY, 80, coords, &temp);
#else
	con_printf(caption);
#endif
}

void ConsoleScreen::PrintOutputPage(void)
{
	this->SetCursorPosition(0, 1);
	unsigned char length;
	for (unsigned char i = 0; ((i < pagesize) && (i < outputbuffersize)); i++)
	{
		con_printf(outputbuffer[screenposition+i]);
		length = con_strlen(outputbuffer[screenposition+i]);
		if (length < 80)
		{
			do
			{
				con_printf(CONSTRING(" "));
				length++;
			} while (length != 80);
		}
	}
}

void ConsoleScreen::PrintInputLine()
{
	this->SetCursorPosition(0, this->GetInputLineScreenPosition());
	con_printf(CONSTRING("> %s"), inputbuffer[inputbuffersize-1]);
}

void ConsoleScreen::UpdateScreen(void)
{
	this->PrintCaption();
	this->PrintOutputPage();
	this->PrintInputLine();
}

void ConsoleScreen::GoOnePageUp(void)
{
	if (screenposition == 0)
	{
		return;
	}
	else if (screenposition < pagesize)
	{
		screenposition = 0;
	}
	else
	{
		screenposition = screenposition - pagesize;
	}
	this->PrintOutputPage();
	this->SetFinalCursorPosition();
}

void ConsoleScreen::GoOnePageDown(void)
{
	if (screenposition >= (outputbuffersize - pagesize))
	{
		return;
	}
	else if ((screenposition + pagesize) > (outputbuffersize - pagesize))
	{
		screenposition = outputbuffersize - pagesize;
	}
	else
	{
		screenposition = screenposition + pagesize;
	}
	this->PrintOutputPage();
	this->SetFinalCursorPosition();
}

void ConsoleScreen::InputHistoryBack(void)
{
	this->ClearInputLine();
	if (inputbufferposition[0] != 0)
	{
		inputbufferposition[0]--;
	}
	else
	{
		if (inputbuffersize != 1)
		{
			inputbufferposition[0] = inputbuffersize - 2;
		}
		else
		{
			inputbufferposition[0] = 0;
		}
	}
	this->FillInputBufferFromHistory();
	this->PrintInputLine();
}

void ConsoleScreen::InputHistoryForward(void)
{
	this->ClearInputLine();
	if (inputbufferposition[0] < (inputbuffersize - 2))
	{
		inputbufferposition[0]++;
	}
	else
	{
		inputbufferposition[0] = 0;
	}
	this->FillInputBufferFromHistory();
	this->PrintInputLine();
}

void ConsoleScreen::WriteToOutputBuffer(const conchar *string)
{
	size_t length = con_strlen(string);
	conchar *tempstring = (conchar *)calloc(81, sizeof(conchar));
	size_t i = 0;
	size_t j = 0;
	while (i < length)
	{
		switch (string[i])
		{
		case CONSTRING('\n'):
			{
				tempstring[j] = CONSTRING('\0');
				this->AppendToOutputBuffer(tempstring);
				j = 0;
				break;
			}
		case CONSTRING('\t'):
			{
				unsigned char pos = j % 8;
				unsigned char lastpos;
				if (pos < 7)
				{
					lastpos = 8;
				}
				else
				{
					lastpos = 16;
				}
				while (pos != lastpos)
				{
					tempstring[j] = CONSTRING(' ');
					j++;
					pos++;
					if (j == 80)
					{
						tempstring[80] = CONSTRING('\0');
						this->AppendToOutputBuffer(tempstring);
						j = 0;
					}
				}
				break;
			}
		default:
			{
				tempstring[j] = string[i];
				j++;
				break;
			}
		}
		if (j == 80)
		{
			tempstring[80] = CONSTRING('\0');
			this->AppendToOutputBuffer(tempstring);
			j = 0;
		}
		i++;
	}
	if (j != 0)
	{
		tempstring[j] = CONSTRING('\0');
		this->AppendToOutputBuffer(tempstring);
	}
	free(tempstring);
}

void ConsoleScreen::AppendToOutputBuffer(const conchar *string)
{
	if (con_strlen(string) > 80)
	{
		this->WriteToOutputBuffer(string);
		return;
	}
	if (outputbuffersize < maxoutputbuffersize)
		{
			ResizeBuffer<conchar **>(outputbuffer, outputbuffersize + 1);
			outputbuffer[outputbuffersize] = (conchar *)calloc(81, sizeof(conchar));
			con_strcpy(outputbuffer[outputbuffersize], string);
			outputbuffersize++;
			if ((outputbuffersize - pagesize) > 0)
			{
				screenposition++;
			}
		}
	else
	{
		conchar *tempstring = outputbuffer[0];
		for (unsigned short i = 0; i < (maxoutputbuffersize - 1); i++)
		{
			outputbuffer[i] = outputbuffer[i+1];
		}
		outputbuffer[maxoutputbuffersize-1] = tempstring;
		tempstring = NULL;
		con_strcpy(outputbuffer[maxoutputbuffersize-1], string);
	}
}

void ConsoleScreen::FillInputBufferFromHistory(void)
{
	size_t length = con_strlen(inputbuffer[inputbufferposition[0]]);
	if (con_strlen(inputbuffer[inputbuffersize-1]) != length)
	{
		ResizeBuffer<conchar *>(inputbuffer[inputbuffersize-1], length + 1);
	}
	con_strcpy(inputbuffer[inputbuffersize-1], inputbuffer[inputbufferposition[0]]);
	inputbufferposition[1] = length;
}

void ConsoleScreen::AddCharToInputBuffer(const int ch)
{
	inputbufferposition[0] = inputbuffersize - 1;
	size_t buffersize = con_strlen(inputbuffer[inputbuffersize-1]);
	ResizeBuffer<conchar *>(inputbuffer[inputbuffersize-1], buffersize + 2);
	conchar *tempstring = (conchar *)calloc((buffersize - inputbufferposition[1] + 1), sizeof(conchar));
	con_strncpy(tempstring, inputbuffer[inputbuffersize-1] + inputbufferposition[1], buffersize - inputbufferposition[1] + 1);
	inputbuffer[inputbuffersize-1][inputbufferposition[1]] = ch;
	con_strncpy(inputbuffer[inputbuffersize-1] + inputbufferposition[1] + 1, tempstring, buffersize - inputbufferposition[1] + 1);
	unsigned char y = this->GetInputLineScreenPosition();
	this->SetCursorPosition(inputbufferposition[1] + 2, y);
	inputbufferposition[1]++;
	con_printf(CONSTRING("%c%s"), ch, tempstring);
	free(tempstring);
	this->SetCursorPosition(inputbufferposition[1] + 2, y);
}

void ConsoleScreen::BackspaceCharInInputBuffer(void)
{
	if (inputbufferposition[1] == 0)
	{
		return;
	}
	inputbufferposition[0] = inputbuffersize - 1;
	size_t buffersize = con_strlen(inputbuffer[inputbuffersize-1]);
	conchar *tempstring = (conchar *)calloc((buffersize - inputbufferposition[1] + 1), sizeof(conchar));
	con_strncpy(tempstring, inputbuffer[inputbuffersize-1] + inputbufferposition[1], buffersize - inputbufferposition[1] + 1);
	ResizeBuffer<conchar *>(inputbuffer[inputbuffersize-1], buffersize);
	con_strncpy(inputbuffer[inputbuffersize-1] + inputbufferposition[1] - 1, tempstring, buffersize - inputbufferposition[1] + 1);
	inputbufferposition[1]--;
	unsigned char y = this->GetInputLineScreenPosition();
	this->SetCursorPosition(inputbufferposition[1] + 2, y);
	con_printf(CONSTRING("%s "), tempstring);
	free(tempstring);
	this->SetCursorPosition(inputbufferposition[1] + 2, y);
}

void ConsoleScreen::MoveCursorLeft(void)
{
	if (inputbufferposition[1] == 0)
	{
		return;
	}
	inputbufferposition[1]--;
#if defined (WIN32)
	this->SetCursorPosition(inputbufferposition[1] + 2, this->GetInputLineScreenPosition());
#else
	size_t buffersize = con_strlen(inputbuffer[inputbuffersize-1]);
	ResizeBuffer<conchar *>(inputbuffer[inputbuffersize-1], buffersize + 2);
	inputbuffer[inputbuffersize-1][buffersize] = 8;
	inputbuffer[inputbuffersize-1][buffersize+1] = '\0';
	this->PrintInputLine();
#endif
}

void ConsoleScreen::MoveCursorRight(void)
{
	size_t buffersize = con_strlen(inputbuffer[inputbuffersize-1]);
	if (inputbufferposition[1] == buffersize)
	{
		return;
	}
	inputbufferposition[1]++;
#ifdef WIN32
	this->SetCursorPosition(inputbufferposition[1] + 2, this->GetInputLineScreenPosition());
#else
	ResizeBuffer<char *>(inputbuffer[inputbuffersize-1], buffersize);
	inputbuffer[inputbuffersize-1][buffersize-1] = CONSTRING('\0');
	this->PrintInputLine();
#endif
}

void ConsoleScreen::DeleteCharInInputBuffer(void)
{
	size_t buffersize = con_strlen(inputbuffer[inputbuffersize-1]);
	if (inputbufferposition[1] == buffersize)
	{
		return;
	}
	inputbufferposition[0] = inputbuffersize - 1;
	conchar *tempstring = (conchar *)calloc((buffersize - inputbufferposition[1]), sizeof(conchar));
	con_strncpy(tempstring, inputbuffer[inputbuffersize-1] + inputbufferposition[1] + 1, buffersize - inputbufferposition[1]);
	ResizeBuffer<conchar *>(inputbuffer[inputbuffersize-1], buffersize);
	con_strncpy(inputbuffer[inputbuffersize-1] + inputbufferposition[1], tempstring, buffersize - inputbufferposition[1]);
	unsigned char y = this->GetInputLineScreenPosition();
	this->SetCursorPosition(inputbufferposition[1] + 2, y);
	con_printf(CONSTRING("%s "), tempstring);
	free(tempstring);
	this->SetCursorPosition(inputbufferposition[1] + 2, y);
}

void ConsoleScreen::AcceptUserInput(void)
{
	if (outputbuffersize >= pagesize)
	{
		this->ClearInputLine();
	}
	this->WriteToInputBuffer();
	inputbufferposition[0] = inputbuffersize - 1;
	inputbufferposition[1] = 0;
	size_t templength = con_strlen(inputbuffer[inputbuffersize-2]) + 3;
	conchar *tempstring = (conchar *)calloc(templength, sizeof(conchar));
	con_sprintf(tempstring, templength, CONSTRING("> %s")), inputbuffer[inputbuffersize-2]);
	this->WriteToOutputBuffer(tempstring);
	concore->InterpretLine(inputbuffer[inputbuffersize-2]);
	this->PrintInputLine();
}

void ConsoleScreen::WriteToInputBuffer(void)
{
	size_t buffersize = con_strlen(inputbuffer[inputbuffersize-1]);
	size_t i = 0;
	do
	{
		if (inputbuffer[inputbuffersize-1][i] == 8)
		{
			ResizeBuffer<conchar *>(inputbuffer[inputbuffersize-1], i + 1);
			inputbuffer[inputbuffersize-1][i] = CONSTRING('\0');
		}
		i++;
	} while (inputbuffer[inputbuffersize-1][i-1] != CONSTRING('\0'));
	if (inputbuffersize < maxinputbuffersize)
		{
			ResizeBuffer<conchar **>(inputbuffer, inputbuffersize + 1);
			inputbuffer[inputbuffersize] = (conchar *)calloc(1, sizeof(conchar));
			inputbuffersize++;
		}
	else
	{
		conchar *tempstring = inputbuffer[0];
		for (unsigned short i = 0; i < (maxinputbuffersize - 1); i++)
		{
			inputbuffer[i] = inputbuffer[i+1];
		}
		inputbuffer[maxinputbuffersize-1] = tempstring;
		tempstring = NULL;
		ResizeBuffer<conchar *>(inputbuffer[maxinputbuffersize-1], 1);
		inputbuffer[maxinputbuffersize-1][0] = CONSTRING('\0');
	}
}