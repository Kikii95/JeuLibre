#include "pch.h"

ActionDatabase& ActionDatabase::Get() {
    static ActionDatabase instance;
    return instance;
}

bool ActionDatabase::LoadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "[ActionDatabase] Erreur ouverture : " << path << std::endl;
        return false;
    }

    nlohmann::json json;
    try { in >> json; }
    catch (...) {
        std::cerr << "[ActionDatabase] Erreur parsing JSON\n";
        return false;
    }

    if (!json.contains("actions") || !json["actions"].is_array()) {
        std::cerr << "[ActionDatabase] Format invalide : 'actions' manquant ou incorrect.\n";
        return false;
    }

    actions.clear();

    for (const auto& entry : json["actions"]) {
        if (!entry.contains("id")) continue;
		/*ActionDefinition*/ ActionData def; // TO DO : ActionDefinition
        def.id = entry["id"];
        def.name = entry.value("name", "");
        //def.description = entry.value("description", "");
        //def.cooldown = entry.value("cooldown", 0);
        def.effectId = entry.value("effectId", "");
        actions[def.id] = def;
    }

    std::cout << "[ActionDatabase] " << actions.size() << " actions chargees depuis " << path << std::endl;
    return true;
}


const ActionData* ActionDatabase::GetAction(const std::string& id) const {
    auto it = actions.find(id);
    return it != actions.end() ? &it->second : nullptr;
}
