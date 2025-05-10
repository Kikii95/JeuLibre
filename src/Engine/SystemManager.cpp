#include "pch.h"

std::vector<System*> SystemManager::GetAllSystems() const {
	std::vector<System*> allSystems;
	allSystems.reserve(activeSystems.size() + renderSystems.size() + reactiveSystems.size() + turnBasedSystems.size());
	allSystems.insert(allSystems.end(), activeSystems.begin(), activeSystems.end());
	allSystems.insert(allSystems.end(), renderSystems.begin(), renderSystems.end());
	allSystems.insert(allSystems.end(), reactiveSystems.begin(), reactiveSystems.end());
	allSystems.insert(allSystems.end(), turnBasedSystems.begin(), turnBasedSystems.end());
	return allSystems;
}

void SystemManager::Update(float dt) {
	UpdateActiveSystems(dt);
	UpdateReactiveSystems(dt);
	UpdateTurnBasedSystems(dt);
}

void SystemManager::UpdateActiveSystems(float dt) {
    const auto& entities = GameEngine::GetInstance().GetEntityManager().GetAllEntities();
    for (System* sys : activeSystems) {
        sys->Update(dt, entities);
		sys->Logs();
    }
}

void SystemManager::UpdateReactiveSystems(float dt) {
	const auto& entities = GameEngine::GetInstance().GetEntityManager().GetAllEntities();
	for (System* sys : reactiveSystems) {
		sys->Update(dt, entities);
		sys->Logs();
	}
}

void SystemManager::UpdateTurnBasedSystems(float dt) {
	const auto& entities = GameEngine::GetInstance().GetEntityManager().GetAllEntities();
	for (System* sys : turnBasedSystems) {
		sys->Update(dt, entities);
		sys->Logs();
	}
}

void SystemManager::UpdateRender(float dt) {
    const auto& entities = GameEngine::GetInstance().GetEntityManager().GetAllEntities();
    for (System* sys : renderSystems) {
        sys->Update(dt, entities);
		sys->Logs();
    }
}

void SystemManager::Clear() {
	systems.clear();
	activeSystems.clear();
	renderSystems.clear();
	reactiveSystems.clear();
	turnBasedSystems.clear();
}
