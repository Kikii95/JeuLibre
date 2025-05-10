#include "pch.h"

ComponentInput::ComponentInput(Entity* entity) : Component(entity) {
	keyBindings[InputAction::MOVE_LEFT] = KEY_Q;
	keyBindings[InputAction::MOVE_RIGHT] = KEY_D;
	keyBindings[InputAction::MOVE_UP] = KEY_Z;
	keyBindings[InputAction::MOVE_DOWN] = KEY_S;

	keyBindings[InputAction::UP] = KEY_UP;
	keyBindings[InputAction::DOWN] = KEY_DOWN;
	keyBindings[InputAction::LEFT] = KEY_LEFT;
	keyBindings[InputAction::RIGHT] = KEY_RIGHT;

	keyBindings[InputAction::JUMP] = KEY_SPACE;
	keyBindings[InputAction::INTERACT] = KEY_E;
	keyBindings[InputAction::SET] = KEY_P;
	keyBindings[InputAction::INVENTORY] = KEY_I;
	keyBindings[InputAction::ENTER] = KEY_ENTER;
	keyBindings[InputAction::ESCAPE] = KEY_ESCAPE;
	keyBindings[InputAction::DROP] = KEY_R;

	mouseBindings[InputAction::SHOOT] = LMB;
	mouseBindings[InputAction::LEFT_MOUSE] = LMB;
	mouseBindings[InputAction::RIGHT_MOUSE] = RMB;
}
