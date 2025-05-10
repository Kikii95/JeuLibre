#include "pch.h"

ComponentCombat::ComponentCombat(Entity* entity)
    : Component(entity) {
}

void ComponentCombat::SetInCombat(bool state) {
    inCombat = state;
}

bool ComponentCombat::IsInCombat() const {
    return inCombat;
}

void ComponentCombat::SetInitiative(int value) {
    initiative = value;
}

int ComponentCombat::GetInitiative() const {
    return initiative;
}

void ComponentCombat::SetAttackRange(int range) {
    attackRange = range;
}

int ComponentCombat::GetAttackRange() const {
    return attackRange;
}

void ComponentCombat::SetCanAct(bool state) {
    canAct = state;
}

bool ComponentCombat::CanAct() const {
    return canAct;
}
