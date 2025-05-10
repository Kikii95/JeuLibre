#pragma once


enum class EntityState {
    Idle,
    Moving,
    Attacking,
    Defending,
    UsingItem,
    Waiting,
	Dead
};

class ComponentState : public Component {
public:
    ComponentState(Entity* entity);

    void SetState(EntityState state);
    EntityState GetState() const;

private:
    EntityState current = EntityState::Idle;
};
