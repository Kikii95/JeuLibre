#pragma once

enum class ShipPart {
    Hull,
    Sail,
    Mast,
    Rudder
};

enum class ShipType {
    Light,
    Medium,
    Heavy
};

class ComponentNavire : public Component {
public:
    ComponentNavire(Entity* entity, ShipType type = ShipType::Medium);

    void SetIntegrity(ShipPart part, float value);
    float GetIntegrity(ShipPart part) const;

    float GetStorageCapacity() const;
    void SetStorageCapacity(float capacity);

    ShipType GetShipType() const;
    void SetShipType(ShipType type);

    void DamagePart(ShipPart part, float amount);
    void RepairPart(ShipPart part, float amount);

private:
    ShipType shipType;
    float storageCapacity;
    std::unordered_map<ShipPart, float> integrityMap;
};
