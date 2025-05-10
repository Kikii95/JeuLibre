#include "pch.h"

ComponentPhysics::ComponentPhysics(Entity* entity)
    : Component(entity), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f) {
}

void ComponentPhysics::ApplyForce(const sf::Vector2f& force) {
    acceleration += force;
}

void ComponentPhysics::ApplyGravity(float gravity) {
    if (affectedByGravity) {
        acceleration.y += gravity;
    }
}

void ComponentPhysics::Jump(float force) {
    if (isOnGround) {
        velocity.y = -force;
        isOnGround = false; 
    }
}

sf::Vector2f ComponentPhysics::GetVelocity() const {
    return velocity;
}

void ComponentPhysics::SetVelocity(const sf::Vector2f& v) {
    velocity = v;
}

void ComponentPhysics::AddVelocity(const sf::Vector2f& v) {
	velocity += v;
}

void ComponentPhysics::SetVelocityX(float x) {
    velocity.x = x;
}

void ComponentPhysics::SetVelocityY(float y) {
    velocity.y = y;
}

sf::Vector2f ComponentPhysics::GetAcceleration() const {
    return acceleration;
}

void ComponentPhysics::SetAcceleration(const sf::Vector2f& a) {
    acceleration = a;
}

void ComponentPhysics::AddAcceleration(const sf::Vector2f& a) {
	acceleration += a;
}

bool ComponentPhysics::IsOnGround() const {
    return isOnGround;
}

void ComponentPhysics::SetIsGrounded(bool state) {
    isOnGround = state;
}

bool ComponentPhysics::IsAffectedByGravity() const {
    return affectedByGravity;
}

void ComponentPhysics::SetAffectedByGravity(bool state) {
    affectedByGravity = state;
}
