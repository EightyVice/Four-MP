#pragma once

struct XUSER_SIGNIN_INFO 
{
   DWORD	xuidL;
   DWORD	xuidH;
   DWORD    dwInfoFlags;
   DWORD	UserSigninState;
   DWORD    dwGuestNumber;
   DWORD    dwSponsorUserIndex;
   CHAR     szUserName[16];
};

struct XUSER_READ_PROFILE_SETTINGS 
{
	DWORD	dwLength;
	BYTE *	pSettings;
};

struct FakeProtectedBuffer 
{
	DWORD	dwMagick;	
	DWORD	dwSize;
	DWORD	__fill[2]; // To match buffer size in Rick's wrapper
	BYTE	bData[4];
};

int __stdcall XWSAStartup (WORD wVersionRequested, LPWSADATA lpWsaData); 
void __stdcall XWSACleanup (); 
SOCKET __stdcall XCreateSocket (int af, int type, int protocol); 
int __stdcall XSockeClose (SOCKET s); 
int __stdcall XSocketShutdown (SOCKET s, int how); 
int __stdcall XSocketIOCTLSocket (SOCKET s, long cmd, long * argp); 
int __stdcall XSocketSetSockOpt (SOCKET s, int level, int optname, const char *optval, int optlen); 
int __stdcall XSocketGetSockName (SOCKET s, sockaddr_in * name, int * namelen); 
SOCKET __stdcall XSocketBind (SOCKET s, sockaddr_in * addr, int addrlen); 
int __stdcall XSocketConnect (SOCKET s, sockaddr_in * addr, int addrlen); 
int __stdcall XSocketListen (SOCKET s, int backlog); 
SOCKET __stdcall XSocketAccept (SOCKET s, sockaddr_in * addr, int addrlen); 
int __stdcall XSocketSelect (int n, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval * timeout); 
int __stdcall XSocketRecv (SOCKET s, char * buf, int len, int flags); 
int __stdcall XSocketRecvFrom (SOCKET s, char * buf, int len, int flags, sockaddr_in * from, int *fromlen); 
int __stdcall XSocketSend (SOCKET s, char * buf, int len, int flags); 
int __stdcall XSocketSendTo (SOCKET s, char * buf, int len, int flags, sockaddr_in * to, int tolen); 
int __stdcall XSocketInet_Addr (char *); 
int __stdcall XWSAGetLastError (); 
WORD __stdcall XSocketNTOHS (WORD n); 
DWORD __stdcall XSocketNTOHL (DWORD n); 
int __stdcall XNetStartup (void * p); // XNetStartup(XNetStartupParams *)
int __stdcall XNetCleanup (); 
int __stdcall XNetCreateKey (void * pxnkid, void * pxnkey); 
int __stdcall XNetRegisterKey (DWORD a1, DWORD a2); 
int __stdcall XNetUnregisterKey (DWORD a); 
int __stdcall XNetXnAddrToInAddr (DWORD a1, DWORD a2, DWORD * p); 
DWORD __stdcall XNetServerToInAddr (DWORD a1, DWORD a2, DWORD a3); 
DWORD __stdcall XNetInAddrToXnAddr (DWORD a1, DWORD a2, DWORD a3); 
int __stdcall XNetUnregisterInAddr (DWORD a); 
int __stdcall XNetConnect (DWORD a); 
int __stdcall XNetGetConnectStatus (DWORD a); 
DWORD __stdcall XNetQosListen (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
DWORD __stdcall XNetQosLookup (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9, DWORD a10, DWORD a11, DWORD a12); 
DWORD __stdcall XNetQosServiceLookup (DWORD a1, DWORD a2, DWORD a3); 
DWORD __stdcall XNetQosRelease (DWORD a); 
DWORD __stdcall XNetGetTitleXnAddr (DWORD * pAddr); 
DWORD __stdcall XNetGetEthernetLinkStatus (); 
DWORD __stdcall XNetSetSystemLinkPort (DWORD a); 
int __stdcall XCustomGetLastActionPress (DWORD a1, DWORD a2, DWORD a3); 
int __stdcall XNotifyGetNext (HANDLE hNotification, DWORD dwMsgFilter, DWORD * pdwId, void * pParam); 
DWORD __stdcall XNotifyPositionUI (DWORD dwPosition); 
DWORD __stdcall XGetOverlappedExtendedError (void *a); 
DWORD __stdcall XGetOverlappedResult (void *a, DWORD * pResult, DWORD bWait); 
int __stdcall XLiveInitialize (DWORD a); // XLiveInitialize(struct _XLIVE_INITIALIZE_INFO *)
int __stdcall XLiveInput (DWORD * p); 
int __stdcall XLiveRender (); 
int __stdcall XLiveUninitialize (); 
int __stdcall XLiveOnCreateDevice (DWORD a1, DWORD a2); 
int __stdcall XLiveOnResetDevice (DWORD a); 
int __stdcall XHVCreateEngine (DWORD a1, DWORD a2, void ** ppEngine); 
int __stdcall XLiveGetUpdateInformation (DWORD a); 
int __stdcall XLiveUpdateSystem (DWORD a); 
int __stdcall XLivePreTranslateMessage (DWORD a); 
int __stdcall XLiveSetDebugLevel (DWORD xdlLevel, DWORD * pxdlOldLevel); 
int __stdcall XShowPlayerReviewUI (DWORD a1, DWORD a2, DWORD a3); 
int __stdcall XShowGuideUI (DWORD a); 
int __stdcall XShowKeyboardUI (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8); 
int __stdcall XCloseHandle (DWORD a); 
int __stdcall XShowGamerCardUI (DWORD a1, DWORD a2, DWORD a3); 
int __stdcall XCancelOverlapped (DWORD a); 
int __stdcall XEnumerate (HANDLE hEnum, void * pvBuffer, DWORD cbBuffer, DWORD * pcItemsReturned, void * pOverlapped); 
int __stdcall XShowSigninUI (DWORD a1, DWORD a2); 
int __stdcall XUserGetXUID (DWORD a, DWORD * pXuid); 
int __stdcall XUserGetSigninState (DWORD dwUserIndex); 
int __stdcall XUserGetName (DWORD dwUserId, char * pBuffer, DWORD dwBufLen); 
int __stdcall XUserAreUsersFriends(DWORD dwUserIndex, DWORD * pXuids, DWORD dwXuidCount, DWORD * pResult, void * pOverlapped); 
int __stdcall XUserCheckPrivilege (DWORD user, DWORD priv, PBOOL b); 
int __stdcall XUserGetSigninInfo (DWORD dwUser, DWORD dwFlags, XUSER_SIGNIN_INFO * pInfo); 
HANDLE __stdcall XNotifyCreateListener (DWORD l, DWORD h); 
int __stdcall XUserReadGamerpictureByKey (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6); 
int __stdcall XShowFriendsUI (DWORD a); 
int __stdcall XUserSetProperty (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
int __stdcall XUserSetContext (DWORD a1, DWORD a2, DWORD a3); 
DWORD __stdcall XUserWriteAchievements (DWORD a1, DWORD a2, DWORD a3); 
DWORD __stdcall XUserCreateAchievementEnumerator (DWORD dwTitleId, DWORD dwUserIndex, DWORD xuidL, DWORD xuidHi, DWORD dwDetailFlags, DWORD dwStartingIndex, DWORD cItem, DWORD * pcbBuffer, HANDLE * phEnum); 
DWORD __stdcall XUserReadStats (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD * pcbResults, DWORD * pResults, void * a8); 
DWORD __stdcall XUserCreateStatsEnumeratorByRank (DWORD dwTitleId, DWORD dwRankStart, DWORD dwNumRows, DWORD dwNuStatSpec, void * pSpecs, DWORD * pcbBuffer, PHANDLE phEnum); 
DWORD __stdcall XUserCreateStatsEnumeratorByXuid (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD * pcbBuffer, PHANDLE phEnum); 
int __stdcall XUserSetContextEx (DWORD dwUserIndex, DWORD dwContextId, DWORD dwContextValue, void * pOverlapped); 
int __stdcall XUserSetPropertyEx (DWORD dwUserIndex, DWORD dwPropertyId, DWORD cbValue, void * pvValue, void * pOverlapped); 
int __stdcall XLiveInitializeEx (void * pXii, DWORD dwVersion); 
DWORD __stdcall XSessionCreate (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8); 
DWORD __stdcall XStringVerify (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, WORD * pResult, DWORD a7); 
DWORD __stdcall XStorageUploadFromMemory (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
int __stdcall XStorageEnumerate (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7); 
int __stdcall XOnlineStartup (); 
int __stdcall XOnlineCleanup (); 
DWORD __stdcall XFriendsCreateEnumerator (DWORD a1, DWORD a2, DWORD a3, DWORD a4, HANDLE * phEnum); 
int __stdcall XUserMuteListQuery (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
int __stdcall XInviteGetAcceptedInfo (DWORD a1, DWORD a2); 
int __stdcall XInviteSend (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
DWORD __stdcall XSessionWriteStats (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6); 
int __stdcall XSessionStart (DWORD a1, DWORD a2, DWORD a3); 
DWORD __stdcall XSessionSearchEx (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9, DWORD a10, DWORD a11); 
DWORD __stdcall XSessionModify (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
DWORD __stdcall XSessionMigrateHost (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
int __stdcall XOnlineGetNatType (); 
DWORD __stdcall XSessionLeaveLocal (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
DWORD __stdcall XSessionJoinRemote (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
DWORD __stdcall XSessionJoinLocal (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
DWORD __stdcall XSessionGetDetails (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
int __stdcall XSessionFlushStats (DWORD a1, DWORD a2); 
DWORD __stdcall XSessionDelete (DWORD a1, DWORD a2); 
DWORD __stdcall XUserReadProfileSettings (DWORD dwTitleId, DWORD dwUserIndex, DWORD dwNumSettingIds, 
					DWORD * pdwSettingIds, DWORD * pcbResults, XUSER_READ_PROFILE_SETTINGS * pResults, DWORD pOverlapped); 
int __stdcall XSessionEnd (DWORD a1, DWORD a2); 
DWORD __stdcall XSessionArbitrationRegister (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7); 
DWORD __stdcall XTitleServerCreateEnumerator (LPCSTR pszServerInfo, DWORD cItem, DWORD * pcbBuffer, PHANDLE phEnum); 
DWORD __stdcall XSessionLeaveRemote (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
DWORD __stdcall XUserWriteProfileSettings (DWORD a1, DWORD a2, DWORD a3, DWORD a4); 
DWORD __stdcall XUserReadProfileSettingsByXuid (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9); 
DWORD __stdcall XLiveCalculateSkill (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5); 
DWORD __stdcall XStorageBuildServerPath (DWORD dwUserIndex, DWORD StorageFacility, 
		void * pvStorageFacilityInfo, DWORD dwStorageFacilityInfoSize, 
		void * pwszItemName, void * pwszServerPath, DWORD * pdwServerPathLength); 
DWORD __stdcall XStorageDownloadToMemory (DWORD dwUserIndex, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, void * a6); 
DWORD __stdcall XLiveProtectedVerifyFile (HANDLE hContentAccess, VOID * pvReserved, PCWSTR pszFilePath); 
DWORD __stdcall XLiveContentCreateAccessHandle (DWORD dwTitleId, void * pContentInfo, 
	DWORD dwLicenseInfoVersion, void * xebBuffer, DWORD dwOffset, HANDLE * phAccess, void * pOverlapped); 
DWORD __stdcall XLiveContentUninstall (void * pContentInfo, void * pxuidFor, void * pInstallCallbackParams); 
DWORD __stdcall XLiveContentGetPath (DWORD dwUserIndex, void * pContentInfo, wchar_t * pszPath, DWORD * pcchPath); 
DWORD __stdcall XLiveContentCreateEnumerator (DWORD a1, void * a2, DWORD * pchBuffer, HANDLE * phContent); 
DWORD __stdcall XLiveContentRetrieveOffersByDate (DWORD dwUserIndex, DWORD dwOffserInfoVersion, 
	SYSTEMTIME * pstStartDate, void * pOffserInfoArray, DWORD * pcOfferInfo, void * pOverlapped); 
DWORD __stdcall XShowMarketplaceUI (DWORD dwUserIndex, DWORD dwEntryPoint, ULONGLONG dwOfferId, DWORD dwContentCategories); 
DWORD __stdcall XLivePBufferAllocate (int size, FakeProtectedBuffer ** pBuffer); 
DWORD __stdcall XLivePBufferFree (FakeProtectedBuffer * pBuffer); 
DWORD __stdcall XLivePBufferSetByteArray (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * source, DWORD size); 
DWORD __stdcall XLivePBufferGetByteArray (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * destination, DWORD size); 
DWORD __stdcall XLivePBufferSetByte (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE value); 
DWORD __stdcall XLivePBufferGetByte (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * value); 
DWORD __stdcall XLivePBufferGetDWORD (FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD * pdwValue); 
DWORD __stdcall XLivePBufferSetDWORD (FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD dwValue ); 
DWORD __stdcall XLiveSetSponsorToken (LPCWSTR pwszToken, DWORD dwTitleId); 
DWORD __stdcall XLiveCreateProtectedDataContext (DWORD * dwType, PHANDLE pHandle); 
DWORD __stdcall XLiveQueryProtectedDataInformation (HANDLE h, DWORD * p); 
DWORD __stdcall XLiveCloseProtectedDataContext (HANDLE h); 
DWORD __stdcall XLiveUnprotectData (BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE * ph); 
DWORD __stdcall XLiveProtectData (BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h); 
DWORD __stdcall xlive_5367 (HANDLE a1, DWORD a2, DWORD a3, BYTE *a4, DWORD a5); 
DWORD __stdcall xlive_5372 (HANDLE a1, DWORD a2, DWORD a3, DWORD a4, BYTE *a5, HANDLE a6);