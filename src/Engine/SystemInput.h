#pragma once
class SystemInput : public System
{
public:
	SystemInput() = default;

	void Update(float dt, const std::vector<Entity*>& entities);
	SystemType GetType() const { return SystemType::Active;}

	void HandleMovement(Entity* entity, const std::map<InputAction, sf::Keyboard::Key>& keys);
	void HandleInteraction(Entity* entity, const std::map<InputAction, sf::Keyboard::Key>& keys);
	void HandleInventoryToggle(const std::map<InputAction, sf::Keyboard::Key>& keys);
	void HandleInventoryControls(const std::map<InputAction, sf::Keyboard::Key>& keys);
	void HandleMouseClicks(ComponentInput* input);
	void HandlePauseMenu(const std::map<InputAction, sf::Keyboard::Key>& keys, Entity* entity);


	void Logs() override;
};

