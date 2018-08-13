#pragma once
#include "../d3d9/d3d9.h"

class CD3DManager
{
public:
	CD3DManager();
	~CD3DManager();

	virtual void OnCreateDevice(IDirect3DDevice9 *, HWND) = 0;
	virtual void OnLostDevice() = 0;
	virtual void OnResetDevice() = 0;
	virtual void OnDraw() = 0;
	virtual void OnBeginDraw() = 0;
	virtual void OnRelease() = 0;

protected:
	IDirect3DDevice9 * m_pd3dDevice;
};