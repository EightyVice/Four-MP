#pragma once
#include "./hook/CScriptThread.h"

class CGameScript : public CScriptThread
{
public:
	CGameScript();
	~CGameScript();

	void GameThread();
private:
};