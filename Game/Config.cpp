#include "Config.h"
#include "Core.h"

using namespace irr;

videoconfig_t videoconfig;
controlsconfig_t controlsconfig;

//Loads config from disk
void Config::LoadConfig() {
	//To-do: load config from file
	videoconfig_t load;
	load.BitDepth = 32U;
	load.DriverType = video::EDT_OPENGL;
	load.Fullscreen = false;
	load.StencilBuffer = false;
	load.Vsync = false;
	load.Resolution = { 640,480 };

	videoconfig = load;
}

//Saves config to disk
bool Config::SaveConfig() {
	//To-do: save config to file
	return true;
}