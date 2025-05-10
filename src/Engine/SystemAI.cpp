#include "pch.h"

SystemAI::SystemAI() {}

void SystemAI::SetInCombat(bool active) {
    inCombat = active;
}

void SystemAI::Update(float dt, const std::vector<Entity*>& entities) {
    for (Entity* e : entities) {
        auto* ai = e->GetComponent<ComponentAI>();
        auto* state = e->GetComponent<ComponentState>();
        if (!ai || !state || state->GetState() != EntityState::Idle) continue;

        Entity* target = FindClosestTarget(e, entities);
        ai->SetTarget(target);

        switch (ai->GetBehavior()) {
        case BehaviorType::Aggressive:
            if (!target) break;

            if (inCombat) {
                if (IsTargetInWeaponRange(e, target)) {
                    state->SetState(EntityState::Attacking);
                }
            }
            else {
                float dist = Distance2D(e->GetComponent<ComponentTransform>()->GetPosition(),
                    target->GetComponent<ComponentTransform>()->GetPosition());
                if (dist <= 300.f) {
                    state->SetState(EntityState::Moving); 
                }
            }
            break;

        case BehaviorType::Fleeing:
            if (!inCombat) {
                state->SetState(EntityState::Moving); 
            }
            break;

        case BehaviorType::Passive:
        default:
            break;
        }
    }
}

Entity* SystemAI::FindClosestTarget(Entity* seeker, const std::vector<Entity*>& entities) {
    auto* seekerTr = seeker->GetComponent<ComponentTransform>();
    if (!seekerTr) return nullptr;

    float minDist = std::numeric_limits<float>::max();
    Entity* closest = nullptr;

    for (Entity* e : entities) {
        if (e == seeker) continue;
        if (!e->GetComponent<ComponentHealth>()) continue;

        auto* tr = e->GetComponent<ComponentTransform>();
        if (!tr) continue;

        float dist = inCombat
            ? DistanceHex(static_cast<sf::Vector2i>(seekerTr->GetPosition()), static_cast<sf::Vector2i>(tr->GetPosition()))
            : Distance2D(seekerTr->GetPosition(), tr->GetPosition());

        if (dist < minDist) {
            minDist = dist;
            closest = e;
        }
    }

    return closest;
}

bool SystemAI::IsTargetInWeaponRange(Entity* attacker, Entity* target) {
    auto* atkTr = attacker->GetComponent<ComponentTransform>();
    auto* tgtTr = target->GetComponent<ComponentTransform>();
    auto* weapon = attacker->GetComponent<ComponentWeapon>();
    if (!atkTr || !tgtTr || !weapon) return false;

    int range = 1;
    const auto* item = ItemDatabase::Get().GetItem(weapon->GetWeaponId());
    if (item) range = item->range;

    sf::Vector2i a = static_cast<sf::Vector2i>(atkTr->GetPosition());
    sf::Vector2i b = static_cast<sf::Vector2i>(tgtTr->GetPosition());

    return DistanceHex(a, b) <= range;
}

float SystemAI::DistanceHex(const sf::Vector2i& a, const sf::Vector2i& b) {
    return (abs(a.x - b.x) + abs(a.x + a.y - b.x - b.y) + abs(a.y - b.y)) / 2.f;
}

float SystemAI::Distance2D(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


void SystemAI::Logs() {
	if (!debugMode || !logSystemAI) return;
	EntityManager& em = GameEngine::GetInstance().GetEntityManager();
	const auto& entities = em.GetAllEntities();
	int total = 0;
	int aggressive = 0;
	int passive = 0;
	int fleeing = 0;
	for (Entity* e : entities) {
		auto* ai = e->GetComponent<ComponentAI>();
		if (!ai) continue;
		++total;
		switch (ai->GetBehavior()) {
		case BehaviorType::Aggressive:
			++aggressive;
			break;
		case BehaviorType::Passive:
			++passive;
			break;
		case BehaviorType::Fleeing:
			++fleeing;
			break;
		default:
			break;
		}
	}
	HEAD("sys_AI") << "Total d'entites : " << total
		<< " | Comportement agressif : " << aggressive
		<< " | Comportement passif : " << passive
		<< " | Comportement fuyard : " << fleeing << ENDL2;
}