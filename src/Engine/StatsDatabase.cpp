#include "pch.h"

using json = nlohmann::json;

StatsDatabase& StatsDatabase::Get() {
    static StatsDatabase instance;
    return instance;
}

bool StatsDatabase::LoadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "[StatsDatabase] Erreur ouverture : " << path << std::endl;
        return false;
    }

    nlohmann::json json;
    try { in >> json; }
    catch (...) {
        std::cerr << "[StatsDatabase] Erreur parsing JSON\n";
        return false;
    }

    if (!json.contains("stats") || !json["stats"].is_array()) {
        std::cerr << "[StatsDatabase] Format invalide : 'stats' manquant ou incorrect.\n";
        return false;
    }

    profiles.clear();

    for (const auto& entry : json["stats"]) {
        if (!entry.contains("id")) continue;
        StatsDefinition def;
        def.id = entry["id"];
        if (entry.contains("texture") && entry["texture"].is_string())
            def.texture = entry["texture"];
        if (entry.contains("size") && entry["size"].is_array() && entry["size"].size() == 2) {
            def.size = { entry["size"][0], entry["size"][1] };
        }
        for (auto it = entry.begin(); it != entry.end(); ++it) {
            if (it.key() != "id" && it.key() != "texture" && it.value().is_number_integer())
                def.values[it.key()] = it.value().get<int>();
        }
        profiles[def.id] = def;
    }


    std::cout << "[StatsDatabase] " << profiles.size() << " profils charges depuis " << path << std::endl;
    return true;
}


const StatsDefinition* StatsDatabase::GetDefinition(const std::string& id) const {
    auto it = profiles.find(id);
    return (it != profiles.end()) ? &it->second : nullptr;
}
