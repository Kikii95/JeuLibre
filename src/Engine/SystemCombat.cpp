#include "pch.h"

SystemCombat::SystemCombat() {}

void SystemCombat::Update(float dt, const std::vector<Entity*>& entities) {
    for (Entity* entity : entities) {
        auto* state = entity->GetComponent<ComponentState>();
        auto* ai = entity->GetComponent<ComponentAI>();
        if (!state || state->GetState() != EntityState::Attacking || !ai) continue;

        Entity* target = ai->GetTarget();
        if (target) {
            ExecuteAttack(entity, target);
            state->SetState(EntityState::Waiting);
        }
    }
}

void SystemCombat::ExecuteAttack(Entity* attacker, Entity* target) {
    if (!attacker || !target) return;

    bool hitSuccess = false;
    int damage = CalculateDamage(attacker, target, hitSuccess);
    GameEngine::GetInstance().GetSystem<SystemHealth>()->ApplyDamage(target, damage);

    auto* weapon = attacker->GetComponent<ComponentWeapon>();
    if (weapon) {
        const ItemDefinition* itemDef = ItemDatabase::Get().GetItem(weapon->GetWeaponId());
        if (itemDef && !itemDef->effectId.empty()) {
            if (hitSuccess) {
                ApplyWeaponEffect(attacker, target, itemDef->effectId);
            }
        }
        if (itemDef && !itemDef->effects.empty()) {
            for (const std::string& eid : itemDef->effects) {
                if (!eid.empty() && hitSuccess) { 
                    ApplyWeaponEffect(attacker, target, eid);
                }
            }
        }

    }
}


int SystemCombat::CalculateDamage(Entity* attacker, Entity* target, bool& hitSuccess) {
    int attack = 0;
    int defense = 0;
    int weaponDamage = 0;
    int critChance = 0;
    int accuracy = 100;

    bool isCrit = false;
    bool isSuccess = true;
    bool isSelfHit = false;
    bool isPerfectHit = false;

    auto* atkStats = attacker->GetComponent<ComponentStats>();
    auto* defStats = target->GetComponent<ComponentStats>();
    auto* weapon = attacker->GetComponent<ComponentWeapon>();

    if (atkStats) {
        attack += atkStats->GetStat("attack");
        critChance = atkStats->GetStat("crit");
        accuracy = atkStats->GetStat("accuracy");
    }

    if (defStats) {
        defense += defStats->GetStat("defense");
    }

    if (weapon) {
        const auto* weaponDef = ItemDatabase::Get().GetItem(weapon->GetWeaponId());
        if (weaponDef) {
            weaponDamage = weaponDef->damage;
            attack += weaponDamage;
        }
    }

    int roll = rand() % 100 + 1;
    std::cout << "[Combat] Jet de chance : " << roll << "\n";

    if (roll == 1) {
        isSelfHit = true;
    }
    else if (roll == 100) {
        isPerfectHit = true;
    }
    else if (roll >= (100 - critChance)) {
        isCrit = true;
    }
    else if (roll < (100 - accuracy)) {
        isSuccess = false;
    }

    if (!isSuccess && !isSelfHit) {
        hitSuccess = false;
        std::cout << "[Combat] Attaque ratée.\n";
        return 0;
    }
    else {
        hitSuccess = true;
    }

    float ratio = static_cast<float>(attack) / std::max(1.0f, static_cast<float>(attack + defense));
    float baseDamage = attack * ratio;

    float variance = 0.9f + static_cast<float>(rand() % 21) / 100.0f;
    float damage = baseDamage * variance;

    if (isCrit) damage *= 1.5f;
    if (isPerfectHit) damage *= 2.0f;

    int finalDamage = std::max(1, static_cast<int>(damage));

    // Logs
    std::cout << "[Combat] ----------------------------\n";
    std::cout << "[Combat] Attaquant : " << attacker->GetID() << " | Cible : " << target->GetID() << "\n";
    std::cout << "[Combat] ATK = " << attack << " (arme +" << weaponDamage << ") | DEF = " << defense << "\n";
	std::cout << "[Combat] OwnDef = " << attacker->GetComponent<ComponentStats>()->GetStat("defense") << "\n";
    std::cout << "[Combat] CRIT = " << critChance << "% | ACC = " << accuracy << "%\n";
    std::cout << "[Combat] Ratio = " << ratio << " | Variance = " << variance << "\n";
    if (isCrit) std::cout << "[Combat] Coup critique (x1.5)\n";
    if (isPerfectHit) std::cout << "[Combat] Réussite critique (x2)\n";
    if (isSelfHit) std::cout << "[Combat] Échec critique ! L'attaquant se blesse.\n";
    std::cout << "[Combat] Dégâts finaux infligés : " << finalDamage << "\n";
    std::cout << "[Combat] ----------------------------\n";

    if (isSelfHit) {
        GameEngine::GetInstance().GetSystem<SystemHealth>()->ApplyDamage(attacker, finalDamage / 2);
        return 0;
    }

    return finalDamage;
}






void SystemCombat::ApplyWeaponEffect(Entity* attacker, Entity* target, const std::string& effectId) {
    if (effectId.empty() || !target) return;


    GameEngine::GetInstance().GetSystem<SystemBuffDebuff>()->ApplyEffect(target, effectId);
    std::cout << "[Combat] Effet de l'arme applique : " << effectId << std::endl;
}


void SystemCombat::Logs() {
	if (!debugMode || !logSystemCombat) return;
	EntityManager& em = GameEngine::GetInstance().GetEntityManager();
	const auto& entities = em.GetAllEntities();
	int total = 0;
	int attacking = 0;
	for (Entity* e : entities) {
		auto* state = e->GetComponent<ComponentState>();
		if (!state) continue;
		++total;
		if (state->GetState() == EntityState::Attacking) {
			++attacking;
			HEAD("sys_COMBAT") << "Entity " << e->GetID() << " est en train d'attaquer." << ENDL;
		}
	}
	HEAD("sys_COMBAT") << "Total d'entites : " << total
		<< " | Attaquant : " << attacking << ENDL2;
}