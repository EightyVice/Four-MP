/// \file
/// \brief Header file that describes the ConsoleScreen class.
/// \details See class description.
/// \author FaTony

#pragma once

#include "ConsoleCore.h"

#if defined (WIN32)
#include <windows.h>
#endif

/// \brief A console screen.
/// \details ConsoleScreen is a wrapper around ConsoleCore that work with the OS native
/// console. It reads keyboard input and outputs text to the console window. It separates
/// console window into 3 sections: Caption - highlighted 1st line that displays important
/// information, output page that holds everything that has been recently printed to the 
/// console and input line that contains was user has currently typed before entering it
/// into the console.
/// \author FaTony

class ConsoleScreen
{
public:
	/// \brief Inits the screen.
	/// \param[in] core Pointer to the console core this screen will be wrapped around.
	ConsoleScreen(ConsoleCore *core);

	/// \brief Unloads everything.
	~ConsoleScreen(void);

	/// \brief Sets caption (1st line).
	/// \param[in] string String to print as caption.
	/// \return No return.
	void SetCaption(const conchar *string);

	/// \brief Handles keyboard input.
	/// \return No return.
	void CheckUserInput(void);

	/// \brief Prints string to the output page.
	/// \param[in] string Format-control string.
	/// \param[in] ... Optional arguments.
	/// \return No return.
	void Print(const conchar *string, ...);
private:
	ConsoleCore *concore; ///< Pointer to the console core this screen is wrapped around.
	conchar *caption; ///< Holds caption text.
	unsigned short maxoutputbuffersize; ///< Holds maximum size of the output buffer (in lines).
	unsigned short outputbuffersize; ///< Holds current size of the output buffer (in lines).
	conchar **outputbuffer; ///< Holds everything that was recently outputted to screen.
	unsigned char maxinputbuffersize; ///< Holds maximum size of the input buffer (in lines).
	unsigned char inputbuffersize; ///< Holds curent size of the input buffer (in lines).
	conchar **inputbuffer; //< Holds input history and current line.
#if defined (WIN32)
	HANDLE outputhandle; ///< Holds handle to the Win32 console.
#endif
	unsigned char inputbufferposition[2]; ///< Holds current cursor position in the input buffer ([0] - Line index, [1] - Character index).
	unsigned char pagesize; ///< How many lines will be shown on one page (excluding caption and input line).
	unsigned short screenposition; ///< Holds index of the first line in the output buffer that will be shown on the current page.

	/// \brief Clears the screen.
	/// \return No return.
	void ClearScreen(void);

	/// \brief Clears the input line.
	/// \return No return.
	void ClearInputLine(void);

	/// \brief Sets the cursor position on the console screen.
	/// \param[in] x X coordinate.
	/// \param[in] y Y coordinate.
	/// \return No return.
	void SetCursorPosition(const unsigned char x, const unsigned char y);

	/// \brief Gets the y coordinate of the input line on the console screen.
	/// \return Y coordinate of the input line on the console screen.
	unsigned char GetInputLineScreenPosition(void);

	/// \brief Sets the cursor position to where user should see it.
	/// \return No return.
	void SetFinalCursorPosition(void);

	/// \brief Prints caption.
	/// \return No return.
	void PrintCaption(void);

	/// \brief Prints the output page.
	/// \return No return.
	void PrintOutputPage(void);

	/// \brief Prints the input line.
	/// \return No return.
	void PrintInputLine(void);

	/// \brief Performs full update of screen.
	/// \return No return.
	void UpdateScreen(void);

	/// \brief Goes up one page.
	/// \return No return.
	void GoOnePageUp(void);

	/// \brief Goes down one page.
	/// \return No return.
	void GoOnePageDown(void);

	/// \brief Goes one entry back in the input history.
	/// \return No return.
	void InputHistoryBack(void);

	/// \brief Goes one entry forward in the input history.
	/// \return No return.
	void InputHistoryForward(void);

	/// \brief Appends string to the output buffer.
	/// \param[in] string String to append.
	/// \return No return.
	void WriteToOutputBuffer(const conchar *string);

	/// \brief Writes prepared string to the output buffer.
	/// \param[in] string String to write.
	/// \return No return.
	void AppendToOutputBuffer(const conchar *string);

	/// \brief Replaces current input with one from history.
	/// \return No return.
	void FillInputBufferFromHistory(void);

	/// \brief Adds one character to the current position in the input buffer.
	/// \param[in] ch Character to add.
	/// \return No return.
	void AddCharToInputBuffer(const int ch);

	/// \brief Backspaces from the current position in the input buffer.
	/// \return No return.
	void BackspaceCharInInputBuffer(void);

	/// \brief Moves cursor left in the input buffer.
	/// \return No return.
	void MoveCursorLeft(void);

	/// \brief Moves cursor right in the input buffer.
	/// \return No return.
	void MoveCursorRight(void);

	/// \brief Deletes a character from the current position in the input buffer.
	/// \return No return.
	void DeleteCharInInputBuffer(void);

	/// \brief Accepts inputted line.
	/// \return No return.
	void AcceptUserInput(void);

	/// \brief Appends current string to the input buffer.
	/// \return No return.
	void WriteToInputBuffer(void);
};
