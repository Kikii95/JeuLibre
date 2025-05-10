#include "pch.h"

SystemDifficulty::SystemDifficulty() {}

void SystemDifficulty::Update(float dt, const std::vector<Entity*>& entities) {
    float totalTime = GameEngine::GetInstance().GetTimer().TotalTime();

    SetCurrentTimeModifier(ComputeTimeModifier(totalTime));

    //for (Entity* e : entities) {
    //    ApplyToEntity(e, mod);
    //}
}


float SystemDifficulty::ComputeTimeModifier(float timeSeconds) const {
	return 0.1f * std::log(1.f + timeSeconds / diffChangeTimer); 
}


void SystemDifficulty::ApplyToEntity(Entity* entity, float timeModifier) {
    auto* difficulty = entity->GetComponent<ComponentDifficulty>();
    auto* stats = entity->GetComponent<ComponentStats>();
    auto* tag = entity->GetComponent<ComponentTag>();

    if (!difficulty || !stats) return;

    difficulty->SetTimeModifier(timeModifier);

    const std::string& zoneName = difficulty->GetZoneName();
    
    float zoneModifier = 1.0f;
    if (zoneName == "ZONE_EASY")       zoneModifier = 1.0f;
    else if (zoneName == "ZONE_MEDIUM") zoneModifier = 1.5f;
    else if (zoneName == "ZONE_HARD")   zoneModifier = 2.0f;
    else if (zoneName == "ZONE_BOSS")   zoneModifier = 3.0f;
    else if (zoneName == "ZONE_BOSS_HARD") zoneModifier = 4.0f;
    else if (zoneName == "ZONE_CHAMPION") zoneModifier = 10.f;

    difficulty->SetZoneModifier(zoneModifier);

    stats->ClearModifiers();

    float effective = difficulty->GetEffectiveDifficulty();
    if (effective > 1.0f) {
        int bonus = static_cast<int>((effective - 1.0f) * 4);
        stats->AddModifier("health", bonus * 2);
        stats->AddModifier("attack", bonus);
        stats->AddModifier("defense", bonus / 2);
    }

    auto* health = entity->GetComponent<ComponentHealth>();
    if (health) {
        float newMaxHealth = stats->GetStat("health");
        health->SetMaxHealth(newMaxHealth);
        health->SetHealth(newMaxHealth);
    }

	//std::cout << "[SystemDifficulty] Entity " << entity->GetID()
	//	<< " | Zone: " << zoneName
	//	<< " | Modificateur temps: " << timeModifier
	//	<< " | Modificateur zone: " << zoneModifier
	//	<< " | Difficulté effective: " << effective
	//	<< ENDL;

}

void SystemDifficulty::SetCurrentTimeModifier(float modifier) {
	currentTimeModifier = modifier;
}

float SystemDifficulty::GetCurrentTimeModifier() {
	return currentTimeModifier;
}

void SystemDifficulty::Logs() {
    if (!debugMode || !logSystemDifficulty) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    float time = GameEngine::GetInstance().GetTimer().TotalTime();
    float mod = ComputeTimeModifier(time);

    int affected = 0;

    for (Entity* e : entities) {
        auto* difficulty = e->GetComponent<ComponentDifficulty>();
        auto* stats = e->GetComponent<ComponentStats>();
        if (!difficulty || !stats) continue;

        ++affected;

        float effective = difficulty->GetEffectiveDifficulty();
        int atk = stats->GetStat("attack");
        int def = stats->GetStat("defense");

        HEAD("sys_DIFFICULTY") << "Entity " << e->GetID()
            << " | Modificateur temps = " << mod
            << " | Diff. effective = " << effective
            << " | ATK: " << atk << " | DEF: " << def
            << ENDL;
    }

    HEAD("sys_DIFFICULTY") << "Temps ecoule : " << time
        << "s | Modificateur applique : " << mod
        << " | Entites affectees : " << affected
        << ENDL;
}
