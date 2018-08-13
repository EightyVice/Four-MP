#include "CConfig.h"

CConfig::CConfig()
{
	m_bChanged = false;
}

CConfig::CConfig(char * pszFileName)
{
	m_bChanged = false;
	if(pszFileName)
	{
		this->LoadConfig(pszFileName);
	}
}

CConfig::~CConfig()
{
	if(m_bChanged)
	{
		this->SaveConfig();
	}
}

bool CConfig::LoadConfig(char * pszFileName)
{
	strcpy(m_pszConfigName, pszFileName);
	FILE * fileHandle = fopen(pszFileName, "r");
	if(!fileHandle) return false;

	wchar_t pszTmp[512];
	while(!feof(fileHandle))
	{
		fgetws(pszTmp, 512, fileHandle);

		wchar_t * pszKey = new wchar_t[128];
		memset(pszKey, 0, sizeof(wchar_t) * 128);

		wchar_t * pszValue = new wchar_t[256];
		memset(pszValue, 0, sizeof(wchar_t) * 256);

		int iLen = wcslen(pszTmp);
		int iCursor = 0;
		bool bWriteValue = false;

		for(int i = 0; i < iLen; i++)
		{
			if(pszTmp[i] == L'=')
			{
				if(!bWriteValue) 
				{
					bWriteValue = true;
					int j = wcslen(pszKey) - 1;
					while(pszKey[j] <= 32 && j != 0)
					{
						pszKey[j] = 0;
						j--;
					}
					iCursor = 0;
					if(j == 0) break;
					continue;
				}
			}
			if(pszTmp[i] == L';' || pszTmp[i] == L'\n' || pszTmp[i] == L'\r' || i + 1 == iLen) 
			{
				iCursor = 0;
				if(wcslen(pszValue) == 0) 
				{
					delete pszKey;
					delete pszValue;
				}
				else
				{
					int j = wcslen(pszValue) - 1;
					while(pszValue[j] <= 32 && j != 0)
					{
						pszValue[j] = 0;
						j--;
					}
					if(j != -1)
					{
						m_mKeyValues[pszKey] = pszValue;
					}
				}
				pszKey = NULL;
				pszValue = NULL;
				break;
			}
			if(pszTmp[i] <= 32 && iCursor == 0)
			{
				continue;
			}
			else
			{
				if(bWriteValue)
					pszValue[iCursor] = pszTmp[i];
				else
					pszKey[iCursor] = pszTmp[i];
				iCursor++;
			}
		}
		memset(pszTmp, 0, sizeof(wchar_t) * 512);
	}

	fclose(fileHandle);
	return true;
}

bool CConfig::SaveConfig()
{
	FILE * fileHandle = fopen(m_pszConfigName, "w");
	if(!fileHandle) return false;

	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin();
    while(it != m_mKeyValues.end())
    {
		fwprintf(fileHandle, L"%s = %s\n", it->first, it->second);
        it++;
    }

	fclose(fileHandle);
	return true;
}

void CConfig::Dump()
{
	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin();
    while(it != m_mKeyValues.end())
    {
		wprintf(L"'%s' = '%s'\n", it->first, it->second);
        it++;
    }
}

bool CConfig::GetBoolValue(const wchar_t * pszKey, const bool bDefValue)
{
	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin();
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			return it->second[0] != L'0';
			break;
		}
        it++;
    }
    return bDefValue;
}

int CConfig::GetIntValue(const wchar_t * pszKey, const int iDefValue)
{
	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin();
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			return _wtoi(it->second);
			break;
		}
        it++;
    }
    return iDefValue;
}

float CConfig::GetFloatValue(const wchar_t * pszKey, const float fDefValue)
{
	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin(); 
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			return (float)_wtof(it->second);
			break;
		}
        it++;
    }
    return fDefValue;
}

wchar_t * CConfig::GetStringValue(const wchar_t * pszKey, const wchar_t * pszDefValue)
{
	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin(); 
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			return (wchar_t *)it->second;
			break;
		}
        it++;
    }
    return (wchar_t *)pszDefValue;
}

void CConfig::SetBoolValue(const wchar_t * pszKey, const bool bValue)
{
	m_bChanged = true;

	wchar_t * pNewValue = new wchar_t[1];
	pNewValue = bValue ? L"1" : L"0";

	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin();
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			const wchar_t * pOldValue = it->second;
			delete pOldValue;
			it->second = pNewValue;
			return;
			break;
		}
        it++;
    }
	m_mKeyValues[pszKey] = pNewValue;
}

void CConfig::SetIntValue(const wchar_t * pszKey, const int iValue)
{
	m_bChanged = true;
	
	wchar_t * pNewValue = new wchar_t[64];
	swprintf(pNewValue, L"%d", iValue);

	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin(); 
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			const wchar_t * pOldValue = it->second;
			delete pOldValue;
			it->second = pNewValue;
			return;
			break;
		}
        it++;
    }
	m_mKeyValues[pszKey] = pNewValue;
}

void CConfig::SetFloatValue(const wchar_t * pszKey, const float fValue)
{
	m_bChanged = true;

	wchar_t * pNewValue = new wchar_t[64];
	swprintf(pNewValue, L"%f", fValue);

	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin(); 
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			const wchar_t * pOldValue = it->second;
			delete pOldValue;
			it->second = pNewValue;
			return;
			break;
		}
        it++;
    }
	m_mKeyValues[pszKey] = pNewValue;
}

void CConfig::SetStringValue(const wchar_t * pszKey, const wchar_t * pszValue)
{
	m_bChanged = true;

	std::map<const wchar_t *, const wchar_t *>::iterator it = m_mKeyValues.begin(); 
    while(it != m_mKeyValues.end())
    {
		if(wcscmp(it->first, pszKey) == 0)
		{
			const wchar_t * pOldValue = it->second;
			delete pOldValue;
			it->second = pszValue;
			return;
			break;
		}
        it++;
    }
	m_mKeyValues[pszKey] = pszValue;
}