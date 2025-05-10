#include "pch.h"

ComponentDifficulty::ComponentDifficulty(Entity* entity, float base)
    : Component(entity), baseDifficulty(base), timeModifier(0.0f), zoneModifier(1.0f) {
}

void ComponentDifficulty::SetBaseDifficulty(float value) {
    baseDifficulty = maximum(0.0f, value);
}

float ComponentDifficulty::GetBaseDifficulty() const {
    return baseDifficulty;
}

void ComponentDifficulty::SetTimeModifier(float modifier) {
    timeModifier = modifier;
}

float ComponentDifficulty::GetTimeModifier() const {
    return timeModifier;
}

void ComponentDifficulty::SetZoneModifier(float modifier) {
    zoneModifier = modifier;
}

float ComponentDifficulty::GetZoneModifier() const {
    return zoneModifier;
}

void ComponentDifficulty::SetZoneName(const std::string& name) {
    zoneName = name;
}

const std::string& ComponentDifficulty::GetZoneName() const {
    return zoneName;
}

float ComponentDifficulty::GetEffectiveDifficulty() const {
    float zoneImpact = 1.0f + (zoneModifier - 1.0f) * 0.75f;
    float timeImpact = baseDifficulty + timeModifier * 0.75f;

    return timeImpact * zoneImpact;
}
