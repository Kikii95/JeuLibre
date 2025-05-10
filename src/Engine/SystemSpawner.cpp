#include "pch.h"

SystemSpawner::SystemSpawner() {}

void SystemSpawner::RegisterSpawnZone(const SpawnZone& zoneData) {
    SpawnZone zone = zoneData;
    zone.timeSinceLastSpawn = ToolBox::GetInstance().RandomFloat(0.f, zone.respawnDelay); 
    zone.respawnDelay *= ToolBox::GetInstance().RandomFloat(0.9f, 1.1f); 
    zones.push_back(zone);

    if(debugMode) {
        // Cercle rouge 
        Entity* redZone = GameEngine::GetInstance().GetEntityManager().CreateEntity();
        redZone->AddComponent<ComponentTransform>(zone.center, sf::Vector2f(zone.radius * 2, zone.radius * 2));
        auto* renderRed = redZone->AddComponent<ComponentRender>();
        renderRed->SetRenderType(RenderType::Circle);
        renderRed->SetRenderLayer(1);
        renderRed->SetColor(sf::Color(255, 0, 0, 30));
        redZone->AddComponent<ComponentTag>("SPAWN_ZONE_DEBUG");

        // Cercle vert 
        float totalDetectionRadius = zone.playerDespawnMargin;
        Entity* greenZone = GameEngine::GetInstance().GetEntityManager().CreateEntity();
        greenZone->AddComponent<ComponentTransform>(zone.center, sf::Vector2f(totalDetectionRadius * 2, totalDetectionRadius * 2));
        auto* renderGreen = greenZone->AddComponent<ComponentRender>();
        renderGreen->SetRenderType(RenderType::Circle);
        renderGreen->SetRenderLayer(0);
        renderGreen->SetColor(sf::Color(0, 255, 0, 15));
        greenZone->AddComponent<ComponentTag>("SPAWN_PLAYER_DETECT_DEBUG");
    }

    std::cout << "[Spawner][DEBUG] Création zone " << zone.id
        << " | Center: (" << zone.center.x << ", " << zone.center.y << ")"
        << " | Radius: " << zone.radius << std::endl;


}


void SystemSpawner::Update(float dt, const std::vector<Entity*>& entities) {
    Entity* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];
    if (!player) return;

    sf::Vector2f playerPos = player->GetComponent<ComponentTransform>()->GetPosition();

    for (SpawnZone& zone : zones) {
        zone.timeSinceLastSpawn += dt;

        float distToPlayer = ToolBox::GetInstance().Distance(playerPos, zone.center);

        if (distToPlayer < zone.radius) {
            TrySpawn(zone);
        }

        for (Entity* entity : GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag(zone.type)) {
            if (zone.type == "MERCHANT") continue;

            auto* transform = entity->GetComponent<ComponentTransform>();
            auto* zoneLink = entity->GetComponent<ComponentZoneSpawner>();
            if (!transform || !zoneLink) continue;
            if (zoneLink->GetZoneId() != zone.id) continue;

            float distEntityToZone = ToolBox::GetInstance().Distance(transform->GetPosition(), zone.center);

            if (distToPlayer > zone.playerDespawnMargin || distEntityToZone > zone.mobDespawnMargin) {
                GameEngine::GetInstance().GetEntityManager().DestroyEntity(entity);
                //std::cout << "[Spawner] Despawn " << zone.type
                //    << " (zone " << zone.id << ") - joueur ou mob trop loin\n";
            }
        }
    }
}



void SystemSpawner::TrySpawn(SpawnZone& zone) {
    int currentCount = CountEntitiesInZone(zone);
    if (currentCount >= zone.maxEntities) return;

    if (zone.timeSinceLastSpawn < zone.respawnDelay)
        return;

    float ratio = static_cast<float>(currentCount) / zone.maxEntities;
    float spawnProbability = (1.0f - ratio) * 0.5f;

    if (ToolBox::GetInstance().RandomFloat(0.f, 1.f) >= spawnProbability)
        return;

    const int maxTries = 10;
    const float spacing = 200.f;
    int tries = 0;

    std::vector<sf::Vector2f> existingPositions;
    for (Entity* e : GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("ENEMY")) {
        auto* t = e->GetComponent<ComponentTransform>();
        auto* s = e->GetComponent<ComponentZoneSpawner>();
        if (!t || !s) continue;

        if (s->GetZoneId() == zone.id) {
            existingPositions.push_back(t->GetPosition());
        }
    }

    while (tries < maxTries) {
        sf::Vector2f pos = GetRandomPointInZone(zone);

        bool tooClose = false;
        for (const auto& p : existingPositions) {
            if (ToolBox::GetInstance().Distance(pos, p) < spacing) {
                tooClose = true;
                break;
            }
        }

        if (!tooClose) {
            Entity* e = EntityFactory::CreateEnemy(zone.id, zone.profileId, zone.difficultyZone, pos);
            if (e) {
                zone.timeSinceLastSpawn = 0.f;
                return;
            }
        }

        ++tries;
    }
}


int SystemSpawner::CountEntitiesInZone(const SpawnZone& zone) {
    int count = 0;
    auto& em = GameEngine::GetInstance().GetEntityManager();

    for (Entity* entity : em.GetEntitiesByTag(zone.type)) {
        auto* transform = entity->GetComponent<ComponentTransform>();
        auto* zoneLink = entity->GetComponent<ComponentZoneSpawner>();
        if (!transform || !zoneLink) continue;

        if (zoneLink->GetZoneId() != zone.id) continue;

        if (ToolBox::GetInstance().Distance(transform->GetPosition(), zone.center) < zone.radius) {
            count++;
        }
    }

    return count;
}

void SystemSpawner::SpawnStaticEntity(const std::string& profileId, const sf::Vector2f& center, float radius, float spacing, int count) {
    int maxEntities = static_cast<int>((3.14159f * radius * radius) / (spacing * spacing));
    if (count > maxEntities) {
        std::cout << "[Spawner] Count demandé (" << count << ") dépasse la capacité max (" << maxEntities << "), ajustement.\n";
        count = maxEntities;
    }

    int spawned = 0;
    int tries = 0;
    int maxTries = count * 20;

    std::vector<sf::Vector2f> usedPositions;

    while (spawned < count && tries < maxTries) {
        sf::Vector2f offset(
            static_cast<float>(rand() % static_cast<int>(radius * 2)) - radius,
            static_cast<float>(rand() % static_cast<int>(radius * 2)) - radius
        );
        sf::Vector2f spawnPos = center + offset;

        bool tooClose = false;
        for (const auto& pos : usedPositions) {
            if (ToolBox::GetInstance().Distance(spawnPos, pos) < spacing) {
                tooClose = true;
                break;
            }
        }
        if (tooClose) {
            ++tries;
            continue;
        }

        Entity* merchant = EntityFactory::CreateMerchant(profileId, spawnPos);
        if (merchant) {
            merchant->AddComponent<ComponentZoneSpawner>("STATIC_MERCHANT");
            usedPositions.push_back(spawnPos);
            ++spawned;
        }

        ++tries;
    }

    std::cout << "[Spawner] Merchants statiques générés : " << spawned << "/" << count << std::endl;
}

sf::Vector2f SystemSpawner::GetRandomPointInZone(const SpawnZone& zone) {
    float angle = ToolBox::GetInstance().RandomFloat(0.f, 2.f * 3.14159265f); 
    float radius = ToolBox::GetInstance().RandomFloat(0.f, zone.radius);     

    float x = zone.center.x + std::cos(angle) * radius;
    float y = zone.center.y + std::sin(angle) * radius;

    return sf::Vector2f(x, y);
}
