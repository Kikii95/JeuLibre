#include "pch.h"

SystemTurnOrder::SystemTurnOrder() {}

void SystemTurnOrder::Update(float dt, const std::vector<Entity*>& entities) {
    
}

void SystemTurnOrder::StartNewRound(const std::vector<Entity*>& entities) {
    turnQueue.clear();
    for (auto* entity : entities) {
        if (entity->HasComponent<ComponentTurnOrder>()) {
            auto* turn = entity->GetComponent<ComponentTurnOrder>();
            turn->SetHasPlayed(false);
            turnQueue.push_back(entity);
        }
    }

    SortByInitiative(turnQueue);
    currentIndex = 0;
}

Entity* SystemTurnOrder::GetNextEntityToPlay(const std::vector<Entity*>& entities) {
    while (currentIndex < static_cast<int>(turnQueue.size())) {
        Entity* e = turnQueue[currentIndex++];
        auto* turn = e->GetComponent<ComponentTurnOrder>();
        if (!turn->HasPlayed()) {
            turn->SetHasPlayed(true);

            auto* state = e->GetComponent<ComponentState>();
            if (state) state->SetState(EntityState::Waiting);

            return e;
        }
    }

    return nullptr; 
}

void SystemTurnOrder::SortByInitiative(std::vector<Entity*>& entities) {
    std::sort(entities.begin(), entities.end(), [](Entity* a, Entity* b) {
        auto* turnA = a->GetComponent<ComponentTurnOrder>();
        auto* turnB = b->GetComponent<ComponentTurnOrder>();
        return turnA->GetTotalInitiative() > turnB->GetTotalInitiative();
        });
}

void SystemTurnOrder::Logs() {
    if (!debugMode || !logSystemTurnOrder) return;

    HEAD("sys_TURNORDER") << "Ordre actuel du tour : " << ENDL;

    for (size_t i = 0; i < turnQueue.size(); ++i) {
        Entity* e = turnQueue[i];
        auto* turn = e->GetComponent<ComponentTurnOrder>();
        if (!turn) continue;

        const int id = e->GetID();
        const int baseInit = turn->GetBaseInitiative();
        const int bonus = turn->GetBonusInitiative();
        const int total = turn->GetTotalInitiative();
        const bool played = turn->HasPlayed();

        HEAD("sys_TURNORDER") << "#" << (int)(i + 1) << " | Entite " << id
            << " | Init: " << baseInit << " + " << bonus
            << " = " << total
            << " | A joue : " << (played ? "Oui" : "Non") << ENDL;
    }

    HEAD("sys_TURNORDER") << "Index actuel dans la file : "
        << (int)currentIndex << "/" << (int)turnQueue.size() << ENDL;
}
