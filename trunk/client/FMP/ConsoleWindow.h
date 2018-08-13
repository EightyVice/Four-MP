/// \file
/// \brief Header file that describes the ConsoleWindow class.
/// \details See class description.
/// \author FaTony

#pragma once

#include <windows.h>
#include "..\GUI\CGUI.h"
#include "../../Shared/logging/log.h"

class ConsoleWindow : public Logger
{
public:
	ConsoleWindow(void);
	~ConsoleWindow(void);
	void Load(void);
	bool IsVisible(void);
	void Show(void);
	void Hide(void);
	virtual void Log(const wchar_t *type, const wchar_t *string, char* = 0);
private:
	bool IsLoaded;
	CRITICAL_SECTION cs;
	CWindow *mainwindow;
	CTextBox *outputbox;
	CEditBox *inputbox;
	CButton *submitbutton;
	void SubmitText(void);
	friend void InputBoxCallback(CElement *pElement, CMSG msg, int Param);
	friend void SubmitButtonCallback(CElement *pElement, CMSG msg, int Param);
};

void InputBoxCallback(CElement *pElement, CMSG msg, int Param);
void SubmitButtonCallback(CElement *pElement, CMSG msg, int Param);
void PrintToConsole(const wchar_t *string, ...);