#pragma once
#include "ComponentEquipment.h"

enum class ItemType {
    Weapon,
	Armor,
	Accessory,
  
    Generic,

    Trophy,
    QuestItem,

    Currency,

    Consumable,
    Resource,

};


enum class AreaType {
    None,
    Line,
    Arc,
    Cone,
    Circle
};

struct ItemDefinition {
    // Identite
    std::string id;
    std::string name;
    std::string description;

    // General
    ItemType type = ItemType::Generic;
    EquipmentSlot equipmentSlot = EquipmentSlot::None;
    float weight = 0.0f;
    int basePrice = 0;
    bool stackable = true;

    // Combat 
    int damage = 0;
    int range = 1;
    int penetration = 0;
    AreaType area = AreaType::None;
    int areaSize = 1;

    // Effets
    std::string effectId;
    int healAmount = 0;
	std::vector<std::string> effects;
};