#pragma once

class SystemDialogue : public System {
public:
    SystemDialogue();

	SystemType GetType() const override { return SystemType::Reactive; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    const DialogueEntry* GetAvailableDialogue(Entity* entity, const std::string& id);
    void TriggerDialogue(Entity* entity, const std::string& id);

	void Logs() override;
};
