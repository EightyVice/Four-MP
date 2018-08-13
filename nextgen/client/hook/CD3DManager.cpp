#include "CD3DManager.h"	

CD3DManager::CD3DManager()
{
	m_pd3dDevice = NULL;
}

CD3DManager::~CD3DManager()
{

}

void CD3DManager::OnCreateDevice(IDirect3DDevice9 * pd3dDevice, HWND)
{
	m_pd3dDevice = pd3dDevice;
}