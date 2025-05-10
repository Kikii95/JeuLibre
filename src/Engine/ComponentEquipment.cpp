#include "pch.h"
ComponentEquipment::ComponentEquipment(Entity* owner)
    : Component(owner) {
}

void ComponentEquipment::Equip(EquipmentSlot slot, const std::string& uid, const std::string& itemId) {
    equipped[slot] = std::make_pair(uid, itemId);
}

void ComponentEquipment::Unequip(EquipmentSlot slot) {
    equipped.erase(slot);
}

bool ComponentEquipment::IsEquipped(EquipmentSlot slot) const {
    return equipped.find(slot) != equipped.end();
}

std::string ComponentEquipment::GetEquippedUID(EquipmentSlot slot) const {
    auto it = equipped.find(slot);
    return (it != equipped.end()) ? it->second.first : "";
}

std::string ComponentEquipment::GetEquippedItemID(EquipmentSlot slot) const {
    auto it = equipped.find(slot);
    return (it != equipped.end()) ? it->second.second : "";
}

EquipmentSlot ComponentEquipment::GetEquippedSlotByUID(const std::string& uid) const {
    for (const auto& [slot, pair] : equipped) {
        if (pair.first == uid)
            return slot;
    }
    return EquipmentSlot::None;
}

const std::unordered_map<EquipmentSlot, std::pair<std::string, std::string>>& ComponentEquipment::GetAll() const {
    return equipped;
}
