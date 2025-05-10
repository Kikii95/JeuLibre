#include "pch.h"

Entity* EntityManager::CreateEntity() {
    auto entity = std::make_unique<Entity>(nextEntityID);
    Entity* rawPtr = entity.get();
    entities.emplace(nextEntityID, std::move(entity)); 

    nextEntityID++;
    return rawPtr;
}

Entity* EntityManager::CreateMapEntity() {
	auto entity = std::make_unique<Entity>(nextMapEntityID);
	Entity* rawPtr = entity.get();
	mapentities.emplace(nextMapEntityID, std::move(entity));
	nextMapEntityID++;
	return rawPtr;
}

Entity* EntityManager::CreateHexGridEntity()
{
	auto entity = std::make_unique<Entity>(nextMapEntityID);
	Entity* rawPtr = entity.get();
	hexgridentities.emplace(nextMapEntityID, std::move(entity));
	nextMapEntityID++;
	return rawPtr;
}

Entity* EntityManager::GetEntity(int id) {
    auto it = entities.find(id);
    return (it != entities.end()) ? it->second.get() : nullptr;
}

std::vector<Entity*> EntityManager::GetAllEntities() {
    std::vector<Entity*> entityList;
    entityList.reserve(entities.size()); 
    for (auto& pair : entities) {
        entityList.push_back(pair.second.get());
    }
    return entityList;
}

//std::vector<Entity*> EntityManager::GetAllEntitiesInZone(const SpawnZone& zone) {
//    std::vector<Entity*> result;
//    std::vector<Entity*> allEntities = GetAllEntities(); 
//
//    for (Entity* e : allEntities) {
//        if (!e->HasComponent<ComponentTransform>()) continue;
//        if (!e->HasComponent<ComponentZoneSpawner>()) continue;
//
//        auto* transform = e->GetComponent<ComponentTransform>();
//        auto* spawner = e->GetComponent<ComponentZoneSpawner>();
//
//        if (spawner->GetZoneId() == zone.id) {
//            float dist = ToolBox::GetInstance().Distance(transform->GetPosition(), zone.center);
//            if (dist <= zone.radius) {
//                result.push_back(e);
//            }
//        }
//    }
//
//    return result;
//}
//


std::vector<Entity*> EntityManager::GetAllMapEntities() {
	std::vector<Entity*> entityList;
	entityList.reserve(mapentities.size());
	for (auto& pair : mapentities) {
		entityList.push_back(pair.second.get());
	}
	return entityList;
}

std::vector<Entity*> EntityManager::GetAllHexGridEntities()
{
    std::vector<Entity*> entityList;
    entityList.reserve(hexgridentities.size());
    for (auto& pair : hexgridentities) {
        entityList.push_back(pair.second.get());
    }
    return entityList;
}

std::vector<Entity*> EntityManager::GetEntitiesByTag(const std::string& tag) {
    std::vector<Entity*> result;
    for (auto& pair : entities) {
        Entity* entity = pair.second.get(); 
        ComponentTag* tagComp = entity->GetComponent<ComponentTag>();
        if (tagComp && tagComp->GetTag() == tag) {
            result.push_back(entity);
        }
    }
    return result;
}

std::vector<Entity*> EntityManager::GetEntitiesInArea(const sf::Vector2i& center, AreaType type, int size, HexDirection direction, std::function<bool(Entity*)> filter
)
{
    std::vector<Entity*> result;
    auto all = GetAllEntities(); 

    for (Entity* e : all) {
        auto* transform = e->GetComponent<ComponentTransform>();
        if (!transform) continue;

        sf::Vector2i pos = static_cast<sf::Vector2i>(transform->GetPosition());
        int dx = pos.x - center.x;
        int dy = pos.y - center.y;
        int manhattan = abs(dx) + abs(dy);
        bool add = false;

        // CIRCLE (zone autour)
        if (type == AreaType::Circle) {
            if (manhattan <= size) add = true;
        }

        // LINE (devant, selon direction hex)
        else if (type == AreaType::Line) {
            sf::Vector2i offset = HexDirectionToOffset(direction, center.x % 2);
            for (int i = 1; i <= size; ++i) {
                if (pos == center + offset * i) {
                    add = true;
                    break;
                }
            }
        }

        // ARC (3 cases devant dans une ligne)
        else if (type == AreaType::Arc) {
            sf::Vector2i forward = HexDirectionToOffset(direction, center.x % 2);
            sf::Vector2i left = HexDirectionToOffset(static_cast<HexDirection>((static_cast<int>(direction) + 5) % 6), center.x % 2);
            sf::Vector2i right = HexDirectionToOffset(static_cast<HexDirection>((static_cast<int>(direction) + 1) % 6), center.x % 2);

            if (pos == center + forward ||
                pos == center + left ||
                pos == center + right)
                add = true;
        }

        // CONE (3-4 cases en triangle etendu)
        else if (type == AreaType::Cone) {
            sf::Vector2i dirOffset = HexDirectionToOffset(direction, center.x % 2);
            for (int i = 1; i <= size; ++i) {
                sf::Vector2i base = center + dirOffset * i;
                if (pos == base) {
                    add = true;
                    break;
                }
                sf::Vector2i left = base + HexDirectionToOffset(static_cast<HexDirection>((static_cast<int>(direction) + 5) % 6), center.x % 2);
                sf::Vector2i right = base + HexDirectionToOffset(static_cast<HexDirection>((static_cast<int>(direction) + 1) % 6), center.x % 2);

                if (pos == left || pos == right) {
                    add = true;
                    break;
                }
            }
        }

        if (add && (!filter || filter(e))) {
            result.push_back(e);
        }
    }

    return result;
}


void EntityManager::DestroyEntity(Entity* e) {
    e->Destroy();
    MarkForDeletion(e);
}


void EntityManager::MarkForDeletion(Entity* entity) {
    m_entitiesToDelete.insert(entity);
}

void EntityManager::Cleanup() {
    for (Entity* e : m_entitiesToDelete) {
        int id = e->GetID();  
        auto it = entities.find(id);
        if (it != entities.end()) {
            entities.erase(it); 
            /*std::cout << "[EntityManager] Entite " << id << " supprimee.\n";*/
        }
    }

    m_entitiesToDelete.clear();

    if (entities.empty()) {
        std::cout << "[EntityManager] Toutes les entites ont ete supprimees. Fermeture demandee.\n";
        /*GameEngine::GetInstance().GetWindow().close();*/
    }
}



void EntityManager::Clear() {
    entities.clear();
	mapentities.clear();
	hexgridentities.clear();
}
