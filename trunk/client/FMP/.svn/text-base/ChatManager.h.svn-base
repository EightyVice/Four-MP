#pragma once

#include "d3d9/d3d9hook.h"

class ChatManager
{
public:
	ChatManager(void);
	~ChatManager(void);
	void AddCharacter(const wchar_t character);
	void Backspace(void);
	void AddChatMessage(const wchar_t *message);
	void SendChatMessage(void);
	void CreateChatFont(IDirect3DDevice9 *device);
	void OnLostDevice(void);
	void OnResetDevice(void);
	void Render(void);
private:
	unsigned char maxoutputbuffersize;
	unsigned char outputbuffersize;
	wchar_t **outputbuffer;
	unsigned char inputbuffersize;
	wchar_t *inputbuffer;
	unsigned char cursorposition;
	LPD3DXFONT font;
};