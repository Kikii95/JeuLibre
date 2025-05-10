#include "pch.h"

#include "ComponentState.h"

ComponentState::ComponentState(Entity* entity)
    : Component(entity) {
}

void ComponentState::SetState(EntityState state) {
    current = state;
}

EntityState ComponentState::GetState() const {
    return current;
}
