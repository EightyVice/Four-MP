#include "sq.h"

#include "../ServerCore.h"
#include "../PlayerManager.h"
#include "../VehicleManager.h"
#include "../NetworkManager.h"
#include "../../../Shared/logging/log.h"

extern ServerCore server;
extern PlayerManager playm;
extern VehicleManager vm;
extern NetworkManager nm;

void sq_SendMessageToAll(HSQUIRRELVM v)
{
	const wchar_t *msg;
	sq_getstring(v, 2, &msg);
	nm.SendChatMessageToAll(msg);
}

void sq_SendMessageToPlayer(HSQUIRRELVM v)
{
	const wchar_t *msg;
	short index;
	sq_getinteger(v, 2, (SQInteger*)&index);
	sq_getstring(v, 3, &msg);
	nm.SendChatMessageToOne(index, msg);
}

void RegUISQFunc(SQVM * v)
{
	register_global_func(v, (SQFUNCTION)sq_SendMessageToAll, L"SendMessageToAll");
	register_global_func(v, (SQFUNCTION)sq_SendMessageToPlayer, L"SendMessageToPlayer");
}