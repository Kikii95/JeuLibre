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

void SystemManager::RemoveAllSystems() {
	activeSystems.clear();
	renderSystems.clear();
	reactiveSystems.clear();
	turnBasedSystems.clear();

	systems.clear();
}

void SystemManager::Update(float dt) {
    // Si arret demande, on court-circuite tout de suite
    if (!GameEngine::GetInstance().IsRunning()) return;

    UpdateActiveSystems(dt);
    if (!GameEngine::GetInstance().IsRunning()) return;

    UpdateReactiveSystems(dt);
    if (!GameEngine::GetInstance().IsRunning()) return;

    UpdateTurnBasedSystems(dt);
}

void SystemManager::UpdateActiveSystems(float dt) {
    auto& ge = GameEngine::GetInstance();
    if (!ge.IsRunning()) return;

    const auto snapshot = activeSystems;

    const auto& entities = ge.GetEntityManager().GetAllEntities();
    for (System* sys : snapshot) {
        if (!ge.IsRunning()) break;
        sys->Update(dt, entities);
        sys->Logs();
    }
}

void SystemManager::UpdateReactiveSystems(float dt) {
    auto& ge = GameEngine::GetInstance();
    if (!ge.IsRunning()) return;

    const auto snapshot = reactiveSystems;

    const auto& entities = ge.GetEntityManager().GetAllEntities();
    for (System* sys : snapshot) {
        if (!ge.IsRunning()) break;
        sys->Update(dt, entities);
        sys->Logs();
    }
}

void SystemManager::UpdateTurnBasedSystems(float dt) {
    auto& ge = GameEngine::GetInstance();
    if (!ge.IsRunning()) return;

    const auto snapshot = turnBasedSystems;

    const auto& entities = ge.GetEntityManager().GetAllEntities();
    for (System* sys : snapshot) {
        if (!ge.IsRunning()) break;
        sys->Update(dt, entities);
        sys->Logs();
    }
}

void SystemManager::UpdateRender(float dt) {
    auto& ge = GameEngine::GetInstance();
    if (!ge.IsRunning()) return;

    const auto snapshot = renderSystems;

    const auto& entities = ge.GetEntityManager().GetAllEntities();
    for (System* sys : snapshot) {
        if (!ge.IsRunning()) break;
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
