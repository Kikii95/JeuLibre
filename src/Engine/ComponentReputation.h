#pragma once

enum class ReputationLevel {
    Hostile,
    Neutral,
    Friendly
};

class ComponentReputation : public Component {
public:
    ComponentReputation(Entity* entity);

    void SetReputation(const std::string& factionId, int value);
    void ModifyReputation(const std::string& factionId, int delta);
    int GetReputation(const std::string& factionId) const;

	std::unordered_map<std::string, int> GetAllReputations() const;

    ReputationLevel GetReputationLevel(const std::string& factionId) const;

private:
    std::unordered_map<std::string, int> reputationMap;
};
