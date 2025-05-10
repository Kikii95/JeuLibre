#pragma once

class SystemCrewManagement : public System {
public:
    SystemCrewManagement();

	SystemType GetType() const override { return SystemType::TurnBased; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

	void Logs() override;

private:
    void PerformRoleLogic(Entity* crew);
};
