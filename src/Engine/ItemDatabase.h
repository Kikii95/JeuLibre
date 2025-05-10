#pragma once
#include "ItemDefinition.h"

class ItemDatabase {
public:
    static ItemDatabase& Get();

    bool LoadFromFile(const std::string& path);
    void AddItem(const ItemDefinition& def);
    const ItemDefinition* GetItem(const std::string& id) const;
    const ItemDefinition* GetItemByUID(const std::string& uid, const ComponentInventory& inv) const;

    const std::unordered_map<std::string, ItemDefinition>& GetAllItems() const;


private:
    std::unordered_map<std::string, ItemDefinition> items;
};

ItemType StringToItemType(const std::string& typeStr);
std::string ItemTypeToString(ItemType type);
EquipmentSlot StringToEquipmentSlot(const std::string& slotStr);
std::string EquipmentSlotToString(EquipmentSlot slot);
std::string LocalizedSlotName(EquipmentSlot slot);