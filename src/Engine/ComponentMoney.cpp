#include "pch.h"

ComponentMoney::ComponentMoney(Entity* entity, int initial)
    : Component(entity), gold(maximum(0, initial)) {
}

void ComponentMoney::Add(int amount) {
    gold += maximum(0, amount);
}

bool ComponentMoney::Spend(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

bool ComponentMoney::Has(int amount) const {
    return gold >= amount;
}

int ComponentMoney::GetBalance() const {
    return gold;
}

void ComponentMoney::SetBalance(int newBalance) {
    gold = maximum(0, newBalance);
}
