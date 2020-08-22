#include "Physics.h"
#include "Config.h"
#include "Core.h"
#include <reactphysics3d/reactphysics3d.h>

#pragma comment(lib, "reactphysics3d.lib")

using namespace rp3d;

PhysicsCommon Common;
PhysicsWorld* World;

const decimal TimeStep = 1.0f / 120.0f; //Physics being simulated at 1/120th of a second
long double Accumulator = 0;
time_t CurrentTime;
time_t PrevTime;
long double DeltaTime;

void physics::Init() {
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.81, 0);
	settings.worldName = "Main";
	World = Common.createPhysicsWorld(settings);
	PrevTime = time(0);
}

void physics::Advance() {
	CurrentTime = time(0);
	DeltaTime = CurrentTime - PrevTime;
	PrevTime = CurrentTime;
	Accumulator += DeltaTime;
	while (Accumulator >= TimeStep) {
		World->update(TimeStep);
		Accumulator -= TimeStep;
	}
}