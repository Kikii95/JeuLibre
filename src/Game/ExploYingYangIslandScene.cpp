#include "pch.h"

void ExploYingYangIslandScene::OnInit()
{
	SceneInitializer::LoadCommonResources();
	SceneInitializer::LoadMap(mpGameEngine, MapType::YingYangIsland);

	Entity* player = EntityFactory::CreatePlayer(sf::Vector2f(0, 0));

	SceneInitializer::SetupStaticEntities(mpGameEngine);

	SceneInitializer::SetupSpawnerZones(mpGameEngine);
	SceneInitializer::SetupUI(player);

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);
}

void ExploYingYangIslandScene::OnUpdate()
{

}

void ExploYingYangIslandScene::OnExit()
{
	GameEngine::GetInstance().CloseScene();
}

void ExploYingYangIslandScene::OnEvent(const std::optional<sf::Event>& event) {}
