#pragma once
#include "System.h"

struct PendingWarmup {
    Entity* entity;
    sf::Vector2f finalPos;
    float timeSinceCreated = 0.f;
};

class SystemWarmup : public System {
public:
    SystemWarmup();

    void Update(float dt, const std::vector<Entity*>& entities) override;
    SystemType GetType() const override { return SystemType::Active; }

    void Logs() override {};

    void RequestWarmup(Entity* entity, const sf::Vector2f& finalPos);

private:
    std::vector<PendingWarmup> pendingWarmups;
};