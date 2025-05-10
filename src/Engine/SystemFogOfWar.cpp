#include "pch.h"

SystemFogOfWar::SystemFogOfWar() {}

void SystemFogOfWar::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto* entity : entities) {
        auto* fog = entity->GetComponent<ComponentFogOfWar>();
        auto* transform = entity->GetComponent<ComponentTransform>();
        if (!fog || !transform) continue;

        RevealAround(entity, 5); 
    }
}

void SystemFogOfWar::RevealAround(Entity* entity, int radius) {
    auto* fog = entity->GetComponent<ComponentFogOfWar>();
    auto* transform = entity->GetComponent<ComponentTransform>();
    if (!fog || !transform) return;

    sf::Vector2f pos = transform->GetPosition();
    int x = static_cast<int>(pos.x) / 32; 
    int y = static_cast<int>(pos.y) / 32;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (std::sqrt(dx * dx + dy * dy) <= radius) {
                fog->Reveal({ x + dx, y + dy });
            }
        }
    }
}

void SystemFogOfWar::Logs() {
    if (!debugMode || !logSystemFogOfWar) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int tracked = 0;
    int totalRevealed = 0;

    for (Entity* e : entities) {
        auto* fog = e->GetComponent<ComponentFogOfWar>();
        if (!fog) continue;

        ++tracked;

        const auto& revealed = fog->GetRevealedTiles();
        totalRevealed += (int)revealed.size();

        HEAD("sys_FOG") << "Entity " << e->GetID()
            << " a revele " << (int)revealed.size()
            << " cases." << ENDL;
    }

    HEAD("sys_FOG") << "Entites avec brouillard actif : " << (int)tracked
        << " | Cases visibles au total : " << (int)totalRevealed << ENDL;
}
