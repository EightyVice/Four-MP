#pragma once

//int GetCarDrive(Vehicle car);
//void GetTarget(float ax, float az, float *x, float *y, float *z, float mn);
//void GetCamTargetedCoords(float *x, float *y, float *z);
float GetDist(float x1,float y1,float z1,float x2, float y2, float z2);
short _GetClosestCar(float x, float y, float z, float r);
short GetPlayerCar(Vehicle);

bool FloatRange(float a, float x, float r);
bool IntRange(int a, int x, int r);