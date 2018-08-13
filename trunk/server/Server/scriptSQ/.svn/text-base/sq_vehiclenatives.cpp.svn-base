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

void sq_CreateVehicle(HSQUIRRELVM v) 
{ 
	int model = 0;
	float position[3], angle;
	int tempcolor[2];
	
	sq_getinteger(v, 2, &model);
	sq_getfloat(v, 3, &position[0]);
	sq_getfloat(v, 4, &position[1]);
	sq_getfloat(v, 5, &position[2]);
	sq_getfloat(v, 6, &angle);
	sq_getinteger(v, 7, &tempcolor[0]);
	sq_getinteger(v, 8, &tempcolor[1]);
	unsigned char color[] = {tempcolor[0], tempcolor[1]};
	short index = vm.CreateVehicle(model, position, angle, color);
	if (index == INVALID_VEHICLE_INDEX)
	{
		sq_pushnull(v);
		return;
	}
	sq_pushinteger(v, index);
}

void RegVehicleSQFunc(SQVM * v)
{
	register_global_func(v, (SQFUNCTION)sq_CreateVehicle, L"CreateVehicle");
}