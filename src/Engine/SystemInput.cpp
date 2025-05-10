#include "pch.h"
#include "SystemInput.h"

void SystemInput::Update(float dt, const std::vector<Entity*>& entities) {
	for (auto* entity : entities) {
		if (entity->IsDestroyed()) continue;

		auto* input = entity->GetComponent<ComponentInput>();
		if (!input) continue;

		auto& keys = input->keyBindings;

		HandleMovement(entity, keys);
		HandleInteraction(entity, keys);
		HandleInventoryToggle(keys);
		HandleInventoryControls(keys);
		HandleMouseClicks(input);
		HandlePauseMenu(keys, entity);
	}
}

void SystemInput::HandleMovement(Entity* entity, const std::map<InputAction, sf::Keyboard::Key>& keys) {
	auto* physics = entity->GetComponent<ComponentPhysics>();
	if (!physics) return;

	sf::Vector2f force(0.f, 0.f);
	const float inputForce = 5000.f;
	const float jumpForce = -80000.f;

	if (Input::IsKeyPressed(keys.at(InputAction::MOVE_LEFT)))  force.x -= inputForce;
	if (Input::IsKeyPressed(keys.at(InputAction::MOVE_RIGHT))) force.x += inputForce;
	if (Input::IsKeyPressed(keys.at(InputAction::MOVE_UP)))    force.y -= inputForce;
	if (Input::IsKeyPressed(keys.at(InputAction::MOVE_DOWN)))  force.y += inputForce;

	if (Input::IsKeyJustPressed(keys.at(InputAction::JUMP)) && physics->IsOnGround()) {
		force.y += jumpForce;
		physics->SetIsGrounded(false);

		GameEngine::GetInstance().GetSystem<SystemHealth>()->ApplyDamage(entity, 15);
	}

	physics->ApplyForce(force);
}

void SystemInput::HandleInteraction(Entity* entity, const std::map<InputAction, sf::Keyboard::Key>& keys) {
	if (Input::IsKeyJustPressed(keys.at(InputAction::INTERACT))) {
		auto* collisionSystem = GameEngine::GetInstance().GetSystem<SystemCollision>();
		Entity* target = collisionSystem->GetCurrentMobCollision(entity);
		if (!target) return;

		ActionData action;
		action.id = "interact_generic";
		action.name = "Interaction";
		action.actionType = ActionType::Interact;

		if (target->HasComponent<ComponentMerchant>()) {
			action.id = "interact_merchant";
			std::cout << "[Input] Interaction avec un marchand\n";
		}
		else if (target->HasComponent<ComponentHealth>()) {
			action.id = "interact_attack";
			std::cout << "[Input] Interaction = attaque\n";
		}
		// TO DO : add more interactions

		GameEngine::GetInstance().GetSystem<SystemAction>()->ExecuteAction(entity, target, &action);
	}
}


void SystemInput::HandleInventoryToggle(const std::map<InputAction, sf::Keyboard::Key>& keys) {
	if (Input::IsKeyJustPressed(keys.at(InputAction::INVENTORY))) {
		auto* invSys = GameEngine::GetInstance().GetSystem<SystemInventory>();
		Entity* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];

		auto* merchSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();

		if (invSys && player && merchSys && !merchSys->IsMerchantVisible()) {
			bool newState = !invSys->IsInventoryVisible();

			invSys->SetInventoryIsVisible(newState);

			if (newState) {
				invSys->DisplayInventory(player);
				GameEngine::GetInstance().GetTimer().Stop();
			}
			else {
				invSys->ClearInventoryDisplay();
				GameEngine::GetInstance().GetTimer().Start();
			}
		}

	}
}

void SystemInput::HandleInventoryControls(const std::map<InputAction, sf::Keyboard::Key>& keys) {
	auto* invSys = GameEngine::GetInstance().GetSystem<SystemInventory>();
	auto* merchSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();
	if (!invSys || !merchSys) return;

	bool isInventoryVisible = invSys->IsInventoryVisible();
	bool isMerchantVisible = merchSys->IsMerchantVisible();
	if (!isInventoryVisible && !isMerchantVisible) return;

	Entity* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];

	if (isMerchantVisible) {
		Entity* merchant = merchSys->GetCurrentMerchant();
		if (!merchant) return;

		auto* merch = merchant->GetComponent<ComponentMerchant>();
		auto* inv = player->GetComponent<ComponentInventory>();
		if (!merch || !inv) return;

		const auto& stock = merch->GetStock();
		const auto& items = inv->GetItems();

		int merchIndex = merch->GetSelectedIndex();
		int invIndex = inv->GetSelectedIndex();

		if (Input::IsKeyJustPressed(keys.at(InputAction::DOWN))) {
			if (merchIndex >= 0) {
				merchIndex = (merchIndex + 1) % stock.size();
				merch->SetSelectedIndex(merchIndex);
				inv->SetSelectedIndex(-1);
			}
			else if (!items.empty()) {
				invIndex = (invIndex + 1) % items.size();
				inv->SetSelectedIndex(invIndex);
				merch->SetSelectedIndex(-1);
			}
			merchSys->ClearMerchantDisplay();
			merchSys->DisplayMerchantStock(merchant);
			invSys->ClearInventoryDisplay();
			invSys->DisplayInventory(player);
		}
		else if (Input::IsKeyJustPressed(keys.at(InputAction::UP))) {
			if (merchIndex >= 0) {
				merchIndex = (merchIndex == 0 ? stock.size() - 1 : merchIndex - 1);
				merch->SetSelectedIndex(merchIndex);
				inv->SetSelectedIndex(-1);
			}
			else if (!items.empty()) {
				invIndex = (invIndex == 0 ? items.size() - 1 : invIndex - 1);
				inv->SetSelectedIndex(invIndex);
				merch->SetSelectedIndex(-1);
			}
			merchSys->ClearMerchantDisplay();
			merchSys->DisplayMerchantStock(merchant);
			invSys->ClearInventoryDisplay();
			invSys->DisplayInventory(player);
		}

		if (Input::IsKeyJustPressed(keys.at(InputAction::ENTER))) {
			if (invIndex >= 0 && invIndex < items.size()) {
				const std::string& itemId = items[invIndex].itemId;
				if (merchSys->SellItem(player, merchant, itemId, 1)) {
					invSys->ClearInventoryDisplay();
					invSys->DisplayInventory(player);
					merchSys->ClearMerchantDisplay();
					merchSys->DisplayMerchantStock(merchant);
				}
				return;
			}
			if (merchIndex >= 0 && merchIndex < stock.size()) {
				const std::string& itemId = stock[merchIndex].item.itemId;
				if (merchSys->BuyItem(player, merchant, itemId, 1)) {
					invSys->UpdateInventory(player);
					invSys->ClearInventoryDisplay();
					invSys->DisplayInventory(player);
					merchSys->ClearMerchantDisplay();
					merchSys->DisplayMerchantStock(merchant);
				}
				return;
			}
		}

		return;
	}


	if (isInventoryVisible) {
		auto* inv = player->GetComponent<ComponentInventory>();
		if (!inv) return;

		if (Input::IsKeyJustPressed(keys.at(InputAction::DOWN))) {
			inv->SetSelectedIndex((inv->GetSelectedIndex() + 1) % inv->GetItems().size());
			invSys->ClearInventoryDisplay();
			invSys->DisplayInventory(player);
		}
		else if (Input::IsKeyJustPressed(keys.at(InputAction::UP))) {
			int newIndex = (inv->GetSelectedIndex() == 0 ? inv->GetItems().size() - 1 : inv->GetSelectedIndex() - 1);
			inv->SetSelectedIndex(newIndex);
			invSys->ClearInventoryDisplay();
			invSys->DisplayInventory(player);
		}

		if (Input::IsKeyJustPressed(keys.at(InputAction::ENTER))) {
			const auto& items = inv->GetItems();
			int selected = inv->GetSelectedIndex();
			if (selected < 0 || selected >= items.size()) return;

			const ItemInstance& selectedItem = items[selected];

			GameEngine::GetInstance().GetSystem<SystemAction>()->UseItem(player, selectedItem);
			invSys->ClearInventoryDisplay();
			invSys->DisplayInventory(player);
		}


		if (Input::IsKeyJustPressed(keys.at(InputAction::DROP))) {
			auto* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];
			GameEngine::GetInstance().GetSystem<SystemInventory>()->DropSelectedItem(player);
		}

	}
}


void SystemInput::HandleMouseClicks(ComponentInput* input) {
	if (Input::IsMouseButtonJustPressed(input->mouseBindings[InputAction::LEFT_MOUSE])) {
		SystemClickable* clickableSys = GameEngine::GetInstance().GetSystem<SystemClickable>();
		if (clickableSys) {
			clickableSys->SetLeftClickDetected(true);
			std::cout << "isClicked : " << clickableSys->IsLeftClickDetected() << std::endl;
		}
	}
	if (Input::IsMouseButtonJustPressed(input->mouseBindings[InputAction::RIGHT_MOUSE])) {
		SystemClickable* clickableSys = GameEngine::GetInstance().GetSystem<SystemClickable>();
		if (clickableSys) {
			clickableSys->SetRightClickDetected(true);
			std::cout << "isClicked : " << clickableSys->IsRightClickDetected() << std::endl;
		}
	}
}

void SystemInput::HandlePauseMenu(const std::map<InputAction, sf::Keyboard::Key>& keys, Entity* entity) {
	if (!Input::IsKeyJustPressed(keys.at(InputAction::ESCAPE))) return;

	auto* invSys = GameEngine::GetInstance().GetSystem<SystemInventory>();
	auto* merchSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();
	auto* pauseSys = GameEngine::GetInstance().GetSystem<SystemPause>();

	if (merchSys->IsMerchantVisible()) {
		merchSys->ClearMerchantDisplay();
		invSys->ClearInventoryDisplay();
		merchSys->SetMerchantIsVisible(false);
		invSys->SetInventoryIsVisible(false);
		merchSys->SetCurrentMerchant(nullptr);
		GameEngine::GetInstance().GetTimer().Start();
		std::cout << "[ESCAPE] Fermeture du marchand + inventaire\n";
		return;
	}

	if (invSys->IsInventoryVisible()) {
		invSys->ClearInventoryDisplay();
		invSys->SetInventoryIsVisible(false);
		GameEngine::GetInstance().GetTimer().Start();
		std::cout << "[ESCAPE] Fermeture de l’inventaire\n";
		return;
	}

	bool newState = !pauseSys->IsPauseMenuVisible();
	pauseSys->SetPauseMenuVisible(newState);

	if (newState) {
		pauseSys->DisplayPauseMenu(entity);
		std::cout << "[ESCAPE] Ouverture du menu pause\n";
	}
	else {
		pauseSys->ClearPauseMenu();
		std::cout << "[ESCAPE] Fermeture du menu pause\n";
	}
}





void SystemInput::Logs() {
	if (!debugMode || !logSystemInput) return;

	EntityManager& em = GameEngine::GetInstance().GetEntityManager();
	const auto& entities = em.GetAllEntities();

	int totalControlled = 0;

	for (Entity* e : entities) {
		auto* input = e->GetComponent<ComponentInput>();
		if (!input) continue;

		++totalControlled;
		const auto& bindings = input->keyBindings;

		HEAD("sys_INPUT") << "Entite " << e->GetID() << " contr�lee manuellement." << ENDL;

		for (const auto& [action, key] : bindings) {
			HEAD("sys_INPUT") << "Touche : " << (int)key << ENDL;
		}
	}

	HEAD("sys_INPUT") << "Total d'entites avec input joueur : " << (int)totalControlled << ENDL;
}
