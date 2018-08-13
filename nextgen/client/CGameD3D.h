#pragma once
#include "./hook/CD3DManager.h"

class CGameD3D : public CD3DManager
{
public:
	CGameD3D();
	~CGameD3D();

	void OnCreateDevice(IDirect3DDevice9 *, HWND);
	void OnLostDevice();
	void OnResetDevice();
	void OnDraw();
	void OnBeginDraw();
	void OnRelease();

private:
};