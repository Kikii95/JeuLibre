#pragma once

class SystemQuest : public System {
public:
    SystemQuest();

	SystemType GetType() const override { return SystemType::Reactive; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    bool CompleteQuestStep(Entity* entity, const std::string& questId, int stepIndex);
    void SetQuestStatus(Entity* entity, const std::string& questId, QuestStatus status);
    QuestStatus GetQuestStatus(Entity* entity, const std::string& questId);

	void Logs() override;
};
