#include "pch.h"

void ExploNavalScene::OnInit()
{
		StatsDatabase::Get().LoadFromFile("../../src/Engine/stats.json");
		EffectDatabase::Get().LoadFromFile("../../src/Engine/effects.json");
		ActionDatabase::Get().LoadFromFile("../../src/Engine/actions.json");
		ItemDatabase::Get().LoadFromFile("../../src/Engine/items.json");
		LootDatabase::Get().LoadFromFile("../../src/Engine/loots.json");
		TileDatabase::Get().LoadFromFile("../../src/Engine/tiles.json");
		SpawnerDatabase::Get().LoadFromFile("../../src/Engine/spawners.json");
		ToolBoxAssets::GetInstance().PreloadFonts();
		ToolBoxAssets::GetInstance().LoadFontFromFile("../../src/Engine/testFont.ttf", "testFont");
	
		SceneInitializer::LoadMap(mpGameEngine, MapType::WorldMap);



	// Player --------------------------------------------------------------------------------------------------------------
		Entity* player = GameEngine::GetInstance().GetEntityManager().CreateEntity();

		player->AddComponent<ComponentTransform>(sf::Vector2f(0,350), sf::Vector2f(32, 60));
		player->AddComponent<ComponentRender>();
		player->AddComponent<ComponentPhysics>();
		player->AddComponent<ComponentTag>("PLAYER");
		player->AddComponent<ComponentCollider>();
		player->AddComponent<ComponentInput>();
		player->AddComponent<ComponentWeapon>();
		player->AddComponent<ComponentHealth>();
		player->AddComponent<ComponentState>();
		player->AddComponent<ComponentMoney>();
		player->AddComponent<ComponentStats>();
		player->AddComponent<ComponentInventory>();
		player->AddComponent<ComponentFont>();
		player->AddComponent<ComponentBuffDebuff>();
		player->AddComponent<ComponentPause>();
		player->AddComponent<ComponentEquipment>();


		//player->GetComponent<ComponentInventory>()->AddItem(ItemInstance("armor_outfit_leather_var4", 1));
		//player->GetComponent<ComponentInventory>()->AddItem(ItemInstance("weapon_dagger_iron", 1));
		//player->GetComponent<ComponentInventory>()->AddItem(ItemInstance("consumable_heal_potion_small_var7", 5));

		GameEngine::GetInstance().GetSystem<SystemStats>()->InitStatsFromProfile(player, "player");


		ToolBoxVisual::GetInstance().ApplyVisualConfig(player);

		auto* inv = player->GetComponent<ComponentInventory>();
		inv->SetCapacity(20);
		inv->SetMaxWeight(100.f);

		auto* render = player->GetComponent<ComponentRender>();
		render->SetTexture("../../res/Game/Viking_boat.png");
		render->SetRenderType(RenderType::Sprite);
		render->SetRenderLayer(3);

		auto* stats = player->GetComponent<ComponentStats>();
		float baseHealth = stats->GetStat("health");

		auto* health = player->GetComponent<ComponentHealth>();
		health->SetMaxHealth(baseHealth);
		health->SetHealth(baseHealth);

		auto* collider = player->GetComponent<ComponentCollider>();
		collider->SetType(ColliderType::Solid);

		sf::Vector2f originalSize(32.f, 60.f);

		sf::Vector2u windowSize = GameEngine::GetInstance().GetWindow().getSize();
		const float BASE_WIDTH = 1280.f;
		const float BASE_HEIGHT = 720.f;

		float scaleX = static_cast<float>(windowSize.x) / BASE_WIDTH;
		float scaleY = static_cast<float>(windowSize.y) / BASE_HEIGHT;

		float scaleRaw = std::min(scaleX, scaleY);
		float uniformScale = 1.f + (scaleRaw - 1.f) * 0.5f;

		sf::Vector2f scaledSize = originalSize * uniformScale;

		player->GetComponent<ComponentTransform>()->SetSize(scaledSize);


	// Wall
		Entity* wall1 = mpGameEngine->GetEntityManager().CreateEntity(); 
    wall1->AddComponent<ComponentTransform>(sf::Vector2f(0, GameEngine::GetInstance().GetWindowSize().y), sf::Vector2f(GameEngine::GetInstance().GetWindowSize().x, 50));
    wall1->AddComponent<ComponentRender>();
    wall1->AddComponent<ComponentTag>("WALL");
    wall1->AddComponent<ComponentCollider>();

	wall1->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);
	//auto* wall1Render = wall1->GetComponent<ComponentRender>();
	//wall1Render->SetRenderType(RenderType::Shape);
	//wall1Render->SetRenderLayer(1);


	Entity* wall2 = mpGameEngine->GetEntityManager().CreateEntity();
	wall2->AddComponent<ComponentTransform>(sf::Vector2f(0, -75), sf::Vector2f(GameEngine::GetInstance().GetWindowSize().x, 50));
	wall2->AddComponent<ComponentRender>();
	wall2->AddComponent<ComponentTag>("WALL");
	wall2->AddComponent<ComponentCollider>();

	wall2->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);
	//auto* wall2Render = wall2->GetComponent<ComponentRender>();
	//wall2Render->SetRenderType(RenderType::Shape);
	//wall2Render->SetRenderLayer(1);


	Entity* wall3 = mpGameEngine->GetEntityManager().CreateEntity();
	wall3->AddComponent<ComponentTransform>(sf::Vector2f(GameEngine::GetInstance().GetWindowSize().x, 0), sf::Vector2f(50, GameEngine::GetInstance().GetWindowSize().y));
	wall3->AddComponent<ComponentRender>();
	wall3->AddComponent<ComponentTag>("WALL");
	wall3->AddComponent<ComponentCollider>();

	wall3->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);
	//auto* wall3Render = wall3->GetComponent<ComponentRender>();
	//wall3Render->SetRenderType(RenderType::Shape);
	//wall3Render->SetRenderLayer(1);


	Entity* wall4 = mpGameEngine->GetEntityManager().CreateEntity();
	wall4->AddComponent<ComponentTransform>(sf::Vector2f(-75, -50), sf::Vector2f(50, GameEngine::GetInstance().GetWindowSize().y));
	wall4->AddComponent<ComponentRender>();
	wall4->AddComponent<ComponentTag>("WALL");
	wall4->AddComponent<ComponentCollider>();


	//auto* wall4Render = wall4->GetComponent<ComponentRender>();
	//wall4Render->SetRenderType(RenderType::Shape);
	//wall4Render->SetRenderLayer(1);

	wall4->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);





	Entity* MountainIsland = mpGameEngine->GetEntityManager().CreateEntity();
	MountainIsland->AddComponent<ComponentTransform>(sf::Vector2f(0, 0), sf::Vector2f(156, 128));
	MountainIsland->AddComponent<ComponentRender>();

	MountainIsland->AddComponent<ComponentTag>("MOUNTAINISLAND");
	MountainIsland->AddComponent<ComponentCollider>();
	MountainIsland->GetComponent<ComponentCollider>()->SetType(ColliderType::Island);

	auto* MountainIslandRender = MountainIsland->GetComponent<ComponentRender>();
	MountainIslandRender->SetRenderType(RenderType::Shape);
	MountainIslandRender->SetRenderLayer(1);
	MountainIslandRender->SetColor(sf::Color::Color(255, 255, 255, 0));





	Entity* GladeIsland = mpGameEngine->GetEntityManager().CreateEntity();
	GladeIsland->AddComponent<ComponentTransform>(sf::Vector2f(140, 399), sf::Vector2f(255, 209));
	GladeIsland->AddComponent<ComponentRender>();

	GladeIsland->AddComponent<ComponentTag>("GLADEISLAND");
	GladeIsland->AddComponent<ComponentCollider>();
	GladeIsland->GetComponent<ComponentCollider>()->SetType(ColliderType::Island);

	auto* GladeIslandRender = GladeIsland->GetComponent<ComponentRender>();
	GladeIslandRender->SetRenderType(RenderType::Shape);
	GladeIslandRender->SetRenderLayer(1);
	GladeIslandRender->SetColor(sf::Color::Color(255, 255, 255, 0));





	Entity* CressentIsland = mpGameEngine->GetEntityManager().CreateEntity();
	CressentIsland->AddComponent<ComponentTransform>(sf::Vector2f(600, 155), sf::Vector2f(167, 213));
	CressentIsland->AddComponent<ComponentRender>();

	CressentIsland->AddComponent<ComponentTag>("CRESSENTISLAND");
	CressentIsland->AddComponent<ComponentCollider>();
	CressentIsland->GetComponent<ComponentCollider>()->SetType(ColliderType::Island);

	auto* CressentIslandRender = CressentIsland->GetComponent<ComponentRender>();
	CressentIslandRender->SetRenderType(RenderType::Shape);
	CressentIslandRender->SetRenderLayer(1);
	CressentIslandRender->SetColor(sf::Color::Color(255, 255, 255, 0));




	Entity* LakeIsland = mpGameEngine->GetEntityManager().CreateEntity();
	LakeIsland->AddComponent<ComponentTransform>(sf::Vector2f(912, 262), sf::Vector2f(168, 256));
	LakeIsland->AddComponent<ComponentRender>();

	LakeIsland->AddComponent<ComponentTag>("LAKEISLAND");
	LakeIsland->AddComponent<ComponentCollider>();
	LakeIsland->GetComponent<ComponentCollider>()->SetType(ColliderType::Island);

	auto* LakeIslandRender = LakeIsland->GetComponent<ComponentRender>();
	LakeIslandRender->SetRenderType(RenderType::Shape);
	LakeIslandRender->SetRenderLayer(1);
	LakeIslandRender->SetColor(sf::Color::Color(255, 255, 255, 0));




	Entity* YingYangIsland = mpGameEngine->GetEntityManager().CreateEntity();
	YingYangIsland->AddComponent<ComponentTransform>(sf::Vector2f(1186, 24), sf::Vector2f(94, 131));
	YingYangIsland->AddComponent<ComponentRender>();

	YingYangIsland->AddComponent<ComponentTag>("YINGYANGISLAND");
	YingYangIsland->AddComponent<ComponentCollider>();
	YingYangIsland->GetComponent<ComponentCollider>()->SetType(ColliderType::Island);

	auto* YingYangIslandRender = YingYangIsland->GetComponent<ComponentRender>();
	YingYangIslandRender->SetRenderType(RenderType::Shape);
	YingYangIslandRender->SetRenderLayer(1);
	YingYangIslandRender->SetColor(sf::Color::Color(255, 255, 255, 0));







	//SET FONT
	for (Entity* entity : mpGameEngine->GetEntityManager().GetEntitiesByTag("ENEMY")) {
		auto* font = entity->GetComponent<ComponentFont>();
		auto* health = entity->GetComponent<ComponentHealth>();
		auto* stats = entity->GetComponent<ComponentStats>();

		if (font && health && stats) {
			font->SetFontByName("testFont");

			std::string id = stats->GetDefinitionId();
			font->SetText(id + " HP: " + std::to_string(health->GetHealth()), true);
			font->SetFillColor(sf::Color::Red);
		}
	}
	//SET FONT
//LOGS -----------------------------------------------------------------------------------------------------------------
	if (!debugMode || !logScene) {
		HEAD("log_Scene") << "Player created" << ENDL;
		HEAD("log_Scene") << "Player has " << player->GetComponent<ComponentHealth>()->GetHealth() << " health" << ENDL;
		HEAD("log_Scene") << "Player has " << player->GetComponent<ComponentMoney>()->GetBalance() << " money" << ENDL;
		HEAD("log_Scene") << "Player has " << player->GetComponent<ComponentStats>()->GetStat("attack") << " attack" << ENDL;
		HEAD("log_Scene") << "Player has " << player->GetComponent<ComponentStats>()->GetStat("crit") << " crit" << ENDL;
	}
	// ---------------------------------------------------------------------------------------------------------------------


	// FONT ----------------------------------------------------------------------------------------------------------------
	/*Entity* playerMoney = mpGameEngine->GetEntityManager().CreateEntity();
	playerMoney->AddComponent<ComponentTransform>(sf::Vector2f(10, 0), sf::Vector2f(NULL, NULL));
	playerMoney->AddComponent<ComponentFont>();
	playerMoney->AddComponent<ComponentTag>("UI_MONEY");

	ComponentFont* moneyFont = playerMoney->GetComponent<ComponentFont>();
	moneyFont->SetFontByName("testFont");
	moneyFont->SetText("Money: " + std::to_string(player->GetComponent<ComponentMoney>()->GetBalance()), true);
	moneyFont->SetFillColor(sf::Color::Red);
	moneyFont->SetFixedOnScreen(true);

	Entity* playerHP = mpGameEngine->GetEntityManager().CreateEntity();
	playerHP->AddComponent<ComponentTransform>(sf::Vector2f(1200, 0), sf::Vector2f(NULL, NULL));
	playerHP->AddComponent<ComponentFont>();
	playerHP->AddComponent<ComponentTag>("UI_HP");

	ComponentFont* hpFont = playerHP->GetComponent<ComponentFont>();
	hpFont->SetFontByName("testFont");
	hpFont->SetText("HP: " + std::to_string(player->GetComponent<ComponentHealth>()->GetHealth()), true);
	hpFont->SetFillColor(sf::Color::Red);
	hpFont->SetFixedOnScreen(true);*/
	// ---------------------------------------------------------------------------------------------------------------------

}

void ExploNavalScene::OnUpdate()
{

}

void ExploNavalScene::OnEvent(const std::optional<sf::Event>& event) {}


