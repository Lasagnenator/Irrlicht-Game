#include "Config.h"
#include "VideoSystem.h"
#include "EventListener.h"
#include "Core.h"
#include "GameLoop.h"
#include <iostream>
#include "ERROR.h"

using namespace irr;

IrrlichtDevice* device;

video::IVideoDriver* driver;
scene::ISceneManager* smgr;
gui::IGUIEnvironment* guienv;
scene::ICameraSceneNode* camera;
scene::ISceneNode* CameraNode;

core::vector3df CameraNodePosition;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//uncomment next line if no console is wanted
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//Entry point to lightcycle game.
int maingame() {
	Config::LoadConfig();
	VideoSystem::GetDriver();
	VideoSystem::GetDevice();
	if (device==0) return DEVICEFAILED; //Could not create driver

	device->setWindowCaption(L"Lightcycles");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	//device->getCursorControl()->setVisible(false);
	device->setResizable(true);
	driver->setViewPort(core::recti({ 0,0 }, videoconfig.Resolution));

	if (device->getFileSystem()->changeWorkingDirectoryTo("./assets/")==false) return DIRECTORYFAILED; //failed to change directory

	if (smgr->loadScene((io::path) "./scenes/ground.irr") == false) return LOADFAILED; //Failed to load scene

	camera = (scene::ICameraSceneNode*)smgr->getSceneNodeFromId(1, NULL);
	if (camera == 0) return CAMERAFAILED; //Could not find player camera object
	camera->bindTargetAndRotation(true);

	bike = smgr->getSceneNodeFromId(2, NULL);
	if (bike == 0) return BIKEFAILED; //Could not find bike object

	int LastFPS = -1;
	int FPS = -1;
	u32 then = device->getTimer()->getTime();

	while (device->run()) {
		const u32 now = device->getTimer()->getTime();
		const f32 Delta = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		if (device->isWindowActive()) {

			GameLoop(Delta);

			driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
			smgr->drawAll();
			driver->endScene();

			//Add fps to title
			FPS = driver->getFPS();
			if (LastFPS != FPS) {
				core::stringw str = L"Lightcycles ";
				str += driver->getName();
				str += L" FPS: ";
				str += FPS;
				device->setWindowCaption(str.c_str());
				LastFPS = FPS;
			}
		}
		else {
			device->yield();
		}
		
	}

	device->drop();

	return 0;
}

int ErrorCode;

int main() {
	//Todo: add logger
	try
	{
		ErrorCode = maingame();
	}
	catch (const std::exception&)
	{
		ErrorCode = -1;
	}
	if (ErrorCode == 0) return 0; //Successful exit
	char temp;
	std::cout << "Error encountered" << std::endl;
	std::cout << "Code " << ErrorCode << std::endl;
	std::cout << "Press any key to exit . . . ";
	std::cin >> temp;
	return 0;
}
