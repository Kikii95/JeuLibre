#include "pch.h"

void GameplayScene::OnInit()
{
	SceneInitializer::LoadCommonResources();
	SceneInitializer::LoadMap(mpGameEngine, MapType::GladeIsland);

	Entity* player = EntityFactory::CreatePlayer(sf::Vector2f(0, 0));

	SceneInitializer::SetupStaticEntities(mpGameEngine);

	SceneInitializer::SetupSpawnerZones(mpGameEngine);
	SceneInitializer::SetupUI(player);

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);
}

void GameplayScene::OnUpdate()
{

}

void GameplayScene::OnExit()
{
	GameEngine::GetInstance().CloseScene();
}

void GameplayScene::OnEvent(const std::optional<sf::Event>& event) {}
