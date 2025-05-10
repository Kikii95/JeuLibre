#pragma once
#include "Component.h"

enum class EquipmentSlot {
    // Armor
    Head,
    Chest,
    Legs,
    Feet,
    Gloves,

    // Jewelry
    Ring,
    Amulet,

    // Other
    Shield,

	// Weapons
    Weapon,

	// Other
    Consumable,
    None
};

class ComponentInventory;

class ComponentEquipment : public Component {
public:
    ComponentEquipment(Entity* owner);

    void Equip(EquipmentSlot slot, const std::string& uid, const std::string& itemId);
    void Unequip(EquipmentSlot slot);
    bool IsEquipped(EquipmentSlot slot) const;

    std::string GetEquippedUID(EquipmentSlot slot) const;
    std::string GetEquippedItemID(EquipmentSlot slot) const;

    EquipmentSlot GetEquippedSlotByUID(const std::string& uid) const;

    const std::unordered_map<EquipmentSlot, std::pair<std::string, std::string>>& GetAll() const;

private:
    std::unordered_map<EquipmentSlot, std::pair<std::string, std::string>> equipped; 
};
