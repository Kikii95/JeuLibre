#include "pch.h"

SystemDialogue::SystemDialogue() {}

void SystemDialogue::Update(float dt, const std::vector<Entity*>& entities) {
}

const DialogueEntry* SystemDialogue::GetAvailableDialogue(Entity* entity, const std::string& id) {
    auto* dialogue = entity->GetComponent<ComponentDialogue>();
    if (!dialogue) return nullptr;

    if (dialogue->IsDialogueAvailable(id)) {
        for (const auto& d : dialogue->GetDialogues()) {
            if (d.id == id)
                return &d;
        }
    }
    return nullptr;
}

void SystemDialogue::TriggerDialogue(Entity* entity, const std::string& id) {
    auto* dialogue = entity->GetComponent<ComponentDialogue>();
    if (!dialogue) return;

    if (dialogue->IsDialogueAvailable(id)) {
        const auto* entry = GetAvailableDialogue(entity, id);
        if (entry) {
            std::cout << "[SystemDialogue] " << entry->text << std::endl;
            dialogue->MarkAsConsumed(id);
        }
    }
    else {
        std::cout << "[SystemDialogue] Dialogue indisponible : " << id << std::endl;
    }
}

void SystemDialogue::Logs() {
    if (!debugMode || !logSystemDialogue) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int available = 0;

    for (Entity* e : entities) {
        auto* comp = e->GetComponent<ComponentDialogue>();
        if (!comp) continue;

        const auto& dialogues = comp->GetDialogues();
        if (dialogues.empty()) continue;

        ++total;

        for (const auto& d : dialogues) {
            if (comp->IsDialogueAvailable(d.id)) {
                ++available;

                HEAD("sys_DIALOGUE") << "Entity " << e->GetID()
                    << " peut declencher : " << (char*)d.id.c_str()
                    << " | Texte : " << (char*)d.text.c_str()
                    << ENDL;
            }
        }
    }

    HEAD("sys_DIALOGUE") << "Entites avec dialogues : " << (int)total
        << " | Dialogues disponibles : " << (int)available
        << ENDL;
}
