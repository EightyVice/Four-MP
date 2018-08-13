/*	Direct3D9 Interface */

#include <windows.h>
#include "../Hook/window.h"
#include "d3d9hook.h"
#include "gui.h"
#include "../ChatManager.h"

extern LPD3DXFONT fFMP;
//extern LPDIRECT3DTEXTURE9 g_Texture;
//extern ID3DXSprite *g_Sprite;
extern FMPGUI Gui;
extern ChatManager chat;

HRESULT CreateD3DXFont( LPDIRECT3DDEVICE9 dDev, LPD3DXFONT* ppd3dxFont, TCHAR* pstrFont, DWORD dwSize, bool bold, bool Italic )
{
    HRESULT hr;
    LPD3DXFONT pd3dxFontNew = NULL;
    HDC hDC;
    int nHeight;

    hDC = GetDC( NULL );
    nHeight = -MulDiv( dwSize, GetDeviceCaps(hDC, LOGPIXELSY), 72 );
    ReleaseDC( NULL, hDC );

    hr = D3DXCreateFont( dDev, nHeight, 0, bold*FW_BOLD, 0,	Italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pstrFont, &pd3dxFontNew);

    if( SUCCEEDED( hr ) )
        *ppd3dxFont = pd3dxFontNew;

    return hr;
}

HRESULT APIENTRY hkIDirect3D9::QueryInterface(REFIID riid,  void **ppvObj)
{
	return m_pD3Dint->QueryInterface(riid,  ppvObj);
}

ULONG APIENTRY hkIDirect3D9::AddRef()
{
	return m_pD3Dint->AddRef();
}

HRESULT APIENTRY hkIDirect3D9::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pD3Dint->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pD3Dint->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
	return m_pD3Dint->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
	return m_pD3Dint->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed)
{
	return m_pD3Dint->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, /*Windowed*/1);
}

HRESULT APIENTRY hkIDirect3D9::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface)
{
	HRESULT hRet = m_pD3Dint->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	
	if( SUCCEEDED(hRet) )
	{
		hkIDirect3DDevice9 *ret = new hkIDirect3DDevice9(ppReturnedDeviceInterface, pPresentationParameters, this);
		Log::Debug(L"Hooked Direct3D9 device: 0x%x -> 0x%x", ret->m_pD3Ddev, ret);

		gameProc = (WNDPROC)GetWindowLong(hFocusWindow,GWL_WNDPROC);
		SetWindowLong(hFocusWindow,GWL_WNDPROC,(LONG)DefWndProc);
		Log::Debug(L"Set window");

		Gui.Load(ret->m_pD3Ddev);
		Log::Debug(L"Save Device");
		
		//clientstate.input = InputStateGui;

		if(fFMP == NULL)
		{
			CreateD3DXFont(ret->m_pD3Ddev, &fFMP, L"Arial", 14, 1, 0);
			chat.CreateChatFont(ret->m_pD3Ddev);
			//D3DXCreateTextureFromFile(ret->m_pD3Ddev, "mousecursorhud.png", &g_Texture);
			//D3DXCreateSprite(ret->m_pD3Ddev, &g_Sprite);
			/*D3DXCreateTextureFromFileEx( ret->m_pD3Ddev, "mousecursorhud.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT,
				D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),NULL, NULL, &g_Texture);*/
		}
	}
	return hRet;
}

HRESULT APIENTRY hkIDirect3D9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
	return m_pD3Dint->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

UINT APIENTRY hkIDirect3D9::GetAdapterCount()
{
	return m_pD3Dint->GetAdapterCount();
}

HRESULT APIENTRY hkIDirect3D9::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE *pMode)
{
	return m_pD3Dint->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT APIENTRY hkIDirect3D9::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier)
{
	return m_pD3Dint->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT APIENTRY hkIDirect3D9::GetAdapterModeCount(UINT Adapter,D3DFORMAT Format)
{
	return m_pD3Dint->GetAdapterModeCount(Adapter, Format);
}

HMONITOR APIENTRY hkIDirect3D9::GetAdapterMonitor(UINT Adapter)
{
	return m_pD3Dint->GetAdapterMonitor(Adapter);
}

HRESULT APIENTRY hkIDirect3D9::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps)
{
	return m_pD3Dint->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HRESULT APIENTRY hkIDirect3D9::RegisterSoftwareDevice(void *pInitializeFunction)
{
	return m_pD3Dint->RegisterSoftwareDevice(pInitializeFunction);
}

ULONG APIENTRY hkIDirect3D9::Release()
{
	return m_pD3Dint->Release();
}