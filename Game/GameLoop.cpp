#include "Core.h"
#include "Config.h"
#include "EventListener.h"
#include "BikeMovement.h"

using namespace irr;

void CameraMovementUpdate(f32 Delta);
void BikeMovementUpdate(f32 Delta);
void CameraOrbitUpdate(f32 Delta);

scene::ISceneNode* bike;

//Run every frame
void GameLoop(f32 Delta) {
	//Todo: add physics engine loop here as well
	// and gui updates
	//Should eventually make this multi-threaded to increase performance. Especially physics

	//CameraMovementUpdate(Delta);

	BikeMovementUpdate(Delta);
	//Todo: make the camera 'orbit' the bike node.
	//CameraOrbitUpdate(Delta);
}

f32 Speed = 0;
BikeMovement::MovementState State = BikeMovement::MovementState::NEUTRAL;

void BikeMovementUpdate(f32 Delta) {
	bike = smgr->getSceneNodeFromId(2, NULL);
	core::vector3df pos = bike->getPosition();

	if (receiver.KeyMap[controlsconfig.Accelerate]) State = BikeMovement::MovementState::ACCELERATING;
	else if (receiver.KeyMap[controlsconfig.Deccelerate]) State = BikeMovement::MovementState::BRAKING;
	else State = BikeMovement::MovementState::NEUTRAL;

	f32 Displacement = BikeMovement::NewPosition(Speed, State, Delta);

	if ((State == BikeMovement::MovementState::BRAKING || State == BikeMovement::MovementState::NEUTRAL) && (Speed<0.4)) {
		Speed = 0;
	}

	//Todo: Make this translate in the facing direction
	core::vector3df rot = bike->getRotation();
	if (receiver.KeyMap[controlsconfig.LeftTilt]) rot.Y -= 20 * Delta;
	if (receiver.KeyMap[controlsconfig.RightTilt]) rot.Y += 20 * Delta;
	core::vector3df direction = rot.rotationToDirection();
	direction.setLength(Displacement);
	pos += direction;

	bike->setPosition(pos);
	bike->setRotation(rot);
	bike->updateAbsolutePosition();

	//Todo: make camera follow behind.
	camera->setTarget(bike->getAbsolutePosition());
}

f32 radius = 20; //20 unit radius.

void CameraOrbitUpdate(f32 Delta) {
	MousePosCurrent = core::vector2d<s32>(MouseEvent.X, MouseEvent.Y);
	if (MouseEvent.isRightPressed()) {
		MousePosDiff = MousePosCurrent - MousePosPrevious;
		CameraNodePosition = camera->getPosition();
		//Move camera
		//...
		camera->setPosition(CameraNodePosition);
		camera->setTarget(bike->getAbsolutePosition());
	}
	MousePosPrevious = MousePosCurrent;
}

//This is good for first person camera.
void CameraMovementUpdate(f32 Delta) {

	///
	///Keyboard movements
	///

	CameraNodePosition = camera->getPosition();
	core::vector3df rot = camera->getRotation();
	core::vector3df direction = rot.rotationToDirection();

	f32 DistanceTravelled = SPEED * Delta;
	if (receiver.KeyMap[controlsconfig.Turbo]) DistanceTravelled *= TURBO;

	if (receiver.KeyMap[controlsconfig.Accelerate]) {
		CameraNodePosition += direction.setLength(DistanceTravelled);
	}
	if (receiver.KeyMap[controlsconfig.Deccelerate]) {
		CameraNodePosition -= direction.setLength(DistanceTravelled);
	}
	//Cross product returns a perpendicular vector to the two inputs.
	if (receiver.KeyMap[controlsconfig.LeftTilt]) {
		CameraNodePosition += direction.crossProduct({ 0,1,0 }).setLength(DistanceTravelled);
	}
	if (receiver.KeyMap[controlsconfig.RightTilt]) {
		CameraNodePosition -= direction.crossProduct({ 0,1,0 }).setLength(DistanceTravelled);
	}
	camera->setPosition(CameraNodePosition);
	camera->updateAbsolutePosition();
	camera->setRotation(rot);

	///
	///Do mouse rotation
	///

	MousePosCurrent = core::vector2d<s32>(MouseEvent.X, MouseEvent.Y);

	if (MouseEvent.isRightPressed()) {
		PlayerRotation = camera->getRotation();
		//Positive x is left to right
		//Positive y is top to bottom
		MousePosDiff = MousePosCurrent - MousePosPrevious;
		PlayerRotation.X += -MousePosDiff.Y * controlsconfig.MouseSensitivity / 100.f;
		PlayerRotation.Y += MousePosDiff.X * controlsconfig.MouseSensitivity / 100.f;

		//Clamp to this range (degrees because Irrlicht doesn't use radians for some reason).
		//90<=x<=270
		//0<=y<=360
		if (PlayerRotation.X <= 90) PlayerRotation.X = 90.1f;
		if (PlayerRotation.X >= 270) PlayerRotation.X = 269.9f;
		if (PlayerRotation.Y < 0) PlayerRotation.Y += 360;
		if (PlayerRotation.Y > 360) PlayerRotation.Y -= 360;

		camera->setRotation(PlayerRotation);
	}
	MousePosPrevious = MousePosCurrent;
}