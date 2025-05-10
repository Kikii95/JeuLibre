#include "pch.h"

ComponentTurnOrder::ComponentTurnOrder(Entity* entity)
    : Component(entity) {
}

void ComponentTurnOrder::SetBaseInitiative(int value) {
    baseInitiative = value;
}

int ComponentTurnOrder::GetBaseInitiative() const {
    return baseInitiative;
}

void ComponentTurnOrder::SetBonusInitiative(int bonus) {
    bonusInitiative = bonus;
}

int ComponentTurnOrder::GetBonusInitiative() const {
    return bonusInitiative;
}

int ComponentTurnOrder::GetTotalInitiative() const {
    return baseInitiative + bonusInitiative;
}

void ComponentTurnOrder::SetHasPlayed(bool state) {
    hasPlayedThisTurn = state;
}

bool ComponentTurnOrder::HasPlayed() const {
    return hasPlayedThisTurn;
}
