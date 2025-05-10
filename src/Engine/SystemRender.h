#pragma once

class SystemRender : public System {
public:
    SystemRender();

	SystemType GetType() const override { return SystemType::UI; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    void DrawWorld(sf::RenderWindow& window, const std::vector<Entity*>& entities);
	void DrawMap(sf::RenderWindow& window, const std::vector<Entity*>& entities);
    void DrawUI(sf::RenderWindow& window, const std::vector<Entity*>& entities);


	void Logs() override;

};
