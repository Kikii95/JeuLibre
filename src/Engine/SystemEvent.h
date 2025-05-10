#pragma once

class SystemEvent : public System {
public:
    SystemEvent();

	SystemType GetType() const override { return SystemType::Active; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    bool TriggerEvent(Entity* entity, const std::string& eventId);
    bool IsEventAvailable(Entity* entity, const std::string& eventId);

	void Logs() override;
};
