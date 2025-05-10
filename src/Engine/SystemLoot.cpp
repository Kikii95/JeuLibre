#include "pch.h"

SystemLoot::SystemLoot() {}

void SystemLoot::GenerateLoot(Entity* source, Entity* receiver) {
    auto* loot = source->GetComponent<ComponentLoot>();
    auto* inventory = receiver->GetComponent<ComponentInventory>();
    if (!loot || !inventory) return;

	std::cout << "[SystemLoot] Tentative de loot de l'entite " << source->GetID() << std::endl; 
    for (const LootSlot& slot : loot->GetLootTable()) {
        float roll = static_cast<float>(rand()) / RAND_MAX;
        if (roll <= slot.dropChance) {
            GameEngine::GetInstance().GetSystem<SystemItem>()->DropItem(slot.item, source->GetComponent<ComponentTransform>()->GetPosition());
            /*if (inventory->AddItem(slot.item)) {
                std::cout << "[SystemLoot] +" << slot.item.quantity
                    << " x " << slot.item.itemId << std::endl;
                GameEngine::GetInstance().GetSystem<SystemInventory>()->UpdateInventory(receiver);
            }
            else {
                std::cout << "[SystemLoot] INVENTAIRE PLEIN !" << std::endl;
				GameEngine::GetInstance().GetSystem<SystemItem>()->DropItem(slot.item, source->GetComponent<ComponentTransform>()->GetPosition()); //Drop item on ground
            }*/
        }
        else {
            std::cout << "[SystemLoot] echec drop : " << slot.item.itemId << std::endl;
        }
    }
    auto* stats = source->GetComponent<ComponentStats>();
    if (stats) {
        std::string id = stats->GetDefinitionId();
        const auto& data = LootDatabase::Get().GetLootData(id);

        if (data.maxGold > 0 && data.maxGold >= data.minGold) {
			int amount = rand() % (data.maxGold - data.minGold + 1) + data.minGold;
            SystemMoney* sysMoney = GameEngine::GetInstance().GetSystem<SystemMoney>();
            sysMoney->Give(receiver, amount);
            std::cout << "[SystemLoot] Drop or : " << amount << " or" << std::endl;
        }
    }

}

void SystemLoot::Logs() {
    if (!debugMode || !logSystemLoot) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int totalLooters = 0;
    int totalItems = 0;

    for (Entity* e : entities) {
        auto* loot = e->GetComponent<ComponentLoot>();
        if (!loot) continue;

        ++totalLooters;
        const auto& table = loot->GetLootTable();

        for (const LootSlot& slot : table) {
            ++totalItems;
            const char* id = (char*)slot.item.itemId.c_str();
            HEAD("sys_LOOT") << "Entite " << e->GetID()
                << " | Objet : " << id
                << " x" << (int)slot.item.quantity
                << " | Chance de drop : " << slot.dropChance << ENDL;
        }
    }

    HEAD("sys_LOOT") << "Sources de loot : " << (int)totalLooters
        << " | Objets potentiels : " << (int)totalItems << ENDL;
}
