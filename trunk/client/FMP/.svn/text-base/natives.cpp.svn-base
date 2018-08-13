#include <windows.h>
#include "log.h"
#include "natives.h"

extern DWORD dwLoadOffset;

int GetNativeAddressByHash(unsigned int a1)
{
	if(a1 == -1) return 0;
	Log("GetNativeAddress: 0x%x , natives count: %d",a1,*(DWORD*)(0x18DF6EC+dwLoadOffset));

	DWORD pointer1 = *(DWORD*)(0x18DF6E4+dwLoadOffset);
	DWORD pointer2 = *(DWORD*)(0x18DF6E0+dwLoadOffset);
	Log("pointers: [0x%x]:(%d),[0x%x]:(%d)",pointer1,pointer1,pointer2,pointer2);

	unsigned int v2;
	unsigned int v3;
	unsigned int v4;
	unsigned int hash_pointer;

	if(!pointer1) 
	{
		Log("not find pointer");
		return 0;
	}
	// reset data
	v3 = a1 % pointer1;
	v4 = a1;
	// first pointer
	hash_pointer = *(DWORD *)(pointer2 + 8 * v3);
	while(hash_pointer != a1)
	{
		v4 = (v4 >> 1) + 1;
		v3 = (v4 + v3) % pointer1;
		hash_pointer = *(DWORD *)(pointer2 + (8 * v3));
		Log("hash_pointer: 0x%x [%d]",hash_pointer,hash_pointer);
	}
	Log("hash_pointer: 0x%x [%d]",hash_pointer,hash_pointer);
	if(hash_pointer == 0)
	{
		Log("hash_pointer null");
		return 0;
	}
	int addr = (int)(*(DWORD*)(pointer2 + (8 * v3) + 4));
	Log("addr = 0x%x",addr);
	return addr;
}
