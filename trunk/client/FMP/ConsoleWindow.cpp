/// \file
/// \brief Source file that contains implementation of the ConsoleWindow class.
/// \details See class description.
/// \author FaTony

#include "ConsoleWindow.h"
#include "..\..\Shared\Console\ConsoleCore.h"
#include "d3d9\gui.h"

extern ConsoleCore concore;
extern FMPGUI Gui;
extern ConsoleWindow conwindow;

ConsoleWindow::ConsoleWindow(void)
{
	IsLoaded = false;
	InitializeCriticalSection(&cs);
}

ConsoleWindow::~ConsoleWindow(void)
{
	/*if (IsLoaded)
	{
		delete outputbox;
		delete inputbox;
		delete submitbutton;
		delete mainwindow;
	}*/
	DeleteCriticalSection(&cs);
	IsLoaded = false;
}

void ConsoleWindow::Load(void)
{
	EnterCriticalSection(&cs_gui);
	mainwindow = new CWindow(Gui.m_Gui, 412, 25, 587, 568, L"Console");
	outputbox = new CTextBox(Gui.m_Gui, 8, 8, 571, 492);
	outputbox->ShowSlider(true);
	inputbox = new CEditBox(Gui.m_Gui, 8, 508, 492, 24, NULL, NULL, InputBoxCallback);
	submitbutton = new CButton(Gui.m_Gui, 508, 508, 64, 24, L"Submit", NULL, SubmitButtonCallback);
	mainwindow->AddElement(outputbox);
	mainwindow->AddElement(inputbox);
	mainwindow->AddElement(submitbutton);
	IsLoaded = true;
	LeaveCriticalSection(&cs_gui);
}

bool ConsoleWindow::IsVisible(void)
{
	return mainwindow->IsVisible();
}

void ConsoleWindow::Show(void)
{
	mainwindow->SetVisible(true);
}

void ConsoleWindow::Hide(void)
{
	mainwindow->SetVisible(false);
}

void ConsoleWindow::Log(const wchar_t *type, const wchar_t *string, va_list arglist)
{
	if (!IsLoaded) return;
	if (string == NULL) return;
	if(!outputbox) return;

	EnterCriticalSection(&cs);

	int stringsize = _vscwprintf(string, arglist);
	wchar_t *tempstring = (wchar_t *)calloc(stringsize + 1, sizeof(wchar_t));
	vswprintf(tempstring, string, arglist);

	outputbox->AddString(tempstring);

	SAFE_DELETE(tempstring); // access violation

	LeaveCriticalSection(&cs);
}

void ConsoleWindow::SubmitText(void)
{
	EnterCriticalSection(&cs);
	this->Log(L">", inputbox->GetString().c_str());
	concore.InterpretLine(inputbox->GetString().c_str());
	inputbox->SetString(L"");
	LeaveCriticalSection(&cs);
}

void InputBoxCallback(CElement *pElement, CMSG msg, int Param)
{
	switch (msg)
	{
	case END:
		{
			conwindow.SubmitText();
			break;
		}
	}
}

void SubmitButtonCallback(CElement *pElement, CMSG msg, int Param)
{
	if (msg != CLICK)
	{
		return;
	}
	conwindow.SubmitText();
}

void PrintToConsole(const wchar_t *string, ...)
{
	va_list arglist; 
	va_start(arglist, string);
	conwindow.Log(L"", string, arglist);
	va_end(arglist); 
}
