#pragma once

class ComponentTransform;

class ComponentPhysics : public Component {
public:
    ComponentPhysics(Entity* entity);

    void ApplyForce(const sf::Vector2f& force);
    void ApplyGravity(float gravity);
    void Jump(float force);

    sf::Vector2f GetVelocity() const;
    void SetVelocity(const sf::Vector2f& velocity);
	void AddVelocity(const sf::Vector2f& velocity);
    void SetVelocityX(float x);
    void SetVelocityY(float y);

    sf::Vector2f GetAcceleration() const;
    void SetAcceleration(const sf::Vector2f& acceleration);
	void AddAcceleration(const sf::Vector2f& acceleration);

    bool IsOnGround() const;
    void SetIsGrounded(bool state);

    bool IsAffectedByGravity() const;
    void SetAffectedByGravity(bool state);

private:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool isOnGround = false;
    bool affectedByGravity = false;
};
