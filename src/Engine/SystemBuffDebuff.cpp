#include "pch.h"

SystemBuffDebuff::SystemBuffDebuff() {}

void SystemBuffDebuff::ApplyEffect(Entity* target, const std::string& effectId) {
    const EffectDefinition* def = EffectDatabase::Get().GetEffect(effectId);
    if (!def) return;



    auto* buff = target->GetComponent<ComponentBuffDebuff>();
    if (!buff) return;

    buff->AddEffect(def, "SOURCE_DIRECT", false); 

	std::cout << "[BuffDebuff] Effet applique : " << def->id << " a entity ID " << target->GetID() << std::endl;
}
void SystemBuffDebuff::Update(float dt, const std::vector<Entity*>& entities) {
    float globalTime = GameEngine::GetInstance().GetTimer().TotalTime();
    constexpr float TICK_INTERVAL = 1.0f;

    auto* healthSys = GameEngine::GetInstance().GetSystem<SystemHealth>();
    auto* statsSys = GameEngine::GetInstance().GetSystem<SystemStats>();

    for (Entity* entity : entities) {
        auto* buff = entity->GetComponent<ComponentBuffDebuff>();
        auto* stats = entity->GetComponent<ComponentStats>();
        if (!buff || !stats) continue;

        std::vector<std::string> toRemove;

        for (auto& effect : buff->GetActiveEffects()) {
            const EffectDefinition* def = EffectDatabase::Get().GetEffect(effect.effectId);
            if (!def) continue;

           /* std::cout << "[BuffDebuff::Update] Entity " << entity->GetID()
                << " | Effet : " << def->id
                << " | fromEquip=" << effect.fromEquip
                << " | applied=" << effect.applied
                << " | remainingTicks=" << effect.remainingTicks << "\n";*/

            if (!effect.applied && !def->statModifiers.empty()) {
                statsSys->ApplyModifierGroup(entity, def->id, def->statModifiers);
                std::cout << "[BuffDebuff] " << def->id << " applique des modifs de stats.\n";
            }

            if (!effect.applied && def->healAmount > 0) {
                healthSys->Heal(entity, def->healAmount);
                std::cout << "[BuffDebuff] " << def->id << " soigne " << def->healAmount << " PV.\n";
            }

            effect.applied = true;

            float elapsed = globalTime - effect.lastTickTime;
            if (elapsed >= def->tickInterval) {
                effect.lastTickTime = globalTime;

                if (def->tickDamage > 0) {
                    healthSys->ApplyDamage(entity, def->tickDamage);
                    std::cout << "[BuffDebuff] " << def->id << " inflige " << def->tickDamage << " dégâts.\n";
                }

                if (def->tickHeal > 0) {
                    healthSys->Heal(entity, def->tickHeal);
                    std::cout << "[BuffDebuff] " << def->id << " régénère " << def->tickHeal << " PV.\n";
                }

                if (!effect.fromEquip && --effect.remainingTicks <= 0) {
                    toRemove.push_back(def->id);
                }
            }
        }


        for (const std::string& id : toRemove) {
            buff->RemoveEffect(id, false);
            std::cout << "[BuffDebuff::Update] Suppression effet : " << id << " (depuis Update)\n";
            statsSys->RemoveModifierGroup(entity, id, false);
            std::cout << "[BuffDebuff] Effet expiré : " << id << "\n";
            std::cout << "[BuffDebuff] Modif de stats retirée : " << id << "\n";
        }
    }
}




void SystemBuffDebuff::Logs() {
	if (!debugMode || !logSystemBuffDebuff) return;
	EntityManager& em = GameEngine::GetInstance().GetEntityManager();
	const auto& entities = em.GetAllEntities();
	int total = 0;
	int buffs = 0;
	for (Entity* e : entities) {
		auto* buff = e->GetComponent<ComponentBuffDebuff>();
		if (!buff) continue;
		++total;
		buffs++;
		HEAD("sys_BUFFDEBUFF") << "Entity " << e->GetID() << " a un composant buff/debuff." << ENDL;
	}
	if (total == 0) {
		HEAD("sys_BUFFDEBUFF") << "Aucun buff/debuff trouve." << ENDL;
	}
}