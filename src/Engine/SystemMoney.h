#pragma once

class SystemMoney : public System {
public:
    SystemMoney();

	SystemType GetType() const override { return SystemType::Reactive; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    bool Pay(Entity* entity, int amount);
    void Give(Entity* entity, int amount);
    int  Get(Entity* entity) const;

	void Logs() override;
};
