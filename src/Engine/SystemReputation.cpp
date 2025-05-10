#include "pch.h"

SystemReputation::SystemReputation() {}

void SystemReputation::Update(float dt, const std::vector<Entity*>& entities) {
}

void SystemReputation::ModifyReputation(Entity* entity, const std::string& factionId, int delta) {
    auto* rep = entity->GetComponent<ComponentReputation>();
    if (!rep) return;

    rep->ModifyReputation(factionId, delta);
    std::cout << "[SystemReputation] Reputation modifiee pour " << factionId
        << " -> nouvelle valeur : " << rep->GetReputation(factionId) << std::endl;
}

int SystemReputation::GetReputationValue(Entity* entity, const std::string& factionId) {
    auto* rep = entity->GetComponent<ComponentReputation>();
    return rep ? rep->GetReputation(factionId) : 0;
}

ReputationLevel SystemReputation::GetReputationLevel(Entity* entity, const std::string& factionId) {
    auto* rep = entity->GetComponent<ComponentReputation>();
    return rep ? rep->GetReputationLevel(factionId) : ReputationLevel::Neutral;
}

void SystemReputation::Logs() {
    if (!debugMode || !logSystemReputation) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    HEAD("sys_REPUTATION") << "etat des reputations :" << ENDL;

    for (Entity* e : entities) {
        auto* rep = e->GetComponent<ComponentReputation>();
        if (!rep) continue;

        int id = e->GetID();
        const auto& allRep = rep->GetAllReputations();

        for (const auto& [faction, value] : allRep) {
            ReputationLevel level = rep->GetReputationLevel(faction);

            const char* levelStr =
                (level == ReputationLevel::Hostile) ? "Hostile" :
                (level == ReputationLevel::Neutral) ? "Neutre" :
                (level == ReputationLevel::Friendly) ? "Allie" : "Inconnu";

            HEAD("sys_REPUTATION") << "Entite " << id
                << " | Faction : " << (char*)faction.c_str()
                << " | Valeur : " << (int)value
                << " | Niveau : " << (char*)levelStr << ENDL;
        }
    }
}
