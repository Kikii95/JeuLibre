#include "pch.h"
#include "LootDatabase.h"

LootDatabase& LootDatabase::Get() {
	static LootDatabase instance;
	return instance;
}

const LootData& LootDatabase::GetLootData(const std::string& mobId) const {
    static const LootData empty;
    auto it = lootTables.find(mobId);
    return (it != lootTables.end()) ? it->second : empty;
}


bool LootDatabase::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[LootDatabase] Erreur ouverture : " << path << std::endl;
        return false;
    }

    nlohmann::json data;
    try { file >> data; }
    catch (...) {
        std::cerr << "[LootDatabase] Erreur parsing JSON\n";
        return false;
    }

    lootTables.clear();

    for (auto& [mobId, section] : data.items()) {
        LootData lootData;

        if (section.contains("money")) {
            lootData.minGold = section["money"].value("min", 0);
            lootData.maxGold = section["money"].value("max", 0);
        }

        if (section.contains("items")) {
            for (const auto& entry : section["items"]) {
                std::string itemId = entry["itemId"];
                int qty = entry.value("quantity", 1);
                float chance = entry.value("chance", 1.0f);
                lootData.items.emplace_back(ItemInstance(itemId, qty), chance);
            }
        }

        lootTables[mobId] = std::move(lootData);
    }

    std::cout << "[LootDatabase] " << lootTables.size() << " tables de loot chargees depuis " << path << std::endl;
    return true;
}


void LootDatabase::LoadLootForAllEnemies(GameEngine* engine) {
    EntityManager& em = engine->GetEntityManager();
    auto enemies = em.GetEntitiesByTag("ENEMY");

    for (Entity* e : enemies) {
        auto* loot = e->GetComponent<ComponentLoot>();
        auto* stats = e->GetComponent<ComponentStats>();
        if (!loot || !stats) continue;

        std::string id = stats->GetDefinitionId();
        const auto& table = LootDatabase::Get().GetLootFor(id);

        for (const LootSlot& slot : table) {
            loot->AddLoot(slot);
        }

        std::cout << "[Loot Init] " << id << " a recu " << table.size() << " objets de loot.\n";
    }
}

const std::vector<LootSlot>& LootDatabase::GetLootFor(const std::string& mobId) const {
    static const std::vector<LootSlot> empty;
    auto it = lootTables.find(mobId);
    return (it != lootTables.end()) ? it->second.items : empty;
}
