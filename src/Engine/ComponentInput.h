#pragma once

enum class InputAction {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
	UP,
    DOWN,
	LEFT,
	RIGHT,
    SHOOT,
    JUMP,
    INTERACT,
	INVENTORY,
    ENTER,
	DROP,
    ESCAPE,
	SET,
	LEFT_MOUSE,
	RIGHT_MOUSE,
	MOUSE_WHEEL_UP,
	MOUSE_WHEEL_DOWN,
};

class ComponentInput : public Component {
public:
    std::map<InputAction, sf::Keyboard::Key> keyBindings;
    std::map<InputAction, sf::Mouse::Button> mouseBindings;

    bool interactAlreadyPressed = false;
	bool inventoryAlreadyPressed = false;
	bool inventoryNavPressed = false;
	bool useItemPressed = false;
	bool escapeAlreadyPressed = false;
	bool lmbAlreadyPressed = false;
	bool rmbAlreadyPressed = false;

    ComponentInput(Entity* entity);
};
