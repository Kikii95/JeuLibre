#pragma once

class ComponentFaction : public Component {
public:
    ComponentFaction(Entity* entity);

    void SetFactionId(const std::string& id);
    std::string GetFactionId() const;

    void SetFactionName(const std::string& name);
    std::string GetFactionName() const;

    void SetZone(const std::string& z);
    std::string GetZone() const;

private:
    std::string factionId;
    std::string factionName;
    std::string zone;
};
