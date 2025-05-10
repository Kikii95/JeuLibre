#include "pch.h"

ComponentNavire::ComponentNavire(Entity* entity, ShipType type)
    : Component(entity), shipType(type), storageCapacity(100.0f) {
    integrityMap[ShipPart::Hull] = 100.0f;
    integrityMap[ShipPart::Sail] = 100.0f;
    integrityMap[ShipPart::Mast] = 100.0f;
    integrityMap[ShipPart::Rudder] = 100.0f;
}

void ComponentNavire::SetIntegrity(ShipPart part, float value) {
    integrityMap[part] = clamp(value, 0.0f, 100.0f);
}

float ComponentNavire::GetIntegrity(ShipPart part) const {
    auto it = integrityMap.find(part);
    if (it != integrityMap.end())
        return it->second;
    return 0.0f;
}

void ComponentNavire::DamagePart(ShipPart part, float amount) {
    SetIntegrity(part, GetIntegrity(part) - amount);
}

void ComponentNavire::RepairPart(ShipPart part, float amount) {
    SetIntegrity(part, GetIntegrity(part) + amount);
}

float ComponentNavire::GetStorageCapacity() const {
    return storageCapacity;
}

void ComponentNavire::SetStorageCapacity(float capacity) {
    storageCapacity = maximum(0.0f, capacity);
}

ShipType ComponentNavire::GetShipType() const {
    return shipType;
}

void ComponentNavire::SetShipType(ShipType type) {
    shipType = type;
}
