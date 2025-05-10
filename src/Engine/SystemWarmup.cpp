#include "pch.h"

SystemWarmup::SystemWarmup() {}

void SystemWarmup::RequestWarmup(Entity* entity, const sf::Vector2f& finalPos) {
    if (!entity) return;

    auto* transform = entity->GetComponent<ComponentTransform>();
    if (!transform) return;

    PendingWarmup pw;
    pw.entity = entity;
    pw.finalPos = transform->GetPosition();
    pw.timeSinceCreated = 0.f;

    transform->SetPosition(sf::Vector2f(-9999.f, -9999.f));

    pendingWarmups.push_back(pw);
}

void SystemWarmup::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto it = pendingWarmups.begin(); it != pendingWarmups.end();) {
        it->timeSinceCreated += dt;

        if (it->timeSinceCreated >= 0.1f) {
            auto* transform = it->entity->GetComponent<ComponentTransform>();
            if (transform) {
                transform->SetPosition(it->finalPos);
            }
            it = pendingWarmups.erase(it);
        }
        else {
            ++it;
        }
    }
}