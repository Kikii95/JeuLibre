#include "pch.h"
#include <fstream>

EffectDatabase& EffectDatabase::Get() {
    static EffectDatabase instance;
    return instance;
}

bool EffectDatabase::LoadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "[EffectDatabase] Erreur ouverture : " << path << std::endl;
        return false;
    }

    nlohmann::json json;
    try { in >> json; }
    catch (...) {
        std::cerr << "[EffectDatabase] Erreur parsing JSON\n";
        return false;
    }

    if (!json.contains("effects") || !json["effects"].is_array()) {
        std::cerr << "[EffectDatabase] Format invalide : 'effects' manquant ou incorrect.\n";
        return false;
    }

    effects.clear();

    for (const auto& entry : json["effects"]) {
        if (!entry.contains("id")) continue;
        EffectDefinition def;
        def.id = entry["id"];
        def.name = entry.value("name", "");
        def.description = entry.value("description", "");
        def.duration = entry.value("duration", 1);
        def.tickInterval = entry.value("tickInterval", 1.0f);

        std::string typeStr = entry.value("type", "debuff");
        def.isBuff = (typeStr == "buff");

        if (typeStr == "buff") def.type = EffectType::StatBoost;
        else if (typeStr == "debuff") def.type = EffectType::DamageOverTime;

        def.tickDamage = entry.value("tickDamage", 0);
        def.tickHeal = entry.value("tickHeal", 0);
        def.healAmount = entry.value("healAmount", 0);

        def.icon = entry.value("icon", "");
        def.tag = entry.value("tag", "");
        def.animation = entry.value("animation", "");

        if (entry.contains("statModifiers")) {
            for (auto& mod : entry["statModifiers"].items()) {
                def.statModifiers[mod.key()] = mod.value().get<int>();
            }
        }



        effects[def.id] = def;
    }

    std::cout << "[EffectDatabase] " << effects.size() << " effets charges depuis " << path << std::endl;
    return true;
}


const EffectDefinition* EffectDatabase::GetEffect(const std::string& id) const {
    auto it = effects.find(id);
    return it != effects.end() ? &it->second : nullptr;
}
