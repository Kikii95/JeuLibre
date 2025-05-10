#pragma once

class ComponentCombat : public Component {
public:
    ComponentCombat(Entity* entity);

    void SetInCombat(bool inCombat);
    bool IsInCombat() const;

    void SetInitiative(int value);
    int GetInitiative() const;

    void SetAttackRange(int range);
    int GetAttackRange() const;

    void SetCanAct(bool state);
    bool CanAct() const;

private:
    bool inCombat = false;
    int initiative = 0;
    int attackRange = 1; 
    bool canAct = true;
};
