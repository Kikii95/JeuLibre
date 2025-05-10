#include "pch.h"

SystemQuest::SystemQuest() {}

void SystemQuest::Update(float dt, const std::vector<Entity*>& entities) {
}

bool SystemQuest::CompleteQuestStep(Entity* entity, const std::string& questId, int stepIndex) {
    auto* quest = entity->GetComponent<ComponentQuest>();
    if (!quest) return false;

    quest->CompleteStep(questId, stepIndex);

    std::cout << "[SystemQuest] etape " << stepIndex << " completee pour la quete " << questId << std::endl;

    QuestData* q = quest->GetQuest(questId);
    if (q) {
        bool allDone = true;
        for (const auto& step : q->steps) {
            if (!step.completed) {
                allDone = false;
                break;
            }
        }
        if (allDone) {
            q->status = QuestStatus::Completed;
            std::cout << "[SystemQuest] Quete " << questId << " terminee !" << std::endl;
        }
    }

    return true;
}

void SystemQuest::SetQuestStatus(Entity* entity, const std::string& questId, QuestStatus status) {
    auto* quest = entity->GetComponent<ComponentQuest>();
    if (quest) {
        quest->SetQuestStatus(questId, status);
    }
}

QuestStatus SystemQuest::GetQuestStatus(Entity* entity, const std::string& questId) {
    auto* quest = entity->GetComponent<ComponentQuest>();
    if (!quest) return QuestStatus::Inactive;

    QuestData* q = quest->GetQuest(questId);
    return q ? q->status : QuestStatus::Inactive;
}

void SystemQuest::Logs() {
    if (!debugMode || !logSystemQuest) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int totalQuests = 0;
    int activeQuests = 0;
    int completedQuests = 0;

    HEAD("sys_QUEST") << "etat des quetes :" << ENDL;

    for (Entity* e : entities) {
        auto* quest = e->GetComponent<ComponentQuest>();
        if (!quest) continue;

        const auto& quests = quest->GetAllQuests();
        //for (const auto& [id, data] : quests) {
        //    ++totalQuests;
        //    if (data.status == QuestStatus::Active)    ++activeQuests;
        //    if (data.status == QuestStatus::Completed) ++completedQuests;

        //    HEAD("sys_QUEST") << "- Entity " << e->GetID()
        //        << " | Quest : " << (char*)id.c_str()
        //        << " | etapes : " << (int)data.steps.size()
        //        << " | Statut : " << (char*)(data.status == QuestStatus::Completed ? "Completee" :
        //            data.status == QuestStatus::Active ? "Active" : "Inactive")
        //        << ENDL;
        //}
    }

    HEAD("sys_QUEST") << "Total : " << (int)totalQuests
        << " | Actives : " << (int)activeQuests
        << " | Completees : " << (int)completedQuests << ENDL;
}
