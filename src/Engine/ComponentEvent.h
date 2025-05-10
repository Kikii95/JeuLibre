#pragma once

struct EventData {
    std::string id;
    std::string description;
    bool triggered = false;
    bool repeatable = false;

    EventData(const std::string& _id, const std::string& _desc, bool _repeatable = false)
        : id(_id), description(_desc), repeatable(_repeatable) {
    }
};

class ComponentEvent : public Component {
public:
    ComponentEvent(Entity* entity);

    void AddEvent(const EventData& event);
    const std::vector<EventData>& GetEvents() const;

    void MarkAsTriggered(const std::string& id);
    bool IsEventAvailable(const std::string& id) const;

private:
    std::vector<EventData> events;
};
