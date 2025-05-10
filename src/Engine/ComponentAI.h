#pragma once
#include "Component.h"

enum class BehaviorType {
    None,
    Aggressive,
    Defensive,
    Passive,
    Fleeing
};

class ComponentAI : public Component {
public:
    ComponentAI(Entity* entity);

    void SetBehavior(BehaviorType behavior);
    BehaviorType GetBehavior() const;

    void SetTarget(Entity* entity);
    Entity* GetTarget() const;

private:
    BehaviorType behavior = BehaviorType::None;
    Entity* target = nullptr;
};
