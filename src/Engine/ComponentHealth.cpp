#include "pch.h"

ComponentHealth::ComponentHealth(Entity* entity)
    : Component(entity) {
}

void ComponentHealth::SetHealth(int hp) {
    health = std::max(0, std::min(hp, maxHealth)); 
}

int ComponentHealth::GetHealth() const {
    return health;
}

void ComponentHealth::SetMaxHealth(int hp) {
    maxHealth = hp;
    if (health > maxHealth) {
        health = maxHealth;
    }
}

int ComponentHealth::GetMaxHealth() const {
    return maxHealth;
}



void SystemHealth::Logs() {
    if (!debugMode || !logSystemHealth) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int dead = 0;
    int low = 0;

    for (Entity* e : entities) {
        auto* health = e->GetComponent<ComponentHealth>();
        if (!health) continue;

        ++total;

        int hp = health->GetHealth();
        int max = health->GetMaxHealth();
        float percent = (float)hp / std::max(1, max);

        HEAD("sys_HEALTH") << "Entity " << e->GetID()
            << " | PV : " << hp << "/" << max
            << " (" << percent * 100.f << "%)" << ENDL;

        if (IsDead(e)) ++dead;
        else if (percent <= 0.3f) ++low;
    }

    HEAD("sys_HEALTH") << "Entites suivies : " << (int)total
        << " | Morts : " << (int)dead
        << " | PV critiques : " << (int)low << ENDL;
}
