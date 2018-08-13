#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "crc.h"
#include "check.h"

extern bool cheats;

int CheckSum()
{
	bool ok = 1;
	int argc = 3;
	_TCHAR* argv[3] = { L"\0", L"common\\data\\handling.dat\0", L"common\\data\\WeaponInfo.xml\0" };
	int right[2] = { 0x3f19c08a, 0x3a5755dd };
	for (int i = 1; i < argc; i++)
	{
		HANDLE hfile = CreateFile(argv[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (hfile == INVALID_HANDLE_VALUE) continue;
		crc32 crc;
		char data[512];
		DWORD len;
		while(ReadFile(hfile, data, 512, &len, NULL) && len) crc.ProcessCRC(data, len);
		if(crc.m_crc32 != right[i-1]) ok = 0;
		CloseHandle(hfile);
	}
	return ok;
}

BOOL SearchFiles(LPCTSTR lpszFileName, LPSEARCHFUNC lpSearchFunc, BOOL bInnerFolders = TRUE)
{
    LPTSTR part;
    wchar_t tmp[MAX_PATH]; // временный массив
    wchar_t name[MAX_PATH];

    HANDLE hSearch = NULL;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    // сначало поиск внутри вложенных папках ...
    if(bInnerFolders)
    {
        if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
        wcscpy(name, part);
        wcscpy(part, L"*.*");

        // если папки существуют, то делаем поиск
        wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
        if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
        do
        {
            // в каждой папке есть две папки с именами "." и ".."
            // и эти папки мы не трогаем

            // пропускаем папки "." и ".."
            if (!wcsncmp(wfd.cFileName, L".", 1) || !wcsncmp(wfd.cFileName, L"..", 2))            
            continue;
        
            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // если мы нашли папку
            {
                wchar_t next[MAX_PATH];
                if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
                wcscpy(part, wfd.cFileName);
                wcscat(next, L"\\");
                wcscat(next, name);

                SearchFiles(next, lpSearchFunc, TRUE);
            }
        }
        while (FindNextFile(hSearch, &wfd)); // ищем следующий файл

        FindClose (hSearch); // заканчиваем поиск
    }

    if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE) 
        return TRUE; // в противном случае выходим
    do
    if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // если мы нашли файл
    {
        wchar_t file[MAX_PATH];
        if(GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
        wcscpy(part, wfd.cFileName);

        lpSearchFunc(file);
    }
    while (FindNextFile(hSearch, &wfd)); // ищем следующий файл
    FindClose (hSearch); // заканчиваем поиск

    return TRUE;
}

void CheckASI(LPCTSTR fn)
{
	LPWSTR path = L"\0";
	GetCurrentDirectory(MAX_PATH, path);
	cheats = 1;
}

void CheckDLL(LPCTSTR fn)
{
	bool nt = 0;
	LPWSTR path = L"\0";
	GetCurrentDirectory(MAX_PATH, path);
	wchar_t fmp[MAX_PATH];

	wchar_t dlls[8][64] = { L"1911.dll", L"binkw32.dll", L"FirewallInstallHelper.dll",
		L"GameuxInstallHelper.dll", L"GTAIVGDF.dll", L"LiveTokenHelper.dll",
		L"Paul.dll", L"xlive.dll"	};

	for(int i = 0; i < sizeof(dlls); i++)
	{
		swprintf(fmp, L"%s%s", path, dlls[i]);
		if(wcscmp(fmp, fn) == 0)
		{
			nt = 1;
		}
	}
	if(nt == 0)
	{
		cheats = 1;
	}
}