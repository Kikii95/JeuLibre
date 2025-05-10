#pragma once
class SystemClickable : public System
{
public:
	SystemClickable();
	~SystemClickable();
	void Update(float dt, const std::vector<Entity*>& entities) override;
	SystemType GetType() const override { return SystemType::Active; }

    sf::Vector2f GetMousePosition();

	void SetLeftClickDetected(bool detected);
	bool IsLeftClickDetected() const;

	void SetRightClickDetected(bool detected);
	bool IsRightClickDetected() const;

	void ClearRightClickCallbacksForTag(const std::string& tag);
	void ClearLeftClickCallbacksForTag(const std::string& tag);

	Entity* CreateInventoryHover(const ItemDefinition* def, const std::string& tagName);
	void ClearInventoryHover();

	void Logs() override;

private:
	bool leftClickDetected = false;
	bool rightClickDetected = false;
};

