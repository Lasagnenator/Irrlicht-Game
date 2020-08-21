#include "EventListener.h"
#include "Core.h"
#include "Config.h"

using namespace irr;

bool EventListener::OnEvent(const irr::SEvent& event) {
	switch (event.EventType) {
	case EET_MOUSE_INPUT_EVENT:
		//mouse event
		//printf("Mouse had input\n");
		MouseHandler(event);
		return true;
	case EET_LOG_TEXT_EVENT:
		//Something got logged
		LogHandler(event);
		break;
	case EET_KEY_INPUT_EVENT:
		//keyboard state changed
		//printf("Keyboard State changed\n");
		KeyboardHandler(event);
		return true;
	case EET_GUI_EVENT:
		GUIHandler(event);
		return false; //returning false because nothing has been done.
	}
	return false;
}

EventListener::EventListener(){
}

//Logs to file
void EventListener::LogHandler(const irr::SEvent& event) {
	//Todo: add logger
}

core::vector3df PlayerRotation;
core::vector2d<s32> MousePosPrevious;
core::vector2d<s32> MousePosDiff;
core::vector2d<s32> MousePosCurrent;
SEvent::SMouseInput MouseEvent;

void EventListener::MouseHandler(const irr::SEvent& event) {

	MouseEvent = event.MouseInput;
}

void EventListener::KeyboardHandler(const irr::SEvent& event) {
	KeyMap[event.KeyInput.Key] = event.KeyInput.PressedDown;
}

void EventListener::GUIHandler(const irr::SEvent& event) {
	//Here if needed.
}

EventListener receiver;
