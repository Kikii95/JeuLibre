#include "pch.h"
#include "ComponentStats.h"

ComponentStats::ComponentStats(Entity* owner)
    : Component(owner) {
}

const std::string& ComponentStats::GetDefinitionId() const { 
    return definitionId; 
}


void ComponentStats::LoadFromDefinition(const std::string& id) {
    this->definitionId = id;
    const StatsDefinition* def = StatsDatabase::Get().GetDefinition(id);
    if (!def) return;
    for (const auto& [name, value] : def->values) {
        SetBaseStat(name, value);
    }
}


void ComponentStats::SetBaseStat(const std::string& name, int value) {
    baseStats[name] = value;
}

void ComponentStats::AddModifier(const std::string& name, int value) {
    modifiers[name] += value;
}

void ComponentStats::ClearModifiers() {
    modifiers.clear();
}

void ComponentStats::ApplyModifierGroup(const std::string& sourceId, const std::unordered_map<std::string, int>& mods) {
    RemoveModifierGroup(sourceId, true);

    for (const auto& [stat, value] : mods) {
        modifiers[stat] += value;
    }

    sourceModifiers[sourceId] = mods;
}


void ComponentStats::RemoveModifierGroup(const std::string& sourceId, bool onlyIfFromEquipment) {
    auto it = sourceModifiers.find(sourceId);
    if (it == sourceModifiers.end()) return;

    if (onlyIfFromEquipment) {
        auto* buffComp = GetEntity()->GetComponent<ComponentBuffDebuff>();
        if (buffComp) {
            auto effectIt = std::find_if(
                buffComp->GetActiveEffects().begin(),
                buffComp->GetActiveEffects().end(),
                [&](const EffectInstance& e) {
                    return e.sourceItemUID == sourceId && e.fromEquip;
                });

            if (effectIt == buffComp->GetActiveEffects().end())
                return;
        }
    }


    for (const auto& [stat, value] : it->second) {
        modifiers[stat] -= value;
        if (modifiers[stat] == 0) {
            modifiers.erase(stat);
        }
    }

    sourceModifiers.erase(sourceId);
}



int ComponentStats::GetStat(const std::string& name) const {
    int base = 0;
    int mod = 0;
    auto itBase = baseStats.find(name);
    if (itBase != baseStats.end()) base = itBase->second;

    auto itMod = modifiers.find(name);
    if (itMod != modifiers.end()) mod = itMod->second;

    return base + mod;
}

const std::unordered_map<std::string, int>& ComponentStats::GetBaseStats() const {
    return baseStats;
}

const std::unordered_map<std::string, int>& ComponentStats::GetModifiers() const {
    return modifiers;
}

void ComponentStats::ResetStats() {
    baseStats.clear();
    modifiers.clear();
    definitionId.clear(); 
}
