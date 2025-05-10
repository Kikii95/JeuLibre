#include "pch.h"

using json = nlohmann::json;

SpawnerDatabase& SpawnerDatabase::Get() {
    static SpawnerDatabase instance;
    return instance;
}

const std::vector<SpawnerDefinition>& SpawnerDatabase::GetAll() const {
    return spawners;
}

bool SpawnerDatabase::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[SpawnerDatabase] Erreur d'ouverture du fichier : " << path << std::endl;
        return false;
    }

    json root;
    try {
        file >> root;
    }
    catch (const std::exception& e) {
        std::cerr << "[SpawnerDatabase] Erreur de parsing JSON : " << e.what() << std::endl;
        return false;
    }

    if (!root.contains("spawners") || !root["spawners"].is_array()) {
        std::cerr << "[SpawnerDatabase] Format JSON invalide : 'spawners' manquant ou incorrect." << std::endl;
        return false;
    }

    spawners.clear();
    const auto& array = root["spawners"];

    for (const auto& entry : array) {
        SpawnerDefinition def;

        def.id = entry.value("id", "");
        if (entry.contains("center") && entry["center"].is_array() && entry["center"].size() == 2) {
            def.center = sf::Vector2f(entry["center"][0], entry["center"][1]);
        }
        else {
            std::cerr << "[SpawnerDatabase] Spawner sans centre valide (id: " << def.id << "). Ignore." << std::endl;
            continue;
        }

        def.radius = entry.value("radius", 500.f);
        def.type = entry.value("type", "ENEMY");
        def.profileId = entry.value("profileId", "");
        def.maxEntities = entry.value("maxEntities", 3);
        def.respawnDelay = entry.value("respawnDelay", 5.f);
        def.difficultyZone = entry.value("difficultyZone", "ZONE_EASY");
		def.playerDespawnMargin = entry.value("playerDespawnMargin", 100.f);
		def.mobDespawnMargin = entry.value("mobDespawnMargin", 100.f);


        spawners.push_back(def);
    }

    std::cout << "[SpawnerDatabase] " << spawners.size() << " zones chargees depuis " << path << std::endl;
    return true;
}
