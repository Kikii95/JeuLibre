#include "pch.h"

void ExploLakeIslandScene::OnInit()
{
	SceneInitializer::LoadCommonResources();
	SceneInitializer::LoadMap(mpGameEngine, MapType::LakeIsland);

	Entity* player = EntityFactory::CreatePlayer(sf::Vector2f(0, 0));

	SceneInitializer::SetupStaticEntities(mpGameEngine);

	SceneInitializer::SetupSpawnerZones(mpGameEngine);
	SceneInitializer::SetupUI(player);

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);
}

void ExploLakeIslandScene::OnUpdate()
{

}

void ExploLakeIslandScene::OnExit()
{
	GameEngine::GetInstance().CloseScene();
}

void ExploLakeIslandScene::OnEvent(const std::optional<sf::Event>& event) {}
