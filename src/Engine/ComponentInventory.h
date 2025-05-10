#pragma once
#include "ItemInstance.h"

class ComponentInventory : public Component {
public:
    ComponentInventory(Entity* entity, float capacity = 100.0f);

	bool HasItem(const std::string& itemId, int quantity) const;

    bool AddItem(const ItemInstance& item);
    bool RemoveItem(const std::string& itemId, int quantity);

	bool RemoveItemByUID(const std::string& uid);

	void SetMaxWeight(float weight);
	float GetMaxWeight() const;
    float GetTotalWeight() const;
	bool IsFull() const;

    float GetCapacity() const;
    void SetCapacity(float newCapacity);

	void SetSelectedIndex(int index);
	int GetSelectedIndex() const;

	std::vector<ItemInstance>& GetItems();
    const std::vector<ItemInstance>& GetItems() const;

private:
    std::vector<ItemInstance> items;
    float capacity;
    float maxWeight = 100.f; 


    int selectedIndex = 0;
};
