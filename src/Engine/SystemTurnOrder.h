#pragma once

class SystemTurnOrder : public System {
public:
    SystemTurnOrder();

	SystemType GetType() const override { return SystemType::TurnBased; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    void StartNewRound(const std::vector<Entity*>& entities);
    Entity* GetNextEntityToPlay(const std::vector<Entity*>& entities);

	void Logs() override;

private:
    std::vector<Entity*> turnQueue;
    int currentIndex = 0;

    void SortByInitiative(std::vector<Entity*>& entities);
};
