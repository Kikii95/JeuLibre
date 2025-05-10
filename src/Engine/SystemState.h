#pragma once
#include "System.h"

class SystemState : public System {
public:
    SystemState();

    SystemType GetType() const override { return SystemType::TurnBased; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

	void Logs() override;

private:
    void Execute(Entity* entity);
};
