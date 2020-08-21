#include "Core.h"
#include "Config.h"
#include "BikeMovement.h"
#include "EventListener.h"

#define DRAGCOEFF 0.015f    //a = -kv^2
#define ACCELERATION 100 //motor's acceleration is constant

using namespace irr;

/*Modifies speed in-place and return displacement*/
f32 BikeMovement::NewPosition(f32 &Speed, BikeMovement::MovementState State, f32 Delta) {
	f32 Acceleration = -GetDrag(Speed);
	switch (State) {
	case ACCELERATING:
		if (receiver.KeyMap[controlsconfig.Turbo]) {
			Acceleration += ACCELERATION * TURBO;
		}
		else {
			Acceleration += ACCELERATION;
		}
		break;
	case BRAKING:
		Acceleration -= ACCELERATION;
		break;
	}
	
	f32 OldSpeed = Speed;
	Speed = NewSpeed(Acceleration, Speed, Delta);

	//s = ut + 1/2 at^2
	f32 Displacement = (OldSpeed * Delta) + (0.5f * Delta * Delta * Acceleration);
	return Displacement;
}

/*Simulates an acceleration drag at some speed.
Proportional to velocity squared usually.*/
inline f32 BikeMovement::GetDrag(f32 Speed) {
	return DRAGCOEFF * Speed * Speed;
}

/*Calculates new speed from some acceleration, current speed and time change*/
inline f32 BikeMovement::NewSpeed(f32 Acceleration, f32 Speed, f32 Delta) {
	return Speed + (Acceleration * Delta);
}
