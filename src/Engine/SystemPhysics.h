#pragma once


class SystemPhysics : public System {
private:
    sf::Vector2f gravity = {0.0f, 9.81f * 1000};

public:
    SystemType GetType() const override { return SystemType::Active; }

    void Update(float dt, const std::vector<Entity*>& entities) override;

    void Logs() override;
};


