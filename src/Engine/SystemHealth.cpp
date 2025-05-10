#include "pch.h"

SystemHealth::SystemHealth() {}

void SystemHealth::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto* entity : entities) {
        auto* health = entity->GetComponent<ComponentHealth>();
        if (!health) continue;

        if (IsDead(entity)) {
            if (auto* state = entity->GetComponent<ComponentState>()) {
                state->SetState(EntityState::Dead);
            }

            Entity* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER").front();
			if (player) {
                GameEngine::GetInstance().GetSystem<SystemLoot>()->GenerateLoot(entity, player);
			}

			OnDeath(entity);

            std::cout << "[SystemHealth] Entite morte." << std::endl;
        }
    }
}

void SystemHealth::ApplyDamage(Entity* entity, int amount) {
	if (entity) {
		auto* health = entity->GetComponent<ComponentHealth>();
		if (health) {
			health->SetHealth(health->GetHealth() - amount > 0 ? health->GetHealth() - amount : 0);
		}
        else {
			std::cout << "[SystemHealth] No ComponentHealth found on entity" << entity->GetID() << std::endl;
        }
	}
}

void SystemHealth::Heal(Entity* entity, int amount) {
	if (entity) {
		auto* health = entity->GetComponent<ComponentHealth>();
		if (health) {
			health->SetHealth(health->GetHealth() + amount < health->GetMaxHealth() ? health->GetHealth() + amount : health->GetMaxHealth());
		}
		else {
			std::cout << "[SystemHealth] No ComponentHealth found on entity" << entity->GetID() << std::endl;
		}
	}
}

bool SystemHealth::IsDead(Entity* entity) const {
	if (entity) {
		auto* health = entity->GetComponent<ComponentHealth>();
		if (health->GetHealth() <= 0) {
			return true;
		}
		else {
			return false;
		}
	}
}

void SystemHealth::OnDeath(Entity* entity) {
	if (entity) {
		auto* health = entity->GetComponent<ComponentHealth>();
		if (health) {
			GameEngine::GetInstance().GetEntityManager().DestroyEntity(entity);
		}
	}
}