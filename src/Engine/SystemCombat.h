#pragma once

class SystemCombat : public System {
public:
    SystemCombat();

    SystemType GetType() const override { return SystemType::TurnBased; }
    void Update(float dt, const std::vector<Entity*>& entities) override;


    void ExecuteAttack(Entity* attacker, Entity* target);

	void Logs() override;

private:
    int CalculateDamage(Entity* attacker, Entity* target, bool& hitSuccess);
    void ApplyWeaponEffect(Entity* attacker, Entity* target, const std::string& effectId);
};
