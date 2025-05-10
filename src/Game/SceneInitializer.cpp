#pragma once

#include "pch.h"
#include "SceneInitializer.h"

void SceneInitializer::LoadCommonResources() {
	StatsDatabase::Get().LoadFromFile("../../src/Engine/stats.json");
	EffectDatabase::Get().LoadFromFile("../../src/Engine/effects.json");
	ActionDatabase::Get().LoadFromFile("../../src/Engine/actions.json");
	ItemDatabase::Get().LoadFromFile("../../src/Engine/items.json");
	LootDatabase::Get().LoadFromFile("../../src/Engine/loots.json");
	TileDatabase::Get().LoadFromFile("../../src/Engine/tiles.json");
	ToolBoxAssets::GetInstance().PreloadFonts();
	ToolBoxAssets::GetInstance().LoadFontFromFile("../../src/Engine/testFont.ttf", "testFont");
}

void SceneInitializer::LoadMap(GameEngine* engine, MapType type) {
	std::string path;
	std::string spawnerPath;

	if (type == MapType::WorldMap) {
		EntityManager& em = engine->GetEntityManager();

		Entity* dot = em.CreateMapEntity();
		dot->AddComponent<ComponentTransform>(sf::Vector2f(0, 0), GameEngine::GetInstance().GetWindowSize());
		dot->AddComponent<ComponentRender>();

		dot->GetComponent<ComponentRender>()->SetTexture("../../res/Game/fullmap.png");
		dot->GetComponent<ComponentRender>()->SetRenderType(RenderType::Sprite);

		std::cout << "[SceneInitializer] WorldMap affichée avec fullmap.png" << std::endl;
		return;
	}

	switch (type) {
	case MapType::GladeIsland:
		path = "../../res/map_GladeIsland.json";
		spawnerPath = "../../res/spawner_GladeIsland.json";
		break;
	case MapType::LakeIsland:
		path = "../../res/map_LakeIsland.json";
		spawnerPath = "../../res/spawner_LakeIsland.json";
		break;
	case MapType::MountainIsland:
		path = "../../res/map_MountainIsland.json";
		spawnerPath = "../../res/spawner_MountainIsland.json";
		break;
	case MapType::YingYangIsland:
		path = "../../res/map_YingYangIsland.json";
		spawnerPath = "../../res/spawner_YingYangIsland.json";
		break;
	case MapType::CressentIsland:
		path = "../../res/map_CressentIsland.json";
		spawnerPath = "../../res/spawner_CressentIsland.json";
		break;
	default:
		std::cerr << "[SceneInitializer] MapType inconnu. Aucun chargement effectué.\n";
		return;
	}

	TileMapLoader::LoadTilemap(engine, path, 500);

	if (!SpawnerDatabase::Get().LoadFromFile(spawnerPath)) {
		std::cerr << "[SceneInitializer] ERREUR : impossible de charger les spawners depuis " << spawnerPath << "\n";
	}
}



void SceneInitializer::SetupStaticEntities(GameEngine* engine){
	auto* spawner = GameEngine::GetInstance().GetSystem<SystemSpawner>();

	spawner->SpawnStaticEntity("merchant", sf::Vector2f(700.f, 700.f), 5000.f, 500.f, 10);

}

void SceneInitializer::SetupSpawnerZones(GameEngine* engine){
	auto* spawner = GameEngine::GetInstance().GetSystem<SystemSpawner>();

	for (const auto& def : SpawnerDatabase::Get().GetAll()) {
		spawner->RegisterSpawnZone({
			def.id,
			def.center,
			def.radius,
			def.type,
			def.profileId,
			def.maxEntities,
			def.respawnDelay,
			0.f,
			def.difficultyZone,
			def.playerDespawnMargin,
			def.mobDespawnMargin
			});
	}
}



void SceneInitializer::SetupUI(Entity* player) {
	auto& em = GameEngine::GetInstance().GetEntityManager();

	// === MONEY ===
	Entity* playerMoney = em.CreateEntity();
	playerMoney->AddComponent<ComponentTransform>(sf::Vector2f(15, 0), sf::Vector2f());
	playerMoney->AddComponent<ComponentFont>();
	playerMoney->AddComponent<ComponentTag>("UI_MONEY");

	auto* moneyFont = playerMoney->GetComponent<ComponentFont>();
	moneyFont->SetFontByName("testFont");
	moneyFont->SetText("Money: " + std::to_string(player->GetComponent<ComponentMoney>()->GetBalance()), true);
	moneyFont->SetFillColor(sf::Color::Red);
	moneyFont->SetFixedOnScreen(true);

	// === HP ===
	sf::Vector2f hpPos(GameEngine::GetInstance().GetWindowSize().x - 100, 0);
	Entity* playerHP = em.CreateEntity();
	playerHP->AddComponent<ComponentTransform>(hpPos, sf::Vector2f());
	playerHP->AddComponent<ComponentFont>();
	playerHP->AddComponent<ComponentTag>("UI_HP");

	auto* hpFont = playerHP->GetComponent<ComponentFont>();
	hpFont->SetFontByName("testFont");
	hpFont->SetText("HP: " + std::to_string(player->GetComponent<ComponentHealth>()->GetHealth()), true);
	hpFont->SetFillColor(sf::Color::Red);
	hpFont->SetFixedOnScreen(true);
}
