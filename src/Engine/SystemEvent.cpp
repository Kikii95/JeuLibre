#include "pch.h"

SystemEvent::SystemEvent() {}

void SystemEvent::Update(float dt, const std::vector<Entity*>& entities) {
    for (auto* entity : entities) {
        auto* comp = entity->GetComponent<ComponentEvent>();
        if (!comp) continue;

        for (const auto& e : comp->GetEvents()) {
            if (comp->IsEventAvailable(e.id)) {
                TriggerEvent(entity, e.id);
                break;
            }
        }
    }
}

bool SystemEvent::TriggerEvent(Entity* entity, const std::string& eventId) {
    auto* comp = entity->GetComponent<ComponentEvent>();
    if (!comp || !comp->IsEventAvailable(eventId)) return false;

    comp->MarkAsTriggered(eventId);
    std::cout << "[SystemEvent] evenement declenche : " << eventId << std::endl;

    return true;
}

bool SystemEvent::IsEventAvailable(Entity* entity, const std::string& eventId) {
    auto* comp = entity->GetComponent<ComponentEvent>();
    return comp && comp->IsEventAvailable(eventId);
}

void SystemEvent::Logs() {
    if (!debugMode || !logSystemEvent) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int ready = 0;

    for (Entity* e : entities) {
        auto* comp = e->GetComponent<ComponentEvent>();
        if (!comp) continue;

        ++total;
        int count = 0;

        for (const auto& ev : comp->GetEvents()) {
            if (comp->IsEventAvailable(ev.id)) {
                ++count;
                ++ready;

                HEAD("sys_EVENT") << "Entity " << e->GetID()
                    << " peut declencher : " << (char*)ev.id.c_str() << ENDL;
            }
        }

        if (count == 0) {
            HEAD("sys_EVENT") << "Entity " << e->GetID()
                << " - aucun evenement declenchable." << ENDL;
        }
    }

    HEAD("sys_EVENT") << "Entites avec evenements : " << (int)total
        << " | evenements disponibles : " << (int)ready << ENDL;
}
