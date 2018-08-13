#include "CGameHook.h"
#include "xlive.h"
#include "log/log.h"

CGameHook::GameAddresses * CGameHook::m_pGame = NULL;

CGameHook::CGameHook()
{
	m_dwLoadOffset = (DWORD)GetModuleHandleA(NULL) - 0x400000;
	Log::Info("Base game address %08X", m_dwLoadOffset);

	m_OriginalProc = NULL;
	
	if(DetectGameVersion())
	{
		GetGameAddresses();
	}
}

CGameHook::~CGameHook()
{
	if(m_pGame) delete m_pGame;
}

bool CGameHook::InstallScriptHook(CScriptThread * pScriptThread)
{
	if(m_pScriptThread || !pScriptThread)
		return false;

	m_pScriptThread = pScriptThread;

	DWORD threadID;
	CreateThread(NULL, 0, ScriptHookThread, m_pScriptThread, NULL, &threadID);
	
	return true;
}

bool CGameHook::InstallDirect3DHook(CD3DManager * pD3DManager)
{
	if(!pD3DManager)
		return false;

	if(!m_pD3DManager[0])
	{
		m_pD3DManager[0] = pD3DManager;
		return true;
	}
	if(!m_pD3DManager[1])
	{
		m_pD3DManager[1] = pD3DManager;
		return true;
	}

	return false;
}

bool CGameHook::InstallWindowHook(WNDPROC wndProc)
{
	m_OriginalProc = wndProc;
	return true;
}

bool CGameHook::InstallXLiveHook()
{
	bool result = true;
	
	result &= injectFunction(m_pGame->xlive.XWSAStartup, (DWORD)XWSAStartup);
	result &= injectFunction(m_pGame->xlive.XWSACleanup, (DWORD)XWSACleanup);
	result &= injectFunction(m_pGame->xlive.XCreateSocket, (DWORD)XCreateSocket);
	result &= injectFunction(m_pGame->xlive.XSockeClose, (DWORD)XSockeClose);
	result &= injectFunction(m_pGame->xlive.XSocketShutdown, (DWORD)XSocketShutdown);
	result &= injectFunction(m_pGame->xlive.XSocketIOCTLSocket, (DWORD)XSocketIOCTLSocket);
	result &= injectFunction(m_pGame->xlive.XSocketSetSockOpt, (DWORD)XSocketSetSockOpt);
	result &= injectFunction(m_pGame->xlive.XSocketBind, (DWORD)XSocketBind);
	result &= injectFunction(m_pGame->xlive.XSocketConnect, (DWORD)XSocketConnect);
	result &= injectFunction(m_pGame->xlive.XSocketListen, (DWORD)XSocketListen);
	result &= injectFunction(m_pGame->xlive.XSocketAccept, (DWORD)XSocketAccept);
	result &= injectFunction(m_pGame->xlive.XSocketSelect, (DWORD)XSocketSelect);
	result &= injectFunction(m_pGame->xlive.XSocketRecv, (DWORD)XSocketRecv);
	result &= injectFunction(m_pGame->xlive.XSocketRecvFrom, (DWORD)XSocketRecvFrom);
	result &= injectFunction(m_pGame->xlive.XSocketSend, (DWORD)XSocketSend);
	result &= injectFunction(m_pGame->xlive.XSocketSendTo, (DWORD)XSocketSendTo);
	result &= injectFunction(m_pGame->xlive.XSocketInet_Addr, (DWORD)XSocketInet_Addr);
	result &= injectFunction(m_pGame->xlive.XSocketGetSockName, (DWORD)XSocketGetSockName);
	result &= injectFunction(m_pGame->xlive.XWSAGetLastError, (DWORD)XWSAGetLastError);
	result &= injectFunction(m_pGame->xlive.XSocketNTOHS, (DWORD)XSocketNTOHS);
	result &= injectFunction(m_pGame->xlive.XSocketNTOHL, (DWORD)XSocketNTOHL);
	result &= injectFunction(m_pGame->xlive.XNetStartup, (DWORD)XNetStartup);
	result &= injectFunction(m_pGame->xlive.XNetCleanup, (DWORD)XNetCleanup);
	result &= injectFunction(m_pGame->xlive.XNetCreateKey, (DWORD)XNetCreateKey);
	result &= injectFunction(m_pGame->xlive.XNetRegisterKey, (DWORD)XNetRegisterKey);
	result &= injectFunction(m_pGame->xlive.XNetUnregisterKey, (DWORD)XNetUnregisterKey);
	result &= injectFunction(m_pGame->xlive.XNetXnAddrToInAddr, (DWORD)XNetXnAddrToInAddr);
	result &= injectFunction(m_pGame->xlive.XNetServerToInAddr, (DWORD)XNetServerToInAddr);
	result &= injectFunction(m_pGame->xlive.XNetInAddrToXnAddr, (DWORD)XNetInAddrToXnAddr);
	result &= injectFunction(m_pGame->xlive.XNetUnregisterInAddr, (DWORD)XNetUnregisterInAddr);
	result &= injectFunction(m_pGame->xlive.XNetConnect, (DWORD)XNetConnect);
	result &= injectFunction(m_pGame->xlive.XNetGetConnectStatus, (DWORD)XNetGetConnectStatus);
	result &= injectFunction(m_pGame->xlive.XNetQosListen, (DWORD)XNetQosListen);
	result &= injectFunction(m_pGame->xlive.XNetQosLookup, (DWORD)XNetQosLookup);
	result &= injectFunction(m_pGame->xlive.XNetQosServiceLookup, (DWORD)XNetQosServiceLookup);
	result &= injectFunction(m_pGame->xlive.XNetQosRelease, (DWORD)XNetQosRelease);
	result &= injectFunction(m_pGame->xlive.XNetGetTitleXnAddr, (DWORD)XNetGetTitleXnAddr);
	result &= injectFunction(m_pGame->xlive.XNetGetEthernetLinkStatus, (DWORD)XNetGetEthernetLinkStatus);
	result &= injectFunction(m_pGame->xlive.XNetSetSystemLinkPort, (DWORD)XNetSetSystemLinkPort);
	result &= injectFunction(m_pGame->xlive.XCustomGetLastActionPress, (DWORD)XCustomGetLastActionPress);
	result &= injectFunction(m_pGame->xlive.XNotifyGetNext, (DWORD)XNotifyGetNext);
	result &= injectFunction(m_pGame->xlive.XNotifyPositionUI, (DWORD)XNotifyPositionUI);
	result &= injectFunction(m_pGame->xlive.XGetOverlappedExtendedError, (DWORD)XGetOverlappedExtendedError);
	result &= injectFunction(m_pGame->xlive.XGetOverlappedResult, (DWORD)XGetOverlappedResult);
	result &= injectFunction(m_pGame->xlive.XLiveInitialize, (DWORD)XLiveInitialize);
	result &= injectFunction(m_pGame->xlive.XLiveInput, (DWORD)XLiveInput);
	result &= injectFunction(m_pGame->xlive.XLiveRender, (DWORD)XLiveRender);
	result &= injectFunction(m_pGame->xlive.XLiveUninitialize, (DWORD)XLiveUninitialize);
	result &= injectFunction(m_pGame->xlive.XLiveOnCreateDevice, (DWORD)XLiveOnCreateDevice);
	result &= injectFunction(m_pGame->xlive.XLiveOnResetDevice, (DWORD)XLiveOnResetDevice);
	result &= injectFunction(m_pGame->xlive.XHVCreateEngine, (DWORD)XHVCreateEngine);
	result &= injectFunction(m_pGame->xlive.XLiveGetUpdateInformation, (DWORD)XLiveGetUpdateInformation);
	result &= injectFunction(m_pGame->xlive.XLiveUpdateSystem, (DWORD)XLiveUpdateSystem);
	result &= injectFunction(m_pGame->xlive.XLivePreTranslateMessage, (DWORD)XLivePreTranslateMessage);
	result &= injectFunction(m_pGame->xlive.XLiveSetDebugLevel, (DWORD)XLiveSetDebugLevel);
	result &= injectFunction(m_pGame->xlive.XShowPlayerReviewUI, (DWORD)XShowPlayerReviewUI);
	result &= injectFunction(m_pGame->xlive.XShowGuideUI, (DWORD)XShowGuideUI);
	result &= injectFunction(m_pGame->xlive.XShowKeyboardUI, (DWORD)XShowKeyboardUI);
	result &= injectFunction(m_pGame->xlive.XCloseHandle, (DWORD)XCloseHandle);
	result &= injectFunction(m_pGame->xlive.XShowGamerCardUI, (DWORD)XShowGamerCardUI);
	result &= injectFunction(m_pGame->xlive.XCancelOverlapped, (DWORD)XCancelOverlapped);
	result &= injectFunction(m_pGame->xlive.XEnumerate, (DWORD)XEnumerate);
	result &= injectFunction(m_pGame->xlive.XShowSigninUI, (DWORD)XShowSigninUI);
	result &= injectFunction(m_pGame->xlive.XUserGetXUID, (DWORD)XUserGetXUID);
	result &= injectFunction(m_pGame->xlive.XUserGetSigninState, (DWORD)XUserGetSigninState);
	result &= injectFunction(m_pGame->xlive.XUserGetName, (DWORD)XUserGetName);
	result &= injectFunction(m_pGame->xlive.XUserAreUsersFriends, (DWORD)XUserAreUsersFriends);
	result &= injectFunction(m_pGame->xlive.XUserCheckPrivilege, (DWORD)XUserCheckPrivilege);
	result &= injectFunction(m_pGame->xlive.XUserGetSigninInfo, (DWORD)XUserGetSigninInfo);
	result &= injectFunction(m_pGame->xlive.XNotifyCreateListener, (DWORD)XNotifyCreateListener);
	result &= injectFunction(m_pGame->xlive.XUserReadGamerpictureByKey, (DWORD)XUserReadGamerpictureByKey);
	result &= injectFunction(m_pGame->xlive.XShowFriendsUI, (DWORD)XShowFriendsUI);
	result &= injectFunction(m_pGame->xlive.XUserSetProperty, (DWORD)XUserSetProperty);
	result &= injectFunction(m_pGame->xlive.XUserSetContext, (DWORD)XUserSetContext);
	result &= injectFunction(m_pGame->xlive.XUserWriteAchievements, (DWORD)XUserWriteAchievements);
	result &= injectFunction(m_pGame->xlive.XUserCreateAchievementEnumerator, (DWORD)XUserCreateAchievementEnumerator);
	result &= injectFunction(m_pGame->xlive.XUserReadStats, (DWORD)XUserReadStats);
	result &= injectFunction(m_pGame->xlive.XUserCreateStatsEnumeratorByRank, (DWORD)XUserCreateStatsEnumeratorByRank);
	result &= injectFunction(m_pGame->xlive.XUserCreateStatsEnumeratorByXuid, (DWORD)XUserCreateStatsEnumeratorByXuid);
	result &= injectFunction(m_pGame->xlive.XUserSetContextEx, (DWORD)XUserSetContextEx);
	result &= injectFunction(m_pGame->xlive.XUserSetPropertyEx, (DWORD)XUserSetPropertyEx);
	result &= injectFunction(m_pGame->xlive.XLiveInitializeEx, (DWORD)XLiveInitializeEx);
	result &= injectFunction(m_pGame->xlive.XSessionCreate, (DWORD)XSessionCreate);
	result &= injectFunction(m_pGame->xlive.XStringVerify, (DWORD)XStringVerify);
	result &= injectFunction(m_pGame->xlive.XStorageUploadFromMemory, (DWORD)XStorageUploadFromMemory);
	result &= injectFunction(m_pGame->xlive.XStorageEnumerate, (DWORD)XStorageEnumerate);
	result &= injectFunction(m_pGame->xlive.XOnlineStartup, (DWORD)XOnlineStartup);
	result &= injectFunction(m_pGame->xlive.XOnlineCleanup, (DWORD)XOnlineCleanup);
	result &= injectFunction(m_pGame->xlive.XFriendsCreateEnumerator, (DWORD)XFriendsCreateEnumerator);
	result &= injectFunction(m_pGame->xlive.XUserMuteListQuery, (DWORD)XUserMuteListQuery);
	result &= injectFunction(m_pGame->xlive.XInviteGetAcceptedInfo, (DWORD)XInviteGetAcceptedInfo);
	result &= injectFunction(m_pGame->xlive.XInviteSend, (DWORD)XInviteSend);
	result &= injectFunction(m_pGame->xlive.XSessionWriteStats, (DWORD)XSessionWriteStats);
	result &= injectFunction(m_pGame->xlive.XSessionStart, (DWORD)XSessionStart);
	result &= injectFunction(m_pGame->xlive.XSessionSearchEx, (DWORD)XSessionSearchEx);
	result &= injectFunction(m_pGame->xlive.XSessionModify, (DWORD)XSessionModify);
	result &= injectFunction(m_pGame->xlive.XSessionMigrateHost, (DWORD)XSessionMigrateHost);
	result &= injectFunction(m_pGame->xlive.XOnlineGetNatType, (DWORD)XOnlineGetNatType);
	result &= injectFunction(m_pGame->xlive.XSessionLeaveLocal, (DWORD)XSessionLeaveLocal);
	result &= injectFunction(m_pGame->xlive.XSessionJoinRemote, (DWORD)XSessionJoinRemote);
	result &= injectFunction(m_pGame->xlive.XSessionJoinLocal, (DWORD)XSessionJoinLocal);
	result &= injectFunction(m_pGame->xlive.XSessionGetDetails, (DWORD)XSessionGetDetails);
	result &= injectFunction(m_pGame->xlive.XSessionFlushStats, (DWORD)XSessionFlushStats);
	result &= injectFunction(m_pGame->xlive.XSessionDelete, (DWORD)XSessionDelete);
	result &= injectFunction(m_pGame->xlive.XUserReadProfileSettings, (DWORD)XUserReadProfileSettings);
	result &= injectFunction(m_pGame->xlive.XSessionEnd, (DWORD)XSessionEnd);
	result &= injectFunction(m_pGame->xlive.XSessionArbitrationRegister, (DWORD)XSessionArbitrationRegister);
	result &= injectFunction(m_pGame->xlive.XTitleServerCreateEnumerator, (DWORD)XTitleServerCreateEnumerator);
	result &= injectFunction(m_pGame->xlive.XSessionLeaveRemote, (DWORD)XSessionLeaveRemote);
	result &= injectFunction(m_pGame->xlive.XUserWriteProfileSettings, (DWORD)XUserWriteProfileSettings);
	result &= injectFunction(m_pGame->xlive.XUserReadProfileSettingsByXuid, (DWORD)XUserReadProfileSettingsByXuid);
	result &= injectFunction(m_pGame->xlive.XLiveCalculateSkill, (DWORD)XLiveCalculateSkill);
	result &= injectFunction(m_pGame->xlive.XStorageBuildServerPath, (DWORD)XStorageBuildServerPath);
	result &= injectFunction(m_pGame->xlive.XStorageDownloadToMemory, (DWORD)XStorageDownloadToMemory);
	result &= injectFunction(m_pGame->xlive.XLiveProtectedVerifyFile, (DWORD)XLiveProtectedVerifyFile);
	result &= injectFunction(m_pGame->xlive.XLiveContentCreateAccessHandle, (DWORD)XLiveContentCreateAccessHandle);
	result &= injectFunction(m_pGame->xlive.XLiveContentUninstall, (DWORD)XLiveContentUninstall);
	result &= injectFunction(m_pGame->xlive.XLiveContentGetPath, (DWORD)XLiveContentGetPath);
	result &= injectFunction(m_pGame->xlive.XLiveContentCreateEnumerator, (DWORD)XLiveContentCreateEnumerator);
	result &= injectFunction(m_pGame->xlive.XLiveContentRetrieveOffersByDate, (DWORD)XLiveContentRetrieveOffersByDate);
	result &= injectFunction(m_pGame->xlive.XShowMarketplaceUI, (DWORD)XShowMarketplaceUI);
	result &= injectFunction(m_pGame->xlive.XLivePBufferAllocate, (DWORD)XLivePBufferAllocate);
	result &= injectFunction(m_pGame->xlive.XLivePBufferFree, (DWORD)XLivePBufferFree);
	result &= injectFunction(m_pGame->xlive.XLivePBufferSetByteArray, (DWORD)XLivePBufferSetByteArray);
	result &= injectFunction(m_pGame->xlive.XLivePBufferGetByteArray, (DWORD)XLivePBufferGetByteArray);
	result &= injectFunction(m_pGame->xlive.XLivePBufferSetByte, (DWORD)XLivePBufferSetByte);
	result &= injectFunction(m_pGame->xlive.XLivePBufferGetByte, (DWORD)XLivePBufferGetByte);
	result &= injectFunction(m_pGame->xlive.XLivePBufferGetDWORD, (DWORD)XLivePBufferGetDWORD);
	result &= injectFunction(m_pGame->xlive.XLivePBufferSetDWORD, (DWORD)XLivePBufferSetDWORD);
	result &= injectFunction(m_pGame->xlive.XLiveSetSponsorToken, (DWORD)XLiveSetSponsorToken);
	result &= injectFunction(m_pGame->xlive.XLiveCreateProtectedDataContext, (DWORD)XLiveCreateProtectedDataContext);
	result &= injectFunction(m_pGame->xlive.XLiveQueryProtectedDataInformation, (DWORD)XLiveQueryProtectedDataInformation);
	result &= injectFunction(m_pGame->xlive.XLiveCloseProtectedDataContext, (DWORD)XLiveCloseProtectedDataContext);
	result &= injectFunction(m_pGame->xlive.XLiveUnprotectData, (DWORD)XLiveUnprotectData);
	result &= injectFunction(m_pGame->xlive.XLiveProtectData, (DWORD)XLiveProtectData);
	result &= injectFunction(m_pGame->xlive.xlive_5367, (DWORD)xlive_5367);
	result &= injectFunction(m_pGame->xlive.xlive_5372, (DWORD)xlive_5372);

	return result;
}

void getSavefilePath (int __unused, char * pBuffer, char * pszSaveName) 
{
	strcpy_s (pBuffer, 256, "FMP\\savegames");

	DWORD attrs = GetFileAttributes (pBuffer);
	if (attrs == INVALID_FILE_ATTRIBUTES) 
	{
		Log::Error("You should install FOUR-MP completely");
		Log::Error("Install savegames in $GTAIV$\\FMP\\savegames\\");
		CreateDirectory (pBuffer, NULL);
		exit(1);
	}
	else if (!(attrs & FILE_ATTRIBUTE_DIRECTORY)) 
	{
		Log::Error ("unable to create directory '%s', file '%s' already exists", pBuffer);
		strcpy_s (pBuffer, 256, pszSaveName);
		return;
	}

	if (pszSaveName) 
	{
		strcat_s (pBuffer, 256, "\\");
		strcat_s (pBuffer, 256, pszSaveName);
	}
	Log::Debug ("[getSavefilePath]: '%s'", pBuffer);
}

bool CGameHook::UnprotectData()
{
	DWORD handle = (DWORD)GetModuleHandleA(NULL);

	BYTE * pImageBase = reinterpret_cast<BYTE *>(handle); 
	PIMAGE_DOS_HEADER pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER> (handle);
	PIMAGE_NT_HEADERS pNtHeader  = reinterpret_cast<PIMAGE_NT_HEADERS> (pImageBase+pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHeader);

	for (int iSection = 0; iSection < pNtHeader->FileHeader.NumberOfSections; ++iSection, ++pSection) 
	{
		char * pszSectionName = reinterpret_cast<char *>(pSection->Name);
		if (!strcmp (pszSectionName, ".text") || !strcmp (pszSectionName, ".rdata")) 
		{
			DWORD dwPhysSize = (pSection->Misc.VirtualSize + 4095) & ~4095;    
			Log::Debug("[EXE] unprotecting section '%s': addr = 0x%08x, size = 0x%08x\n", pSection->Name, pSection->VirtualAddress, dwPhysSize);

			DWORD oldProtect;
			DWORD newProtect = (pSection->Characteristics & IMAGE_SCN_MEM_EXECUTE) ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE;
			if (!VirtualProtect (reinterpret_cast <VOID *>(handle+pSection->VirtualAddress), dwPhysSize, newProtect, &oldProtect)) 
			{
				Log::Error("[EXE] Virtual protect error\n");
				return false;
			}
		}
	}
	return true;
}

bool CGameHook::PatchGame()
{
	switch(m_dwGameVersion)
	{
	case 0x1070:
		*(DWORD *)(0x401835 + m_dwLoadOffset) = 1;		    // disable sleep
		*(BYTE  *)(0xD356D0 + m_dwLoadOffset) = 0xC3;	    // RETN - enable debugger in error menu (don't load WER.dll)
		*(DWORD *)(0x403F10 + m_dwLoadOffset) = 0x900008C2;	// RETN 8 - certificates check
		*(DWORD *)(0x40262D + m_dwLoadOffset) = 0x4AE9C033;	// xor eax, eax - address of the RGSC object
		*(DWORD *)(0x402631 + m_dwLoadOffset) = 0x90000002;	// jmp 40289E (skip RGSC connect and EFC checks)		
		*(WORD  *)(0x402883 + m_dwLoadOffset) = 0xA390;	    // NOP; MOV [g_rgsc], eax
		memset ((BYTE *)(0x4028ED + m_dwLoadOffset), 0x90, 0x2A);
		*(DWORD *)(0x40291D + m_dwLoadOffset) = 0x90909090;	// NOP*4- last RGSC init check
		*(WORD  *)(0x402921 + m_dwLoadOffset) = 0x9090;	    // NOP*2- last RGSC init check 

		// skip missing tests...
		memset ((BYTE *)(0x402B12 + m_dwLoadOffset), 0x90, 14);
		memset ((BYTE *)(0x402D17 + m_dwLoadOffset), 0x90, 14);
		*(DWORD *)(0x403870 + m_dwLoadOffset) = 0x90C3C033;	// xor eax, eax; retn
		*(DWORD *)(0x404250 + m_dwLoadOffset) = 0x90C3C033;	// xor eax, eax; retn

		// savegames
		*(WORD *)(0x5B06E5 + m_dwLoadOffset) = 0x9090; 	// NOP; NOP - save file CRC32 check
		injectFunction (0x5B0110 + m_dwLoadOffset, (DWORD)getSavefilePath); // replace getSavefilePath

		*(DWORD *)(0xBAC160 + m_dwLoadOffset) = 0x90C301B0;	// mov al, 1; retn
		*(DWORD *)(0xBAC180 + m_dwLoadOffset) = 0x90C301B0;
		*(DWORD *)(0xBAC190 + m_dwLoadOffset) = 0x90C301B0;
		*(DWORD *)(0xBAC1C0 + m_dwLoadOffset) = 0x90C301B0;
		return true;
		break;
	case 0x1061:
		// process patches
		*(DWORD *)(0x401835 + m_dwLoadOffset) = 1;		    // disable sleep
		*(BYTE  *)(0xD34FB0 + m_dwLoadOffset) = 0xC3;	    // RETN - enable debugger in error menu (don't load WER.dll)
		*(DWORD *)(0x403F30 + m_dwLoadOffset) = 0x900008C2;	// RETN 8 - certificates check
		*(DWORD *)(0x40264D + m_dwLoadOffset) = 0x4AE9C033;	// xor eax, eax - address of the RGSC object
		*(DWORD *)(0x402651 + m_dwLoadOffset) = 0x90000002;	// jmp 40289E (skip RGSC connect and EFC checks)		
		*(WORD  *)(0x4028A3 + m_dwLoadOffset) = 0xA390;	    // NOP; MOV [g_rgsc], eax
		memset ((BYTE *)(0x40290D + m_dwLoadOffset), 0x90, 0x2A);
		*(DWORD *)(0x40293D + m_dwLoadOffset) = 0x90909090;	// NOP*4- last RGSC init check
		*(WORD  *)(0x402941 + m_dwLoadOffset) = 0x9090;	    // NOP*2- last RGSC init check 

		// skip missing tests...
		memset ((BYTE *)(0x402B32 + m_dwLoadOffset), 0x90, 14);
		memset ((BYTE *)(0x402D37 + m_dwLoadOffset), 0x90, 14);
		*(DWORD *)(0x403890 + m_dwLoadOffset) = 0x90C3C033;	// xor eax, eax; retn
		*(DWORD *)(0x404270 + m_dwLoadOffset) = 0x90C3C033;	// xor eax, eax; retn

		// savegames
		*(WORD *)(0x5B0425 + m_dwLoadOffset) = 0x9090; 	// NOP; NOP - save file CRC32 check
		injectFunction (0x5AFE50 + m_dwLoadOffset, (DWORD)getSavefilePath); // replace getSavefilePath

		*(DWORD *)(0xBAF690 + m_dwLoadOffset) = 0x90C301B0;	// mov al, 1; retn
		*(DWORD *)(0xBAF6B0 + m_dwLoadOffset) = 0x90C301B0;
		*(DWORD *)(0xBAF6C0 + m_dwLoadOffset) = 0x90C301B0;
		*(DWORD *)(0xBAF6F0 + m_dwLoadOffset) = 0x90C301B0;
		return true;
		break;
	}
	return false;
}

bool CGameHook::injectFunction(DWORD from, DWORD to)
{
	if(!from || !to) 
	{
		Log::Warning("Inject %08X => %08X failed", from, to);
		return false;
	}

	DWORD oldp;
	VirtualProtect((LPVOID)from, 5, PAGE_EXECUTE_READWRITE, &oldp);

	BYTE *patch = (BYTE *)from;
	*patch = 0xE9;    // JMP
	*(DWORD *)(patch + 1) = (to - (from + 5));  

	VirtualProtect((LPVOID)from, 5, oldp, &oldp);

	return true;
}

bool CGameHook::DetectGameVersion()
{
	DWORD signature = *(DWORD *)(0x608C34+m_dwLoadOffset);

	if (signature == 0x831F7518)
		m_dwGameVersion = 0x1010;
	else if (signature == 0xC483FFE4) 
		m_dwGameVersion = 0x1020;
	else if (signature == 0x280F0000)
		m_dwGameVersion = 0x1030;
 	else if (signature == 0x110FF300)
		m_dwGameVersion = 0x1040;
	else if (signature == 0xf3385058)
		m_dwGameVersion = 0x1050;
	else if (signature == 0x0000989e)
		m_dwGameVersion = 0x1051;
	else if (signature == 0x00a42494)
		m_dwGameVersion = 0x1060;
	else if (signature == 0x00000094) 
		m_dwGameVersion = 0x1061;
    else if (signature == 0xda280f30)
        m_dwGameVersion = 0x1062;
    else if (signature == 0x1006e857) 
        m_dwGameVersion = 0x1070;
    else if (signature == 0x0f14247c)
        m_dwGameVersion = 0x1110;
    else if (signature == 0x0d5c0ff3) 
        m_dwGameVersion = 0x1120;
	else 
	{
		m_dwGameVersion = 0x0;
		Log::Error ("Unknown game version (signature = 0x%08x)\n", signature);
		return false;
	}

	Log::Info("You use %X version", m_dwGameVersion);

	return true;
}

bool CGameHook::GetGameAddresses()
{
	switch( m_dwGameVersion )
	{
	case 0x1070:
		m_pGame = new GameAddresses;
		m_pGame->xlive.XLivePBufferSetDWORD = 0xD30318 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferGetDWORD = 0xD3031E + m_dwLoadOffset;
		m_pGame->xlive.XNotifyPositionUI = 0xD30324 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferFree = 0xD3032A + m_dwLoadOffset;
		m_pGame->xlive.XLiveRender = 0xD30330 + m_dwLoadOffset;
		m_pGame->xlive.XLiveOnResetDevice = 0xD30336 + m_dwLoadOffset;
		m_pGame->xlive.XLiveOnCreateDevice = 0xD3033C + m_dwLoadOffset;
		m_pGame->xlive.XLiveUninitialize = 0xD30342 + m_dwLoadOffset;
		m_pGame->xlive.XUserGetSigninInfo = 0xD30348 + m_dwLoadOffset;
		m_pGame->xlive.XCloseHandle = 0xD3034E + m_dwLoadOffset;
		m_pGame->xlive.XLiveContentGetPath = 0xD30354 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferGetByteArray = 0xD3035A + m_dwLoadOffset;
		m_pGame->xlive.XLiveContentCreateAccessHandle = 0xD30360 + m_dwLoadOffset;
		m_pGame->xlive.XNotifyCreateListener = 0xD30366 + m_dwLoadOffset;
		m_pGame->xlive.XNotifyGetNext = 0xD3036C + m_dwLoadOffset;
		m_pGame->xlive.XWSAGetLastError = 0xD30372 + m_dwLoadOffset;
		m_pGame->xlive.XSocketSelect = 0xD30378 + m_dwLoadOffset;
		m_pGame->xlive.XEnumerate = 0xD3037E + m_dwLoadOffset;
		m_pGame->xlive.XTitleServerCreateEnumerator = 0xD30384 + m_dwLoadOffset;
		m_pGame->xlive.XSocketNTOHS = 0xD3038A + m_dwLoadOffset;
		m_pGame->xlive.XSocketNTOHL = 0xD30390 + m_dwLoadOffset;
		m_pGame->xlive.XGetOverlappedResult = 0xD30396 + m_dwLoadOffset;
		m_pGame->xlive.XSocketIOCTLSocket = 0xD3039C + m_dwLoadOffset;
		m_pGame->xlive.XSockeClose = 0xD303A2 + m_dwLoadOffset;
		m_pGame->xlive.XSocketConnect = 0xD303A8 + m_dwLoadOffset;
		m_pGame->xlive.XCreateSocket = 0xD303AE + m_dwLoadOffset;
		m_pGame->xlive.XSocketSend = 0xD303B4 + m_dwLoadOffset;
		m_pGame->xlive.XNetGetTitleXnAddr = 0xD303BA + m_dwLoadOffset;
		m_pGame->xlive.XNetServerToInAddr = 0xD303C0 + m_dwLoadOffset;
		m_pGame->xlive.XSocketShutdown = 0xD303C6 + m_dwLoadOffset;
		m_pGame->xlive.XUserReadProfileSettings = 0xD303CC + m_dwLoadOffset;
		m_pGame->xlive.XUserWriteProfileSettings = 0xD303D2 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferSetByteArray = 0xD303D8 + m_dwLoadOffset;
		m_pGame->xlive.XLiveContentCreateEnumerator = 0xD303DE + m_dwLoadOffset;
		m_pGame->xlive.XNetQosRelease = 0xD303E4 + m_dwLoadOffset;
		m_pGame->xlive.XNetQosLookup = 0xD303EA + m_dwLoadOffset;
		m_pGame->xlive.XNetQosListen = 0xD303F0 + m_dwLoadOffset;
		m_pGame->xlive.XStringVerify = 0xD303F6 + m_dwLoadOffset;
		m_pGame->xlive.XStorageUploadFromMemory = 0xD303FC + m_dwLoadOffset;
		m_pGame->xlive.XStorageBuildServerPath = 0xD30402 + m_dwLoadOffset;
		m_pGame->xlive.XStorageDownloadToMemory = 0xD30408 + m_dwLoadOffset;
		m_pGame->xlive.xlive_5367 = 0xD3040E + m_dwLoadOffset;
		m_pGame->xlive.XGetOverlappedExtendedError = 0xD30414 + m_dwLoadOffset;
		m_pGame->xlive.xlive_5372 = 0xD3041A + m_dwLoadOffset;
		m_pGame->xlive.XCancelOverlapped = 0xD30420 + m_dwLoadOffset;
		m_pGame->xlive.XUserAreUsersFriends = 0xD30426 + m_dwLoadOffset;
		m_pGame->xlive.XUserMuteListQuery = 0xD3042C + m_dwLoadOffset;
		m_pGame->xlive.XHVCreateEngine = 0xD30432 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferSetByte = 0xD30438 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferGetByte = 0xD3043E + m_dwLoadOffset;
		m_pGame->xlive.XLiveInitializeEx = 0xD30444 + m_dwLoadOffset;
		m_pGame->xlive.XNetSetSystemLinkPort = 0xD3044A + m_dwLoadOffset;
		m_pGame->xlive.XLiveQueryProtectedDataInformation = 0xD30450 + m_dwLoadOffset;
		m_pGame->xlive.XLiveUnprotectData = 0xD30456 + m_dwLoadOffset;
		m_pGame->xlive.XLiveProtectData = 0xD3045C + m_dwLoadOffset;
		m_pGame->xlive.XLiveCloseProtectedDataContext = 0xD30462 + m_dwLoadOffset;
		m_pGame->xlive.XLiveCreateProtectedDataContext = 0xD30468 + m_dwLoadOffset;
		m_pGame->xlive.XSocketAccept = 0xD3046E + m_dwLoadOffset;
		m_pGame->xlive.XSocketRecv = 0xD30474 + m_dwLoadOffset;
		m_pGame->xlive.XSocketListen = 0xD3047A + m_dwLoadOffset;
		m_pGame->xlive.XSocketBind = 0xD30480 + m_dwLoadOffset;
		m_pGame->xlive.XSocketGetSockName = 0xD30486 + m_dwLoadOffset;
		m_pGame->xlive.XSocketInet_Addr = 0xD3048C + m_dwLoadOffset;
		m_pGame->xlive.XWSAStartup = 0xD30492 + m_dwLoadOffset;
		m_pGame->xlive.XNetStartup = 0xD30498 + m_dwLoadOffset;
		m_pGame->xlive.XWSACleanup = 0xD3049E + m_dwLoadOffset;
		m_pGame->xlive.XNetCleanup = 0xD304A4 + m_dwLoadOffset;
		m_pGame->xlive.XLivePreTranslateMessage = 0xD304AA + m_dwLoadOffset;
		m_pGame->xlive.XUserGetName = 0xD304B0 + m_dwLoadOffset;
		m_pGame->xlive.XLiveUpdateSystem = 0xD304B6 + m_dwLoadOffset;
		m_pGame->xlive.XInviteGetAcceptedInfo = 0xD304BC + m_dwLoadOffset;
		m_pGame->xlive.XUserSetContextEx = 0xD304C2 + m_dwLoadOffset;
		m_pGame->xlive.XLiveGetUpdateInformation = 0xD304C8 + m_dwLoadOffset;
		m_pGame->xlive.XUserCreateStatsEnumeratorByRank = 0xD304CE + m_dwLoadOffset;
		m_pGame->xlive.XUserReadStats = 0xD304D4 + m_dwLoadOffset;
		m_pGame->xlive.XUserCreateStatsEnumeratorByXuid = 0xD304DA + m_dwLoadOffset;
		m_pGame->xlive.XUserSetContext = 0xD304E0 + m_dwLoadOffset;
		m_pGame->xlive.XUserSetProperty = 0xD304E6 + m_dwLoadOffset;
		m_pGame->xlive.XOnlineCleanup = 0xD304EC + m_dwLoadOffset;
		m_pGame->xlive.XOnlineStartup = 0xD304F2 + m_dwLoadOffset;
		m_pGame->xlive.XNetGetConnectStatus = 0xD304F8 + m_dwLoadOffset;
		m_pGame->xlive.XNetUnregisterInAddr = 0xD304FE + m_dwLoadOffset;
		m_pGame->xlive.XNetGetEthernetLinkStatus = 0xD30504 + m_dwLoadOffset;
		m_pGame->xlive.XUserCheckPrivilege = 0xD3050A + m_dwLoadOffset;
		m_pGame->xlive.XUserGetSigninState = 0xD30510 + m_dwLoadOffset;
		m_pGame->xlive.XOnlineGetNatType = 0xD30516 + m_dwLoadOffset;
		m_pGame->xlive.XSessionSearchEx = 0xD3051C + m_dwLoadOffset;
		m_pGame->xlive.XUserWriteAchievements = 0xD30522 + m_dwLoadOffset;
		m_pGame->xlive.XUserCreateAchievementEnumerator = 0xD30528 + m_dwLoadOffset;
		m_pGame->xlive.XFriendsCreateEnumerator = 0xD3052E + m_dwLoadOffset;
		m_pGame->xlive.XShowGuideUI = 0xD30534 + m_dwLoadOffset;
		m_pGame->xlive.XShowSigninUI = 0xD3053A + m_dwLoadOffset;
		m_pGame->xlive.XShowGamerCardUI = 0xD30540 + m_dwLoadOffset;
		m_pGame->xlive.XShowPlayerReviewUI = 0xD30546 + m_dwLoadOffset;
		m_pGame->xlive.XShowMarketplaceUI = 0xD3054C + m_dwLoadOffset;
		m_pGame->xlive.XSessionJoinLocal = 0xD30552 + m_dwLoadOffset;
		m_pGame->xlive.XSessionCreate = 0xD30558 + m_dwLoadOffset;
		m_pGame->xlive.XSessionMigrateHost = 0xD3055E + m_dwLoadOffset;
		m_pGame->xlive.XSessionJoinRemote = 0xD30564 + m_dwLoadOffset;
		m_pGame->xlive.XSessionLeaveRemote = 0xD3056A + m_dwLoadOffset;
		m_pGame->xlive.XSessionDelete = 0xD30570 + m_dwLoadOffset;
		m_pGame->xlive.XSessionModify = 0xD30576 + m_dwLoadOffset;
		m_pGame->xlive.XSessionLeaveLocal = 0xD3057C + m_dwLoadOffset;
		m_pGame->xlive.XSessionGetDetails = 0xD30582 + m_dwLoadOffset;
		m_pGame->xlive.XInviteSend = 0xD30588 + m_dwLoadOffset;
		m_pGame->xlive.XSessionWriteStats = 0xD3058E + m_dwLoadOffset;
		m_pGame->xlive.XSessionStart = 0xD30594 + m_dwLoadOffset;
		m_pGame->xlive.XSessionFlushStats = 0xD3059A + m_dwLoadOffset;
		m_pGame->xlive.XSessionArbitrationRegister = 0xD305A0 + m_dwLoadOffset;
		m_pGame->xlive.XSessionEnd = 0xD305A6 + m_dwLoadOffset;
		m_pGame->xlive.XSocketRecvFrom = 0xD305AC + m_dwLoadOffset;
		m_pGame->xlive.XSocketSendTo = 0xD305B2 + m_dwLoadOffset;
		m_pGame->xlive.XSocketSetSockOpt = 0xD305B8 + m_dwLoadOffset;
		m_pGame->xlive.XNetXnAddrToInAddr = 0xD305BE + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferAllocate = 0xD30312 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_HASH_GET = 0x5A8290 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_THREAD_ID = 0x1849ADC + m_dwLoadOffset;
		m_pGame->script.ADDRESS_SCRIPTS_COUNT = 0x1849AF8 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_SCRIPT_POINTER_1 = 0x198332C + m_dwLoadOffset;
		m_pGame->script.ADDRESS_SCRIPT_POINTER_2 = 0x1983328 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_ACTIVE_THREAD = 0x1849AE0 + m_dwLoadOffset; 
		m_pGame->script.ADDRESS_THREADS_ARRAY = 0x1983310 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_THREAD_TICK = 0xBBCDF0 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_MOUSE_POS_X = 0x188AB90 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_MOUSE_POS_Y = 0x188AB9C + m_dwLoadOffset;
		break;
	case 0x1061:
		m_pGame = new GameAddresses;
		m_pGame->xlive.XUserGetSigninInfo = 0xD2FC16;
		m_pGame->xlive.XCloseHandle = 0xD2FC1C + m_dwLoadOffset;
		m_pGame->xlive.XLiveContentGetPath = 0xD2FC22 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferGetByteArray = 0xD2FC28 + m_dwLoadOffset;
		m_pGame->xlive.XLiveContentCreateAccessHandle = 0xD2FC2E + m_dwLoadOffset;
		m_pGame->xlive.XNotifyCreateListener = 0xD2FC34 + m_dwLoadOffset;
		m_pGame->xlive.XNotifyGetNext = 0xD2FC3A + m_dwLoadOffset;
		m_pGame->xlive.XWSAGetLastError = 0xD2FC40 + m_dwLoadOffset;
		m_pGame->xlive.XSocketSelect = 0xD2FC46 + m_dwLoadOffset;
		m_pGame->xlive.XEnumerate = 0xD2FC4C + m_dwLoadOffset;
		m_pGame->xlive.XTitleServerCreateEnumerator = 0xD2FC52 + m_dwLoadOffset;
		m_pGame->xlive.XSocketNTOHS = 0xD2FC58 + m_dwLoadOffset;
		m_pGame->xlive.XSocketNTOHL = 0xD2FC5E + m_dwLoadOffset;
		m_pGame->xlive.XGetOverlappedResult = 0xD2FC64 + m_dwLoadOffset;
		m_pGame->xlive.XSocketIOCTLSocket = 0xD2FC6A + m_dwLoadOffset;
		m_pGame->xlive.XSockeClose = 0xD2FC70 + m_dwLoadOffset;
		m_pGame->xlive.XSocketConnect = 0xD2FC76 + m_dwLoadOffset;
		m_pGame->xlive.XCreateSocket = 0xD2FC7C + m_dwLoadOffset;
		m_pGame->xlive.XSocketSend = 0xD2FC82 + m_dwLoadOffset;
		m_pGame->xlive.XNetGetTitleXnAddr = 0xD2FC88 + m_dwLoadOffset;
		m_pGame->xlive.XNetServerToInAddr = 0xD2FC8E + m_dwLoadOffset;
		m_pGame->xlive.XSocketShutdown = 0xD2FC94 + m_dwLoadOffset;
		m_pGame->xlive.XUserReadProfileSettings = 0xD2FC9A + m_dwLoadOffset;
		m_pGame->xlive.XUserWriteProfileSettings = 0xD2FCA0 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferSetByteArray = 0xD2FCA6 + m_dwLoadOffset;
		m_pGame->xlive.XLiveContentCreateEnumerator = 0xD2FCAC + m_dwLoadOffset;
		m_pGame->xlive.XStringVerify = 0xD2FCB2 + m_dwLoadOffset;
		m_pGame->xlive.XNetQosRelease = 0xD2FCB8 + m_dwLoadOffset;
		m_pGame->xlive.XNetQosLookup = 0xD2FCBE + m_dwLoadOffset;
		m_pGame->xlive.XNetQosListen = 0xD2FCC4 + m_dwLoadOffset;
		m_pGame->xlive.XStorageDownloadToMemory = 0xD2FCCA + m_dwLoadOffset;
		m_pGame->xlive.XStorageUploadFromMemory = 0xD2FCD0 + m_dwLoadOffset;
		m_pGame->xlive.XStorageBuildServerPath = 0xD2FCD6 + m_dwLoadOffset;
		m_pGame->xlive.xlive_5367 = 0xD2FCDC + m_dwLoadOffset;
		m_pGame->xlive.XGetOverlappedExtendedError = 0xD2FCE2 + m_dwLoadOffset;
		m_pGame->xlive.xlive_5372 = 0xD2FCE8 + m_dwLoadOffset;
		m_pGame->xlive.XCancelOverlapped = 0xD2FCEE + m_dwLoadOffset;
		m_pGame->xlive.XUserAreUsersFriends = 0xD2FCF4 + m_dwLoadOffset;
		m_pGame->xlive.XUserMuteListQuery = 0xD2FCFA + m_dwLoadOffset;
		m_pGame->xlive.XHVCreateEngine = 0xD2FD00 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferSetByte = 0xD2FD06 + m_dwLoadOffset;
		m_pGame->xlive.XLivePBufferGetByte = 0xD2FD0C + m_dwLoadOffset;
		m_pGame->xlive.XLiveInitializeEx = 0xD2FD12 + m_dwLoadOffset;
		m_pGame->xlive.XNetSetSystemLinkPort = 0xD2FD18 + m_dwLoadOffset;
		m_pGame->xlive.XLiveQueryProtectedDataInformation = 0xD2FD1E + m_dwLoadOffset;
		m_pGame->xlive.XLiveUnprotectData = 0xD2FD24 + m_dwLoadOffset;
		m_pGame->xlive.XLiveProtectData = 0xD2FD2A + m_dwLoadOffset;
		m_pGame->xlive.XLiveCloseProtectedDataContext = 0xD2FD30 + m_dwLoadOffset;
		m_pGame->xlive.XLiveCreateProtectedDataContext = 0xD2FD36 + m_dwLoadOffset;
		m_pGame->xlive.XSocketRecv = 0xD2FD3C + m_dwLoadOffset;
		m_pGame->xlive.XSocketListen = 0xD2FD42 + m_dwLoadOffset;
		m_pGame->xlive.XSocketBind = 0xD2FD48 + m_dwLoadOffset;
		m_pGame->xlive.XSocketGetSockName = 0xD2FD4E + m_dwLoadOffset;
		m_pGame->xlive.XSocketInet_Addr = 0xD2FD54 + m_dwLoadOffset;
		m_pGame->xlive.XSocketAccept = 0xD2FD5A + m_dwLoadOffset;
		m_pGame->xlive.XNetStartup = 0xD2FD60 + m_dwLoadOffset;
		m_pGame->xlive.XWSACleanup = 0xD2FD66 + m_dwLoadOffset;
		m_pGame->xlive.XNetCleanup = 0xD2FD6C + m_dwLoadOffset;
		m_pGame->xlive.XWSAStartup = 0xD2FD72 + m_dwLoadOffset;
		m_pGame->xlive.XLivePreTranslateMessage = 0xD2FD78 + m_dwLoadOffset;
		m_pGame->xlive.XUserGetName = 0xD2FD7E + m_dwLoadOffset;
		m_pGame->xlive.XLiveUpdateSystem = 0xD2FD84 + m_dwLoadOffset;
		m_pGame->xlive.XInviteGetAcceptedInfo = 0xD2FD8A + m_dwLoadOffset;
		m_pGame->xlive.XUserSetContextEx = 0xD2FD90 + m_dwLoadOffset;
		m_pGame->xlive.XLiveGetUpdateInformation = 0xD2FD96 + m_dwLoadOffset;
		m_pGame->xlive.XUserCreateStatsEnumeratorByRank = 0xD2FD9C + m_dwLoadOffset;
		m_pGame->xlive.XUserReadStats = 0xD2FDA2 + m_dwLoadOffset;
		m_pGame->xlive.XUserCreateStatsEnumeratorByXuid = 0xD2FDA8 + m_dwLoadOffset;
		m_pGame->xlive.XUserSetContext = 0xD2FDAE + m_dwLoadOffset;
		m_pGame->xlive.XUserSetProperty = 0xD2FDB4 + m_dwLoadOffset;
		m_pGame->xlive.XOnlineCleanup = 0xD2FDBA + m_dwLoadOffset;
		m_pGame->xlive.XOnlineStartup = 0xD2FDC0 + m_dwLoadOffset;
		m_pGame->xlive.XNetGetConnectStatus = 0xD2FDC6 + m_dwLoadOffset;
		m_pGame->xlive.XNetUnregisterInAddr = 0xD2FDCC + m_dwLoadOffset;
		m_pGame->xlive.XNetGetEthernetLinkStatus = 0xD2FDD2 + m_dwLoadOffset;
		m_pGame->xlive.XUserCheckPrivilege = 0xD2FDD8 + m_dwLoadOffset;
		m_pGame->xlive.XUserGetSigninState = 0xD2FDDE + m_dwLoadOffset;
		m_pGame->xlive.XOnlineGetNatType = 0xD2FDE4 + m_dwLoadOffset;
		m_pGame->xlive.XSessionSearchEx = 0xD2FDEA + m_dwLoadOffset;
		m_pGame->xlive.XUserCreateAchievementEnumerator = 0xD2FDF0 + m_dwLoadOffset;
		m_pGame->xlive.XUserWriteAchievements = 0xD2FDF6 + m_dwLoadOffset;
		m_pGame->xlive.XShowMarketplaceUI = 0xD2FDFC + m_dwLoadOffset;
		m_pGame->xlive.XShowGuideUI = 0xD2FE02 + m_dwLoadOffset;
		m_pGame->xlive.XShowSigninUI = 0xD2FE08 + m_dwLoadOffset;
		m_pGame->xlive.XShowGamerCardUI = 0xD2FE0E + m_dwLoadOffset;
		m_pGame->xlive.XShowPlayerReviewUI = 0xD2FE14 + m_dwLoadOffset;
		m_pGame->xlive.XFriendsCreateEnumerator = 0xD2FE1A + m_dwLoadOffset;
		m_pGame->xlive.XSessionJoinRemote = 0xD2FE20 + m_dwLoadOffset;
		m_pGame->xlive.XSessionLeaveRemote = 0xD2FE26 + m_dwLoadOffset;
		m_pGame->xlive.XSessionDelete = 0xD2FE2C + m_dwLoadOffset;
		m_pGame->xlive.XSessionModify = 0xD2FE32 + m_dwLoadOffset;
		m_pGame->xlive.XSessionLeaveLocal = 0xD2FE38 + m_dwLoadOffset;
		m_pGame->xlive.XSessionGetDetails = 0xD2FE3E + m_dwLoadOffset;
		m_pGame->xlive.XInviteSend = 0xD2FE44 + m_dwLoadOffset;
		m_pGame->xlive.XSessionJoinLocal = 0xD2FE4A + m_dwLoadOffset;
		m_pGame->xlive.XSessionCreate = 0xD2FE50 + m_dwLoadOffset;
		m_pGame->xlive.XSessionMigrateHost = 0xD2FE56 + m_dwLoadOffset;
		m_pGame->xlive.XSessionStart = 0xD2FE5C + m_dwLoadOffset;
		m_pGame->xlive.XSessionFlushStats = 0xD2FE62 + m_dwLoadOffset;
		m_pGame->xlive.XSessionArbitrationRegister = 0xD2FE68 + m_dwLoadOffset;
		m_pGame->xlive.XSessionEnd = 0xD2FE6E + m_dwLoadOffset;
		m_pGame->xlive.XSessionWriteStats = 0xD2FE74 + m_dwLoadOffset;
		m_pGame->xlive.XSocketRecvFrom = 0xD2FE7A + m_dwLoadOffset;
		m_pGame->xlive.XSocketSendTo = 0xD2FE80 + m_dwLoadOffset;
		m_pGame->xlive.XSocketSetSockOpt = 0xD2FE86 + m_dwLoadOffset;
		m_pGame->xlive.XNetXnAddrToInAddr = 0xD2FE8C + m_dwLoadOffset;
		m_pGame->script.ADDRESS_HASH_GET = 0x5A7F10 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_THREAD_ID = 0x1848B00 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_SCRIPTS_COUNT = 0x1848B1C + m_dwLoadOffset;
		m_pGame->script.ADDRESS_SCRIPT_POINTER_1 = 0x198234C + m_dwLoadOffset;
		m_pGame->script.ADDRESS_SCRIPT_POINTER_2 = 0x1982348 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_ACTIVE_THREAD = 0x1848B04 + m_dwLoadOffset; 
		m_pGame->script.ADDRESS_THREADS_ARRAY = 0x1982330 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_THREAD_TICK = 0xBC0330 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_MOUSE_POS_X = 0x1889BB4 + m_dwLoadOffset;
		m_pGame->script.ADDRESS_MOUSE_POS_Y = 0x1889BC0 + m_dwLoadOffset;
		break;
	default:
		Log::Error("This version unsupported");
		return false;
		break;
	}
	return true;
}

DWORD CGameHook::GetBase()
{
	return m_dwLoadOffset;
}

DWORD CGameHook::GetGameVersion()
{
	return m_dwGameVersion;
}

sysArray<GtaThread>* CGameHook::GetThreadsArray()
{
	return reinterpret_cast< sysArray<GtaThread>* >(m_pGame->script.ADDRESS_THREADS_ARRAY);
}

scrThread* CGameHook::GetActiveThread()
{
	return *reinterpret_cast< scrThread** >(m_pGame->script.ADDRESS_ACTIVE_THREAD);
}

void CGameHook::SetActiveThread(scrThread* thread)
{
	*reinterpret_cast< scrThread** >(m_pGame->script.ADDRESS_ACTIVE_THREAD) = thread;
}

DWORD CGameHook::GetHash(char *ThreadName)
{
	DWORD hash;
	ptr call_this = ptr_cast(m_pGame->script.ADDRESS_HASH_GET);
	_asm
	{
		mov eax, ThreadName;
		call call_this;
		mov hash, eax;
	}
	return hash;
}

DWORD CGameHook::GetScriptCount()
{
	return *(DWORD *)(m_pGame->script.ADDRESS_ACTIVE_THREAD);
}

void CGameHook::SetScriptCount(DWORD c)
{
	*(DWORD *)(m_pGame->script.ADDRESS_SCRIPTS_COUNT) = c;
}

DWORD CGameHook::GetThreadID()
{
	return *(DWORD *)(m_pGame->script.ADDRESS_THREAD_ID);
}

void CGameHook::SetThreadID(DWORD id)
{
	*(DWORD *)(m_pGame->script.ADDRESS_THREAD_ID) = id;
}

bool CGameHook::GetMousePos(int *x, int *y)
{
	x = (int *)(m_pGame->script.ADDRESS_MOUSE_POS_X);
	y = (int *)(m_pGame->script.ADDRESS_MOUSE_POS_Y);
	return true;
}

void CGameHook::ThreadTick(scrThread * thread, unsigned int msec)
{
	DWORD fn = m_pGame->script.ADDRESS_THREAD_TICK;
	_asm
	{
		push msec;
		mov ecx, thread;
		call fn;
	}
}

DWORD WINAPI CGameHook::ScriptHookThread(void * p)
{
	while(*(DWORD *)(m_pGame->script.ADDRESS_SCRIPTS_COUNT) == 0) Sleep(1);
	
	CScriptThread * script = (CScriptThread *) p;
	script->AttachGtaThread();

	return 0;
}

void CGameHook::OnD3DCreateDevice(IDirect3DDevice9 * pd3dDevice, HWND hWnd)
{
	Log::Debug("OnCreateDevice");
	if(m_OriginalProc)
	{
		WNDPROC wndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
		SetWindowLong(hWnd, GWL_WNDPROC,(LONG)m_OriginalProc);
		m_OriginalProc = wndProc;
	}

	for(int i = 0; i < D3DMAN_COUNT; i++)
	{
		if(m_pD3DManager[i]) m_pD3DManager[i]->OnCreateDevice(pd3dDevice, hWnd);
	}
}

void CGameHook::OnD3DDraw()
{
	for(int i = 0; i < D3DMAN_COUNT; i++)
	{
		if(m_pD3DManager[i]) m_pD3DManager[i]->OnDraw();
	}
}

void CGameHook::OnD3DBeginDraw()
{
	for(int i = 0; i < D3DMAN_COUNT; i++)
	{
		if(m_pD3DManager[i]) m_pD3DManager[i]->OnBeginDraw();
	}
}

void CGameHook::OnD3DLostDevice()
{
	Log::Debug("OnLostDevice");
	for(int i = 0; i < D3DMAN_COUNT; i++)
	{
		if(m_pD3DManager[i]) m_pD3DManager[i]->OnLostDevice();
	}
}

void CGameHook::OnD3DResetDevice()
{
	Log::Debug("OnResetDevice");
	for(int i = 0; i < D3DMAN_COUNT; i++)
	{
		if(m_pD3DManager[i]) m_pD3DManager[i]->OnResetDevice();
	}
}

void CGameHook::OnD3DRelease()
{
	Log::Debug("OnRelease");
	for(int i = 0; i < D3DMAN_COUNT; i++)
	{
		if(m_pD3DManager[i]) m_pD3DManager[i]->OnRelease();
	}
}

LRESULT CGameHook::CallOriginalWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProc(m_OriginalProc, hWnd, Msg, wParam, lParam);
}