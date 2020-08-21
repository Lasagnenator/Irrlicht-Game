#ifndef __BIKEMOVEMENT__
#define __BIKEMOVEMENT__

#include "Core.h"

#pragma once

namespace BikeMovement {
	/*Describes the current key combination*/
	enum MovementState {
		NEUTRAL,
		ACCELERATING,
		BRAKING
	};

	/*Simulates an acceleration drag at some speed.
Proportional to velocity squared usually.*/
	inline irr::f32 GetDrag(irr::f32 Speed);

	/*Calculates new speed from some acceleration, current speed and time change*/
	inline irr::f32 NewSpeed(irr::f32 Acceleration, irr::f32 CurrentSpeed, irr::f32 Delta);

	/*Modifies speed in-place and return displacement*/
	irr::f32 NewPosition(irr::f32 &Speed, BikeMovement::MovementState State, irr::f32 Delta);

}

#endif
