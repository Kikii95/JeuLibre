#include "pch.h"

ComponentWeapon::ComponentWeapon(Entity* entity)
    : Component(entity) {}

const std::string& ComponentWeapon::GetWeaponId() const {
    return weaponId;
}

int ComponentWeapon::GetDamage() const {
    const auto* def = ItemDatabase::Get().GetItem(weaponId);
    return def ? def->damage : 0;
}

int ComponentWeapon::GetRange() const {
    const auto* def = ItemDatabase::Get().GetItem(weaponId);
    return def ? def->range : 0;
}

bool ComponentWeapon::IsValid() const {
    return ItemDatabase::Get().GetItem(weaponId) != nullptr;
}

void ComponentWeapon::Equip(const std::string& id) {
    weaponId = id;
}

void ComponentWeapon::Unequip() {
    weaponId.clear();
}

bool ComponentWeapon::IsEquipped() const {
    return !weaponId.empty();
}
