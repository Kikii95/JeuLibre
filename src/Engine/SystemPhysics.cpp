#include "pch.h"

void SystemPhysics::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto* entity : entities) {
        ComponentPhysics* physics = entity->GetComponent<ComponentPhysics>();
        if (!physics) continue;

        sf::Vector2f acceleration = physics->GetAcceleration();

        if (physics->IsAffectedByGravity() && !physics->IsOnGround()) {
            acceleration += gravity;
        }

        sf::Vector2f velocity = physics->GetVelocity();
        velocity += acceleration * dt;

        bool noInput = (acceleration.x == 0.f && acceleration.y == 0.f);
        float friction = noInput ? 0.90f : 0.98f;
        velocity *= friction;

        const float maxFallSpeed = 5000.0f;
        if (velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;

        physics->SetVelocity(velocity);
        physics->SetAcceleration({ 0.f, 0.f });

        ComponentTransform* transform = entity->GetComponent<ComponentTransform>();
        if (!transform) continue;

        transform->MoveBy(velocity * dt);

        if (physics->IsAffectedByGravity()) {
            float groundY = 720.0f - 100.0f;
            if (transform->GetPosition().y >= groundY) {
                transform->SetPosition({ transform->GetPosition().x, groundY });
                velocity.y = 0.0f;
                physics->SetVelocity(velocity);
                physics->SetIsGrounded(true);
            }
            else {
                physics->SetIsGrounded(false);
            }
        }
    }
}



void SystemPhysics::Logs() {
    if (!debugMode || !logSystemPhysics) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int withGravity = 0;
    int grounded = 0;

    for (Entity* e : entities) {
        auto* phys = e->GetComponent<ComponentPhysics>();
        if (!phys) continue;

        ++total;
        if (phys->IsAffectedByGravity()) ++withGravity;
        if (phys->IsOnGround()) ++grounded;
    }

    HEAD("sys_PHYSICS") << "Entites physiques : " << (int)total
        << " | Gravite active : " << (int)withGravity
        << " | Au sol : " << (int)grounded << ENDL;
}
