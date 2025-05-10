#pragma once

enum class QuestStatus {
    Inactive,
    Active,
    Completed,
    Failed
};

struct QuestStep {
    std::string description;
    bool completed = false;
};

struct QuestData {
    std::string id;
    std::string title;
    std::string description;
    QuestStatus status = QuestStatus::Inactive;
    std::vector<QuestStep> steps;

    QuestData(const std::string& id, const std::string& title, const std::string& desc)
        : id(id), title(title), description(desc) {
    }
};

class ComponentQuest : public Component {
public:
    ComponentQuest(Entity* entity);

    void AddQuest(const QuestData& quest);
    QuestData* GetQuest(const std::string& id);
    const std::vector<QuestData>& GetAllQuests() const;

    void SetQuestStatus(const std::string& id, QuestStatus status);
    void CompleteStep(const std::string& questId, int stepIndex);

private:
    std::vector<QuestData> quests;
};
