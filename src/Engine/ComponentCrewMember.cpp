#include "pch.h"

ComponentCrewMember::ComponentCrewMember(Entity* entity)
    : Component(entity), crewRole(CrewRole::Undefined), crewStatus(CrewStatus::Active) {
}

void ComponentCrewMember::SetName(const std::string& name) {
    crewName = name;
}

std::string ComponentCrewMember::GetName() const {
    return crewName;
}

void ComponentCrewMember::SetRole(CrewRole role) {
    crewRole = role;
}

CrewRole ComponentCrewMember::GetRole() const {
    return crewRole;
}

void ComponentCrewMember::SetStatus(CrewStatus status) {
    crewStatus = status;
}

CrewStatus ComponentCrewMember::GetStatus() const {
    return crewStatus;
}
