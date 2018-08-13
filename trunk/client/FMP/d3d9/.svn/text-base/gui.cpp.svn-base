#include <vector>
#include <windows.h>
#include <math.h>

#define LIB_INCLUDE
#include "../../GUI/CGUI.h"

#include "gui.h"
#include "../../../Shared/logging/log.h"
#include "../../Shared/ClientCore.h"
#include "../ConsoleWindow.h"
#include "../Hook/classes.h"
#include "../../Shared/NetworkManager.h"
#include "../masterserver.h"

extern ClientCore client;
extern ConsoleWindow conwindow;
extern NetworkManager nm;

CRITICAL_SECTION cs_gui;

// Windows
CWindow * fServBrowser;
CWindow * fChat;
CWindow * fOption;
CWindow * fUserRegister;
CWindow * fUserLogin;
CWindow * fInfo;
CWindow * fEnterNick;
// Chat elements
CTextBox * cc_tChat;
CEditBox * cc_tEnter;
CButton * cc_bEnter;
// Server Browser elemenets
CListView *sbServList, *sbPlayerList;
CButton *sbTab[4];
CEditBox *sbEnterIP, *sbEnterPort;
CButton *sbConnect, *sbRefresh, *sbAddToFav;
CDropDown *sbFltPing; 
CCheckBox *sbFltNotFull, *sbFltNoPassword, *sbFltNotEmpty;
CEditBox *sbFltLocation, *sbFltMode;
// Register elements
CEditBox *urLogin, *urPass, *urConfirm, *urEmail, *urNick;
CText *urLoginText, *urPassText, *urConfirmText, *urEmailText, *urNickText, *urInfoText;
CButton *urSendReg, *urCancelReg;
// Login elements
CText *upLoginInfo, *upStrLogin, *upStrPass;
CEditBox *upLogin, *upPassword;
CButton *upSendLogin, *upShowRegister;
CCheckBox *upRemeberMe;
// Enter nick
CEditBox * enNick; 
CButton * enOK;

std::vector<ServerInfo*> server_list;
std::vector<ServerInfo*> server_list_fav;

int tab = 3;

MasterServer fmpms;
extern FMPHook HOOK;
extern FMPGUI Gui;

namespace CALLBACKS
{
	void Refresh( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		Log::Debug(L"CALLBACKS::Refresh called");

		sbServList->Clear();

		if(tab == 0 || tab == 2)
		{
			fmpms.ClearServerList();
			server_list.clear();

			bool r = fmpms.QueryServerList(0, tab == 2, sbFltNotEmpty->GetChecked(), sbFltNotFull->GetChecked(), 
				sbFltNoPassword->GetChecked(),	0, 0, sbFltMode->GetString().size()>0?sbFltMode->GetString().c_str():0, sbFltLocation->GetString().size()?sbFltLocation->GetString().c_str():0);

			if(!r) { fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(L"Load server list failed"); fInfo->SetVisible(1); }
			else
			{
				char *tmp = new char[128];
				ServerInfo *msi;
				for(int i = 0; i < fmpms.GetNumServers(); i++)
				{
					msi = fmpms.GetServerInfo(i);
					if(!msi) continue;
					nm.Ping(msi->ip, msi->port);
				}
			}
		}
		else if(tab == 3)
		{
			for(int i = 0; i < (int)server_list_fav.size(); i++)
			{
				if(server_list_fav[i])
				{
					Gui.UpdateServer(server_list_fav[i]);
					nm.Ping(server_list_fav[i]->ip, server_list_fav[i]->port); 
				}
			}
		}
		else if(tab == 1)
		{
			nm.Ping("255.255.255.255");
		}
		Log::Debug(L"CALLBACKS::Refresh complete");
	}
	void GetLAN( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		Log::Debug(L"CALLBACKS::GetLAN called");

		sbServList->Clear();
		server_list.clear();

		sbTab[tab]->SetEnabled(1);
		tab = 1;
		sbTab[tab]->SetEnabled(0);

		nm.Ping("255.255.255.255");

		Log::Debug(L"CALLBACKS::GetLAN complete");
	}
	void GetInet( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		if(!Gui.IsLogged()) 
		{
			fUserLogin->SetVisible(1);
			fServBrowser->SetVisible(0);
			return;
		}

		Log::Debug(L"CALLBACKS::GetInet called");

		sbTab[tab]->SetEnabled(1);
		tab = 0;
		sbTab[tab]->SetEnabled(0);

		if(fmpms.GetNumServers() > 0)
		{
			char tmp[64];
			ServerInfo *msi;
			sbServList->Clear();
			server_list.clear();

			for(int i = 0; i < fmpms.GetNumServers(); i++)
			{
				msi = fmpms.GetServerInfo(i);
				if(!msi) continue;
				nm.Ping(msi->ip, msi->port); 
			}
		}
		Log::Debug(L"CALLBACKS::GetInet complete");
	}
	void GetVIP( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		if(!Gui.IsLogged()) 
		{
			fUserLogin->SetVisible(1);
			fServBrowser->SetVisible(0);
			return;
		}

		Log::Debug(L"CALLBACKS::GetVIP called");

		sbTab[tab]->SetEnabled(1);
		tab = 2;
		sbTab[tab]->SetEnabled(0);

		if(fmpms.GetNumServers() > 0)
		{
			char tmp[64];
			ServerInfo *msi;
			sbServList->Clear();
			server_list.clear();

			for(int i = 0; i < fmpms.GetNumServers(); i++)
			{
				msi = fmpms.GetServerInfo(i);
				if(!msi) continue;
				if(msi->vip == 1)
					nm.Ping(msi->ip, msi->port); 
			}
		}
		Log::Debug(L"CALLBACKS::GetVIP complete");
	}
	void GetFavourite( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		/*if(!Gui.IsLogged()) 
		{
			fUserLogin->SetVisible(1);
			fServBrowser->SetVisible(0);
			return;
		}*/
		Log::Debug(L"CALLBACKS::GetFavourite called");

		sbServList->Clear();
		server_list.clear();

		sbTab[tab]->SetEnabled(1);
		tab = 3;
		sbTab[tab]->SetEnabled(0);

		if(server_list_fav.size() == 0) return;

		for(int i = 0; i < (int)server_list_fav.size(); i++)
		{
			if(server_list_fav[i])
			{
				Gui.UpdateServer(server_list_fav[i]);
				nm.Ping(server_list_fav[i]->ip, server_list_fav[i]->port); 
			}
		}

		Log::Debug(L"CALLBACKS::GetFavourite complete");
	}
	void Login( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK && msg != END) return;
		if((pElement == upLogin || pElement == upPassword) && msg == CLICK) return;

		Log::Debug(L"CALLBACKS::Login called");

		std::wstring login = upLogin->GetString();
		std::wstring pass = upPassword->GetString();
		if(upRemeberMe->GetChecked())
		{
			wchar_t path[MAX_PATH];
			client.GetPath(L"fmp.ini", path);
			WritePrivateProfileString(L"FOURMP", L"Login", login.c_str(), path);
			WritePrivateProfileString(L"FOURMP", L"Password", pass.c_str(), path);
		}

		if(login.length() < 3 || pass.length() < 6) return;

		bool r = fmpms.QueryUserLogin(login.c_str(), pass.c_str());
		if(r) 
		{
			fUserLogin->SetVisible(0);
			fServBrowser->SetVisible(1);
			Gui.Logged();
			
			client.SetFMPID(fmpms.GetUserId());
			client.SetName(fmpms.GetUserName());
			client.SetSessionKey(fmpms.GetUserSession());
		}
		else Gui.Message(fmpms.GetError());

		Log::Debug(L"CALLBACKS::Login complete");
	}
	void ShowRegister( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		Log::Debug(L"CALLBACKS::ShowRegister called");

		fUserRegister->SetVisible(1);
		fUserLogin->SetVisible(0);
		Log::Debug(L"CALLBACKS::ShowRegister complete");
	}
	void HideRegister( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		Log::Debug(L"CALLBACKS::HideRegister called");

		fUserRegister->SetVisible(0);
		fUserLogin->SetVisible(1);
		Log::Debug(L"CALLBACKS::HideRegister complete");
	}
	void Register( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		Log::Debug(L"CALLBACKS::Register called");

		std::wstring login = urLogin->GetString();
		std::wstring pass = urPass->GetString();
		std::wstring confirm = urConfirm->GetString();
		std::wstring email = urEmail->GetString();
		std::wstring nick = urNick->GetString();

		if(wcscmp(pass.c_str(), confirm.c_str()) == 0)
		{
			bool r = fmpms.QueryUserRegister(login.c_str(), nick.c_str(), pass.c_str(), email.c_str());
			if(!r) fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(L"Registration failed");
			else
			{
				fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(L"Registration ok");
				fUserRegister->SetVisible(0);
				fUserLogin->SetVisible(1);
			}
		}
		else
			fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(L"Password != confirm password");

		fInfo->SetVisible(1);
		Log::Debug(L"CALLBACKS::Register complete");
	}
	void InfoOK( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;

		Log::Debug(L"CALLBACKS::InfoOK called");
		fInfo->SetVisible(0);
		Log::Debug(L"CALLBACKS::IfoOK complete");
	}
	void Logout( CElement * pElement, CMSG msg, int param )
	{
		if(msg != CLICK) return;
		Log::Debug(L"CALLBACKS::Logout called");
		
		bool r = fmpms.QueryUserLogout();
		if(!r) fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(L"Logout failed");
		else 
		{
			fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(L"Logout ok");
			fUserLogin->SetVisible(1);
		}
		fInfo->SetVisible(1);
		Log::Debug(L"CALLBACKS::Logout complete");
	}
	void Chat(CElement *pElement, CMSG msg, int Param)
	{
		if(msg != SELECT && msg != END && msg != CLICK) return;
		Log::Debug(L"CALLBACKS::Chat called");
		//Log::Debug(L"Chat callback");
		if(pElement == cc_tChat && msg == SELECT)
		{
			Log::Debug(L"CALLBACKS::Chat >> Select");
			// Select chat string
		}
		else if((pElement == cc_tEnter && msg == END) || (pElement == cc_bEnter && msg == CLICK))
		{
			// Send message
			Log::Debug(L"CALLBACKS::Chat >> Add");
			cc_tChat->AddString(cc_tEnter->GetString());
			Log::Debug(L"CALLBACKS::Chat >> Add end");
		}
		//Log::Debug(L"Chat callback end");
		Log::Debug(L"CALLBACKS::Chat complete");
	}
	void ServerList(CElement *pElement, CMSG msg, int Param)
	{
	}
	void FilterPing(CElement *pElement, CMSG msg, int Param)
	{
		if(msg != CLICK) return;

	}
	void Connect(CElement *pElement, CMSG msg, int Param)
	{
		if(msg != CLICK) return;

		Log::Debug(L"CALLBACKS::Connect called");
		if(!sbServList) return;

		int sel = sbServList->GetSelected();
		Log::Debug(L"Selected %d (%d/%d)", sel, sbServList->GetSize(), server_list.size());
		if(sel >= 0)
		{
			if(!Gui.IsLogged())
			{
				fEnterNick->SetVisible(1);
				return;
			}
			ServerInfo *tmp_msi = server_list.at(sel);
			Log::Debug(L"FROM LIST - Server: [%s:%d]", tmp_msi->ip, tmp_msi->port);
			nm.ConnectToServer(tmp_msi->ip, tmp_msi->port);
		}
		Log::Debug(L"CALLBACKS::Connect complete");
	}
	void EnterNick(CElement *pElement, CMSG msg, int Param)
	{
		if(msg != CLICK && msg != END) return;

		std::wstring n = enNick->GetString();
		if(n.length() < 4) 
		{
			if(n.length() > 0)
				Gui.Message(L"Small nick");
			return;
		}
		
		client.SetName(n.c_str());
		fEnterNick->SetVisible(0);

		if(!sbServList) return;

		int sel = sbServList->GetSelected();
		if(sel >= 0)
		{
			ServerInfo *tmp_msi = server_list.at(sel);
			Log::Debug(L"FROM LIST - Server: [%s:%d]", tmp_msi->ip, tmp_msi->port);
			nm.ConnectToServer(tmp_msi->ip, tmp_msi->port);
		}
	}
	void ServerBrowser(CElement *pElement, CMSG msg, int Param)
	{
		if(msg == END)
		{
			if(client.GetGameState() > GameStateConnecting)
			{
				if(fChat->IsVisible()) fChat->SetVisible(0);

				if(!conwindow.IsVisible()) 
				{
					client.SetInputState(InputStateGame);
					HOOK.InputFreeze(0);
				}
			}
			else if(!Gui.IsLogged())
			{
				fUserLogin->SetVisible(1);
				fServBrowser->SetVisible(0);
			}
		}
	}
	void UserLogin(CElement *pElement, CMSG msg, int Param)
	{
		if(msg == END)
		{
			fUserLogin->SetVisible(0);
			fServBrowser->SetVisible(1);
			sbTab[1]->SetEnabled(0);
			sbTab[tab]->SetEnabled(1);
			tab = 1;
		}
	}
	void AddFav(CElement *pElement, CMSG msg, int Param)
	{
		if(msg != CLICK) return;

		/*if(!Gui.IsLogged()) 
		{
			fUserLogin->SetVisible(1);
			fServBrowser->SetVisible(0);
			return;
		}*/

		if(sbEnterIP->GetString().length() > 0 && sbEnterPort->GetString().length() > 0)
		{
			// Add entered server
			ServerInfo * tmp_msi = new ServerInfo;
			memset(tmp_msi, 0, sizeof(ServerInfo));
			wcstombs(tmp_msi->ip, sbEnterIP->GetString().c_str(), 64);
			tmp_msi->port = _wtoi(sbEnterPort->GetString().c_str());
			swprintf_s(tmp_msi->name, 128, L"%s:%d", tmp_msi->ip, tmp_msi->port);

			if(tab == 3)
			{
				Gui.UpdateServer(tmp_msi);
				Log::Debug(L"Server: %s:%d", tmp_msi->ip, tmp_msi->port);
				nm.Ping(tmp_msi->ip, tmp_msi->port);
			}
			server_list_fav.push_back(tmp_msi);

			sbEnterIP->SetString(L"");
			sbEnterPort->SetString(L"");
		}
	}
};

FMPGUI::FMPGUI()
{
	Log::Debug(L"FMPGUI::FMPGUI called");
	g_Mouse[0] = 0;
	g_Mouse[1] = 0;
	g_Mouse[2] = 0;
	GuiReady = 0;
	s_iWidth = 800;
	s_iHeight = 600;

	InitializeCriticalSection(&cs_gui);
	Log::Debug(L"FMPGUI::FMPGUI completed");
}

FMPGUI::~FMPGUI()
{
	Log::Debug(L"FMPGUI::~FMPGUI called");
	Release();
	Log::Debug(L"FMPGUI::~FMPGUI completed");
}

void FMPGUI::Release()
{
	if(!GuiReady) return;
	Log::Debug(L"FMPGUI::Release called");
	GuiReady = 0;
	EnterCriticalSection(&cs_gui);
	SAFE_DELETE(m_Gui);
	LeaveCriticalSection(&cs_gui);
	DeleteCriticalSection(&cs_gui);
	Log::Debug(L"FMPGUI::Release completed");
}

void FMPGUI::Load(IDirect3DDevice9 * g_pDevice)
{
	if(GuiReady) return;

	EnterCriticalSection(&cs_gui);
	Log::Debug(L"FMPGUI::Load called");
	fmpms.Load();
	Log::Debug(L"FMPGUI::Load >> Master Server");

	D3DVIEWPORT9 vp;
	g_pDevice->GetViewport(&vp);
	s_iWidth = vp.Width;
	s_iHeight = vp.Height;

	m_Gui = new CGUI( g_pDevice );
	m_Gui->LoadInterfaceFromFile( L"FMP\\GUITheme.xml" );

	Log::Debug(L"FMPGUI::Load >> Load Font");
	m_Gui->LoadFont(10, L"Arial");
	m_Gui->SetFontColors(0, 0, 0, 0, 255); // <!--black-->
	m_Gui->SetFontColors(1, 255, 255, 255, 255); // <!--white-->
	m_Gui->SetFontColors(2, 0, 0, 255, 255); // <!--blue-->
	m_Gui->SetFontColors(3, 0, 255, 0, 255); // <!--green-->
	m_Gui->SetFontColors(4, 255, 0, 0, 255); // <!--red-->
	m_Gui->SetFontColors(5, 255, 0, 128, 255); // <!--pink-->
	m_Gui->SetFontColors(6, 255, 0, 255, 255); // <!--purple-->
	m_Gui->SetFontColors(7, 255, 150, 0, 255); // <!--orange-->
	m_Gui->SetFontColors(8, 255, 255, 0, 255); // <!--yellow-->
	m_Gui->SetFontColors(9, 0, 0, 128, 255); // <!--dark blue-->

	Log::Debug(L"FMPGUI::Load >> Create server browser");
	// Create Servers Brouser
	fServBrowser = new CWindow(m_Gui, s_iWidth/2-375, s_iHeight/2-250, 750, 500, L"SERVER BROWSER", L"SERVER_BROWSER", CALLBACKS::ServerBrowser);
	Log::Debug(L"FMPGUI::Load >> Server browser window has been created.");

	int ServerWidth[6] = {16, 210, 60, 60, 100, 100};
	sbServList = new CListView(m_Gui, 0, 29, ServerWidth, 350, 6, NULL, L"SERVER_LIST", CALLBACKS::ServerList);
	sbServList->SetColumnImage(0, L"FMPGUI/Pass.png", L"FMPGUI/noPass.png", L"FMPGUI/Pass.png", 16, 16);

	sbServList->SetTitle(L"P");
	sbServList->SetTitle(L"Server Name");
	sbServList->SetTitle(L"Slots");
	sbServList->SetTitle(L"Ping");
	sbServList->SetTitle(L"Mode");
	sbServList->SetTitle(L"Location");

	int PlayerWidth[2] = {128, 76};
	sbPlayerList = new CListView(m_Gui, 546, 49, PlayerWidth, 200, 2, NULL, L"PLAYER_LIST");

	sbPlayerList->SetTitle(L"Player");
	sbPlayerList->SetTitle(L"Score");

	sbTab[0] = new CButton(m_Gui, 20, 0, 200, 0, L"Internet", L"TAB_INTERNET", CALLBACKS::GetInet);
	sbTab[1] = new CButton(m_Gui, 169, 0, 200, 0, L"LAN", L"TAB_LAN", CALLBACKS::GetLAN);
	sbTab[2] = new CButton(m_Gui, 318, 0, 200, 0, L"VIP", L"TAB_VIP", CALLBACKS::GetVIP);
	sbTab[3] = new CButton(m_Gui, 467, 0, 200, 0, L"Favourite", L"TAB_FAVOURITE", CALLBACKS::GetFavourite);

	sbEnterIP = new CEditBox(m_Gui, 600, 290, 120, 0, L"127.0.0.1", L"EDIT_IP");
	sbEnterPort = new CEditBox(m_Gui, 625, 330, 60, 0, L"7777", L"EDIT_PORT");

	CText *sbTextIP = new CText(m_Gui, 560, 295, 100, 20, L"IP", L"TEXT_IP", NULL);
	CText *sbTextPort = new CText(m_Gui, 560, 335, 100, 20, L"Port", L"TEXT_PORT", NULL);

	sbConnect = new CButton(m_Gui, 560, 380, 80, 0, L"Connect", L"MAN_CONNECT", CALLBACKS::Connect);
	sbRefresh = new CButton(m_Gui, 660, 380, 80, 0, L"Refresh", L"MAN_REFRESH", CALLBACKS::Refresh);
	sbAddToFav = new CButton(m_Gui, 600, 405, 120, 0, L"Add to favourites", L"MAN_ADDFAV", CALLBACKS::AddFav);

	sbFltPing = new CDropDown(m_Gui, 150, 380, 80, 20, L"Ping", L"FILTER_PING", CALLBACKS::FilterPing);
	sbFltNotFull = new CCheckBox(m_Gui, 150, 410, 0, 0, 0, L"", L"FILTER_NOT_FULL");
	sbFltLocation = new CEditBox(m_Gui, 305, 380, 80, 20, L"", L"FILTER_LOCATION");
	sbFltMode = new CEditBox(m_Gui, 305, 410, 80, 20, L"", L"FILTER_MODE");
	sbFltNotEmpty = new CCheckBox(m_Gui, 480, 385, 0, 0, 0, L"", L"FILTER_NOT_EMPTY");
	sbFltNoPassword = new CCheckBox(m_Gui, 480, 410, 0, 0, 1, L"", L"FILTER_NO_PASSWORD");

	sbFltPing->AddElement(L"< 50", L"50");
	sbFltPing->AddElement(L"50 - 100", L"50100");
	sbFltPing->AddElement(L"100 - 200", L"100200");
	sbFltPing->AddElement(L"200 - 500", L"200500");
	sbFltPing->AddElement(L"> 500", L"500");

	fServBrowser->AddElement(sbServList);
	fServBrowser->AddElement(sbPlayerList);
	fServBrowser->AddElement(sbTab[0]);
	fServBrowser->AddElement(sbTab[1]);
	fServBrowser->AddElement(sbTab[2]);
	fServBrowser->AddElement(sbTab[3]);
	fServBrowser->AddElement(sbEnterPort);
	fServBrowser->AddElement(sbEnterIP);
	fServBrowser->AddElement(sbTextIP);
	fServBrowser->AddElement(sbTextPort);
	fServBrowser->AddElement(sbConnect);
	fServBrowser->AddElement(sbRefresh);
	fServBrowser->AddElement(sbAddToFav);
	fServBrowser->AddElement(sbFltPing);
	fServBrowser->AddElement(sbFltLocation);
	fServBrowser->AddElement(sbFltMode);
	fServBrowser->AddElement(sbFltNotFull);
	fServBrowser->AddElement(sbFltNotEmpty);
	fServBrowser->AddElement(sbFltNoPassword);
	fServBrowser->SetVisible(0);
	// Create Chat
	Log::Debug(L"FMPGUI::Load >> Create chat");
	fChat = new CWindow(m_Gui, 10, 10, 300, 400, L"FOUR-MP CHAT");
	cc_tChat = new CTextBox(m_Gui, 10, 10, 280, 320, NULL, NULL, CALLBACKS::Chat);
	cc_tEnter = new CEditBox(m_Gui, 10, 330, 220, 0, NULL, NULL, CALLBACKS::Chat);
	cc_bEnter = new CButton(m_Gui, 230, 330, 60, 0, L"SEND", NULL, CALLBACKS::Chat);
	fChat->AddElement(cc_tChat);
	fChat->AddElement(cc_tEnter);
	fChat->AddElement(cc_bEnter);
	fChat->SetVisible( 0 );

	// Create Option
	Log::Debug(L"FMPGUI::Load >> Create options");
	fOption = new CWindow(m_Gui, 200, 200, 400, 300, L"FOUR-MP OPTIONS");
	CText * tInfo = new CText(m_Gui, 10, 10, 300, 100, L"WAIT OR CREATE INTERFACE");
	fOption->AddElement(tInfo);
	fOption->SetVisible( 0 );

	// Create login window
	Log::Debug(L"FMPGUI::Load >> Create login");
	fUserLogin = new CWindow(m_Gui, s_iWidth/2-150, s_iHeight/2-100, 300, 200, L"USER LOGIN", L"WND_USER_LOGIN", CALLBACKS::UserLogin);
	upLoginInfo = new CText(m_Gui, 20, 15, 280, 40, L"Please login or register", L"UP_INFO");
	upLogin = new CEditBox(m_Gui, 100, 45, 180, 0, L"", L"UP_LOGIN", CALLBACKS::Login);
	upPassword = new CEditBox(m_Gui, 100, 75, 180, 0, L"", L"UP_PASSWORD", CALLBACKS::Login);
	upPassword->HideContent(1);
	upStrLogin = new CText(m_Gui, 20, 50, 100, 20, L"Login", L"UP_STR_LOGIN");
	upStrPass = new CText(m_Gui, 20, 80, 100, 20, L"Password", L"UP_STR_PASSWORD");
	upSendLogin = new CButton(m_Gui, 10, 140, 135, 0, L"Login", L"UP_BTN_LOGIN", CALLBACKS::Login);
	upShowRegister = new CButton(m_Gui, 150, 140, 135, 0, L"Register", L"UP_BTN_REGISTER", CALLBACKS::ShowRegister);
	upRemeberMe = new CCheckBox(m_Gui, 70, 110, 0, 0, 0, L"    Remember me", L"UP_CB_REMEBER"); 

	fUserLogin->AddElement(upLoginInfo);
	fUserLogin->AddElement(upLogin);
	fUserLogin->AddElement(upPassword);
	fUserLogin->AddElement(upStrLogin);
	fUserLogin->AddElement(upStrPass);
	fUserLogin->AddElement(upSendLogin);
	fUserLogin->AddElement(upShowRegister);
	fUserLogin->AddElement(upRemeberMe);

	// Create register window
	Log::Debug(L"FMPGUI::Load >> Create register");
	fUserRegister = new CWindow(m_Gui, s_iWidth/2-150, s_iHeight/2-140, 300, 280, L"USER REGISTER", L"WND_USER_REG");
	urLogin = new CEditBox(m_Gui, 100, 50, 180, 0, L"", L"REG_LOGIN");
	urPass = new CEditBox(m_Gui, 100, 80, 180, 0, L"", L"REG_PASSWORD");
	urConfirm = new CEditBox(m_Gui, 100, 110, 180, 0, L"", L"REG_CONFIRM");
	urEmail = new CEditBox(m_Gui, 100, 140, 180, 0, L"", L"REG_EMAIL");
	urNick = new CEditBox(m_Gui, 100, 170, 180, 0, L"", L"REG_NICK");
	urLoginText = new CText(m_Gui, 10, 55, 100, 20, L"Login", L"REG_LOGIN_TEXT");
	urPassText = new CText(m_Gui, 10, 85, 100, 20, L"Password", L"REG_PASSWORD_TEXT");
	urConfirmText = new CText(m_Gui, 10, 115, 100, 20, L"Confirm", L"REG_CONFIRM_TEXT");
	urEmailText = new CText(m_Gui, 10, 145, 100, 20, L"Email", L"REG_EMAIL_TEXT");
	urNickText = new CText(m_Gui, 10, 175, 100, 20, L"Nick", L"REG_NICK_TEXT");
	urInfoText = new CText(m_Gui, 20, 15, 280, 20, L"Please register to play", L"UR_INFO");
	urSendReg = new CButton(m_Gui, 10, 220, 135, 0, L"Register", L"UR_BTN_REG", CALLBACKS::Register);
	urCancelReg = new CButton(m_Gui, 150, 220, 135, 0, L"Cancel", L"UR_BTN_CANCEL", CALLBACKS::HideRegister);

	urPass->HideContent(1);
	urConfirm->HideContent(1);

	fUserRegister->AddElement(urLogin);
	fUserRegister->AddElement(urPass);
	fUserRegister->AddElement(urConfirm);
	fUserRegister->AddElement(urEmail);
	fUserRegister->AddElement(urNick);
	fUserRegister->AddElement(urLoginText);
	fUserRegister->AddElement(urPassText);
	fUserRegister->AddElement(urConfirmText);
	fUserRegister->AddElement(urEmailText);
	fUserRegister->AddElement(urNickText);
	fUserRegister->AddElement(urInfoText);
	fUserRegister->AddElement(urSendReg);
	fUserRegister->AddElement(urCancelReg);
	fUserRegister->SetVisible(0);
	fUserRegister->SetCloseButton(0);

	// Create messages window
	Log::Debug(L"FMPGUI::Load >> Create messages window");
	fInfo = new CWindow(m_Gui, s_iWidth/2-100, s_iHeight/2-50, 200, 100, L"Information", L"WND_INFO");
	CText *iTxt = new CText(m_Gui, 10, 10, 180, 60, L"INFO", L"INFO_TEXT");
	CButton *iBt = new CButton(m_Gui, 50, 45, 100, 0, L"OK", L"INFO_OK", CALLBACKS::InfoOK);
	fInfo->AddElement(iTxt);
	fInfo->AddElement(iBt);
	fInfo->SetVisible(0);

	fEnterNick = new CWindow(m_Gui, s_iWidth/2-100, s_iHeight/2-40, 200, 80, L"Enter nick", L"WND_ENTER_NICK");
	enNick = new CEditBox(m_Gui, 10, 10, 130, 0, NULL, NULL, CALLBACKS::EnterNick);
	enOK = new CButton(m_Gui, 150, 10, 40, 0, L"OK", NULL, CALLBACKS::EnterNick);
	fEnterNick->AddElement(enNick);
	fEnterNick->AddElement(enOK);
	fEnterNick->SetVisible(0);

	wchar_t path[MAX_PATH], tmp[64];
	client.GetPath(L"fmp.ini", path);
	GetPrivateProfileString(L"FOURMP", L"Login", L"", tmp, 64, path);
	if(wcslen(tmp) > 2)
	{
		upLogin->SetString(tmp);
		GetPrivateProfileString(L"FOURMP", L"Password", L"", tmp, 64, path);
		upPassword->SetString(tmp);
		upRemeberMe->SetChecked(1);
	}

	Log::Debug(L"FMPGUI::Load >> Load console");
	conwindow.Load();
	conwindow.Hide();

	Log::Debug(L"FMPGUI::Load >> Disable tab");
	sbTab[tab]->SetEnabled(0);

	Log::Debug(L"FMPGUI::Load >> Set Visible");
	m_Gui->SetVisible( true );

	Log::Debug(L"FMPGUI::Load >> Update GUI");
	m_Gui->UpdateFromFile(L"FMP\\GUIStyle.xml");

	GuiReady = 1;
	Log::Debug(L"FMPGUI::Load complete");
	LeaveCriticalSection(&cs_gui);
}

void FMPGUI::HandleMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if( GuiReady )
	{
		EnterCriticalSection(&cs_gui);
		CMouse *mouse = m_Gui->GetMouse();
		if(mouse) mouse->HandleMessage(Msg, wParam, lParam);

		CKeyboard *keybd = m_Gui->GetKeyboard();
		if(keybd) keybd->HandleMessage(Msg, wParam, lParam);
		LeaveCriticalSection(&cs_gui);
	}
}

void FMPGUI::MoveMouse(int x, int y)
{
	if( GuiReady )
	{
		EnterCriticalSection(&cs_gui);
		m_Gui->GetMouse()->SetPos(x, y);
		m_Gui->MouseMove(m_Gui->GetMouse());

		bool mouse = 0;
		if(g_Mouse[0] != (GetAsyncKeyState(1) != 0))
		{
			g_Mouse[0] = GetAsyncKeyState(1) != 0;
			m_Gui->GetMouse()->SetLeftButton(g_Mouse[0]);
			mouse = 1;
		}
		if(g_Mouse[1] != (GetAsyncKeyState(2) != 0))
		{
			g_Mouse[1] = GetAsyncKeyState(2) != 0;
			m_Gui->GetMouse()->SetRightButton(g_Mouse[1]);
			mouse = 1;
		}
		if(g_Mouse[2] != (GetAsyncKeyState(3) != 0))
		{
			g_Mouse[2] = GetAsyncKeyState(3) != 0;
			m_Gui->GetMouse()->SetMiddleButton(g_Mouse[2]);
			mouse = 1;
		}

		if(mouse)
			m_Gui->KeyEvent( SKey( 0, (GetAsyncKeyState(1)||GetAsyncKeyState(2)||GetAsyncKeyState(3)) && 1 ) );
		LeaveCriticalSection(&cs_gui);
	}
}

void FMPGUI::Draw()
{
	EnterCriticalSection(&cs_gui);
	if( GuiReady ) m_Gui->Draw();
	LeaveCriticalSection(&cs_gui);
}

void FMPGUI::Resize(int width, int height)
{
	if(!GuiReady) return;
	if(width < 800 || height < 600) return;
	if(s_iWidth == width && s_iHeight == height) return;

	s_iWidth = width;
	s_iHeight = height;

	fServBrowser->SetAbsPos(CPos( width/2 - fServBrowser->GetWidth()/2, height/2 - fServBrowser->GetHeight()/2 ));
	fUserRegister->SetAbsPos(CPos( width/2 - fUserRegister->GetWidth()/2, height/2 - fUserRegister->GetHeight()/2 ));
	fUserLogin->SetAbsPos(CPos( width/2 - fUserLogin->GetWidth()/2, height/2 - fUserLogin->GetHeight()/2 ));
	fInfo->SetAbsPos(CPos( width/2 + fInfo->GetWidth()/2, height/2 - fInfo->GetHeight()/2 ));
	fEnterNick->SetAbsPos(CPos( width/2 - fEnterNick->GetWidth()/2, height/2 - fEnterNick->GetHeight()/2 ));
}

void FMPGUI::OnResetDevice()
{
	//if(!GuiReady) return;
	m_Gui->OnResetDevice (  );
	GuiReady = 1;
}

void FMPGUI::OnLostDevice()
{
	//if(!GuiReady) return;
	GuiReady = 0;
	m_Gui->OnLostDevice (  );
}

DWORD FMPGUI::GetWidth()
{
	return s_iWidth;
}

DWORD FMPGUI::GetHeight()
{
	return s_iHeight;
}

void FMPGUI::Logged()
{
	logged = 1;
}

bool FMPGUI::IsLogged()
{
	return logged;
}

void FMPGUI::UpdateServer(ServerInfo *msi)
{
	if(!GuiReady) return;

	EnterCriticalSection(&cs_gui);
	int index = -1;
	wchar_t tmp[32];

	for(int i = 0; i < (int)server_list.size(); i++)
		if(strcmp(server_list[i]->ip, msi->ip) == 0 && server_list[i]->port == msi->port)
		{
			index = i;
			break;
		}

	sbServList->PutStr((msi->password?L"1":L"0"), 0, index);
	sbServList->PutStr(msi->name, 1, index);
	swprintf_s(tmp, 32, L"%d/%d", msi->players, msi->maxplayers);
	sbServList->PutStr(tmp, 2, index);
	swprintf_s(tmp, 32, L"%d", msi->ping);
	sbServList->PutStr(tmp, 3, index);
	sbServList->PutStr(msi->mode, 4, index);
	sbServList->PutStr(msi->loc, 5, index);

	if(index == -1)
	{
		server_list.push_back(msi);
	}
	else
	{
		//delete server_list[index];
		server_list[index] = msi;
	}
	LeaveCriticalSection(&cs_gui);
}

void FMPGUI::Message(wchar_t *data)
{
	if(!GuiReady) return;

	EnterCriticalSection(&cs_gui);
	fInfo->GetElementByString(L"INFO_TEXT", 1)->SetString(data);
	fInfo->SetVisible(1);
	LeaveCriticalSection(&cs_gui);
}
