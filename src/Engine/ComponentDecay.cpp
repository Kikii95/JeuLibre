#include "pch.h"
#include "ComponentDecay.h"

ComponentDecay::ComponentDecay(Entity* entity, float lifetimeSeconds)
	: Component(entity), lifetime(lifetimeSeconds), elapsed(0.f) {
}

void ComponentDecay::Update(float dt) {
	elapsed += dt;
}

bool ComponentDecay::IsExpired() const {
	return elapsed >= lifetime;
}

float ComponentDecay::GetRemaining() const {
	return lifetime - elapsed;
}

