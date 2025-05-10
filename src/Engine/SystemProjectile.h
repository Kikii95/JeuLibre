#pragma once

class SystemProjectile : public System {
public:
    SystemProjectile();

    SystemType GetType() const override { return SystemType::Active; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    void SpawnProjectile(Entity* owner, const std::string& itemId, HexDirection direction);

	void Logs() override;
};
