#include "pch.h"

ComponentLoot::ComponentLoot(Entity* entity)
    : Component(entity) {
}

void ComponentLoot::AddLoot(const LootSlot& loot) {
    lootTable.push_back(loot);
	//std::cout << "[ComponentLoot] Loot added: " << loot.item.itemId << " with chance: " << loot.dropChance << std::endl;
	//std::cout << "[ComponentLoot] Total loot slots: " << lootTable.size() << std::endl;
}

const std::vector<LootSlot>& ComponentLoot::GetLootTable() const {
    return lootTable;
}
