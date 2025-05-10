#include "pch.h"

ComponentReputation::ComponentReputation(Entity* entity)
    : Component(entity) {
}

void ComponentReputation::SetReputation(const std::string& factionId, int value) {
    reputationMap[factionId] = clamp(value, -100, 100);
}

void ComponentReputation::ModifyReputation(const std::string& factionId, int delta) {
    int current = GetReputation(factionId);
    SetReputation(factionId, current + delta);
}

int ComponentReputation::GetReputation(const std::string& factionId) const {
    auto it = reputationMap.find(factionId);
    if (it != reputationMap.end()) return it->second;
    return 0;
}

std::unordered_map<std::string, int> ComponentReputation::GetAllReputations() const {
    return reputationMap;
}

ReputationLevel ComponentReputation::GetReputationLevel(const std::string& factionId) const {
    int rep = GetReputation(factionId);
    if (rep <= -30) return ReputationLevel::Hostile;
    if (rep >= 30) return ReputationLevel::Friendly;
    return ReputationLevel::Neutral;
}
