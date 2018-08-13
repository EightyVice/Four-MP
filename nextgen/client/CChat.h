#pragma once
#include "./hook/CD3DManager.h"
#include "CFont.h"
#include <d3dx9.h>

#define MAX_CHAT_MESSAGE_LENGTH 0x200

class CChat : public CD3DManager
{
public:
	CChat(const int iMaxMessages = 16, const int iMaxHistory = 64, const int iMaxMyHistory = 16, const int iFontSize = 10, 
		const wchar_t * pszFontName = L"Arial", const bool bFontBold = false, const bool bFontItalic = false);
	~CChat();

	void SetChatColors(D3DCOLOR dwFrameColor = 0xAA000000, D3DCOLOR dwScrollColor = 0xFFFFFFFF, 
		D3DCOLOR dwScrollBackgroundColor = 0xBB000000, D3DCOLOR dwEnterBackgroundColor = 0xDD000000, D3DCOLOR dwEnterTextColor = 0xFFFFDD00);
	void SetChatTransform(float fPosX = 10.0f, float fPosY = 10.0f);

	void OnCreateDevice(IDirect3DDevice9 *, HWND);
	void OnLostDevice();
	void OnResetDevice();
	void OnDraw();
	void OnBeginDraw();
	void OnRelease();

	void AddMessage(wchar_t *);
	void DeleteMessage(const int index);
	void Clear();

	void ChangeEnterMessageState();
	void ChangeChatState();

	bool IsMessageEnterActive();
	bool IsMessageNotNull();

	void AddCharToMessage(wchar_t sChar);
	void DeleteCharFromMessage();
	void GetMyMessage(wchar_t * pszMsg);

	void ScrollDownHistory();
	void ScrollUpHistory();
	void MoveCursorLeft();
	void MoveCursorRight();

	bool ScrollDown();
	bool ScrollUp();
	void ScrollEnd();

private:
	CFont * m_pFont;
	ID3DXSprite * m_pSprite;
	ID3DXLine * m_pLine;

	CRITICAL_SECTION critSect;

	DWORD m_dwWidth;
	DWORD m_dwHeight;

	struct MESSAGE
	{
		MESSAGE(wchar_t * pszMsg, D3DCOLOR Color) 
		{ 
			this->msg = new wchar_t[MAX_CHAT_MESSAGE_LENGTH];
			memset(this->msg, 0, MAX_CHAT_MESSAGE_LENGTH * sizeof(wchar_t));

			int len = wcslen(pszMsg);
			for(int i = 0; i < len; i++)
			{
				if(pszMsg[i] < 32) break;
				this->msg[i] = pszMsg[i];
			}

			this->color = Color; 
			this->next = NULL;
		}
		~MESSAGE() 
		{ 
			if(msg) delete msg; 
			if(next) delete next; 
		}

		wchar_t *msg;
		D3DCOLOR color;
		MESSAGE * next;
	};

	MESSAGE ** m_pMessages;
	wchar_t ** m_pMyMsgHistory;
	wchar_t * m_pMyMsg;

	int m_iMaxMessages;
	int m_iMaxHistory;
	int m_iMaxMyHistory;
	int m_iMessagesCount;

	int m_iFontSize;
	const wchar_t *m_pszFontName;
	bool m_bFontBold;
	bool m_bFontItalic;

	bool m_bUserScroll;
	int m_iScrollPos;
	DWORD m_dwCursorPos;
	int m_iHistoryPos;

	float m_iFrameWidth;
	float m_iFrameHeight;

	D3DCOLOR m_dwFrameColor;
	D3DCOLOR m_dwScrollColor;
	D3DCOLOR m_dwScrollBackgroundColor;
	D3DCOLOR m_dwEnterBackgroundColor;
	D3DCOLOR m_dwEnterTextColor;

	float m_fPosX;
	float m_fPosY;

	bool m_bEnterMessage;
	char m_bChatShow;
};