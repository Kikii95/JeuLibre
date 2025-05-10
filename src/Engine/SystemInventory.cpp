#include "pch.h"

SystemInventory::SystemInventory() {}

void SystemInventory::Update(float dt, const std::vector<Entity*>& entities) {
}

bool SystemInventory::TransferItem(Entity* from, Entity* to, const std::string& itemId, int quantity) {
    auto* invFrom = from->GetComponent<ComponentInventory>();
    auto* invTo = to->GetComponent<ComponentInventory>();
    if (!invFrom || !invTo) return false;

    const auto& items = invFrom->GetItems();
    for (const auto& item : items) {
        if (item.itemId == itemId && item.quantity >= quantity) {
            ItemInstance transfer(itemId, quantity);

            if (!invTo->AddItem(transfer)) return false;

            invFrom->RemoveItem(itemId, quantity);

            std::cout << "[SystemInventory] Transfert reussi : " << quantity << " x " << itemId << std::endl;
            return true;
        }
    }

    std::cout << "[SystemInventory] echec transfert : pas assez de " << itemId << std::endl;
    return false;
}


void SystemInventory::DropSelectedItem(Entity* player) {
    auto* inv = player->GetComponent<ComponentInventory>();
    if (!inv) return;

    const auto& items = inv->GetItems();
    int index = inv->GetSelectedIndex();
    if (index < 0 || index >= static_cast<int>(items.size())) return;

    ItemInstance instance = items[index];
    const ItemDefinition* def = ItemDatabase::Get().GetItem(instance.itemId);
    if (!def) return;

    auto* equip = player->GetComponent<ComponentEquipment>();
    auto* equipSys = GameEngine::GetInstance().GetSystem<SystemEquipment>();
    if (equip && equipSys && instance.isEquipped) {
        equipSys->UnequipSlot(player, def->equipmentSlot);
        std::cout << "[Inventory] Objet déséquipé avant drop : " << instance.itemId << "\n";
    }

    inv->RemoveItem(instance.itemId, 1);

    auto* transform = player->GetComponent<ComponentTransform>();
    if (!transform) return;

    sf::Vector2f pos = transform->GetPosition();

    GameEngine::GetInstance().GetSystem<SystemItem>()->DropItem(instance, pos);

    std::cout << "[Inventory] Objet drop : " << instance.itemId << "\n";

    ClearInventoryDisplay();
    DisplayInventory(player);
}


void SystemInventory::DisplayInventory(Entity* player) {
    auto* inv = player->GetComponent<ComponentInventory>();
    if (!inv) return;

    const auto& items = inv->GetItems();
    sf::Vector2f basePos(50.f, 100.f);
    float currentY = basePos.y;
    float padding = 5.f;
    const float boxWidth = 500.f;
    const float boxHeight = 35.f;

    Entity* titleEntity = GameEngine::GetInstance().GetEntityManager().CreateEntity();
    titleEntity->AddComponent<ComponentTransform>(sf::Vector2f(basePos.x, currentY - boxHeight - 10.f), sf::Vector2f(boxWidth, boxHeight));
    titleEntity->AddComponent<ComponentFont>();
    titleEntity->AddComponent<ComponentTag>("INVENTORY_ITEM");

    ComponentFont* titleFont = titleEntity->GetComponent<ComponentFont>();
    titleFont->SetFontByName("testFont");
    titleFont->SetFixedOnScreen(true);

    float weight = inv->GetTotalWeight();
    float maxWeight = inv->GetMaxWeight();
    std::string header = "INVENTAIRE - Poids : " + std::to_string((int)weight) + "/" + std::to_string((int)maxWeight);
    titleFont->SetText(header, false);
    titleFont->SetFillColor(sf::Color::Cyan);

    auto* equip = player->GetComponent<ComponentEquipment>();
   if (equip) {
        for (const auto& [slot, itemData] : equip->GetAll()) {
            std::string display = LocalizedSlotName(slot) + " : ";

            if (equip->IsEquipped(slot)) {
                std::string itemId = equip->GetEquippedItemID(slot);
                const ItemDefinition* def = ItemDatabase::Get().GetItem(itemId);
                display += def ? def->name : itemId;
            } else {
                display += "???";
            }

            Entity* slotEntity = GameEngine::GetInstance().GetEntityManager().CreateEntity();
            slotEntity->AddComponent<ComponentTransform>(sf::Vector2f(basePos.x, currentY), sf::Vector2f(boxWidth, boxHeight));
            slotEntity->AddComponent<ComponentFont>()->SetText(display, false);
            slotEntity->AddComponent<ComponentTag>("INVENTORY_ITEM");
            slotEntity->AddComponent<ComponentClickable>();

            slotEntity->GetComponent<ComponentFont>()->SetFontByName("testFont");
            slotEntity->GetComponent<ComponentFont>()->SetFixedOnScreen(true);
            slotEntity->GetComponent<ComponentFont>()->SetFillColor(sf::Color(200, 200, 255));

            slotEntity->GetComponent<ComponentClickable>()->SetOnLeftClick([slot]() {
                auto& engine = GameEngine::GetInstance();
                auto* player = engine.GetEntityManager().GetEntitiesByTag("PLAYER")[0];
                auto* inv = player->GetComponent<ComponentInventory>();
                auto* equip = player->GetComponent<ComponentEquipment>();

                if (equip && equip->IsEquipped(slot)) {
                    std::string itemId = equip->GetEquippedItemID(slot);
                    auto* sysEquip = engine.GetSystem<SystemEquipment>();
                    sysEquip->EquipItem(player, itemId);

                    auto* sys = engine.GetSystem<SystemInventory>();
                    sys->ClearInventoryDisplay();
                    sys->DisplayInventory(player);
                }
            });

            currentY += boxHeight + padding;
        }
    }
   currentY -= 15.f;

   Entity* separator = GameEngine::GetInstance().GetEntityManager().CreateEntity();
   separator->AddComponent<ComponentTransform>(sf::Vector2f(basePos.x, currentY), sf::Vector2f(boxWidth, 2.f));
   separator->AddComponent<ComponentFont>()->SetText("----------------------------------", false);
   separator->AddComponent<ComponentTag>("INVENTORY_ITEM");
   separator->GetComponent<ComponentFont>()->SetFontByName("testFont");
   separator->GetComponent<ComponentFont>()->SetFixedOnScreen(true);
   separator->GetComponent<ComponentFont>()->SetFillColor(sf::Color(0, 0, 0));
   separator->GetComponent<ComponentFont>()->SetCharacterSize(50.f);

   currentY += separator->GetComponent<ComponentFont>()->GetText().getCharacterSize();



    for (size_t i = 0; i < items.size(); ++i) {
        const auto& instance = items[i];
        const auto* def = ItemDatabase::Get().GetItem(instance.itemId);
        if (!def) continue;

        Entity* textEntity = GameEngine::GetInstance().GetEntityManager().CreateEntity();
        textEntity->AddComponent<ComponentTransform>(sf::Vector2f(basePos.x, currentY), sf::Vector2f(boxWidth, boxHeight));
        textEntity->AddComponent<ComponentFont>();
        textEntity->AddComponent<ComponentTag>("INVENTORY_ITEM");
        textEntity->AddComponent<ComponentClickable>();
        textEntity->AddComponent<ComponentItem>(instance);

        textEntity->GetComponent<ComponentClickable>()->SetOnLeftClick([this, i]() {
            auto* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];
            auto* inv = player->GetComponent<ComponentInventory>();
            if (!inv) return;

            inv->SetSelectedIndex(static_cast<int>(i));

            auto* merchant = GameEngine::GetInstance().GetSystem<SystemMerchant>()->GetCurrentMerchant();
            if (merchant)
                merchant->GetComponent<ComponentMerchant>()->SetSelectedIndex(-1);

            ClearInventoryDisplay();
            DisplayInventory(player);

            auto* merchSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();
            if (merchSys && merchSys->IsMerchantVisible()) {
                merchSys->ClearMerchantDisplay();
                merchSys->DisplayMerchantStock(merchant);
            }
            });

        auto* font = textEntity->GetComponent<ComponentFont>();
        font->SetFontByName("testFont");
        font->SetFixedOnScreen(true);

        std::string prefix = (i == inv->GetSelectedIndex()) ? "> " : "  ";
        std::string suffix;

        if (instance.isEquipped)
            suffix += " [équipé]";

        auto* merchantSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();
        if (merchantSys && merchantSys->IsMerchantVisible()) {
            Entity* merchant = merchantSys->GetCurrentMerchant();
            if (merchant) {
                int price = merchantSys->GetSellPrice(instance.itemId, merchant);
                suffix += " (" + std::to_string(price) + " or)";
            }
        }

        std::string fullText = prefix + def->name + " x" + std::to_string(instance.quantity) + suffix;
        font->SetText(fullText, false);
        font->SetFillColor((i == inv->GetSelectedIndex()) ? sf::Color::Yellow : sf::Color::White);

        currentY += boxHeight + padding;
    }
}



void SystemInventory::ClearInventoryDisplay() {
    auto& em = GameEngine::GetInstance().GetEntityManager();
    auto invEntities = em.GetEntitiesByTag("INVENTORY_ITEM");
    for (Entity* e : invEntities) {
		em.DestroyEntity(e);
    }

    //std::cout << "[Inventaire] Nettoyage de l'affichage.\n";
}

bool SystemInventory::IsInventoryVisible() const {
	return inventoryVisible;
}

void SystemInventory::SetInventoryIsVisible(bool visible) {
	inventoryVisible = visible;
}

const ItemDefinition* SystemInventory::ResolveEquippedItemDefinition(Entity* entity, const std::string& uid) {
    auto* inv = entity->GetComponent<ComponentInventory>();
    if (!inv) return nullptr;

    // Chercher dans l'inventaire
    for (const auto& item : inv->GetItems()) {
        if (item.uid == uid) {
            return ItemDatabase::Get().GetItem(item.itemId);
        }
    }

    // S’il n’est pas dans l’inventaire, on n’a plus le itemId
    // => Parcourir les slots équipés pour retrouver le bon
    auto* equip = entity->GetComponent<ComponentEquipment>();
    if (!equip) return nullptr;

    for (const auto& [slot, storedUid] : equip->GetAll()) {
        if (storedUid.first == uid) {
            // On suppose que le slot contient le bon uid
            // Pas d’itemId, mais tu peux éventuellement stocker une map secondaire {uid  itemId}
            // ou bien... fallback sur ??? ici
            // Tu pourrais aussi stocker le dernier ItemInstance équipé dans le composant équipement
            break;
        }
    }

    return nullptr;
}


void SystemInventory::UpdateInventory(Entity* entity) {
    if (inventoryVisible) {
		ClearInventoryDisplay();
		DisplayInventory(entity);
	}
}

void SystemInventory::ToggleEquipWeapon(Entity* player) {
    auto* inventory = player->GetComponent<ComponentInventory>();
    if (!inventory || inventory->GetItems().empty()) return;

    int index = inventory->GetSelectedIndex();
    if (index < 0 || index >= inventory->GetItems().size()) return;

    const auto& item = inventory->GetItems()[index];
    const ItemDefinition* def = ItemDatabase::Get().GetItem(item.itemId);
    if (!def || def->type != ItemType::Weapon) {
        std::cout << "[Inventaire] ? Cet objet n'est pas une arme.\n";
        return;
    }

    auto* weapon = player->GetComponent<ComponentWeapon>();
    if (!weapon) {
        std::cout << "[Inventaire] ?? Aucun ComponentWeapon trouve.\n";
        return;
    }

    if (weapon->GetWeaponId() == item.itemId) {
        weapon->Unequip();
        std::cout << "[Inventaire] ?? Arme desequipee : " << def->name << "\n";
    }
    else {
        weapon->Equip(item.itemId);
        std::cout << "[Inventaire] ?? Arme equipee : " << def->name << "\n";
    }

    ClearInventoryDisplay();
    DisplayInventory(player);
}

void SystemInventory::Logs() {
    if (!debugMode || !logSystemInventory) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int totalInventories = 0;
    int totalItems = 0;
    int stackedItems = 0;

    for (Entity* e : entities) {
        auto* inv = e->GetComponent<ComponentInventory>();
        if (!inv) continue;

        ++totalInventories;
        const auto& items = inv->GetItems();

        for (const auto& item : items) {
            const char* id = (char*)item.itemId.c_str();
            HEAD("sys_INVENTORY") << "Entite " << e->GetID()
                << " possede " << (int)item.quantity
                << " x " << id << ENDL;

            ++totalItems;
            stackedItems += item.quantity;
        }
    }

    HEAD("sys_INVENTORY") << "Inventaires trouves : " << (int)totalInventories
        << " | Objets listes : " << (int)totalItems
        << " | Total (quantite cumulee) : " << (int)stackedItems << ENDL;
}
