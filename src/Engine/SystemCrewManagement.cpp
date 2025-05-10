#include "pch.h"

SystemCrewManagement::SystemCrewManagement() {}

void SystemCrewManagement::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto* entity : entities) {
        if (!entity->HasComponent<ComponentCrewMember>()) continue;
        PerformRoleLogic(entity);
    }
}

void SystemCrewManagement::PerformRoleLogic(Entity* crew) {
    auto* member = crew->GetComponent<ComponentCrewMember>();
    auto role = member->GetRole();

    switch (role) {
    case CrewRole::Medic: {
        auto* health = crew->GetComponent<ComponentHealth>();
        GameEngine::GetInstance().GetSystem<SystemHealth>()->ApplyDamage(crew, 15);
        std::cout << "[SystemCrewManagement] Soins prodigues." << std::endl;
        
        break;
    }

    case CrewRole::Sailor: {
        //TO DO
        break;
    }

    default:
        break;
    }
}

void SystemCrewManagement::Logs() {
    if (!debugMode || !logSystemCrewManagement) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int medics = 0;
    int sailors = 0;

    for (Entity* e : entities) {
        auto* crew = e->GetComponent<ComponentCrewMember>();
        if (!crew) continue;

        ++total;
        std::string roleName;

        switch (crew->GetRole()) {
        case CrewRole::Medic:
            ++medics;
            roleName = "Medic";
            break;
        case CrewRole::Sailor:
            ++sailors;
            roleName = "Sailor";
            break;
        default:
            roleName = "Unknown";
            break;
        }

        HEAD("sys_CREW") << "Entity " << e->GetID()
            << " | Rôle : " << (char*)roleName.c_str()
            << ENDL;
    }

    HEAD("sys_CREW") << "Total membres d’equipage : " << (int)total
        << " | Medics : " << (int)medics
        << " | Sailors : " << (int)sailors
        << ENDL;
}
