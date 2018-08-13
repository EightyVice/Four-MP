#include "d3d9hook.h"


void DetourFunc(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len+5);
	DWORD dwback;

	VirtualProtect(src, len, PAGE_READWRITE, &dwback);

	memcpy(jmp, src, len);	jmp += len;
	
	jmp[0] = 0xE9;
	*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

	VirtualProtect(src, len, dwback, &dwback);
}

IDirect3D9 *APIENTRY hkDirect3DCreate9(UINT SDKVersion)
{
	IDirect3D9 *d3dint = Direct3DCreate9(SDKVersion);
	if( d3dint != NULL )
	{
		hkIDirect3D9 *ret = new hkIDirect3D9(&d3dint);
		Log::Debug(L"Direct3DCreate9(%i) succeeded...", SDKVersion);
		Log::Debug(L"Hooked Direct3D9 interface: 0x%x -> 0x%x", ret->m_pD3Dint, ret);
	}
	else
		Log::Debug(L"Direct3DCreate9(%i) failed...", SDKVersion);
	
	return d3dint;
}
