#include "pch.h"

ComponentFaction::ComponentFaction(Entity* entity)
    : Component(entity) {
}

void ComponentFaction::SetFactionId(const std::string& id) {
    factionId = id;
}

std::string ComponentFaction::GetFactionId() const {
    return factionId;
}

void ComponentFaction::SetFactionName(const std::string& name) {
    factionName = name;
}

std::string ComponentFaction::GetFactionName() const {
    return factionName;
}

void ComponentFaction::SetZone(const std::string& z) {
    zone = z;
}

std::string ComponentFaction::GetZone() const {
    return zone;
}
