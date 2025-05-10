#include "pch.h"

ComponentAI::ComponentAI(Entity* entity)
    : Component(entity) {
}

void ComponentAI::SetBehavior(BehaviorType b) {
    behavior = b;
}

BehaviorType ComponentAI::GetBehavior() const {
    return behavior;
}

void ComponentAI::SetTarget(Entity* e) {
    target = e;
}

Entity* ComponentAI::GetTarget() const {
    return target;
}
