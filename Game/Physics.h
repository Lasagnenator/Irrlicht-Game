#ifndef __PHYSICS__
#define __PHYSICS__
#pragma once

#include "Config.h"

namespace physics {
	//Creates the world and all objects in the world
	void Init();
	//Advances the physics of the world every 1/120th of a second
	void Advance();
}

#endif
