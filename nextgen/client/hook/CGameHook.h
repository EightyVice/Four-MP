#pragma once
#include <windows.h>
#include "CScriptThread.h"
#include "CD3DManager.h"

#define D3DMAN_COUNT 2

class CGameHook
{
public:
	CGameHook();
	~CGameHook();

	DWORD GetBase();
	DWORD GetGameVersion();

	scrThread* GetActiveThread();
	DWORD GetHash(char *ThreadName);
	bool GetMousePos(int *x, int *y);
	DWORD GetScriptCount();
	sysArray<GtaThread>* GetThreadsArray();
	DWORD GetThreadID();

	void SetActiveThread(scrThread* thread);
	void SetScriptCount(DWORD c);
	void SetThreadID(DWORD id);

	void CGameHook::ThreadTick(scrThread *, unsigned int);

	void OnD3DCreateDevice(IDirect3DDevice9 *, HWND);
	void OnD3DDraw();
	void OnD3DBeginDraw();
	void OnD3DLostDevice();
	void OnD3DResetDevice();
	void OnD3DRelease();

	LRESULT CallOriginalWindowProc(HWND, UINT, WPARAM, LPARAM);

	bool InstallScriptHook(CScriptThread *);
	bool InstallXLiveHook();
	bool InstallDirect3DHook(CD3DManager *);
	bool InstallWindowHook(WNDPROC);

	bool injectFunction(DWORD from, DWORD to);

	bool PatchGame();
	bool UnprotectData();

private:
	bool DetectGameVersion();
	bool GetGameAddresses();

	static DWORD WINAPI ScriptHookThread(void *);

	DWORD m_dwLoadOffset;
	DWORD m_dwGameVersion;

	CD3DManager * m_pD3DManager[D3DMAN_COUNT];
	CScriptThread * m_pScriptThread;
	WNDPROC m_OriginalProc;

	struct XLiveAddresses
	{
		DWORD XWSAStartup;
		DWORD XWSACleanup;
		DWORD XCreateSocket;
		DWORD XSockeClose;
		DWORD XSocketShutdown;
		DWORD XSocketIOCTLSocket;
		DWORD XSocketSetSockOpt;
		DWORD XSocketBind;
		DWORD XSocketConnect;
		DWORD XSocketListen;
		DWORD XSocketAccept;
		DWORD XSocketSelect;
		DWORD XSocketRecv;
		DWORD XSocketRecvFrom;
		DWORD XSocketSend;
		DWORD XSocketSendTo;
		DWORD XSocketInet_Addr;
		DWORD XSocketGetSockName;
		DWORD XWSAGetLastError;
		DWORD XSocketNTOHS;
		DWORD XSocketNTOHL;
		DWORD XNetStartup;
		DWORD XNetCleanup;
		DWORD XNetCreateKey;
		DWORD XNetRegisterKey;
		DWORD XNetUnregisterKey;
		DWORD XNetXnAddrToInAddr;
		DWORD XNetServerToInAddr;
		DWORD XNetInAddrToXnAddr;
		DWORD XNetUnregisterInAddr;
		DWORD XNetConnect;
		DWORD XNetGetConnectStatus;
		DWORD XNetQosListen;
		DWORD XNetQosLookup;
		DWORD XNetQosServiceLookup;
		DWORD XNetQosRelease;
		DWORD XNetGetTitleXnAddr;
		DWORD XNetGetEthernetLinkStatus;
		DWORD XNetSetSystemLinkPort;
		DWORD XCustomGetLastActionPress;
		DWORD XNotifyGetNext;
		DWORD XNotifyPositionUI;
		DWORD XGetOverlappedExtendedError;
		DWORD XGetOverlappedResult;
		DWORD XLiveInitialize;
		DWORD XLiveInput;
		DWORD XLiveRender;
		DWORD XLiveUninitialize;
		DWORD XLiveOnCreateDevice;
		DWORD XLiveOnResetDevice;
		DWORD XHVCreateEngine;
		DWORD XLiveGetUpdateInformation;
		DWORD XLiveUpdateSystem;
		DWORD XLivePreTranslateMessage;
		DWORD XLiveSetDebugLevel;
		DWORD XShowPlayerReviewUI;
		DWORD XShowGuideUI;
		DWORD XShowKeyboardUI;
		DWORD XCloseHandle;
		DWORD XShowGamerCardUI;
		DWORD XCancelOverlapped;
		DWORD XEnumerate;
		DWORD XShowSigninUI;
		DWORD XUserGetXUID;
		DWORD XUserGetSigninState;
		DWORD XUserGetName;
		DWORD XUserAreUsersFriends;
		DWORD XUserCheckPrivilege;
		DWORD XUserGetSigninInfo;
		DWORD XNotifyCreateListener;
		DWORD XUserReadGamerpictureByKey;
		DWORD XShowFriendsUI;
		DWORD XUserSetProperty;
		DWORD XUserSetContext;
		DWORD XUserWriteAchievements;
		DWORD XUserCreateAchievementEnumerator;
		DWORD XUserReadStats;
		DWORD XUserCreateStatsEnumeratorByRank;
		DWORD XUserCreateStatsEnumeratorByXuid;
		DWORD XUserSetContextEx;
		DWORD XUserSetPropertyEx;
		DWORD XLiveInitializeEx;
		DWORD XSessionCreate;
		DWORD XStringVerify;
		DWORD XStorageUploadFromMemory;
		DWORD XStorageEnumerate;
		DWORD XOnlineStartup;
		DWORD XOnlineCleanup;
		DWORD XFriendsCreateEnumerator;
		DWORD XUserMuteListQuery;
		DWORD XInviteGetAcceptedInfo;
		DWORD XInviteSend;
		DWORD XSessionWriteStats;
		DWORD XSessionStart;
		DWORD XSessionSearchEx;
		DWORD XSessionModify;
		DWORD XSessionMigrateHost;
		DWORD XOnlineGetNatType;
		DWORD XSessionLeaveLocal;
		DWORD XSessionJoinRemote;
		DWORD XSessionJoinLocal;
		DWORD XSessionGetDetails;
		DWORD XSessionFlushStats;
		DWORD XSessionDelete;
		DWORD XUserReadProfileSettings;
		DWORD XSessionEnd;
		DWORD XSessionArbitrationRegister;
		DWORD XTitleServerCreateEnumerator;
		DWORD XSessionLeaveRemote;
		DWORD XUserWriteProfileSettings;
		DWORD XUserReadProfileSettingsByXuid;
		DWORD XLiveCalculateSkill;
		DWORD XStorageBuildServerPath;
		DWORD XStorageDownloadToMemory;
		DWORD XLiveProtectedVerifyFile;
		DWORD XLiveContentCreateAccessHandle;
		DWORD XLiveContentUninstall;
		DWORD XLiveContentGetPath;
		DWORD XLiveContentCreateEnumerator;
		DWORD XLiveContentRetrieveOffersByDate;
		DWORD XShowMarketplaceUI;
		DWORD XLivePBufferAllocate;
		DWORD XLivePBufferFree;
		DWORD XLivePBufferSetByteArray;
		DWORD XLivePBufferGetByteArray;
		DWORD XLivePBufferSetByte;
		DWORD XLivePBufferGetByte;
		DWORD XLivePBufferGetDWORD;
		DWORD XLivePBufferSetDWORD;
		DWORD XLiveSetSponsorToken;
		DWORD XLiveCreateProtectedDataContext;
		DWORD XLiveQueryProtectedDataInformation;
		DWORD XLiveCloseProtectedDataContext;
		DWORD XLiveUnprotectData;
		DWORD XLiveProtectData;
		DWORD xlive_5367;
		DWORD xlive_5372;
	};

	struct ScriptAddresses
	{
		DWORD ADDRESS_HASH_GET;
		DWORD ADDRESS_THREAD_ID;
		DWORD ADDRESS_SCRIPTS_COUNT;
		DWORD ADDRESS_SCRIPT_POINTER_1;
		DWORD ADDRESS_SCRIPT_POINTER_2;
		DWORD ADDRESS_ACTIVE_THREAD; 
		DWORD ADDRESS_THREADS_ARRAY;
		DWORD ADDRESS_THREAD_TICK;
		DWORD ADDRESS_MOUSE_POS_X;
		DWORD ADDRESS_MOUSE_POS_Y;
	};

	struct GameAddresses
	{
		XLiveAddresses xlive;
		ScriptAddresses script;

	};

	static GameAddresses * m_pGame;
};