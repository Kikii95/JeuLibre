#include "pch.h"
#include "SystemSpawner.h"

void CombatTerreScene::OnInit()
{
	StatsDatabase::Get().LoadFromFile("../../src/Engine/stats.json");
	EffectDatabase::Get().LoadFromFile("../../src/Engine/effects.json");
	ActionDatabase::Get().LoadFromFile("../../src/Engine/actions.json");
	ItemDatabase::Get().LoadFromFile("../../src/Engine/items.json");
	ToolBoxAssets::GetInstance().LoadFontFromFile("../../src/Engine/testFont.ttf", "testFont");

	SpawnHexGrid(mpGameEngine, 50);
	// Player --------------------------------------------------------------------------------------------------------------
	Entity* player = mpGameEngine->GetEntityManager().CreateEntity();

	// ADD COMPONENTS
	player->AddComponent<ComponentTransform>(sf::Vector2f(0, 0), sf::Vector2f(50, 50));
	player->AddComponent<ComponentRender>();
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

	ComponentFont* playerFont = player->GetComponent<ComponentFont>();
	if (playerFont) {
		playerFont->SetFontByName("testFont");
		playerFont->SetText("PLAYER", true);
		playerFont->SetFillColor(sf::Color::Green);
	}

	//CONFIG COMPONENTS
	player->GetComponent<ComponentTransform>()->SetPosition(hexGridCoordinates[{7, 2}] - sf::Vector2f(player->GetComponent<ComponentTransform>()->GetSize().x / 2, player->GetComponent<ComponentTransform>()->GetSize().y / 2));
	player->GetComponent<ComponentRender>()->SetRenderType(RenderType::Shape);
	player->GetComponent<ComponentCollider>()->SetType(ColliderType::Solid);
	player->GetComponent<ComponentStats>()->LoadFromDefinition("player");
	player->GetComponent<ComponentInventory>()->SetCapacity(100.0f);
	player->GetComponent<ComponentHealth>()->SetMaxHealth(player->GetComponent<ComponentStats>()->GetStat("health"));
	player->GetComponent<ComponentHealth>()->SetHealth(player->GetComponent<ComponentStats>()->GetStat("health"));
	ComponentInventory* playerInv = player->GetComponent<ComponentInventory>();
	playerInv->AddItem(ItemInstance("weapon_sword_rusty", 1));
	playerInv->AddItem(ItemInstance("weapon_bow_basic", 2));
	playerInv->AddItem(ItemInstance("weapon_axe_woodcutter", 1));
	playerInv->AddItem(ItemInstance("consumable_heal_potion_small", 8));
	playerInv->AddItem(ItemInstance("consumable_heal_food_meat", 3));
	playerInv->AddItem(ItemInstance("consumable_energy_drink", 5));
	playerInv->AddItem(ItemInstance("weapon_dagger_iron", 1));


	// Player --------------------------------------------------------------------------------------------------------------

	// Enemies

	// ENEMIES --------------------------------------------------------------------------------------------------------------
	std::vector<std::string> enemyProfiles = {
		"thief", "archer", "soldier", "assassin", "mage", "brute"
	};

	int nombreEnnemis = 10;
	std::vector<sf::Vector2i> positionsDisponibles;

	for (const auto& pair : hexGridCoordinates) {
		const sf::Vector2f& pos = pair.second;

		// Vérifie si la case est déjà occupée par une entité (joueur, ennemi, etc.)
		bool caseLibre = true;
		for (Entity* e : mpGameEngine->GetEntityManager().GetAllEntities()) {
			if (!e->HasComponent<ComponentTransform>()) continue;
			sf::Vector2f center = e->GetComponent<ComponentTransform>()->GetPosition() +
				sf::Vector2f(e->GetComponent<ComponentTransform>()->GetSize().x / 2,
					e->GetComponent<ComponentTransform>()->GetSize().y / 2);
			if (center == pos) {
				caseLibre = false;
				break;
			}
		}

		if (caseLibre) positionsDisponibles.push_back(pair.first);
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(positionsDisponibles.begin(), positionsDisponibles.end(), g);

	for (int i = 0; i < std::min(nombreEnnemis, (int)positionsDisponibles.size()); ++i) {
		sf::Vector2i coord = positionsDisponibles[i];
		sf::Vector2f pos = hexGridCoordinates[coord];

		// Choisir un profil aléatoire
		std::string profileId = enemyProfiles[rand() % enemyProfiles.size()];

		SpawnZone zone;

		// Créer l'ennemi via EntityFactory
		Entity* enemy = EntityFactory::CreateEnemy(zone.id, profileId, zone.difficultyZone, pos);

		// Ajout d’un label texte pour debug (facultatif)


		enemy->GetComponent<ComponentTransform>()->SetSize(sf::Vector2f(50, 50));
		enemy->GetComponent<ComponentTransform>()->SetPosition(pos - sf::Vector2f(enemy->GetComponent<ComponentTransform>()->GetSize().x / 2, enemy->GetComponent<ComponentTransform>()->GetSize().y / 2));

		if (enemy->HasComponent<ComponentFont>()) {
			auto* font = enemy->GetComponent<ComponentFont>();
			font->SetFontByName("testFont");
			font->SetText(profileId, true);
			font->SetFillColor(sf::Color::Red);
			enemy->GetComponent<ComponentFont>()->SetCharacterSize(30);
			ToolBoxVisual::GetInstance().CenterTextAbove(enemy, font, 30.f, 0.f);
			enemy->GetComponent<ComponentFont>()->SetFillColor(sf::Color::White);
		}
	}

	LootDatabase::Get().LoadLootForAllEnemies(mpGameEngine);

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
	Entity* playerMoney = mpGameEngine->GetEntityManager().CreateEntity();
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
	hpFont->SetFixedOnScreen(true);
	// ---------------------------------------------------------------------------------------------------------------------

}

void CombatTerreScene::OnUpdate() {

}

void CombatTerreScene::OnEvent(const std::optional<sf::Event>& event) {}


void CombatTerreScene::SpawnHexGrid(GameEngine* engine, float radius)
{
	GameEngine& instance = engine->GetInstance();
	EntityManager& em = engine->GetEntityManager();
	float WindowWidth = instance.GetWindow().getSize().x;
	float WindowHeight = instance.GetWindow().getSize().y;
	float hexWidth = radius * 2;
	float hexHeight = std::sqrt(3.f) * radius;

	float horizSpacing = hexWidth;       // = 1.5 * radius
	float vertSpacing = hexHeight;               // = sqrt(3) * radius

	int gridSizeX = static_cast<int>(WindowWidth / horizSpacing) + 2;
	int gridSizeY = static_cast<int>(WindowHeight / (hexHeight * 0.75f)) + 2;

	for (int y = 0; y < gridSizeY; ++y) {
		for (int x = 0; x < gridSizeX; ++x) {
			float posX = x * horizSpacing;
			float posY = y * (hexHeight);

			if (y % 2 == 1) {
				posX += hexWidth * 0.5f;
			}

			sf::Vector2f pos(posX, posY);
			sf::Vector2i gridCoord(x, y);

			Entity* hexagon = em.CreateEntity();
			hexagon->AddComponent<ComponentTransform>(pos, sf::Vector2f(radius * 2, radius * 2));
			hexagon->AddComponent<ComponentRender>();
			hexagon->AddComponent<ComponentTag>("HEXAGON");
			hexagon->AddComponent<ComponentClickable>();
			hexagon->GetComponent<ComponentRender>()->SetRenderType(RenderType::Hexagon);
			hexagon->GetComponent<ComponentRender>()->GetHexagonShape().setOutlineColor(sf::Color::Red);
			hexagon->GetComponent<ComponentRender>()->SetRenderLayer(0);

			hexGridCoordinates[gridCoord] = pos;
			reverseHexGridCoordinates[pos] = gridCoord;
			hexagon->GetComponent<ComponentClickable>()->SetOnLeftClick([this, hexagon]() {
				if (IsSelectMenuVisible() == false) {
					if (IsEntityOnHexagon(hexagon) != nullptr) {
						SetSelectMenuVisible(true);
						DisplaySelectMenu(IsEntityOnHexagon(hexagon));
					}
					else {
						std::cout << "No entity on hexagon" << std::endl;
					}
				}
				});
			hexCoordToEntity[gridCoord] = hexagon;
		}
	}
}

void CombatTerreScene::DisplaySelectMenu(Entity* entity) {


	GameEngine::GetInstance().GetTimer().Stop();

	// === RESUME ===
	Entity* AttackBouton = GameEngine::GetInstance().GetEntityManager().CreateEntity();
	AttackBouton->AddComponent<ComponentTransform>(sf::Vector2f(50, 100), sf::Vector2f(200, 50));
	AttackBouton->AddComponent<ComponentFont>();
	AttackBouton->AddComponent<ComponentTag>("SELECTMENU_UI");
	AttackBouton->AddComponent<ComponentClickable>();




	AttackBouton->GetComponent<ComponentClickable>()->SetOnLeftClick([this, entity]() {
		std::cout << "Attack clicked!" << std::endl;
		auto* weapon = entity->GetComponent<ComponentWeapon>();
		if (!weapon) return;

		const ItemDefinition* itemDef = ItemDatabase::Get().GetItem(weapon->GetWeaponId());
		if (!itemDef) return;

		int range = itemDef->range;
		auto playerPos = entity->GetComponent<ComponentTransform>()->GetPosition() +
			sf::Vector2f(entity->GetComponent<ComponentTransform>()->GetSize().x / 2,
				entity->GetComponent<ComponentTransform>()->GetSize().y / 2);

		std::vector<sf::Vector2i> hexesInRange = GetHexesInRange(reverseHexGridCoordinates[playerPos], range);

		for (const sf::Vector2i& hexCoord : hexesInRange) {
			auto it = hexCoordToEntity.find(hexCoord);
			if (it == hexCoordToEntity.end()) continue;

			Entity* hexEntity = it->second;
			ComponentRender* render = hexEntity->GetComponent<ComponentRender>();
			if (!render || render->GetRenderType() != RenderType::Hexagon) continue;

			sf::ConvexShape* shape = &render->GetHexagonShape();
			if (shape) shape->setOutlineColor(sf::Color::White);

			hexEntity->GetComponent<ComponentClickable>()->SetOnRightClick([this, hexCoord, entity, hexesInRange]() {
				Entity* target = nullptr;
				for (Entity* e : GameEngine::GetInstance().GetEntityManager().GetAllEntities()) {
					if (e == entity) continue;
					if (!e->HasComponent<ComponentHealth>()) continue;
					sf::Vector2f eCenter = e->GetComponent<ComponentTransform>()->GetPosition() +
						sf::Vector2f(e->GetComponent<ComponentTransform>()->GetSize().x / 2,
							e->GetComponent<ComponentTransform>()->GetSize().y / 2);
					if (reverseHexGridCoordinates[eCenter] == hexCoord) {
						target = e;
						break;
					}
				}

				if (target) {
					GameEngine::GetInstance().GetSystem<SystemCombat>()->ExecuteAttack(entity, target);
				}
				else {
					std::cout << "[Combat] Aucun ennemi sur cette case." << std::endl;
				}

				for (const sf::Vector2i& h : hexesInRange) {
					auto it = hexCoordToEntity.find(h);
					if (it != hexCoordToEntity.end()) {
						auto* render = it->second->GetComponent<ComponentRender>();
						if (render) render->GetHexagonShape().setOutlineColor(sf::Color::Red);
					}
				}

				SetSelectMenuVisible(false);
				ClearSelectMenu();


				//GameEngine::GetInstance().GetSystem<SystemClickable>()->ClearRightClickCallbacksForTag("HEXAGON");
				});
		}
		});


	auto* font = AttackBouton->GetComponent<ComponentFont>();
	font->SetFontByName("testFont");
	font->SetText("Attack", false);
	font->SetFillColor(sf::Color::White);
	font->SetFixedOnScreen(true);

	Entity* MoveBouton = GameEngine::GetInstance().GetEntityManager().CreateEntity();
	MoveBouton->AddComponent<ComponentTransform>(sf::Vector2f(50, 200), sf::Vector2f(200, 50));
	MoveBouton->AddComponent<ComponentFont>();
	MoveBouton->AddComponent<ComponentTag>("SELECTMENU_UI");
	MoveBouton->AddComponent<ComponentClickable>();
	MoveBouton->GetComponent<ComponentClickable>()->SetOnLeftClick([this, entity]() {
		int moverange = entity->GetComponent<ComponentStats>()->GetStat("speed") / 2;
		std::vector<sf::Vector2i> hexesInRange = GetHexesInRange(reverseHexGridCoordinates[entity->GetComponent<ComponentTransform>()->GetPosition() + sf::Vector2f(entity->GetComponent<ComponentTransform>()->GetSize().x / 2, entity->GetComponent<ComponentTransform>()->GetSize().y / 2)], moverange);
		for (const sf::Vector2i& hexCoord : hexesInRange)
		{
			auto it = hexCoordToEntity.find(hexCoord);
			if (it != hexCoordToEntity.end())
			{
				Entity* hexEntity = it->second;
				ComponentRender* render = hexEntity->GetComponent<ComponentRender>();
				if (render && render->GetRenderType() == RenderType::Hexagon)
				{
					sf::ConvexShape* shape = &render->GetHexagonShape();
					if (shape)
					{
						shape->setOutlineColor(sf::Color::White);
					}
				}
				hexEntity->GetComponent<ComponentClickable>()->SetOnRightClick([this, entity, hexEntity, hexesInRange]() {
					entity->GetComponent<ComponentTransform>()->SetPosition(hexEntity->GetComponent<ComponentTransform>()->GetPosition() - sf::Vector2f(entity->GetComponent<ComponentTransform>()->GetSize().x / 2, entity->GetComponent<ComponentTransform>()->GetSize().y / 2));
					for (const sf::Vector2i& hexCoord : hexesInRange)
					{
						auto it = hexCoordToEntity.find(hexCoord);
						if (it != hexCoordToEntity.end())
						{
							Entity* allhexEntity = it->second;
							ComponentRender* render = allhexEntity->GetComponent<ComponentRender>();
							sf::ConvexShape* shape = &render->GetHexagonShape();
							if (shape)
							{
								shape->setOutlineColor(sf::Color::Red);
							}

							SetSelectMenuVisible(false);
							ClearSelectMenu();


							//GameEngine::GetInstance().GetSystem<SystemClickable>()->ClearRightClickCallbacksForTag("HEXAGON");
							//ComponentClickable* clickable = allhexEntity->GetComponent<ComponentClickable>();
							//if (clickable)
							//{
							//	clickable->SetOnRightClick([this, entity]() {
							//		std::cout << "annulé" << std::endl;
							//	});
							//}
						}
					}
					});
			}
		}
		});
	auto* MoveFont = MoveBouton->GetComponent<ComponentFont>();
	MoveFont->SetFontByName("testFont");
	MoveFont->SetText("Move", false);
	MoveFont->SetFillColor(sf::Color::White);
	MoveFont->SetFixedOnScreen(true);

	Entity* CancelBouton = GameEngine::GetInstance().GetEntityManager().CreateEntity();
	CancelBouton->AddComponent<ComponentTransform>(sf::Vector2f(50, 300), sf::Vector2f(200, 50));
	CancelBouton->AddComponent<ComponentFont>();
	CancelBouton->AddComponent<ComponentTag>("SELECTMENU_UI");
	CancelBouton->AddComponent<ComponentClickable>();

	CancelBouton->GetComponent<ComponentClickable>()->SetOnLeftClick([this, entity]() {
		SetSelectMenuVisible(false);
		ClearSelectMenu();
		});

	auto* CancelFont = CancelBouton->GetComponent<ComponentFont>();
	CancelFont->SetFontByName("testFont");
	CancelFont->SetText("Cancel", false);
	CancelFont->SetFillColor(sf::Color::White);
	CancelFont->SetFixedOnScreen(true);
}

void CombatTerreScene::ClearSelectMenu()
{
	GameEngine::GetInstance().GetTimer().Start();
	for (Entity* e : GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("SELECTMENU_UI")) {
		GameEngine::GetInstance().GetEntityManager().DestroyEntity(e);
	}
}

Entity* CombatTerreScene::IsEntityOnHexagon(Entity* hexagon)
{
	sf::Vector2f pos = hexagon->GetComponent<ComponentTransform>()->GetPosition();
	for (Entity* e : GameEngine::GetInstance().GetEntityManager().GetAllEntities())
	{
		if (e->GetComponent<ComponentTransform>()->GetPosition() + sf::Vector2f(e->GetComponent<ComponentTransform>()->GetSize().x / 2, e->GetComponent<ComponentTransform>()->GetSize().y / 2) == pos && e->GetComponent<ComponentTag>()->GetTag() == "PLAYER") {
			return e;
		}
	}
	return nullptr;
}

std::vector<sf::Vector2i> CombatTerreScene::GetHexesInRange(sf::Vector2i center, int range)
{
	std::vector<sf::Vector2i> result;

	for (int dx = -range; dx <= range; ++dx) {
		for (int dy = std::max(-range, -dx - range); dy <= std::min(range, -dx + range); ++dy) {
			int dz = -dx - dy;

			// Convert cube -> offset (odd-q vertical)
			int q = center.x;
			int r = center.y;

			int cx = q - (r - (r & 1)) / 2;
			int cy = r;
			int cz = -cx - cy;

			int nx = cx + dx;
			int ny = cy + dy;
			int nz = cz + dz;

			int nr = ny;
			int nq = nx + (ny - (ny & 1)) / 2;

			sf::Vector2i neighbor(nq, nr);
			if (hexGridCoordinates.count(neighbor) > 0) {
				result.push_back(neighbor);
			}
		}
	}

	return result;
}

