#include "pch.h"

SystemMerchant::SystemMerchant() {}

void SystemMerchant::Update(float dt, const std::vector<Entity*>& entities) {
}

bool SystemMerchant::BuyItem(Entity* buyer, Entity* merchant, const std::string& itemId, int quantity) {
    auto* merch = merchant->GetComponent<ComponentMerchant>();
    auto* buyerInv = buyer->GetComponent<ComponentInventory>();
    auto* buyerMoney = buyer->GetComponent<ComponentMoney>();
    if (!merch || !buyerInv || !buyerMoney) return false;

    auto& stock = merch->GetStock();
    for (auto& slot : stock) {
        if (slot.item.itemId == itemId && slot.item.quantity >= quantity) {
            int price = GetItemPrice(slot, merch->GetBuyRate()) * quantity;

            if (!buyerMoney->Has(price)) {
                std::cout << "[SystemMerchant] Pas assez d’or ! (" << buyerMoney->GetBalance() << "/" << price << ")" << std::endl;
                return false;
            }

            ItemInstance toBuy(itemId, quantity);
            if (buyerInv->AddItem(toBuy)) {
                slot.item.quantity -= quantity;
                buyerMoney->Spend(price);
                std::cout << "[SystemMerchant] Achat : " << quantity << " x " << itemId << " pour " << price << " or" << std::endl;
                return true;
            }
        }
    }

    std::cout << "[SystemMerchant] Achat echoue." << std::endl;
    return false;
}


bool SystemMerchant::SellItem(Entity* player, Entity* merchant, const std::string& itemId, int quantity) {
    auto* inv = player->GetComponent<ComponentInventory>();
    auto* money = player->GetComponent<ComponentMoney>();
    auto* merch = merchant->GetComponent<ComponentMerchant>();
    auto* weapon = player->GetComponent<ComponentWeapon>();
    if (!inv || !money || !merch) return false;

    if (!inv->HasItem(itemId, quantity)) return false;

    if (weapon && weapon->IsEquipped() && weapon->GetWeaponId() == itemId) {
        weapon->Unequip();
        std::cout << "[Merchant] Objet déséquipé avant vente : " << itemId << std::endl;
    }

    ItemInstance instanceToSell(itemId, quantity);
    MerchantSlot newSlot(instanceToSell);

    int unitPrice = GetSellPrice(itemId, merchant);
    money->Add(unitPrice * quantity);

    if (!inv->RemoveItem(itemId, quantity)) return false;

    merch->AddItem(newSlot);

    std::cout << "[Merchant] Vente de " << quantity << " x " << itemId
        << " pour " << unitPrice * quantity << " or" << std::endl;

    return true;
}




int SystemMerchant::GetItemPrice(const MerchantSlot& slot, float rate) const {
    const ItemDefinition* def = ItemDatabase::Get().GetItem(slot.item.itemId);
    int basePrice = def ? def->basePrice : 0;
    return static_cast<int>((slot.overridePrice > 0 ? slot.overridePrice : basePrice) * rate);
}

void SystemMerchant::DisplayMerchantStock(Entity* merchant) {
    auto* merch = merchant->GetComponent<ComponentMerchant>();
    if (!merch) return;

    const auto& stock = merch->GetStock();
    sf::Vector2f basePos(650.f, 100.f);
    float currentY = basePos.y;
    float padding = 5.f;
    const float boxWidth = 500.f;
    const float boxHeight = 35.f;

    Entity* title = GameEngine::GetInstance().GetEntityManager().CreateEntity();
    title->AddComponent<ComponentTransform>(sf::Vector2f(basePos.x, currentY - boxHeight - 10), sf::Vector2f(boxWidth, boxHeight));
    title->AddComponent<ComponentFont>();
    title->AddComponent<ComponentTag>("MERCHANT_ITEM");

    auto* titleFont = title->GetComponent<ComponentFont>();
    titleFont->SetFontByName("testFont");
    titleFont->SetText("MARCHAND", false);
    titleFont->SetFixedOnScreen(true);
    titleFont->SetFillColor(sf::Color::Green);

    int selected = merch->GetSelectedIndex();

    for (size_t i = 0; i < stock.size(); ++i) {
        const auto& slot = stock[i];
        const auto* def = ItemDatabase::Get().GetItem(slot.item.itemId);
        if (!def || slot.item.quantity <= 0) continue;

        Entity* entry = GameEngine::GetInstance().GetEntityManager().CreateEntity();
        entry->AddComponent<ComponentTransform>(sf::Vector2f(basePos.x, currentY), sf::Vector2f(boxWidth, boxHeight));
        entry->AddComponent<ComponentFont>();
        entry->AddComponent<ComponentTag>("MERCHANT_ITEM");
		entry->AddComponent<ComponentItem>(slot.item);

        entry->AddComponent<ComponentClickable>();
        entry->GetComponent<ComponentClickable>()->SetOnLeftClick([i]() {
            auto* merchSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();
            Entity* merchant = merchSys->GetCurrentMerchant();
            if (!merchant) return;

            auto* merch = merchant->GetComponent<ComponentMerchant>();
            if (!merch) return;

            merch->SetSelectedIndex(i);

            Entity* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];
            player->GetComponent<ComponentInventory>()->SetSelectedIndex(-1);

            merchSys->ClearMerchantDisplay();
            merchSys->DisplayMerchantStock(merchant);
            GameEngine::GetInstance().GetSystem<SystemInventory>()->ClearInventoryDisplay();
            GameEngine::GetInstance().GetSystem<SystemInventory>()->DisplayInventory(player);
            });


        ComponentFont* font = entry->GetComponent<ComponentFont>();
        font->SetFontByName("testFont");
        font->SetFixedOnScreen(true);

        std::string prefix = (i == selected) ? "> " : "  ";
        font->SetText(prefix + def->name + " x" + std::to_string(slot.item.quantity) + " (" + std::to_string(GetItemPrice(slot, merch->GetBuyRate())) + " or)", false);
        font->SetFillColor((i == selected) ? sf::Color::Yellow : sf::Color::White);

        currentY += boxHeight + padding;
    }

    std::cout << "[Marchand] Affichage de " << stock.size() << " objets." << std::endl;
}

void SystemMerchant::ClearMerchantDisplay() {
    auto& em = GameEngine::GetInstance().GetEntityManager();
    for (auto* e : em.GetEntitiesByTag("MERCHANT_ITEM")) {
        em.DestroyEntity(e);
    }
}

bool SystemMerchant::IsMerchantVisible() const {
	return merchantIsVisible;
}

void SystemMerchant::SetMerchantIsVisible(bool visible) {
	merchantIsVisible = visible;
}

void SystemMerchant::SetCurrentMerchant(Entity* e) {
	currentMerchant = e;
}

Entity* SystemMerchant::GetCurrentMerchant() const {
	return currentMerchant;
}

int SystemMerchant::GetSellPrice(const std::string& itemId, Entity* merchant) const {
    auto* merch = merchant->GetComponent<ComponentMerchant>();
    if (!merch) return 0;

    const ItemDefinition* def = ItemDatabase::Get().GetItem(itemId);
    if (!def) return 0;

    return static_cast<int>(def->basePrice * merch->GetSellRate());
}

void SystemMerchant::GenerateRandomMerchantStock(Entity* merchant, int itemCount) {
    auto* merch = merchant->GetComponent<ComponentMerchant>();
    if (!merch) return;

    merch->ClearStock();

    const auto& itemDefs = ItemDatabase::Get().GetAllItems();
    std::vector<std::string> itemPool;

    for (const auto& [id, def] : itemDefs) {
        if (def.type != ItemType::Trophy && def.type != ItemType::QuestItem) {
            itemPool.push_back(id);
        }
    }

    for (int i = 0; i < itemCount; ++i) {
        if (itemPool.empty()) break;

        std::string itemId = itemPool[rand() % itemPool.size()];
        int quantity = rand() % 5 + 1;

        int overridePrice = 0;
        if (rand() % 2 == 0) {
            const auto* def = ItemDatabase::Get().GetItem(itemId);
            if (def && def->basePrice > 0) {
                float factor = 0.8f + static_cast<float>(rand() % 71) / 100.f;
                overridePrice = static_cast<int>(def->basePrice * factor);
            }
        }

        MerchantSlot slot(ItemInstance(itemId, quantity), overridePrice);
        merch->AddItem(slot);
    }

    std::cout << "[Merchant] Stock aléatoire généré (" << merch->GetStock().size() << " items)\n";
}






void SystemMerchant::Logs() {
    if (!debugMode || !logSystemMerchant) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int totalMerchants = 0;
    int totalItems = 0;
    int totalStock = 0;

    for (Entity* e : entities) {
        auto* merchant = e->GetComponent<ComponentMerchant>();
        if (!merchant) continue;

        ++totalMerchants;

        for (const auto& slot : merchant->GetStock()) {
            ++totalItems;
            totalStock += slot.item.quantity;

            const char* itemId = (char*)slot.item.itemId.c_str();
            int quantity = slot.item.quantity;
            int price = GameEngine::GetInstance()
                .GetSystem<SystemMerchant>()
                ->GetItemPrice(slot, merchant->GetBuyRate());

            HEAD("sys_MERCHANT") << "Merchant " << e->GetID()
                << " vend " << quantity
                << " x " << itemId
                << " a " << price << " or (piece)" << ENDL;
        }
    }

    HEAD("sys_MERCHANT") << "Marchands : " << (int)totalMerchants
        << " | Articles listes : " << (int)totalItems
        << " | Stock total : " << (int)totalStock << ENDL;
}
