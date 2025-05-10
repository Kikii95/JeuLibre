#pragma once

struct LootSlot {
    ItemInstance item;
	float dropChance = 1.0f;

    LootSlot(const ItemInstance& instance, float chance = 1.0f)
        : item(instance), dropChance(chance) {
    }
};

class ComponentLoot : public Component {
public:
    ComponentLoot(Entity* entity);

    void AddLoot(const LootSlot& loot);
    const std::vector<LootSlot>& GetLootTable() const;

private:
    std::vector<LootSlot> lootTable;
};
