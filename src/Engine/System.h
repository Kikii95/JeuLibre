#pragma once

enum class SystemType {
    Active,
    Reactive,
    TurnBased,
    UI
};

class Entity;

class System {
public:
    virtual ~System() = default;

    virtual void Update(float dt, const std::vector<Entity*>& entities) = 0;
    virtual SystemType GetType() const = 0;

    virtual void Logs() = 0;
};
