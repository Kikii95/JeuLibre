#include "pch.h"

SystemFaction::SystemFaction() {}

void SystemFaction::Update(float dt, const std::vector<Entity*>& entities) {
}

FactionRelation SystemFaction::GetRelationToPlayer(Entity* entity, Entity* player) {
    auto* faction = entity->GetComponent<ComponentFaction>();
    auto* playerRep = player->GetComponent<ComponentReputation>();
    if (!faction || !playerRep) return FactionRelation::Neutral;

    ReputationLevel level = playerRep->GetReputationLevel(faction->GetFactionId());

    switch (level) {
    case ReputationLevel::Hostile:  return FactionRelation::Hostile;
    case ReputationLevel::Neutral:  return FactionRelation::Neutral;
    case ReputationLevel::Friendly: return FactionRelation::Friendly;
    default:                        return FactionRelation::Neutral;
    }
}

void SystemFaction::ApplyZoneModifier(Entity* e) {
    auto* faction = e->GetComponent<ComponentFaction>();
    auto* stats = e->GetComponent<ComponentStats>();
    if (!faction || !stats) return;

    std::string zone = faction->GetFactionId();

    if (zone == "north") {
        stats->AddModifier("attack", 2);
        stats->AddModifier("defense", 1);
    }
    else if (zone == "south") {
        stats->AddModifier("attack", -1);
    }
}

void SystemFaction::Logs() {
    if (!debugMode || !logSystemFaction) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    std::unordered_map<std::string, int> zones;

    for (Entity* e : entities) {
        auto* faction = e->GetComponent<ComponentFaction>();
        if (!faction) continue;

        ++total;
        std::string zone = faction->GetFactionId();
        zones[zone]++;

        HEAD("sys_FACTION") << "Entity " << e->GetID()
            << " appartient a la zone : " << (char*)zone.c_str()
            << ENDL;
    }

    for (const auto& [zone, count] : zones) {
        HEAD("sys_FACTION") << "Zone : " << (char*)zone.c_str()
            << " | Entites : " << (int)count << ENDL;
    }

    HEAD("sys_FACTION") << "Total d’entites avec une faction definie : " << (int)total << ENDL;
}
