#ifndef __Core__
#define __Core__

#pragma once
#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

extern irr::IrrlichtDevice* device;
extern irr::video::IVideoDriver* driver;
extern irr::scene::ISceneManager* smgr;
extern irr::gui::IGUIEnvironment* guienv;
extern irr::scene::ICameraSceneNode* camera;
extern irr::scene::ISceneNode* CameraNode;

enum GAMESTATE {
	MAINMENU,
	OPTIONS,
	PAUSE,
	GAME
};

#endif
