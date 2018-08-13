#include <windows.h>
#include "../../../Shared/logging/log.h"
#include "hook.h"
#include "natives.h"

extern DWORD dwLoadOffset;

struct _SCRIPTPTRSTRUC{
	unsigned int hash;
	int addr;
}*scriptptr;

int GetNativeAddressByHash(unsigned int a1) // { VoLT }
{
	if(a1 == -1) return 0;

	DWORD pointer1 = *(DWORD*)SCRIPT_POINTER_1;
	scriptptr = *(_SCRIPTPTRSTRUC**)SCRIPT_POINTER_2;

	unsigned int v3;
	unsigned int v4;
	unsigned int hash_pointer;
	if(!pointer1){
		Log::Debug("# not find pointer");
		return 0;
	}
	v3 = a1 % pointer1;
	v4 = a1;
	hash_pointer = scriptptr[v3].hash;
	while(hash_pointer != a1){
		v4 = (v4 >> 1) + 1;
		v3 = (v4 + v3) % pointer1;
		hash_pointer = scriptptr[v3].hash;
		if(hash_pointer == 0){
			Log::Debug("# hash_pointer null");
			return 0;
		}
	}
	if(hash_pointer != 0)
		return scriptptr[v3].addr;
	// ересь по другому мозг не придумал
	Log::Debug("# hash_pointer null");
		return 0;
}