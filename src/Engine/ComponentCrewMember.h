#pragma once

enum class CrewRole {
    Undefined,
    Captain,
    Gunner,
    Sailor,
    Medic,
    Engineer
};

enum class CrewStatus {
    Active,
    Injured,
    Unconscious,
    Dead
};

class ComponentCrewMember : public Component {
public:
    ComponentCrewMember(Entity* entity);

    void SetName(const std::string& name);
    std::string GetName() const;

    void SetRole(CrewRole role);
    CrewRole GetRole() const;

    void SetStatus(CrewStatus status);
    CrewStatus GetStatus() const;

private:
    std::string crewName;
    CrewRole crewRole;
    CrewStatus crewStatus;
};
