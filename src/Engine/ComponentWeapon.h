#pragma once

class ComponentWeapon : public Component {
public:
    ComponentWeapon(Entity* entity);

    const std::string& GetWeaponId() const;

    int GetDamage() const;
    int GetRange() const;
    bool IsValid() const;

    void Equip(const std::string& id);
    void Unequip();
    bool IsEquipped() const;

private:
    std::string weaponId;
};
