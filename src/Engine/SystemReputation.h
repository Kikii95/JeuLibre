#pragma once

class SystemReputation : public System {
public:
    SystemReputation();

	SystemType GetType() const override { return SystemType::Reactive; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    void ModifyReputation(Entity* entity, const std::string& factionId, int delta);
    int GetReputationValue(Entity* entity, const std::string& factionId);
    ReputationLevel GetReputationLevel(Entity* entity, const std::string& factionId);

	void Logs() override;
};
