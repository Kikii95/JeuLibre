#pragma once

class SystemHealth : public System {
public:
    SystemHealth();

	SystemType GetType() const override { return SystemType::TurnBased; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

	void ApplyDamage(Entity* entity, int amount);
	void Heal(Entity* entity, int amount);

	bool IsDead(Entity* entity) const;

	void OnDeath(Entity* entity);

	void Logs() override;
};
