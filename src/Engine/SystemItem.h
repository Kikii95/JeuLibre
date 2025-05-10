#pragma once
#include "System.h"

class SystemItem : public System {
public:
    SystemItem();

    void Update(float dt, const std::vector<Entity*>& entities) override;
	SystemType GetType() const override { return SystemType::Active; }
    
    void PickupItem(Entity* picker, Entity* itemEntity);
    void DropItem(const ItemInstance& instance, const sf::Vector2f& position);

    void Logs() override {};

private:
	float itemLifetime = 60.f; // seconds
};
