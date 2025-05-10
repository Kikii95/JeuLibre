#include "pch.h"

void ExploCressentIslandScene::OnInit()
{ 
	SceneInitializer::LoadCommonResources();
	SceneInitializer::LoadMap(mpGameEngine, MapType::CressentIsland);

	Entity* player = EntityFactory::CreatePlayer(sf::Vector2f(0, 0));

	SceneInitializer::SetupStaticEntities(mpGameEngine);

	SceneInitializer::SetupSpawnerZones(mpGameEngine);
	SceneInitializer::SetupUI(player);

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);
}

void ExploCressentIslandScene::OnUpdate()
{

}

void ExploCressentIslandScene::OnExit()
{
	GameEngine::GetInstance().CloseScene();
}

void ExploCressentIslandScene::OnEvent(const std::optional<sf::Event>& event) {}
