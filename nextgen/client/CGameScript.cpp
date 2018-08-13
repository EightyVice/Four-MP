#include "CGameScript.h"
#include "CChat.h"
#include "log/log.h"

extern CChat *pChat;

CGameScript::CGameScript()
{
	SetName("FOURMP");
}

CGameScript::~CGameScript()
{

}

void CGameScript::GameThread()
{
	while(IsThreadAlive())
	{
		
		Wait(50);
	}
}
