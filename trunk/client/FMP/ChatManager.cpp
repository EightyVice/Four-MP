#include <windows.h>
#include <stdio.h>

#include "ChatManager.h"
#include "../../Shared/Network/Limits.h"
#include "../../Shared/Console/common.h"
#include "../../Shared/logging/log.h"
#include "d3d9/d3d9int.h"
#include "../Shared/ClientCore.h"
#include "../Shared/NetworkManager.h"

extern ClientCore client;
extern NetworkManager nm;

ChatManager::ChatManager(void)
{
	maxoutputbuffersize = 64;
	outputbuffer = NULL;
	outputbuffersize = 0;
	inputbuffer = (wchar_t *)calloc(1, sizeof(wchar_t));
	inputbuffersize = 1;
	cursorposition = 0;
	font = NULL;
}

ChatManager::~ChatManager(void)
{
	for (unsigned char i = 0; i < outputbuffersize; i++)
	{
		free(outputbuffer[i]);
	}
	free(outputbuffer);
	free(inputbuffer);
}

void ChatManager::AddCharacter(const wchar_t character)
{
	if (character < 32)
	{
		return;
	}
	if (inputbuffersize == MAX_CHAT_MESSAGE_LENGTH)
	{
		return;
	}
	if (!ResizeBuffer<wchar_t *>(inputbuffer, inputbuffersize + 1))
	{
		return;
	}
	inputbuffer[cursorposition] = character;
	cursorposition++;
	inputbuffer[inputbuffersize] = L'\0';
	inputbuffersize++;
}

void ChatManager::Backspace(void)
{
	if (cursorposition == 0)
	{
		return;
	}
	ResizeBuffer<wchar_t *>(inputbuffer, inputbuffersize - 1);
	inputbuffer[inputbuffersize-2] = L'\0';
	cursorposition--;
	inputbuffersize--;
}

void ChatManager::AddChatMessage(const wchar_t *message)
{
	if (message == NULL)
	{
		return;
	}
	size_t length = wcslen(message) + 1;
	wchar_t *tempmessage;
	if (length > MAX_CHAT_MESSAGE_LENGTH)
	{
		tempmessage = (wchar_t *)calloc(MAX_CHAT_MESSAGE_LENGTH, sizeof(wchar_t));
		wcsncpy(tempmessage, message, MAX_CHAT_MESSAGE_LENGTH);
		tempmessage[MAX_CHAT_MESSAGE_LENGTH-1] = L'\0';
		length = MAX_CHAT_MESSAGE_LENGTH;
	}
	else
	{
		tempmessage = (wchar_t *)calloc(length, sizeof(wchar_t));
		wcscpy(tempmessage, message);
	}
	Log::Void(tempmessage);
	if (outputbuffersize < maxoutputbuffersize)
	{
		if (!ResizeBuffer<wchar_t **>(outputbuffer, outputbuffersize + 1))
		{
			free(tempmessage);
			return;
		}
		outputbuffer[outputbuffersize] = (wchar_t *)calloc(length, sizeof(wchar_t));
		wcscpy(outputbuffer[outputbuffersize], tempmessage);
		outputbuffersize++;
		free(tempmessage);
		return;
	}
	wchar_t *tempstring = outputbuffer[0];
	for(unsigned char i = 0; i < (outputbuffersize - 1); i++)
	{
		outputbuffer[i] = outputbuffer[i+1];
	}
	outputbuffer[outputbuffersize-1] = tempstring;
	tempstring = NULL;
	if (!ResizeBuffer<wchar_t *>(outputbuffer[outputbuffersize-1], length))
	{
		free(tempmessage);
		return;
	}
	wcscpy(outputbuffer[outputbuffersize-1], tempmessage);
	free(tempmessage);
	return;
}

void ChatManager::SendChatMessage(void)
{
	if (inputbuffer == NULL)
	{
		return;
	}
	if(inputbuffersize == 1)
	{
		return;
	}
	nm.SendPlayerChat(inputbuffer);
	ResizeBuffer<wchar_t *>(inputbuffer, 1);
	inputbuffer[0] = L'\0';
	cursorposition = 0;
	inputbuffersize = 1;
}

void ChatManager::CreateChatFont(IDirect3DDevice9 *device)
{
	CreateD3DXFont(device, &font, L"Arial", 10, 0, 0);
}

void ChatManager::OnLostDevice(void)
{
	if (font != NULL)
	{
		font->OnLostDevice();
	}
}

void ChatManager::OnResetDevice(void)
{
	if (font != NULL)
	{
		font->OnResetDevice();
	}
}

void ChatManager::Render(void)
{
	RECT rc = {2, 2, 800, 600};
	unsigned char i;
	if (outputbuffersize > 8)
	{
		i = outputbuffersize - 8;
	}
	else
	{
		i = 0;
	}
	for(; i < outputbuffersize; i++)
	{
		font->DrawText(0, outputbuffer[i], -1, &rc, DT_TOP|DT_LEFT, D3DCOLOR_XRGB(255, 255, 0));
		rc.top += 11;
	}
	if (client.GetInputState() != InputStateChat)
	{
		return;
	}
	rc.top += 2;
	font->DrawText(0, L">", -1, &rc, DT_TOP|DT_LEFT, D3DCOLOR_XRGB(255, 255, 0));
	rc.left += 10;
	font->DrawText(0, inputbuffer, -1, &rc, DT_TOP|DT_LEFT, D3DCOLOR_XRGB(255, 255, 0));
}