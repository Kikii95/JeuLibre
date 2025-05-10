#include "pch.h"

ComponentZoneSpawner::ComponentZoneSpawner(Entity* entity, const std::string& zoneId)
	: Component(entity), zoneId(zoneId) {
}

const std::string& ComponentZoneSpawner::GetZoneId() {
	return zoneId;
}

void ComponentZoneSpawner::SetZoneId(const std::string& id) {
	zoneId = id;
}

void ComponentZoneSpawner::SetRecentlySpawned(bool value) {
	recentlySpawned = value;
}

bool ComponentZoneSpawner::IsRecentlySpawned() const {
	return recentlySpawned;
}

