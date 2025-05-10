#include "pch.h"

using json = nlohmann::json;

ItemDatabase& ItemDatabase::Get() {
    static ItemDatabase instance;
    return instance;
}

bool ItemDatabase::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erreur d'ouverture : " << path << std::endl;
        return false;
    }

    json root;
    file >> root;

    if (!root.contains("items") || !root["items"].is_array()) {
        std::cerr << "Format JSON invalide : 'items' manquant ou incorrect." << std::endl;
        return false;
    }

    const auto& itemsArray = root["items"];
    for (const auto& entry : itemsArray) {
        ItemDefinition def;
        def.id = entry["id"];
        def.name = entry["name"];
        def.description = entry.value("description", "");
        def.type = StringToItemType(entry["type"]);
        def.equipmentSlot = StringToEquipmentSlot(entry.value("equipmentSlot", ""));
        def.weight = entry.value("weight", 0.0f);
        def.basePrice = entry.value("basePrice", 0);
        def.stackable = entry.value("stackable", true);
        def.damage = entry.value("damage", 0);
        def.range = entry.value("range", 0);
        def.healAmount = entry.value("healAmount", 0);
        def.effectId = entry.value("effectId", "");
        def.areaSize = entry.value("areaSize", 1);
        def.penetration = entry.value("penetration", 0);

        std::string areaStr = entry.value("area", "None");
        if (areaStr == "Arc")        def.area = AreaType::Arc;
        else if (areaStr == "Cone")  def.area = AreaType::Cone;
        else if (areaStr == "Circle")def.area = AreaType::Circle;
        else if (areaStr == "Line")  def.area = AreaType::Line;
        else                         def.area = AreaType::None;

        if (entry.contains("effects") && entry["effects"].is_array()) {
            for (const auto& effectId : entry["effects"]) {
                if (effectId.is_string()) {
                    def.effects.push_back(effectId.get<std::string>());
                }
            }
        }

        AddItem(def);
    }


    std::cout << "[ItemDatabase] " << items.size() << " objets charges depuis " << path << std::endl;
    return true;
}

void ItemDatabase::AddItem(const ItemDefinition& def) {
    items[def.id] = def;
}

const ItemDefinition* ItemDatabase::GetItem(const std::string& id) const {
    auto it = items.find(id);
    return it != items.end() ? &it->second : nullptr;
}

const ItemDefinition* ItemDatabase::GetItemByUID(const std::string& uid, const ComponentInventory& inv) const {
    for (const auto& item : inv.GetItems()) {
        if (item.uid == uid) {
            return GetItem(item.itemId);
        }
    }
    return nullptr;
}


const std::unordered_map<std::string, ItemDefinition>& ItemDatabase::GetAllItems() const {
    return items;
}

ItemType StringToItemType(const std::string& typeStr) {
    if (typeStr == "Generic")    return ItemType::Generic;
    if (typeStr == "Weapon")     return ItemType::Weapon;
    if (typeStr == "Armor")      return ItemType::Armor;
    if (typeStr == "Accessory")  return ItemType::Accessory;
    if (typeStr == "Consumable") return ItemType::Consumable;
    if (typeStr == "Resource")   return ItemType::Resource;
    if (typeStr == "Trophy")     return ItemType::Trophy;
    if (typeStr == "QuestItem")  return ItemType::QuestItem;
    if (typeStr == "Currency")   return ItemType::Currency;
    return ItemType::Generic;
}


std::string ItemTypeToString(ItemType type) {
    switch (type) {
    case ItemType::Generic:    return "Generic";
    case ItemType::Weapon:     return "Weapon";
    case ItemType::Armor:      return "Armor";
    case ItemType::Accessory:  return "Accessory";
    case ItemType::Consumable: return "Consumable";
    case ItemType::Resource:   return "Resource";
    case ItemType::Trophy:     return "Trophy";
    case ItemType::QuestItem:  return "QuestItem";
    case ItemType::Currency:   return "Currency";
    default:                   return "Unknown";
    }
}

EquipmentSlot StringToEquipmentSlot(const std::string& slotStr) {
    if (slotStr == "Head")        return EquipmentSlot::Head;
    if (slotStr == "Chest")        return EquipmentSlot::Chest;
    if (slotStr == "Legs")        return EquipmentSlot::Legs;
    if (slotStr == "Feet")        return EquipmentSlot::Feet;
    if (slotStr == "Gloves")      return EquipmentSlot::Gloves;
    if (slotStr == "Ring")        return EquipmentSlot::Ring;
    if (slotStr == "Amulet")      return EquipmentSlot::Amulet;
    if (slotStr == "Shield")      return EquipmentSlot::Shield;
    if (slotStr == "Weapon")      return EquipmentSlot::Weapon;
    if (slotStr == "Consumable")  return EquipmentSlot::Consumable;
    return EquipmentSlot::None;
}


std::string EquipmentSlotToString(EquipmentSlot slot) {
    switch (slot) {
    case EquipmentSlot::Head:        return "Head";
    case EquipmentSlot::Chest:        return "Chest";
    case EquipmentSlot::Legs:        return "Legs";
    case EquipmentSlot::Feet:        return "Feet";
    case EquipmentSlot::Gloves:      return "Gloves";
    case EquipmentSlot::Ring:        return "Ring";
    case EquipmentSlot::Amulet:      return "Amulet";
    case EquipmentSlot::Shield:      return "Shield";
    case EquipmentSlot::Weapon:      return "Weapon";
    case EquipmentSlot::Consumable:  return "Consumable";
    default:                         return "Unknown";
    }
}

std::string LocalizedSlotName(EquipmentSlot slot) {
    static std::map<EquipmentSlot, std::string> localized = {
        {EquipmentSlot::Head, "Tête"},
        {EquipmentSlot::Chest, "Buste"},
        {EquipmentSlot::Legs, "Jambes"},
        {EquipmentSlot::Feet, "Pieds"},
        {EquipmentSlot::Gloves, "Gants"},
        {EquipmentSlot::Ring, "Anneau"},
        {EquipmentSlot::Amulet, "Amulette"},
        {EquipmentSlot::Shield, "Bouclier"},
        {EquipmentSlot::Weapon, "Arme"},
        {EquipmentSlot::Consumable, "Objet rapide"},
        {EquipmentSlot::None, "Aucun"}
    };
    return localized.contains(slot) ? localized[slot] : "Inconnu";
}
