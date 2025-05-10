#include "pch.h"

ComponentQuest::ComponentQuest(Entity* entity)
    : Component(entity) {
}

void ComponentQuest::AddQuest(const QuestData& quest) {
    for (const auto& q : quests) {
        if (q.id == quest.id) return; 
    }
    quests.push_back(quest);
}

QuestData* ComponentQuest::GetQuest(const std::string& id) {
    for (auto& q : quests) {
        if (q.id == id) return &q;
    }
    return nullptr;
}

const std::vector<QuestData>& ComponentQuest::GetAllQuests() const {
    return quests;
}

void ComponentQuest::SetQuestStatus(const std::string& id, QuestStatus status) {
    if (QuestData* q = GetQuest(id)) {
        q->status = status;
    }
}

void ComponentQuest::CompleteStep(const std::string& questId, int stepIndex) {
    if (QuestData* q = GetQuest(questId)) {
        if (stepIndex >= 0 && stepIndex < static_cast<int>(q->steps.size())) {
            q->steps[stepIndex].completed = true;
        }
    }
}
