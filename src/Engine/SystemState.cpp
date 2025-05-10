#include "pch.h"

SystemState::SystemState() {}

void SystemState::Update(float dt, const std::vector<Entity*>& entities) {
    for (Entity* e : entities) {
        auto* state = e->GetComponent<ComponentState>();
        if (!state) continue;

        switch (state->GetState()) {
        case EntityState::Attacking:
        case EntityState::Moving:
        case EntityState::UsingItem:
            Execute(e);
            break;
        default:
            break;
        }
    }
}

void SystemState::Execute(Entity* entity) {
    auto* state = entity->GetComponent<ComponentState>();
    auto* ai = entity->GetComponent<ComponentAI>();

    switch (state->GetState()) {
    case EntityState::Attacking: {
        if (ai && ai->GetTarget()) {
            SystemCombat combat;
            combat.Update(0.f, { entity }); 
        }
        state->SetState(EntityState::Waiting);
        break;
    }

    case EntityState::Moving: {
        std::cout << "[SystemState] Deplacement d’une entite (simule)." << std::endl;
        state->SetState(EntityState::Waiting);
        break;
    }

    case EntityState::UsingItem: {
        std::cout << "[SystemState] Utilisation d’un objet (simule)." << std::endl;
        state->SetState(EntityState::Waiting);
        break;
    }

    default: break;
    }
}

void SystemState::Logs() {
    if (!debugMode || !logSystemState) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int attacking = 0;
    int moving = 0;
    int waiting = 0;
    int idle = 0;

    for (Entity* e : entities) {
        auto* state = e->GetComponent<ComponentState>();
        if (!state) continue;

        ++total;
        switch (state->GetState()) {
        case EntityState::Attacking: ++attacking; break;
        case EntityState::Moving:    ++moving;    break;
        case EntityState::Waiting:   ++waiting;   break;
        case EntityState::Idle:      ++idle;      break;
        default: break;
        }
    }

    HEAD("sys_STATE") << "Entites avec ComponentState : " << (int)total << ENDL;
    HEAD("sys_STATE") << "- Attacking : " << (int)attacking
        << " | Moving : " << (int)moving
        << " | Waiting : " << (int)waiting
        << " | Idle : " << (int)idle << ENDL;
}
