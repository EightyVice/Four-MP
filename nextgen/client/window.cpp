#include <windows.h>
#include "window.h"
#include "./hook/CGameHook.h"
#include "CChat.h"
#include "log/log.h"

extern CGameHook *pGameHook;
extern CChat * pChat;

LRESULT CALLBACK DefWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_F7:
			{
				pChat->ChangeChatState();
			} break;
			case VK_F6:
			{
				pChat->ChangeEnterMessageState();
			} break;
			case VK_RETURN:
			{
				if(pChat->IsMessageEnterActive() && pChat->IsMessageNotNull())
				{
					pChat->ChangeEnterMessageState();
					wchar_t msg[MAX_CHAT_MESSAGE_LENGTH];
					wcscpy_s(msg, MAX_CHAT_MESSAGE_LENGTH, L"   WNeZRoS:    ");
					msg[0] = 1;
					*(DWORD*)(msg + 1) = 0xFFFF0000;
					msg[11] = 1;
					*(DWORD*)(msg + 12) = 0xFFFFFFFF;
					pChat->GetMyMessage(msg + 14);
					pChat->AddMessage(msg);
				}
			} break;
			case VK_BACK:
			{
				pChat->DeleteCharFromMessage();
			} break;
			case VK_LEFT:
			{
				pChat->MoveCursorLeft();
			} break;
			case VK_RIGHT:
			{
				pChat->MoveCursorRight();
			} break;
			case VK_UP:
			{
				pChat->ScrollUpHistory();
			} break;
			case VK_DOWN:
			{
				pChat->ScrollDownHistory();
			} break;
			case VK_PRIOR:
			{
				pChat->ScrollUp();
			} break;
			case VK_NEXT:
			{
				pChat->ScrollDown();
			} break;
			case VK_END:
			{
				pChat->ScrollEnd();
			} break;
			case VK_F1:
			{
				Log::Info("F1");
				wchar_t msg[64];
				wcscpy(msg, L"   W   N   e   Z   R   o   S   :    Hello");
				msg[0] = msg[4] = msg[8] = msg[12] = msg[16] = msg[20] = msg[24] = msg[28] = msg[32] = 1;
				*(DWORD*)(msg+1) = 0xFFFF0000;
				*(DWORD*)(msg + 5) = 0xFF00FF00;
				*(DWORD*)(msg + 9) = 0xFF0000FF;
				*(DWORD*)(msg + 13) = 0xFFFFFF00;
				*(DWORD*)(msg + 17) = 0xFF00FFFF;
				*(DWORD*)(msg + 21) = 0xFFFF00FF;
				*(DWORD*)(msg + 25) = 0xFFFFFFFF;
				*(DWORD*)(msg + 29) = 0xFF000000;
				*(DWORD*)(msg + 33) = 0xFFFFFFFF;
				pChat->AddMessage(msg);
			} break;
			case VK_F2:
			{
				Log::Info("F2");
				wchar_t msg[64];
				wcscpy(msg, L"   DEM@N777:    Hello");
				msg[0] = 1;
				*(DWORD*)(msg+1) = 0xFF0000FF;
				msg[13] = 1;
				*(DWORD*)(msg + 14) = 0xFFFFDD00;
				pChat->AddMessage(msg);
			} break;
			case VK_F3:
			{
				Log::Info("F3");
				wchar_t msg[64];
				wcscpy(msg, L"   WNeZRoS:    How are you");
				msg[0] = 1;
				*(DWORD*)(msg+1) = 0xFFFF0000;
				msg[12] = 1;
				*(DWORD*)(msg + 13) = 0xFFFFFFFF;
				pChat->AddMessage(msg);
			} break;
			default:
				{
					BYTE bKeys[256] = {0};
					GetKeyboardState(bKeys);

					wchar_t wKey = 0;
					ToUnicode(wParam, HIWORD(lParam) & 0xFF, bKeys, &wKey, 1, 0);
					pChat->AddCharToMessage(wKey);
				} break;
			}
		} break;
	}

	return pGameHook->CallOriginalWindowProc(hWnd, Msg, wParam, lParam);
}