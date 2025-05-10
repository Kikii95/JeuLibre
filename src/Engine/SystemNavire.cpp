#include "pch.h"

SystemNavire::SystemNavire() {}

void SystemNavire::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto* entity : entities) {
        auto* navire = entity->GetComponent<ComponentNavire>();
        auto* transform = entity->GetComponent<ComponentTransform>();
        if (!navire || !transform) continue;

        float speedModifier = CalculateSpeedModifier(navire);
        sf::Vector2f direction = { 1.0f, 0.0f }; 

        transform->MoveBy(direction * speedModifier * dt);

    }
}

float SystemNavire::CalculateSpeedModifier(const ComponentNavire* navire) const {
    float sailIntegrity = navire->GetIntegrity(ShipPart::Sail);
    float rudderIntegrity = navire->GetIntegrity(ShipPart::Rudder);

    float avg = (sailIntegrity + rudderIntegrity) / 2.0f;
    return clamp(avg / 100.0f, 0.1f, 1.0f);
}


void SystemNavire::Logs() {
    if (!debugMode || !logSystemNavire) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int navigables = 0;

    for (Entity* e : entities) {
        auto* navire = e->GetComponent<ComponentNavire>();
        auto* transform = e->GetComponent<ComponentTransform>();
        if (!navire || !transform) continue;

        ++total;
        ++navigables;

        float sail = navire->GetIntegrity(ShipPart::Sail);
        float rudder = navire->GetIntegrity(ShipPart::Rudder);
        float speed = CalculateSpeedModifier(navire);

        HEAD("sys_NAVIRE") << "Entite " << e->GetID()
            << " | Voile : " << (int)sail
            << " | Gouvernail : " << (int)rudder
            << " | Vitesse modifiee : " << speed << ENDL;
    }

    HEAD("sys_NAVIRE") << "Navires contrôles : " << (int)navigables
        << " / Entites totales : " << (int)total << ENDL;
}
