#include "pch.h"

ComponentEvent::ComponentEvent(Entity* entity)
    : Component(entity) {
}

void ComponentEvent::AddEvent(const EventData& event) {
    events.push_back(event);
}

const std::vector<EventData>& ComponentEvent::GetEvents() const {
    return events;
}

void ComponentEvent::MarkAsTriggered(const std::string& id) {
    for (auto& e : events) {
        if (e.id == id) {
            e.triggered = true;
            return;
        }
    }
}

bool ComponentEvent::IsEventAvailable(const std::string& id) const {
    for (const auto& e : events) {
        if (e.id == id) {
            return !e.triggered || e.repeatable;
        }
    }
    return false;
}
