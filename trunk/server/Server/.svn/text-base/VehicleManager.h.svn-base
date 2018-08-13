#pragma once

#include "../../Shared/Network/VehicleDefines.h"

class VehicleManager
{
public:
	VehicleManager(void);
	~VehicleManager(void);
	short GetMaxVehicleBufferSize(void);
	short GetVehicleBufferSize(void);
	bool IsVehicleExists(const short index);
	short CreateVehicle(const int model, const float position[3], const float angle, const unsigned char color[2]);
	unsigned int GetVehicleModel(const short index);
	bool GetVehiclePosition(const short index, float (&position)[3]);
	bool GetVehicleAngle(const short index, float &angle);
	bool GetVehicleColor(const short index, unsigned char (&color)[2]);
	bool SetVehiclePosition(const short index, const float position[3]);
	bool SetVehicleAngle(const short index, const float angle);
private:
	struct Vehicle
	{
		unsigned int model; ///< Holds the model hash of the vehicle.
		float position[3]; ///< Holds the position of the vehicle.
		float angle[3]; ///< Holds the angle of the vehicle.
		short health; ///< Holds the health of the vehicle.
		short enginehealth; ///< Holds the engine health of the vehicle.
		bool doorexists[6]; ///< Holds whether the vehicle's doors exist.
		bool doorlock[6]; ///< Holds whether the vehicle's doors are locked.
		float doorangle[6]; ///< Holds the vehicle's doors angles.
		unsigned char color[2]; ///< Holds the color of the vehicle.
	};
	short maxvehiclebuffersize;
	short vehiclebuffersize;
	Vehicle **vehiclebuffer;
	short GetVehicleFreeSlot(void);
	bool SetVehiclePositionInternal(const short index, const float position[3]);
	bool SetVehicleAngleInternal(const short index, const float angle);
	friend class NetworkManager;
};
