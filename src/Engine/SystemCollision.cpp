#include "pch.h"
#include "../src/Game/GameplayScene.h"
#include "../src/Game/ExploNavalScene.h"

#include "../src/Game/ExploMountainIslandScene.h"
#include "../src/Game/ExploCressentIslandScene.h"
#include "../src/Game/ExploGladeIslandScene.h"
#include "../src/Game/ExploLakeIslandScene.h"
#include "../src/Game/ExploYingYangIslandScene.h"

// #include "GameModeManager.h" 

SystemCollision::SystemCollision() {}

void SystemCollision::SetExplorationMode(bool active) {
    explorationMode = active;
}

Entity* SystemCollision::GetLastMobCollision(Entity* actor) {
    auto it = lastMobCollisions.find(actor);
	/*std::cout << "[LastMobCollision] Actor : " << actor->GetID() << " - Target : " << (it != lastMobCollisions.end() ? it->second->GetID() : -1) << "\n";*/
    return (it != lastMobCollisions.end()) ? it->second : nullptr;
}

Entity* SystemCollision::GetCurrentMobCollision(Entity* actor) {
    for (const auto& [a, b] : mobCollisionPairs) {
		/*std::cout << "[Collision] Mob : " << a->GetID() << " - " << b->GetID() << "\n";*/
        if (a == actor) return b;
    }
    return nullptr;
}

void SystemCollision::Update(float dt, const std::vector<Entity*>& entities) {
    if (!explorationMode) return; 
    mobCollisionPairs.clear();


    for (size_t i = 0; i < entities.size(); ++i) {
        Entity* a = entities[i];

        if (a->GetComponent<ComponentProjectile>()) continue; //TO DO : 

        auto* colA = a->GetComponent<ComponentCollider>();
        auto* trA = a->GetComponent<ComponentTransform>();
        if (!colA || !trA) continue;

        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity* b = entities[j];
            if (b->GetComponent<ComponentProjectile>()) continue;

            auto* colB = b->GetComponent<ComponentCollider>();
            auto* trB = b->GetComponent<ComponentTransform>();
            if (!colB || !trB) continue;
            if (!colB->IsColliding()) continue;

            sf::FloatRect rectA(trA->GetPosition(), trA->GetSize());
            sf::FloatRect rectB(trB->GetPosition(), trB->GetSize());

            if ((rectA.findIntersection(rectB)).has_value()) {
                ResolveCollision(a, b);
            }
        }
    }
}

void SystemCollision::ResolveCollision(Entity* a, Entity* b) {
    auto* colA = a->GetComponent<ComponentCollider>();
    auto* colB = b->GetComponent<ComponentCollider>();
    if (!colA || !colB) return;

    Entity* actor = a;
    Entity* target = b;
    ColliderType type = colB->GetColliderType();

    if (colA->GetColliderType() != ColliderType::Solid) {
        actor = b;
        target = a;
        type = colA->GetColliderType();
    }

    auto* physics = actor->GetComponent<ComponentPhysics>();
    if (!physics) return;

    switch (type) {
    case ColliderType::Solid: {

		if (physics->IsOnGround()) break;

        auto* transform = actor->GetComponent<ComponentTransform>();
        auto* physics = actor->GetComponent<ComponentPhysics>();
        if (!transform) break;

        sf::Vector2f prev = transform->GetPreviousPosition();
        sf::Vector2f curr = transform->GetPosition();
        sf::Vector2f delta = curr - prev;

        if (curr.y > target->GetComponent<ComponentTransform>()->GetPosition().y + target->GetComponent<ComponentTransform>()->GetSize().y / 2) {
            physics->SetIsGrounded(true);
            break;
        }
        
        sf::Vector2f rollback = curr;
        if (std::abs(delta.x) > 0.001f) rollback.x = prev.x;
        if (std::abs(delta.y) > 0.001f) rollback.y = prev.y;

        transform->SetPosition(prev);
		physics->SetAcceleration({ 0.f, 0.f });

        if (physics) {
            if (std::abs(delta.x) > 0.001f) physics->SetVelocityX(0.f);
            if (delta.y < 0.0f) physics->SetVelocityY(0.f);
        }
        


        break;
    }


    case ColliderType::Mob: {
        lastMobCollisions[actor] = target;
        mobCollisionPairs.push_back({ actor, target });


        // ===================

        break;
    }
    case ColliderType::Island: {/*
        lastMobCollisions[actor] = target;*/
        mobCollisionPairs.push_back({ actor, target });

        // === Bloc ajout� ===
        auto* currentCollision = GetCurrentMobCollision(actor);
        if (currentCollision) {
            auto* tag = currentCollision->GetComponent<ComponentTag>();
            if (tag && tag->GetTag() == "MOUNTAINISLAND") {
                std::cout << "[Collision] Player is colliding with Mountain Island" << std::endl;
                GameEngine::GetInstance().QueueSceneChange<ExploMountainIslandScene>();
            }
            else  if (tag && tag->GetTag() == "CRESSENTISLAND") {
                std::cout << "[Collision] Player is colliding with Cressent Island" << std::endl;
                GameEngine::GetInstance().QueueSceneChange<ExploCressentIslandScene>();
            }
            else  if (tag && tag->GetTag() == "GLADEISLAND") {
                GameEngine::GetInstance().QueueSceneChange<ExploGladeIslandScene>();
                std::cout << "[Collision] Player is colliding with Glade Island" << std::endl;
            }
            else  if (tag && tag->GetTag() == "LAKEISLAND") {
                std::cout << "[Collision] Player is colliding with Lake Island" << std::endl;
                GameEngine::GetInstance().QueueSceneChange<ExploLakeIslandScene>();
            }
            else  if (tag && tag->GetTag() == "YINGYANGISLAND") {
                std::cout << "[Collision] Player is colliding with Ying Yang Island" << std::endl;
                GameEngine::GetInstance().QueueSceneChange<ExploYingYangIslandScene>();
            }
        }

       


    }
                          



    //case ColliderType::Object: {
    //    std::cout << "[Collision] Objet : action 'interact'.\n";
    //    const ActionData* action = ActionDatabase::Get().GetAction("interact_lever"); // exemple generique
    //    if (action) {
    //        GameEngine::GetInstance().GetSystem<SystemAction>()->ExecuteAction(actor, action);
    //    }
    //    break;
    //}

    //case ColliderType::Gatherable: {
    //    std::cout << "[Collision] Ressource : action 'gather'.\n";
    //    const ActionData* action = ActionDatabase::Get().GetAction("gather_wood"); // exemple generique
    //    if (action) {
    //        GameEngine::GetInstance().GetSystem<SystemAction>()->ExecuteAction(actor, action);
    //    }
    //    break;
    //}
    }
}


void SystemCollision::Logs() {
	if (!debugMode || !logSystemCollision) return;
	EntityManager& em = GameEngine::GetInstance().GetEntityManager();
	const auto& entities = em.GetAllEntities();
	int total = 0;
	int mobs = 0;
	int objects = 0;
	int gatherables = 0;
	for (Entity* e : entities) {
		auto* collider = e->GetComponent<ComponentCollider>();
		if (!collider) continue;
		++total;
		switch (collider->GetColliderType()) {
		case ColliderType::Mob:
			++mobs;
			break;
		case ColliderType::Object:
			++objects;
			break;
		case ColliderType::Gatherable:
			++gatherables;
			break;
		default:
			break;
		}
	}
	HEAD("sys_COLLISION") << "Total : " << total << " | Mobs : " << mobs << " | Objets : " << objects << " | Ressources : " << gatherables << ENDL;
}