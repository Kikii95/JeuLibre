#pragma once

class ComponentTurnOrder : public Component {
public:
    ComponentTurnOrder(Entity* entity);

    void SetBaseInitiative(int value);
    int GetBaseInitiative() const;

    void SetBonusInitiative(int bonus);
    int GetBonusInitiative() const;

    int GetTotalInitiative() const;

    void SetHasPlayed(bool state);
    bool HasPlayed() const;

private:
    int baseInitiative = 0;
    int bonusInitiative = 0;
    bool hasPlayedThisTurn = false;
};
