#include "pch.h"

GameLogicManager::GameLogicManager(SystemManager* systemManager)
    : systems(systemManager), currentPhase(GamePhase::Exploration) {
}

void GameLogicManager::SetPhase(GamePhase newPhase) {
    currentPhase = newPhase;
}

GamePhase GameLogicManager::GetCurrentPhase() const {
    return currentPhase;
}

void GameLogicManager::SetEntities(const std::vector<Entity*>& allEntities) {
    entities = allEntities;
}

void GameLogicManager::Update(float dt) {
    switch (currentPhase) {
    case GamePhase::Exploration: UpdateExploration(dt); break;
    case GamePhase::Combat:      UpdateCombat(dt);      break;
    case GamePhase::TurnStart:   UpdateTurnStart(dt);   break;
    case GamePhase::TurnEnd:     UpdateTurnEnd(dt);     break;
    case GamePhase::Dialogue:    UpdateDialogue(dt);    break;
    case GamePhase::Event:       UpdateEvent(dt);       break;
    }
}

// ----------------------------
// Phase : Exploration (active)
// ----------------------------
void GameLogicManager::UpdateExploration(float dt) {
    systems->UpdateActiveSystems(dt);           // physics, navire, transform...
    systems->UpdateRender(dt);     // SystemRender seul
}

// ----------------------------
// Phase : Combat (passif)
// ----------------------------
void GameLogicManager::UpdateCombat(float dt) {
    systems->GetSystem<SystemCombat>()->Update(dt, entities);
    systems->GetSystem<SystemHealth>()->Update(dt, entities);
    systems->GetSystem<SystemBuffDebuff>()->Update(dt, entities);
    systems->GetSystem<SystemCrewManagement>()->Update(dt, entities);
}

// ----------------------------
// Phase : Debut de tour
// ----------------------------
void GameLogicManager::UpdateTurnStart(float dt) {
    systems->GetSystem<SystemTurnOrder>()->Update(dt, entities);
    systems->GetSystem<SystemBuffDebuff>()->Update(dt, entities);
    SetPhase(GamePhase::Combat); // enchaîne avec combat
}

// ----------------------------
// Phase : Fin de tour
// ----------------------------
void GameLogicManager::UpdateTurnEnd(float dt) {
    systems->GetSystem<SystemEvent>()->Update(dt, entities);
    systems->GetSystem<SystemHealth>()->Update(dt, entities);
    SetPhase(GamePhase::TurnStart); // boucle au tour suivant
}

// ----------------------------
// Phase : Dialogue
// ----------------------------
void GameLogicManager::UpdateDialogue(float dt) {
    // Gere sur input UI ou declencheur
    // Ici, on peut juste bloquer tout ou montrer une UI
}

// ----------------------------
// Phase : evenement special
// ----------------------------
void GameLogicManager::UpdateEvent(float dt) {
    // Peut declencher :
    // SystemLoot, SystemQuest, SystemMerchant...
}
