#pragma once


enum class GamePhase {
    Exploration,
    Combat,
    TurnStart,
    TurnEnd,
    Dialogue,
    Event
};

class GameLogicManager {
public:
    GameLogicManager(SystemManager* systemManager);

    void Update(float dt);
    void SetPhase(GamePhase newPhase);
    GamePhase GetCurrentPhase() const;

    void SetEntities(const std::vector<Entity*>& allEntities);

private:
    SystemManager* systems;
    std::vector<Entity*> entities;
    GamePhase currentPhase;

    // Par phase
    void UpdateExploration(float dt);
    void UpdateCombat(float dt);
    void UpdateTurnStart(float dt);
    void UpdateTurnEnd(float dt);
    void UpdateDialogue(float dt);
    void UpdateEvent(float dt);
};
