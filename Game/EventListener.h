#ifndef __EventListener__
#define __EventListener__

#pragma once
//#include <IEventReceiver.h>
#include "Core.h"
class EventListener : public irr::IEventReceiver{
public:
	//Handles events
	virtual bool OnEvent(const irr::SEvent& event);
	EventListener();
	//State of the keyboard
	bool KeyMap[irr::KEY_KEY_CODES_COUNT] = {false};
private:
	void LogHandler(const irr::SEvent& event);
	void MouseHandler(const irr::SEvent& event);
	void KeyboardHandler(const irr::SEvent& event);
	void GUIHandler(const irr::SEvent& event);
};

//The main event receiver.
extern EventListener receiver;
//Position of the camera node (not automatically updated)
extern irr::core::vector3df CameraNodePosition;
//Rotation of the player (not automatically updated)
extern irr::core::vector3df PlayerRotation;
extern irr::core::vector2d<irr::s32> MousePosPrevious;
extern irr::core::vector2d<irr::s32> MousePosDiff;
extern irr::core::vector2d<irr::s32> MousePosCurrent;
//The most recent mouse event
extern irr::SEvent::SMouseInput MouseEvent;

#endif
