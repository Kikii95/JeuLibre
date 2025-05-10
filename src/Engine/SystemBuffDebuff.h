#pragma once

class SystemBuffDebuff : public System {
public:
    SystemBuffDebuff();

    SystemType GetType() const override { return SystemType::TurnBased; }

    void Update(float dt, const std::vector<Entity*>& entities) override;

    void ApplyEffect(Entity* target, const std::string& effectId);

	void Logs() override;
};
