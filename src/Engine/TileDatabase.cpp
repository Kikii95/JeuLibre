#include "pch.h"

using json = nlohmann::json;

TileDatabase& TileDatabase::Get() {
    static TileDatabase instance;
    return instance;
}

bool TileDatabase::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[TileDatabase] Erreur : impossible d’ouvrir " << path << std::endl;
        return false;
    }

    json j;
    file >> j;

    if (!j.contains("tiles") || !j["tiles"].is_array()) {
        std::cerr << "[TileDatabase] Format invalide dans " << path << std::endl;
        return false;
    }

    for (const auto& entry : j["tiles"]) {
        TileDefinition def;
        def.id = entry.value("id", 0);
        def.texturePath = entry.value("texture", "");

        tiles[def.id] = def;
    }

    std::cout << "[TileDatabase] " << tiles.size() << " tiles chargées depuis " << path << std::endl;
    return true;
}

const TileDefinition* TileDatabase::GetTile(int id) const {
    auto it = tiles.find(id);
    return (it != tiles.end()) ? &it->second : nullptr;
}
