#pragma once

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>

#include "d3d9int.h"
#include "d3d9dev.h"
#include "d3d9tex.h"

#include "../../../Shared/logging/log.h"

typedef IDirect3D9 *(APIENTRY *tDirect3DCreate9)(UINT);
extern tDirect3DCreate9 oDirect3DCreate9;

void DetourFunc(BYTE *src, const BYTE *dst, const int len);
IDirect3D9 *APIENTRY hkDirect3DCreate9(UINT SDKVersion);