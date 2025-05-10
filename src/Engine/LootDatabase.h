#pragma once
#include "ComponentLoot.h"

struct LootData {
    std::vector<LootSlot> items;
    int minGold = 0;
    int maxGold = 0;
};

class LootDatabase {
public:
    static LootDatabase& Get();
    const LootData& GetLootData(const std::string& mobId) const;

    bool LoadFromFile(const std::string& path);

    void LoadLootForAllEnemies(GameEngine* engine);
    const std::vector<LootSlot>& GetLootFor(const std::string& mobId) const;

private:
    std::unordered_map<std::string, LootData> lootTables;

};
