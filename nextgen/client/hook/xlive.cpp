#include <windows.h>
#include "xlive.h"
#include "log/log.h"

// #1: XWSAStartup
int __stdcall XWSAStartup (WORD wVersionRequested, LPWSADATA lpWsaData) 
{ 
	lpWsaData->wVersion = 2;
	return 0;
}

// #2: XWSACleanup
void __stdcall XWSACleanup () 
{

}

// #3: XCreateSocket
SOCKET __stdcall XCreateSocket (int af, int type, int protocol) 
{ 
	return INVALID_SOCKET;
}

// #4: XSockeClose
int __stdcall XSockeClose (SOCKET s) 
{	
	return 0;
}

// #5: XSocketShutdown
int __stdcall XSocketShutdown (SOCKET s, int how) 
{	
	return 0;
}

// #6: XSocketIOCTLSocket
int __stdcall XSocketIOCTLSocket (SOCKET s, long cmd, long * argp) 
{
	return 0;
}

// #7: XSocketSetSockOpt
int __stdcall XSocketSetSockOpt (SOCKET s, int level, int optname, const char *optval, int optlen) 
{
	return 0;
}

// #9: XSocketGetSockName
int __stdcall XSocketGetSockName (SOCKET s, sockaddr_in * name, int * namelen) 
{
	if (namelen && name && *namelen == sizeof (sockaddr_in)) 
		memset (name, 0, sizeof (sockaddr_in));
	return 0;
}

// #11: XSocketBind
SOCKET __stdcall XSocketBind (SOCKET s, sockaddr_in * addr, int addrlen) 
{
	return INVALID_SOCKET;
}

// #12: XSocketConnect
int __stdcall XSocketConnect (SOCKET s, sockaddr_in * addr, int addrlen) 
{
	return 0;
}

// #13: XSocketListen
int __stdcall XSocketListen (SOCKET s, int backlog) 
{ 
	return 0;
}

// #14: XSocketAccept
SOCKET __stdcall XSocketAccept (SOCKET s, sockaddr_in * addr, int addrlen) 
{ 
	return INVALID_SOCKET;
}

// #15: XSocketSelect
int __stdcall XSocketSelect (int n, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval * timeout) 
{ 
	return 0;
}

// #18: XSocketRecv
int __stdcall XSocketRecv (SOCKET s, char * buf, int len, int flags) 
{ 
	return 0;
}

// #20: XSocketRecvFrom
int __stdcall XSocketRecvFrom (SOCKET s, char * buf, int len, int flags, sockaddr_in * from, int *fromlen) 
{ 
	return 0;
}

// #22: XSocketSend
int __stdcall XSocketSend (SOCKET s, char * buf, int len, int flags) 
{
	return 0;
}

// #24: XSocketSendTo
int __stdcall XSocketSendTo (SOCKET s, char * buf, int len, int flags, sockaddr_in * to, int tolen) 
{ 
	return 0;
}

// #26: XSocketInet_Addr
int __stdcall XSocketInet_Addr (char * a) 
{ 
	return 0;
}

// #27: XWSAGetLastError
int __stdcall XWSAGetLastError () 
{
	return WSAENETDOWN; // 0 ?
}

// #38: XSocketNTOHS
WORD __stdcall XSocketNTOHS (WORD n) 
{	
	return ((n&0xFF00) >> 8)|((n&0xFF) << 8);
}

// #39: XSocketNTOHL
DWORD __stdcall XSocketNTOHL (DWORD n) 
{ 
	return ((n&0xFF000000) >> 24)|((n & 0x00FF0000) >> 8)|((n&0x0000FF00) << 8)|((n & 0x000000FF) << 24);
}

// #51: XNetStartup
int __stdcall XNetStartup (void * p) // XNetStartup(XNetStartupParams *)
{ 
	return 0;
}

// #52: XNetCleanup
int __stdcall XNetCleanup () 
{ 
	return 0;
}

// #54: XNetCreateKey
int __stdcall XNetCreateKey (void * pxnkid, void * pxnkey) 
{ 
	return 0;
}

// #55: XNetRegisterKey
int __stdcall XNetRegisterKey (DWORD a1, DWORD a2) 
{ 
	return 0;
}

// #56: XNetUnregisterKey
int __stdcall XNetUnregisterKey (DWORD a) 
{
	return 0;
}

// #57: XNetXnAddrToInAddr
int __stdcall XNetXnAddrToInAddr (DWORD a1, DWORD a2, DWORD * p) 
{
	*p = 0;
	return 0;
}

// #58: XNetServerToInAddr
DWORD __stdcall XNetServerToInAddr (DWORD a1, DWORD a2, DWORD a3) 
{ 
	return 0;
}

// #60: XNetInAddrToXnAddr
DWORD __stdcall XNetInAddrToXnAddr (DWORD a1, DWORD a2, DWORD a3) 
{ 
	return 0;
} 

// #63: XNetUnregisterInAddr
int __stdcall XNetUnregisterInAddr (DWORD a) 
{
	return 0;
}

// #65: XNetConnect
int __stdcall XNetConnect (DWORD a) 
{ 
	return 0;
}

// #66: XNetGetConnectStatus
int __stdcall XNetGetConnectStatus (DWORD a) 
{ 
	return 0;	
}

// #69: XNetQosListen
DWORD __stdcall XNetQosListen (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0; 
}

// #70: XNetQosLookup
DWORD __stdcall XNetQosLookup (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9, DWORD a10, DWORD a11, DWORD a12) 
{ 
	return 0; 
}

// #71: XNetQosServiceLookup
DWORD __stdcall XNetQosServiceLookup (DWORD a1, DWORD a2, DWORD a3) 
{ 
	return 0;
}

// #72: XNetQosRelease
DWORD __stdcall XNetQosRelease (DWORD a) 
{	
	return 0; 
}

// #73: XNetGetTitleXnAddr
DWORD __stdcall XNetGetTitleXnAddr (DWORD * pAddr) 
{
	*pAddr = 0x0100007F;	// 127.0.0.1
	return 4; 
}

// #75: XNetGetEthernetLinkStatus
DWORD __stdcall XNetGetEthernetLinkStatus () 
{ 
	return 1; 
}

// #84: XNetSetSystemLinkPort
DWORD __stdcall XNetSetSystemLinkPort (DWORD a) 
{ 
	return 0; 
}

// #473: XCustomGetLastActionPress
int __stdcall XCustomGetLastActionPress (DWORD a1, DWORD a2, DWORD a3) 
{ 
	return 0;
}

// #651: XNotifyGetNext
int __stdcall XNotifyGetNext (HANDLE hNotification, DWORD dwMsgFilter, DWORD * pdwId, void * pParam) 
{
	return 0;   // no notifications
}

// #652: XNotifyPositionUI
DWORD __stdcall XNotifyPositionUI (DWORD dwPosition) 
{
	return 0;
}

// #1082: XGetOverlappedExtendedError
DWORD __stdcall XGetOverlappedExtendedError (void *a) 
{ 
	return 0;
}

// #1083: XGetOverlappedResult
DWORD __stdcall XGetOverlappedResult (void *a, DWORD * pResult, DWORD bWait) 
{ 
	if (pResult)
		*pResult = 0;	// 0 elements enumerated
	
	return 0;
}

// #5000: XLiveInitialize
int __stdcall XLiveInitialize (DWORD a) // XLiveInitialize(struct _XLIVE_INITIALIZE_INFO *)
{	
	return 0;
}

// #5001: XLiveInput
int __stdcall XLiveInput (DWORD * p) 
{
	p[5] = 0;
	return 1;	// -1 ?
}


// #5002: XLiveRender
int __stdcall XLiveRender () 
{
	return 0;
}

// #5003: XLiveUninitialize
int __stdcall XLiveUninitialize () 
{ 
	return 0;
}

// #5005: XLiveOnCreateDevice
int __stdcall XLiveOnCreateDevice (DWORD a1, DWORD a2) 
{
	return 0;
}

// #5007: XLiveOnResetDevice
int __stdcall XLiveOnResetDevice (DWORD a) 
{
	return 0;
}

// #5008: XHVCreateEngine
int __stdcall XHVCreateEngine (DWORD a1, DWORD a2, void ** ppEngine) 
{ 
    if (ppEngine)
        *ppEngine = NULL;
	return -1;	// disable live voice   
}

// #5022: XLiveGetUpdateInformation
int __stdcall XLiveGetUpdateInformation (DWORD a) 
{
	return -1; // no update
}

// #5024: XLiveUpdateSystem
int __stdcall XLiveUpdateSystem (DWORD a) 
{
	return -1; // no update
}

// #5030: XLivePreTranslateMessage
int __stdcall XLivePreTranslateMessage (DWORD a) 
{
	return 0;
}

// #5031: XLiveSetDebugLevel
int __stdcall XLiveSetDebugLevel (DWORD xdlLevel, DWORD * pxdlOldLevel) 
{ 
	return 0;
}

// #5214: XShowPlayerReviewUI
int __stdcall XShowPlayerReviewUI (DWORD a1, DWORD a2, DWORD a3) 
{
	return 0;
}

// #5215: XShowGuideUI
int __stdcall XShowGuideUI (DWORD a) 
{
	return 1;
}

// #5216: XShowKeyboardUI
int __stdcall XShowKeyboardUI (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8) 
{ 
	return 0;
}

// #5251: XCloseHandle
int __stdcall XCloseHandle (DWORD a) 
{
	return 0;
}

// #5252: XShowGamerCardUI
int __stdcall XShowGamerCardUI (DWORD a1, DWORD a2, DWORD a3) 
{
	return 0;
}

// #5254: XCancelOverlapped
int __stdcall XCancelOverlapped (DWORD a) 
{
	return 0;
}

// #5256: XEnumerate
int __stdcall XEnumerate (HANDLE hEnum, void * pvBuffer, DWORD cbBuffer, DWORD * pcItemsReturned, void * pOverlapped) 
{
	if (pcItemsReturned)
		*pcItemsReturned = 0;
	return 0;	// some error ? 
}

// #5260: XShowSigninUI
int __stdcall XShowSigninUI (DWORD a1, DWORD a2) 
{ 
	return 0;
}

// #5261: XUserGetXUID
int __stdcall XUserGetXUID (DWORD a, DWORD * pXuid) 
{ 
	pXuid[0] = pXuid[1] = 0x10001000; 
	return 0; // ???
}


// #5262: XUserGetSigninState
int __stdcall XUserGetSigninState (DWORD dwUserIndex) 
{
	return 1; // eXUserSigninState_SignedInLocally
}

// #5263: XUserGetName
int __stdcall XUserGetName (DWORD dwUserId, char * pBuffer, DWORD dwBufLen) 
{
	if (dwBufLen < 8)
		return 1;
	memcpy (pBuffer, "FOURMP", 8);
	return 0;
}

// #5264: XUserAreUsersFriends
int __stdcall XUserAreUsersFriends(DWORD dwUserIndex, DWORD * pXuids, DWORD dwXuidCount, DWORD * pResult, void * pOverlapped) 
{
    return ERROR_NOT_LOGGED_ON;
}

// #5265: XUserCheckPrivilege
int __stdcall XUserCheckPrivilege (DWORD user, DWORD priv, PBOOL b) 
{
	*b = false;
	return ERROR_NOT_LOGGED_ON;
}

// #5267: XUserGetSigninInfo
int __stdcall XUserGetSigninInfo (DWORD dwUser, DWORD dwFlags, XUSER_SIGNIN_INFO * pInfo) 
{  
	pInfo->xuidL = pInfo->xuidH = dwFlags != 1 ? (dwUser+1)*0x10001000 : 0; // some arbitrary id for offline user, INVALID_XUID for online user
	if (dwFlags != 1) {
		pInfo->dwInfoFlags = 1;
		pInfo->UserSigninState = 1; // eXUserSigninState_SignedInLocally
		//strcpy (pInfo->szUserName, "FOURMP");
	}
	return 0;
}

// #5270: XNotifyCreateListener
HANDLE __stdcall XNotifyCreateListener (DWORD l, DWORD h) 
{
	return (HANDLE)1; // any non-zero value. (zero treated as fatal error)
}

// #5273: XUserReadGamerpictureByKey
int __stdcall XUserReadGamerpictureByKey (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6) 
{ 
	return 0;
}

// #5275: XShowFriendsUI
int __stdcall XShowFriendsUI (DWORD a) 
{
	return 0;
}

// #5276: XUserSetProperty
int __stdcall XUserSetProperty (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{
	return 0;
}

// #5277: XUserSetContext
int __stdcall XUserSetContext (DWORD a1, DWORD a2, DWORD a3) 
{
	return 0;
}

// #5278: XUserWriteAchievements
DWORD __stdcall XUserWriteAchievements (DWORD a1, DWORD a2, DWORD a3) 
{
	return 0;
}

// #5280: XUserCreateAchievementEnumerator
DWORD __stdcall XUserCreateAchievementEnumerator (DWORD dwTitleId, DWORD dwUserIndex, DWORD xuidL, DWORD xuidHi, DWORD dwDetailFlags, DWORD dwStartingIndex, DWORD cItem, DWORD * pcbBuffer, HANDLE * phEnum) 
{
    if (pcbBuffer)
        *pcbBuffer = 0;
    if (phEnum)
	    *phEnum = INVALID_HANDLE_VALUE;
	return 1;   // return error (otherwise, 0-size buffer will be allocated)
}

// #5281: XUserReadStats
DWORD __stdcall XUserReadStats (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD * pcbResults, DWORD * pResults, void * a8) 
{ 
	if (pcbResults)	
		*pcbResults = 4;
	if (pResults)
		*pResults = 0;
	return 0;
}

// #5284: XUserCreateStatsEnumeratorByRank
DWORD __stdcall XUserCreateStatsEnumeratorByRank (DWORD dwTitleId, DWORD dwRankStart, DWORD dwNumRows, DWORD dwNuStatSpec, void * pSpecs, DWORD * pcbBuffer, PHANDLE phEnum) 
{ 
    if (pcbBuffer)
        *pcbBuffer = 0;
	*phEnum = INVALID_HANDLE_VALUE;
	return 1;
}

// #5286: XUserCreateStatsEnumeratorByXuid
DWORD __stdcall XUserCreateStatsEnumeratorByXuid (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD * pcbBuffer, PHANDLE phEnum) 
{ 
    if (pcbBuffer)
        pcbBuffer = 0;
	*phEnum = INVALID_HANDLE_VALUE;
	return 1;
}

// #5292: XUserSetContextEx
int __stdcall XUserSetContextEx (DWORD dwUserIndex, DWORD dwContextId, DWORD dwContextValue, void * pOverlapped) 
{
	return 0;
}

// #5293: XUserSetPropertyEx
int __stdcall XUserSetPropertyEx (DWORD dwUserIndex, DWORD dwPropertyId, DWORD cbValue, void * pvValue, void * pOverlapped) 
{ 
	return 0;
}

// #5297: XLiveInitializeEx
int __stdcall XLiveInitializeEx (void * pXii, DWORD dwVersion) 
{
	return 0;
}
	
// #5300: XSessionCreate
DWORD __stdcall XSessionCreate (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8) 
{ 
	return -1;
}

// #5303: XStringVerify
DWORD __stdcall XStringVerify (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, WORD * pResult, DWORD a7) 
{
	*pResult = 0;
	return 0;
}

// #5305: XStorageUploadFromMemory
DWORD __stdcall XStorageUploadFromMemory (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0;
}

// #5306: XStorageEnumerate
int __stdcall XStorageEnumerate (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7) 
{ 
	return 0;
}

// #5310: XOnlineStartup
int __stdcall XOnlineStartup () 
{ 
	return 0; 
}

// #5311: XOnlineCleanup
int __stdcall XOnlineCleanup () 
{
	return 0;
}

// #5312: XFriendsCreateEnumerator
DWORD __stdcall XFriendsCreateEnumerator (DWORD a1, DWORD a2, DWORD a3, DWORD a4, HANDLE * phEnum) 
{ 
	*phEnum = INVALID_HANDLE_VALUE;
	return 0; 
}

// #5314: XUserMuteListQuery
int __stdcall XUserMuteListQuery (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{ 
	return 0; 
}

// #5315: XInviteGetAcceptedInfo
int __stdcall XInviteGetAcceptedInfo (DWORD a1, DWORD a2) 
{ 
	return 1; 
}

// #5316: XInviteSend
int __stdcall XInviteSend (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0; 
}

// #5317: XSessionWriteStats
DWORD __stdcall XSessionWriteStats (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6) 
{ 
	return 0; 
}

// #5318: XSessionStart
int __stdcall XSessionStart (DWORD a1, DWORD a2, DWORD a3) 
{
	return 0;
}

// #5319: XSessionSearchEx
DWORD __stdcall XSessionSearchEx (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9, DWORD a10, DWORD a11) 
{ 
	return 0; 
}

// #5322: XSessionModify
DWORD __stdcall XSessionModify (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0; 
}

// #5323: XSessionMigrateHost
DWORD __stdcall XSessionMigrateHost (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{  
	return 0; 
}

// #5324: XOnlineGetNatType
int __stdcall XOnlineGetNatType () 
{ 
	return 0; 
}

// #5325: XSessionLeaveLocal
DWORD __stdcall XSessionLeaveLocal (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{ 
	return 0; 
}

// #5326: XSessionJoinRemote
DWORD __stdcall XSessionJoinRemote (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0; 
}

// #5327: XSessionJoinLocal
DWORD __stdcall XSessionJoinLocal (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0; 
}

// #5328: XSessionGetDetails
DWORD __stdcall XSessionGetDetails (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{ 
	return 0; 
}

// #5329: XSessionFlushStats
int __stdcall XSessionFlushStats (DWORD a1, DWORD a2) 
{ 
	return 0; 
}

// #5330: XSessionDelete
DWORD __stdcall XSessionDelete (DWORD a1, DWORD a2) 
{ 
	return 0; 
}

// #5331: XUserReadProfileSettings
DWORD __stdcall XUserReadProfileSettings (DWORD dwTitleId, DWORD dwUserIndex, DWORD dwNumSettingIds, 
					DWORD * pdwSettingIds, DWORD * pcbResults, XUSER_READ_PROFILE_SETTINGS * pResults, DWORD pOverlapped) 
{
	if (*pcbResults < 1036) {
		*pcbResults = 1036;	// TODO: make correct calculation by IDs.
		return ERROR_INSUFFICIENT_BUFFER;
	}
	memset (pResults, 0, *pcbResults);
	pResults->dwLength = *pcbResults-sizeof (XUSER_READ_PROFILE_SETTINGS);
	pResults->pSettings = (BYTE *)pResults+sizeof (XUSER_READ_PROFILE_SETTINGS);
	return 0;
}

// #5332: XSessionEnd
int __stdcall XSessionEnd (DWORD a1, DWORD a2) 
{	
	return 0;
}

// #5333: XSessionArbitrationRegister
DWORD __stdcall XSessionArbitrationRegister (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7) 
{ 
	return 0; 
}

// #5335: XTitleServerCreateEnumerator
DWORD __stdcall XTitleServerCreateEnumerator (LPCSTR pszServerInfo, DWORD cItem, DWORD * pcbBuffer, PHANDLE phEnum) 
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 1;
}

// #5336: XSessionLeaveRemote
DWORD __stdcall XSessionLeaveRemote (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{ 
	return 0; 
}

// #5337: XUserWriteProfileSettings
DWORD __stdcall XUserWriteProfileSettings (DWORD a1, DWORD a2, DWORD a3, DWORD a4) 
{
	return 0;
}

// #5339: XUserReadProfileSettingsByXuid
DWORD __stdcall XUserReadProfileSettingsByXuid (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9) 
{
	return 0;
}

// #5343: XLiveCalculateSkill
DWORD __stdcall XLiveCalculateSkill (DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) 
{ 
	return 0;
}

// #5344: XStorageBuildServerPath
DWORD __stdcall XStorageBuildServerPath (DWORD dwUserIndex, DWORD StorageFacility, 
		void * pvStorageFacilityInfo, DWORD dwStorageFacilityInfoSize, 
		void * pwszItemName, void * pwszServerPath, DWORD * pdwServerPathLength) 
{ 
	return 0; 
}

// #5345: XStorageDownloadToMemory
DWORD __stdcall XStorageDownloadToMemory (DWORD dwUserIndex, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, void * a6) 
{ 
	return 0; 
}

// #5349: XLiveProtectedVerifyFile
DWORD __stdcall XLiveProtectedVerifyFile (HANDLE hContentAccess, VOID * pvReserved, PCWSTR pszFilePath) 
{
	return 0;
}

// #5350: XLiveContentCreateAccessHandle
DWORD __stdcall XLiveContentCreateAccessHandle (DWORD dwTitleId, void * pContentInfo, 
	DWORD dwLicenseInfoVersion, void * xebBuffer, DWORD dwOffset, HANDLE * phAccess, void * pOverlapped) 
{
	if (phAccess)
		*phAccess = INVALID_HANDLE_VALUE;
	return E_OUTOFMEMORY;	// TODO: fix it
}

// #5352: XLiveContentUninstall
DWORD __stdcall XLiveContentUninstall (void * pContentInfo, void * pxuidFor, void * pInstallCallbackParams) 
{
	return 0;
}

// #5355: XLiveContentGetPath
DWORD __stdcall XLiveContentGetPath (DWORD dwUserIndex, void * pContentInfo, wchar_t * pszPath, DWORD * pcchPath) 
{
	if (pcchPath)
		*pcchPath = 0;
	if (pszPath)
		*pszPath = 0;
	return 0;
}

// #5360: XLiveContentCreateEnumerator
DWORD __stdcall XLiveContentCreateEnumerator (DWORD a1, void * a2, DWORD * pchBuffer, HANDLE * phContent) 
{
	if (phContent)
		*phContent = INVALID_HANDLE_VALUE;
	return 0;
}

// #5361: XLiveContentRetrieveOffersByDate
DWORD __stdcall XLiveContentRetrieveOffersByDate (DWORD dwUserIndex, DWORD dwOffserInfoVersion, 
	SYSTEMTIME * pstStartDate, void * pOffserInfoArray, DWORD * pcOfferInfo, void * pOverlapped) 
{
	if (pcOfferInfo)
		*pcOfferInfo = 0;
	return 0;
} 

// #5365: XShowMarketplaceUI
DWORD __stdcall XShowMarketplaceUI (DWORD dwUserIndex, DWORD dwEntryPoint, ULONGLONG dwOfferId, DWORD dwContentCategories) 
{
	return 1;
}

// #5016: XLivePBufferAllocate
DWORD __stdcall XLivePBufferAllocate (int size, FakeProtectedBuffer ** pBuffer) 
{
	*pBuffer = (FakeProtectedBuffer *)malloc (size+16);
	if (!*pBuffer) {
		Log::Debug ("ERROR: XLivePBufferAllocate unable to allocate %d bytes", size);
		return E_OUTOFMEMORY;
	}

	(*pBuffer)->dwMagick = 0xDEADDEAD;	// some arbitrary number
	(*pBuffer)->dwSize = size;
	return 0;
}

// #5017: XLivePBufferFree
DWORD __stdcall XLivePBufferFree (FakeProtectedBuffer * pBuffer) 
{
	if (pBuffer && pBuffer->dwMagick == 0xDEADDEAD)
		free (pBuffer);
	return 0;
}

// #5295: XLivePBufferSetByteArray
DWORD __stdcall XLivePBufferSetByteArray (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * source, DWORD size) 
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || !source || offset < 0 || offset+size > pBuffer->dwSize)
		return 0;
	memcpy (pBuffer->bData+offset, source, size);
	return 0;
}

// #5294: XLivePBufferGetByteArray
DWORD __stdcall XLivePBufferGetByteArray (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * destination, DWORD size) 
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || !destination || offset < 0 || offset+size > pBuffer->dwSize)
		return 0;
	memcpy (destination, pBuffer->bData+offset, size);
	return 0;
}

// #5019: XLivePBufferSetByte
DWORD __stdcall XLivePBufferSetByte (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE value) 
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || offset < 0 || offset > pBuffer->dwSize)
		return 0;
	pBuffer->bData[offset] = value;
	return 0;
}

// #5018: XLivePBufferGetByte
DWORD __stdcall XLivePBufferGetByte (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * value) 
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || !value || offset < 0 || offset > pBuffer->dwSize)
		return 0;
	*value = pBuffer->bData[offset];
	return 0;
}

// #5020: XLivePBufferGetDWORD
DWORD __stdcall XLivePBufferGetDWORD (FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD * pdwValue) 
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || dwOffset < 0 || dwOffset > pBuffer->dwSize-4 || !pdwValue)
		return 0;
	*pdwValue = *(DWORD *)(pBuffer->bData+dwOffset);
	return 0;
}

// #5021: XLivePBufferSetDWORD
DWORD __stdcall XLivePBufferSetDWORD (FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD dwValue ) 
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || dwOffset < 0 || dwOffset > pBuffer->dwSize-4)
		return 0;
	*(DWORD *)(pBuffer->bData+dwOffset) = dwValue;
	return 0;
}

// #5026: XLiveSetSponsorToken
DWORD __stdcall XLiveSetSponsorToken (LPCWSTR pwszToken, DWORD dwTitleId) 
{
    return S_OK;
}


// #5036: XLiveCreateProtectedDataContext
DWORD __stdcall XLiveCreateProtectedDataContext (DWORD * dwType, PHANDLE pHandle) 
{
	if (pHandle)
		*pHandle = (HANDLE)1;
	return 0;
}

// #5037: XLiveQueryProtectedDataInformation
DWORD __stdcall XLiveQueryProtectedDataInformation (HANDLE h, DWORD * p) 
{
	return 0;
}

// #5038: XLiveCloseProtectedDataContext
DWORD __stdcall XLiveCloseProtectedDataContext (HANDLE h) 
{
	return 0;
}

// #5035: XLiveUnprotectData
DWORD __stdcall XLiveUnprotectData (BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE * ph) 
{
	if (!pDataSize || !ph)	// invalid parameter
		return E_FAIL;
	*ph = (HANDLE)1;
	if (dwInDataSize > 12)
		dwInDataSize = 12;	// RF:G workaround
	if (!pOutBuffer || *pDataSize < dwInDataSize) {
		*pDataSize = dwInDataSize;
		return ERROR_INSUFFICIENT_BUFFER;
	}
	*pDataSize = dwInDataSize;
	memcpy (pOutBuffer, pInBuffer, dwInDataSize);
	return 0;
}

// #5034: XLiveProtectData
DWORD __stdcall XLiveProtectData (BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h) 
{
	*pDataSize = dwInDataSize;
	if (*pDataSize >= dwInDataSize && pOutBuffer)
		memcpy (pOutBuffer, pInBuffer, dwInDataSize);
	return 0;
}

// #5367
DWORD __stdcall xlive_5367 (HANDLE a1, DWORD a2, DWORD a3, BYTE *a4, DWORD a5) 
{
    return 1;
}

// #5372
DWORD __stdcall xlive_5372 (HANDLE a1, DWORD a2, DWORD a3, DWORD a4, BYTE *a5, HANDLE a6) 
{
    return 1;
}