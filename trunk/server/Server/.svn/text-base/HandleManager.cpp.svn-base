/// \file
/// \brief Source file that contains implementation of the HandleManager class.
/// \details See class description.
/// \author FaTony

#include <stdlib.h>

#include "HandleManager.h"
#include "../../Shared/Console/common.h"
#include "../../Shared/logging/log.h"
#include "CoreHandleTypesManager.h"
#include "PluginManager.h"
#include "VirtualMachineManager.h"

extern CoreHandleTypesManager chtm;
extern PluginManager plugm;
extern VirtualMachineManager vmm;

HandleManager::HandleManager(void)
{
	maxtypebuffersize = 65535;
	maxhandlesperowner = 16384;
	pluginowneroffset = 1 + vmm.GetMaxVirtualMachineBufferSize();
	maxcountbuffersize =  pluginowneroffset + plugm.GetMaxPluginBufferSize();
	maxhandlebuffersize = maxcountbuffersize * maxhandlesperowner;
	typebuffer = (HandleType **)calloc(NUM_CORE_HANDLE_TYPES, sizeof(HandleType *));
	for (unsigned short i = 0; i < NUM_CORE_HANDLE_TYPES; i++)
	{
		typebuffer[i] = new HandleType;
		typebuffer[i]->owner = 255;
		typebuffer[i]->handlecount = 0;
	}
	typebuffersize = NUM_CORE_HANDLE_TYPES;
	handlebuffer = NULL;
	countbuffer = NULL;
	handlebuffersize = 0;
	countbuffersize = 0;
}

HandleManager::~HandleManager(void)
{
	for (unsigned short i = 0; i < typebuffersize; i++)
	{
		delete typebuffer[i];
	}
	delete typebuffer;
	if (handlebuffer != NULL)
	{
		for (int i = 0; i < handlebuffersize; i++)
		{
			if (handlebuffer[i] != NULL)
			{
				delete handlebuffer[i];
			}
		}
		delete handlebuffer;
	}
	if (countbuffer != NULL)
	{
		for (short i = 0; i < countbuffersize; i++)
		{
			if (countbuffer[i] != NULL)
			{
				delete countbuffer[i];
			}
		}
		delete countbuffer;
	}
}

void HandleManager::ReleaseAllHandleTypes(const unsigned char pluginindex)
{
	for (unsigned short index = 0; index < typebuffersize; index++)
	{
		this->ReleaseHandleType(pluginindex, index);
	}
}

bool HandleManager::RequestNewHandleType(const unsigned char pluginindex, unsigned short &typeindex)
{
	if (!this->GetHandleTypeFreeSlot(typeindex))
	{
		return false;
	}
	if (typeindex == typebuffersize)
	{
		if (!ResizeBuffer<HandleType **>(typebuffer, typebuffersize + 1))
		{
			return false;
		}
		typebuffersize++;
	}
	typebuffer[typeindex] = new HandleType;
	typebuffer[typeindex]->owner = pluginindex;
	typebuffer[typeindex]->handlecount = 0;
	return true;
}

bool HandleManager::ReleaseHandleType(const unsigned char pluginindex, const unsigned short typeindex)
{
	if (typeindex >= typebuffersize)
	{
		return false;
	}
	if (typebuffer[typeindex] == NULL)
	{
		return false;
	}
	if (typebuffer[typeindex]->owner != pluginindex)
	{
		return false;
	}
	if (typebuffer[typeindex]->handlecount != 0)
	{
		//TODO: Close all handles??
		return false;
	}
	delete typebuffer[typeindex];
	typebuffer[typeindex] = NULL;
	return true;
}

void HandleManager::CloseAllHandles(const short owner)
{
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return;
	}
	if (countbuffer[owner] == NULL)
	{
		return;
	}
	if (countbuffer[owner][0] == 0)
	{
		return;
	}
	for (int i = 0; i < handlebuffersize; i++)
	{
		if (handlebuffer[i] != NULL)
		{
			for (short j = 0; (handlebuffer[i] != NULL) && (j < handlebuffer[i]->numowners); j++)
			{
				if (handlebuffer[i]->owner[j] == owner)
				{
					this->CloseHandle(owner, i);
				}
			}
		}
	}
}

int HandleManager::AddNewHandle(const short owner, const unsigned short type, void *ptr)
{
	if (ptr == NULL)
	{
		return INVALID_HANDLE;
	}
	if ((owner < 0) || (owner >= maxcountbuffersize))
	{
		return false;
	}
	int handle = this->FindHandle(ptr);
	if (handle != INVALID_HANDLE)
	{
		if (handlebuffer[handle]->type != type)
		{
			return INVALID_HANDLE;
		}
		if(!this->AddHandleOwner(handle, owner))
		{
			return INVALID_HANDLE;
		}
		return handle;
	}
	handle = this->GetHandleFreeSlot();
	if (handle == INVALID_HANDLE)
	{
		return INVALID_HANDLE;
	}
	if (!this->IncreaseHandleCount(owner))
	{
		return INVALID_HANDLE;
	}
	if (handle == handlebuffersize)
	{
		if (!ResizeBuffer<Handle **>(handlebuffer, handle + 1))
		{
			return INVALID_HANDLE;
		}
		handlebuffersize = handle + 1;
	}
	handlebuffer[handle] = new Handle;
	handlebuffer[handle]->numowners = 1;
	handlebuffer[handle]->owner = new short;
	handlebuffer[handle]->owner[0] = owner;
	handlebuffer[handle]->type = type;
	handlebuffer[handle]->ptr = ptr;
	typebuffer[type]->handlecount++;
	return handle;
}

bool HandleManager::GetHandleType(const short owner, const int handle, unsigned short &type)
{
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return false;
	}
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return false;
	}
	if (handlebuffer[handle] == NULL)
	{
		return false;
	}
	if (!this->IsHandleOwned(handle, owner))
	{
		return false;
	}
	type = handlebuffer[handle]->type;
	return true;
}

void *HandleManager::GetHandlePointer(const short owner, const int handle)
{
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return NULL;
	}
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return NULL;
	}
	if (handlebuffer[handle] == NULL)
	{
		return NULL;
	}
	if (!this->IsHandleOwned(handle, owner))
	{
		return NULL;
	}
	return handlebuffer[handle]->ptr;
}

bool HandleManager::SetHandlePointer(const short owner, const int handle, void *ptr)
{
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return false;
	}
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return false;
	}
	if (handlebuffer[handle] == NULL)
	{
		return false;
	}
	if (!this->IsHandleOwned(handle, owner))
	{
		return false;
	}
	handlebuffer[handle]->ptr = ptr;
	return true;
}

bool HandleManager::CloseHandle(const short owner, const int handle)
{
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return false;
	}
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return false;
	}
	if (handlebuffer[handle] == NULL)
	{
		return false;
	}
	if (!this->DeleteHandleOwner(handle, owner))
	{
		return false;
	}
	return true;
}

bool HandleManager::GetHandleTypeFreeSlot(unsigned short &type)
{
	for (type = 0; type < typebuffersize; type++)
	{
		if (typebuffer[type] == NULL)
		{
			return true;
		}
	}
	if (typebuffersize == maxtypebuffersize)
	{
		return false;
	}
	return true;
}

int HandleManager::GetHandleFreeSlot(void)
{
	int handle;
	for (handle = 0; handle < handlebuffersize; handle++)
	{
		if (handlebuffer[handle] == NULL)
		{
			return handle;
		}
	}
	if (handlebuffersize == maxhandlebuffersize)
	{
		return INVALID_HANDLE;
	}
	return handle;
}

int HandleManager::FindHandle(const void *ptr)
{
	for (int handle = 0; handle < handlebuffersize; handle++)
	{
		if ((handlebuffer[handle] != NULL) && (handlebuffer[handle]->ptr == ptr))
		{
			return handle;
		}
	}
	return INVALID_HANDLE;
}

bool HandleManager::IsHandleOwned(const int handle, const short owner)
{
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return false;
	}
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return false;
	}
	if (handlebuffer[handle] == NULL)
	{
		return false;
	}
	for (short i = 0; i < handlebuffer[handle]->numowners; i++)
	{
		if (handlebuffer[handle]->owner[i] == owner)
		{
			return true;
		}
	}
	return false;
}

bool HandleManager::AddHandleOwner(const int handle, const short owner)
{
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return false;
	}
	if ((owner < 0) || (owner >= maxcountbuffersize))
	{
		return false;
	}
	if (handlebuffer[handle] == NULL)
	{
		return false;
	}
	if (this->IsHandleOwned(handle, owner))
	{
		return true;
	}
	if (!ResizeBuffer<short *>(handlebuffer[handle]->owner, handlebuffer[handle]->numowners + 1))
	{
		return false;
	}
	handlebuffer[handle]->owner[handlebuffer[handle]->numowners] = owner;
	handlebuffer[handle]->numowners++;
	if (!this->IncreaseHandleCount(owner))
	{
		return false;
	}
	return true;
}

bool HandleManager::DeleteHandleOwner(const int handle, const short owner)
{
	if ((handle < 0) || (handle >= handlebuffersize))
	{
		return false;
	}
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return false;
	}
	if (handlebuffer[handle] == NULL)
	{
		return false;
	}
	short i = 0;
	while ((handlebuffer[handle]->owner[i] != owner) && (i < handlebuffer[handle]->numowners))
	{
		i++;
	}
	if (i == handlebuffer[handle]->numowners)
	{
		return false;
	}
	for (;i < (handlebuffer[handle]->numowners - 1); i++)
	{
		handlebuffer[handle]->owner[i] = handlebuffer[handle]->owner[i+1];
	}
	if (!ResizeBuffer<short *>(handlebuffer[handle]->owner, handlebuffer[handle]->numowners - 1))
	{
		return false;
	}
	handlebuffer[handle]->numowners--;
	if (handlebuffer[handle]->numowners == 0)
	{
		if (handlebuffer[handle]->type < NUM_CORE_HANDLE_TYPES)
		{
			chtm.CloseHandle(handle);
		}
		else
		{
			//TODO: Dynamic handle types
			free(handlebuffer[handle]->ptr);
		}
		typebuffer[handlebuffer[handle]->type]->handlecount--;
		delete handlebuffer[handle];
		handlebuffer[handle] = NULL;
	}
	this->DecreaseHandleCount(owner);
	return true;
}

bool HandleManager::IncreaseHandleCount(const short owner)
{
	if ((owner < 0) || (owner >= maxcountbuffersize))
	{
		return false;
	}
	if (owner >= countbuffersize)
	{
		if (!ResizeBuffer<short **>(countbuffer, owner + 1))
		{
			return false;
		}
		for (short i = countbuffersize; i <= owner; i++)
		{
			countbuffer[i] = NULL;
		}
		countbuffersize = owner + 1;
	}
	if (countbuffer[owner] == NULL)
	{
		countbuffer[owner] = new short;
		countbuffer[owner][0] = 1;
		return true;
	}
	if (countbuffer[owner][0] == maxhandlesperowner)
	{
		Log::Info(L"MEMORY LEAK IN MODULE %d. Unloading.", owner);
		this->CloseAllHandles(owner);
		return false;
	}
	countbuffer[owner][0]++;
	return true;
}

bool HandleManager::DecreaseHandleCount(const short owner)
{
	if ((owner < 0) || (owner >= countbuffersize))
	{
		return false;
	}
	if (countbuffer[owner] == NULL)
	{
		return false;
	}
	if (countbuffer[owner][0] <= 0)
	{
		return false;
	}
	countbuffer[owner][0]--;
	return true;
}