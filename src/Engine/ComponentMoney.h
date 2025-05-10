#pragma once

class ComponentMoney : public Component {
public:
    ComponentMoney(Entity* entity, int initial = 0);

    void Add(int amount);
    bool Spend(int amount);
    bool Has(int amount) const;

    int GetBalance() const;
    void SetBalance(int newBalance);

private:
    int gold;
};
