#pragma once

class SystemLoot : public System {
public:
    SystemLoot();

    SystemType GetType() const override { return SystemType::Reactive; }

    void GenerateLoot(Entity* source, Entity* receiver);

    void Update(float dt, const std::vector<Entity*>&) override {}
	void Logs() override;
};
