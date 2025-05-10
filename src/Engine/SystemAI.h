#pragma once
#include "System.h"

class SystemAI : public System {
public:
    SystemAI();

    SystemType GetType() const override { return SystemType::TurnBased; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    void SetInCombat(bool active); // call from GameManager

	void Logs() override;

private:
    bool inCombat = false;

    Entity* FindClosestTarget(Entity* seeker, const std::vector<Entity*>& candidates);
    bool IsTargetInWeaponRange(Entity* attacker, Entity* target);
    float DistanceHex(const sf::Vector2i& a, const sf::Vector2i& b);
    float Distance2D(const sf::Vector2f& a, const sf::Vector2f& b);
};
