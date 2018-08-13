#include "CGameD3D.h"

CGameD3D::CGameD3D() : CD3DManager()
{

}

CGameD3D::~CGameD3D()
{

}

void CGameD3D::OnCreateDevice(IDirect3DDevice9 * pd3dDevice, HWND hWnd)
{
	CD3DManager::OnCreateDevice(pd3dDevice, hWnd);
}

void CGameD3D::OnLostDevice()
{

}

void CGameD3D::OnResetDevice()
{

}

void CGameD3D::OnDraw()
{

}

void CGameD3D::OnBeginDraw()
{

}

void CGameD3D::OnRelease()
{

}
