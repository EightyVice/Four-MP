#include <math.h>
#include "Hook\types.h"
#include "Hook\classes.h"
#include "Hook\scripting.h"
#include "../../Shared/logging/log.h"
#include "VehicleManager.h"

extern FVehicle gVehicle[MAX_VEHICLES];

using namespace Natives;

int FMPHook::GetCarDrive(Vehicle car)
{
	Log::Debug(L"CraDrive %d", car);
	if(!DoesVehicleExist(car)) { Log::Debug(L"DOES"); return 1; }
	Log::Debug(L"CarDrive x%dx", 1);
	if(IsCarStopped(car)) { Log::Debug(L"STOP"); return 0; }
	Vector3 v;
	Log::Debug(L"CarDrive x%dx", 2);
	GetCarSpeedVector(car, &v, 1);
	Log::Debug(L"CarDrive x%dx", 3);
	float x = floor(v.X * 1000 + 0.5)/1000;
	float y = floor(v.Y * 1000 + 0.5)/1000;
	Log::Debug(L"CarDrive x%dx - %fx%f", x, y);
	if(abs(x) > abs(y))
	{
		// ось движения Х (основная)
		if(x < 0)
			return -1;
	}
	else
	{
		// ось движения Y
		if(y < 0)
			return -1;
	}
	Log::Debug(L"CarDrive x%dx", 5);
	return 1;
}

void FMPHook::GetTarget(float ax, float az, float *x, float *y, float *z, float mn)
{
	float a, b, c, s;

	c = Sqrt(2.8f * 2.0f)*mn;
	
	s = c * Cos(ax);
	b = s * Cos(az);
	a = Sqrt( (b*b) + (s*s) - ( 2*b*s * Cos(az) ) );
	c = Sqrt( ((s*s)/(Cos(ax)*Cos(ax))) - (s*s) );

	if(ax < 0 || ax >= 180) c = -c;
	if(((az >= 90 && az <= 270) || az <= -90) && b > 0) b=-b;
	if(((az >= 0 && az <= 180) || az <= - 180) && az > 0) a=-a;

	*x=a; *y=b; *z=c;
}

void FMPHook::GetCamTargetedCoords(float *x, float *y, float *z)
{
	Camera cam;
	float cx, cy, cz;
	float ax, ay, az;
	float a, b, c;

	GetGameCam(&cam);
	GetCamPos(cam, &cx, &cy, &cz);
	GetCamRot(cam, &ax, &ay, &az);

	GetTarget(ax, az, &a, &b, &c);
	*x = a + cx;
	*y = b + cy;
	*z = c + cz;
}

float GetDist(float x1,float y1,float z1,float x2, float y2, float z2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2) );
}

short _GetClosestCar(float x, float y, float z, float r)
{
	float min = r;
	short id = INVALID_VEHICLE_INDEX;
	for (short i = 0; i < MAX_VEHICLES; i++)
	{
		if(gVehicle[i].exist == 1)
		{
			float d = GetDist(x, y, z, gVehicle[i].position[0], gVehicle[i].position[1], gVehicle[i].position[2]);
			if(d < min)
			{
				min = d;
				id = i;
			}
		}
	}
	return id;
}

short GetPlayerCar(Vehicle car)
{
	for(int i = 0; i < MAX_VEHICLES; i++)
	{
		if(gVehicle[i].exist == 1)
		{
			if(car == gVehicle[i].CarID)
				return i;
		}
	}
	return -1;
}

bool FloatRange(float a, float x, float r)
{
	return (a > x-r && a < x+r);
}

bool IntRange(int a, int x, int r)
{
	return (a > x-r && a < x+r);
}