#pragma once

#include "Scene.h"
#include "SceneInitializer.h"

class CombatTerreScene : public Scene
{
public:
	void OnInit() override;
	void OnEvent(const std::optional<sf::Event>& event) override;
	void OnUpdate() override;
	void OnExit() override {}

	void SpawnHexGrid(GameEngine* engine, float radius);
	void DisplaySelectMenu(Entity* entity);
	void ClearSelectMenu();

	void SetSelectMenuVisible(bool visible) { SelectMenuVisible = visible; }
	bool IsSelectMenuVisible() const { return SelectMenuVisible; }

	Entity* IsEntityOnHexagon(Entity* hexagon);

	std::vector<sf::Vector2i> GetHexesInRange(sf::Vector2i center, int range);


private:
	std::unordered_map < sf::Vector2i, sf::Vector2f, ToolBox::Vector2iHasher, ToolBox::Vector2iEqual > hexGridCoordinates;
	std::unordered_map<sf::Vector2f, sf::Vector2i, ToolBox::Vector2fHasher, ToolBox::Vector2fEqual> reverseHexGridCoordinates;
	std::unordered_map<sf::Vector2i, Entity*, ToolBox::Vector2iHasher, ToolBox::Vector2iEqual> hexCoordToEntity;


	bool SelectMenuVisible = false;
};

