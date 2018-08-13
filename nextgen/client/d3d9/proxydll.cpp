#include <windows.h>

#include "d3d9.h"
#include "myIDirect3D9.h"
#include "myIDirect3DDevice9.h"
#include "myIDirect3DSwapChain9.h"
#include "proxydll.h"
#include "log/log.h"
#include "../main.h"

myIDirect3DSwapChain9 * gl_pmyIDirect3DSwapChain9;
myIDirect3DDevice9 * gl_pmyIDirect3DDevice9;
myIDirect3D9 * gl_pmyIDirect3D9;
HINSTANCE gl_hOriginalDll;
HINSTANCE gl_hThisInstance;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{   
    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: 
		Start(hModule);
		InitInstance(hModule); 
		break;
	case DLL_PROCESS_DETACH: 
		ExitInstance(); 
		Close(); 
		break;
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	}
    return TRUE;
}

IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hOriginalDll) LoadOriginalDll(); 
	
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type) GetProcAddress( gl_hOriginalDll, "Direct3DCreate9");
    
	if (!D3DCreate9_fn) 
    {
        Log::Debug("D3D9: Pointer to original D3DCreate9 function not received ERROR ****");
        ExitProcess(0);
    }
	
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);
	gl_pmyIDirect3D9 = new myIDirect3D9(pIDirect3D9_orig);
	
	return gl_pmyIDirect3D9;
}

void InitInstance(HANDLE hModule) 
{
	Log::Debug("D3D9: InitInstance called.");
	
	gl_hOriginalDll = NULL;
	gl_hThisInstance = NULL;
	gl_pmyIDirect3D9 = NULL;
	gl_pmyIDirect3DDevice9 = NULL;
	gl_pmyIDirect3DSwapChain9 = NULL;
	
	gl_hThisInstance = (HINSTANCE)hModule;
}

void LoadOriginalDll(void)
{
	if (gl_hOriginalDll) return;

    char buffer[MAX_PATH];
    
	GetSystemDirectoryA(buffer,MAX_PATH);
	strcat_s(buffer, MAX_PATH, "\\d3d9.dll");
	
	gl_hOriginalDll = LoadLibraryA(buffer);

	if (!gl_hOriginalDll)
	{
		Log::Debug("D3D9: Original d3d9.dll not loaded ERROR ****");
		ExitProcess(0); 
	}
}

void ExitInstance() 
{    
    Log::Debug("D3D9: ExitInstance called.");
	
	if (gl_hOriginalDll)
	{
		FreeLibrary(gl_hOriginalDll);
	    gl_hOriginalDll = NULL;  
	}
}

