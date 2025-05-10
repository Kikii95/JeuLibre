#pragma once

class SystemInventory : public System {
public:
    SystemInventory();

	SystemType GetType() const override { return SystemType::Reactive; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    bool TransferItem(Entity* from, Entity* to, const std::string& itemId, int quantity);
    void DropSelectedItem(Entity* player);
    void DisplayInventory(Entity* entity); 
    void ClearInventoryDisplay();

    bool IsInventoryVisible() const;
    void SetInventoryIsVisible(bool visible);

    const ItemDefinition* ResolveEquippedItemDefinition(Entity* entity, const std::string& uid);

	void UpdateInventory(Entity* entity);

    void ToggleEquipWeapon(Entity* player);

	void Logs() override;

private:
    bool inventoryVisible = false;

};
