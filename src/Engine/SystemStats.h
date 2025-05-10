class SystemStats : public System
{
public:
	SystemStats();
	SystemType GetType() const override { return SystemType::TurnBased; }
	void Update(float dt, const std::vector<Entity*>& entities) override;
	void Logs() override;

    void ApplyModifier(Entity* entity, const std::string& stat, int value);
    void RemoveModifier(Entity* entity, const std::string& stat, int value);
    void ClearModifiers(Entity* entity);
    int GetEffectiveStat(Entity* entity, const std::string& stat) const;

	void ApplyModifierGroup(Entity* entity, const std::string& sourceId, const std::unordered_map<std::string, int>& mods);
	void RemoveModifierGroup(Entity* entity, const std::string& sourceId, bool onlyIfFromEquipment);

	void InitStatsFromProfile(Entity* entity, const std::string& profileId);
};
