#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct ServerInfo;
class CGUI;

class FMPGUI
{
	CGUI *m_Gui;
	bool g_Mouse[3];
	bool GuiReady;
	DWORD s_iWidth, s_iHeight;
	bool logged;

	friend class ConsoleWindow;
public:
	FMPGUI();
	~FMPGUI();

	void Release();

	void Load(IDirect3DDevice9 * g_pDevice);
	void HandleMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	void MoveMouse(int x, int y);
	void Draw();
	void Resize(int width, int height);

	void OnResetDevice();
	void OnLostDevice();

	bool IsLogged();
	void Logged();

	void UpdateServer(ServerInfo *msi);
	void Message(wchar_t *data);

	DWORD GetWidth();
	DWORD GetHeight();
};

extern CRITICAL_SECTION cs_gui;