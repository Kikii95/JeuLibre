#include "pch.h"

void ExploGladeIslandScene::OnInit()
{
	SceneInitializer::LoadCommonResources();
	SceneInitializer::LoadMap(mpGameEngine, MapType::GladeIsland);

	Entity* player = EntityFactory::CreatePlayer(sf::Vector2f(0, 0));

	SceneInitializer::SetupStaticEntities(mpGameEngine);

	SceneInitializer::SetupSpawnerZones(mpGameEngine);
	SceneInitializer::SetupUI(player);

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);
}

void ExploGladeIslandScene::OnUpdate()
{

}

void ExploGladeIslandScene::OnExit()
{
	GameEngine::GetInstance().CloseScene();
}

void ExploGladeIslandScene::OnEvent(const std::optional<sf::Event>& event) {}
