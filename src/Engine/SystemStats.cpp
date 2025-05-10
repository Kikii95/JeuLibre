#include "pch.h"

SystemStats::SystemStats() {
}

void SystemStats::Update(float dt, const std::vector<Entity*>& entities) {
}

void SystemStats::Logs() {
}

void SystemStats::ApplyModifier(Entity* entity, const std::string& stat, int value) {
    auto* stats = entity->GetComponent<ComponentStats>();
    if (stats) {
        stats->AddModifier(stat, value);
    }
}

void SystemStats::RemoveModifier(Entity* entity, const std::string& stat, int value) {
    auto* stats = entity->GetComponent<ComponentStats>();
    if (stats) {
        stats->AddModifier(stat, -value);
    }
}

void SystemStats::ClearModifiers(Entity* entity) {
    auto* stats = entity->GetComponent<ComponentStats>();
    if (stats) {
        stats->ClearModifiers();
    }
}

void SystemStats::ApplyModifierGroup(Entity* entity, const std::string& sourceId, const std::unordered_map<std::string, int>& mods) {
    auto* stats = entity->GetComponent<ComponentStats>();
    if (stats) {
        stats->ApplyModifierGroup(sourceId, mods);
    }
}

void SystemStats::RemoveModifierGroup(Entity* entity, const std::string& sourceId, bool onlyIfFromEquipment) {
    auto* stats = entity->GetComponent<ComponentStats>();
    if (stats) {
        stats->RemoveModifierGroup(sourceId, onlyIfFromEquipment);
    }
}



int SystemStats::GetEffectiveStat(Entity* entity, const std::string& stat) const {
    auto* stats = entity->GetComponent<ComponentStats>();
    if (stats) {
        return stats->GetStat(stat);
    }
    return 0;
}

void SystemStats::InitStatsFromProfile(Entity* entity, const std::string& profileId) {
    if (!entity) return;

    auto* stats = entity->GetComponent<ComponentStats>();
    if (!stats) {
        stats = entity->AddComponent<ComponentStats>();
    }

    stats->LoadFromDefinition(profileId);

	auto* tag = entity->GetComponent<ComponentTag>();
	if (tag){
        {
            if (tag->GetTag() != "PLAYER") {
                auto* sysDiff = GameEngine::GetInstance().GetSystem<SystemDifficulty>();
                sysDiff->ApplyToEntity(entity, sysDiff->GetCurrentTimeModifier());
            }
        }
	}



}
