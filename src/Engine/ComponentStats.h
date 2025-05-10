#pragma once

class ComponentStats : public Component {
public:
    ComponentStats(Entity* owner);

    const std::string& GetDefinitionId() const;
    void LoadFromDefinition(const std::string& id);

    void SetBaseStat(const std::string& name, int value);
    void AddModifier(const std::string& name, int value);
    void ClearModifiers();

    void ApplyModifierGroup(const std::string& sourceId, const std::unordered_map<std::string, int>& mods);
    void RemoveModifierGroup(const std::string& sourceId, bool onlyIfFromEquipment = false);

    int GetStat(const std::string& name) const;

    const std::unordered_map<std::string, int>& GetBaseStats() const;
    const std::unordered_map<std::string, int>& GetModifiers() const;

	void ResetStats();

private:
    std::unordered_map<std::string, int> baseStats;
    std::unordered_map<std::string, int> modifiers;

    std::unordered_map<std::string, std::unordered_map<std::string, int>> sourceModifiers;

	std::string definitionId;
};
