#include "pch.h"

void ExploMountainIslandScene::OnInit()
{
	SceneInitializer::LoadCommonResources();
	SceneInitializer::LoadMap(mpGameEngine, MapType::MountainIsland);

	Entity* player = EntityFactory::CreatePlayer(sf::Vector2f(0, 0));

	SceneInitializer::SetupStaticEntities(mpGameEngine);

	SceneInitializer::SetupSpawnerZones(mpGameEngine);
	SceneInitializer::SetupUI(player);

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);
}

void ExploMountainIslandScene::OnUpdate()
{

}

void ExploMountainIslandScene::OnExit()
{
	GameEngine::GetInstance().CloseScene();
}

void ExploMountainIslandScene::OnEvent(const std::optional<sf::Event>& event) {}
