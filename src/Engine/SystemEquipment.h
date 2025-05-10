#pragma once

class SystemEquipment : public System {
public:
    SystemEquipment() = default;

    void Update(float dt, const std::vector<Entity*>& entities) override;

	void EquipItem(Entity* entity, const std::string& itemId);
	void EquipItemByInstance(Entity* entity, const ItemInstance& item);

	const std::unordered_map<EquipmentSlot, std::string>& GetAll(Entity* entity) const;
	void UnequipSlot(Entity* entity, EquipmentSlot slot);

    void ApplyEquipmentEffects(Entity* entity); 
    void RemoveEquipmentEffects(Entity* entity, EquipmentSlot onlySlot);


    SystemType GetType() const override { return SystemType::Reactive; }
    void Logs() override;
};
