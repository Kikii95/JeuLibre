#pragma once

class ComponentDifficulty : public Component {
public:
    ComponentDifficulty(Entity* entity, float base = 1.0f);

    void SetBaseDifficulty(float value);
    float GetBaseDifficulty() const;

    void SetTimeModifier(float modifier);
    float GetTimeModifier() const;

    void SetZoneModifier(float modifier);
    float GetZoneModifier() const;

    void SetZoneName(const std::string& name);
    const std::string& GetZoneName() const;

    float GetEffectiveDifficulty() const;

private:
    float baseDifficulty;
    float timeModifier;
    float zoneModifier = 1.0f;
    std::string zoneName;
};
