#pragma once

IDirect3D9* WINAPI Direct3DCreate9 (UINT SDKVersion);

void InitInstance(HANDLE hModule);
void ExitInstance(void);
void LoadOriginalDll(void);