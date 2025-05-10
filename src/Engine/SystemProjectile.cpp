#include "pch.h"

SystemProjectile::SystemProjectile() {}

void SystemProjectile::Update(float dt, const std::vector<Entity*>& entities) {
    for (Entity* e : entities) {
        auto* proj = e->GetComponent<ComponentProjectile>();
        if (!proj) continue;

        if (proj->rangeLeft <= 0 || proj->hitsRemaining <= 0) {
            e->Destroy();
            continue;
        }

        int parity = proj->gridPos.x % 2;
        sf::Vector2i offset = HexDirectionToOffset(proj->direction, parity);
        proj->gridPos += offset;
        proj->rangeLeft--;

        const auto* def = ItemDatabase::Get().GetItem(proj->itemId);
        if (!def) continue;

        auto impacted = GameEngine::GetInstance().GetEntityManager().GetEntitiesInArea(
            proj->gridPos, def->area, def->areaSize, proj->direction,
            [](Entity* e) { return e->HasComponent<ComponentHealth>(); }
        );

        for (Entity* target : impacted) {
            if (target == proj->owner) continue;

            auto* hp = target->GetComponent<ComponentHealth>();
            if (hp) {
                GameEngine::GetInstance().GetSystem<SystemHealth>()->ApplyDamage(target, 15);

                if (!def->effectId.empty()) {
					/*GameEngine::GetInstance().GetSystemManager().GetSystem<SystemBuffDebuff>()->ApplyEffect(target, def->effectId);*/
                }

                proj->hitsRemaining--;
                if (proj->hitsRemaining <= 0) {
                    e->Destroy();
                    break;
                }
            }
        }
    }
}

void SystemProjectile::SpawnProjectile(Entity* owner, const std::string& itemId, HexDirection direction) {
    const auto* def = ItemDatabase::Get().GetItem(itemId);
    if (!def) return;

    Entity* p = GameEngine::GetInstance().GetEntityManager().CreateEntity();

    auto* proj = p->AddComponent<ComponentProjectile>();
    proj->itemId = itemId;
    proj->owner = owner;
    proj->direction = direction;
    proj->rangeLeft = def->range;
    proj->hitsRemaining = def->penetration > 0 ? def->penetration : 1;

    auto* ownerTransform = owner->GetComponent<ComponentTransform>();
    proj->gridPos = static_cast<sf::Vector2i>(ownerTransform->GetPosition());
}

void SystemProjectile::Logs() {
    if (!debugMode || !logSystemProjectile) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int active = 0;
    int destroyedSoon = 0;

    for (Entity* e : entities) {
        auto* proj = e->GetComponent<ComponentProjectile>();
        if (!proj) continue;

        ++total;
        if (proj->rangeLeft <= 1 || proj->hitsRemaining <= 1) ++destroyedSoon;
        else ++active;
    }

    HEAD("sys_PROJECTILE") << "Projectiles en jeu : " << (int)total
        << " | Actifs : " << (int)active
        << " | En fin de vie : " << (int)destroyedSoon << ENDL;
}
