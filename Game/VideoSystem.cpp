#include "VideoSystem.h"
#include "Core.h"
#include "EventListener.h"
#include "Config.h"
#include <iostream>

using namespace irr;

video::E_DRIVER_TYPE DriverType = videoconfig.DriverType;


video::E_DRIVER_TYPE VideoSystem::GetDriver() {
    //To-do: make this frmo a gui eventually
    /// Code taken from Irrlicht docs
    printf("Please select the driver you want for this example:\n"\
        " (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
        " (d) Burning's Software Renderer\n (e) Software Renderer\n"\
        " (f) NullDevice\n(otherwise) Use default\n\n");

    char i;
    std::cin >> i;

    switch (i){
    case 'a': DriverType = video::EDT_OPENGL; break;
    case 'b': DriverType = video::EDT_DIRECT3D9; break;
    case 'c': DriverType = video::EDT_DIRECT3D8; break;
    case 'd': DriverType = video::EDT_BURNINGSVIDEO; break;
    case 'e': DriverType = video::EDT_SOFTWARE; break;
    case 'f': DriverType = video::EDT_NULL; break;
    default: break;
    }
    videoconfig.DriverType = DriverType;
    return DriverType;
}

IrrlichtDevice* VideoSystem::GetDevice() {
    device = createDevice(videoconfig.DriverType, videoconfig.Resolution, videoconfig.BitDepth, videoconfig.Fullscreen, videoconfig.StencilBuffer, videoconfig.Vsync, &receiver);
    return device;
}
