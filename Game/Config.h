#ifndef __Config__
#define __Config__

#include "Core.h"

struct videoconfig_t;
struct controlsconfig_t;

namespace Config {
	void LoadConfig();
	bool SaveConfig();
}

struct videoconfig_t {
	bool Vsync = false;
	irr::u32 BitDepth = 32U; //Unused in windowed mode
	bool Fullscreen = false;
	bool StencilBuffer = false;
	irr::video::E_DRIVER_TYPE DriverType = irr::video::EDT_BURNINGSVIDEO; //Should only ever be OpenGL/DirectX or software
	irr::core::dimension2d<irr::u32> Resolution = irr::core::dimension2d<irr::u32>(1280, 720);
};
extern videoconfig_t videoconfig;

struct controlsconfig_t {
	irr::s32 MouseSensitivity = 50; //0-100 slider
	irr::EKEY_CODE Accelerate = irr::KEY_KEY_W;
	irr::EKEY_CODE LeftTilt = irr::KEY_KEY_A;
	irr::EKEY_CODE RightTilt = irr::KEY_KEY_D;
	irr::EKEY_CODE Deccelerate = irr::KEY_KEY_S;
	irr::EKEY_CODE ToggleJetwall = irr::KEY_SPACE;
	irr::EKEY_CODE Turbo = irr::KEY_LSHIFT;
};
extern controlsconfig_t controlsconfig;

#define SPEED 40 //40 units per second
#define TURBO 3  //3 times faster on turbo

#endif
