#include "pch.h"

ComponentInventory::ComponentInventory(Entity* entity, float capacity)
    : Component(entity), capacity(capacity) {
}

bool ComponentInventory::HasItem(const std::string& itemId, int quantity) const {
	for (const auto& item : items) {
		if (item.itemId == itemId && item.quantity >= quantity) {
			return true;
		}
	}
	return false;
}

bool ComponentInventory::AddItem(const ItemInstance& item) {
    const ItemDefinition* def = ItemDatabase::Get().GetItem(item.itemId);
    if (!def) return false;

    if (GetTotalWeight() + def->weight > maxWeight) {
        std::cout << "[Inventory] Trop lourd pour ajouter cet item !" << std::endl;
        return false;
    }


    if (!def->stackable) {
        for (int i = 0; i < item.quantity; ++i) {
            ItemInstance inst(item.itemId, 1);
            items.push_back(inst);
        }
        std::cout << "[Inventory] " << item.quantity << "x " << def->name << " (non stackable)\n";
        return true;
    }

    for (auto& i : items) {
        if (i.itemId == item.itemId) {
            i.quantity += item.quantity;
            std::cout << "[Inventory] Stacke : " << def->name << " x" << item.quantity << "\n";
            return true;
        }
    }

    items.push_back(item);
    std::cout << "[Inventory] Nouveau stack : " << def->name << " x" << item.quantity << "\n";
    return true;
}


bool ComponentInventory::RemoveItem(const std::string& itemId, int quantity) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->itemId == itemId) {
            if (it->quantity <= quantity) {
                items.erase(it);
            }
            else {
                it->quantity -= quantity;
            }
            return true;
        }
    }
    return false;
}

bool ComponentInventory::RemoveItemByUID(const std::string& uid) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->uid == uid) {
            if (it->quantity > 1) {
                it->quantity--;
            }
            else {
                items.erase(it);
            }
            return true;
        }
    }
    return false;
}


float ComponentInventory::GetMaxWeight() const {
    return maxWeight; 
}

void ComponentInventory::SetMaxWeight(float value) {
    maxWeight = value; 
}

bool ComponentInventory::IsFull() const {
    return GetTotalWeight() > maxWeight; 
}


float ComponentInventory::GetTotalWeight() const {
    float total = 0.0f;
    for (const auto& item : items) {
        const ItemDefinition* def = ItemDatabase::Get().GetItem(item.itemId);
        if (def) {
            total += def->weight * item.quantity;
        }
    }
    return total;
}

float ComponentInventory::GetCapacity() const {
    return capacity;
}

void ComponentInventory::SetCapacity(float newCapacity) {
    capacity = maximum(0.0f, newCapacity);
}

void ComponentInventory::SetSelectedIndex(int index) {
	selectedIndex = index;
}

int ComponentInventory::GetSelectedIndex() const {
	return selectedIndex;
}

std::vector<ItemInstance>& ComponentInventory::GetItems() {
	return items;
}

const std::vector<ItemInstance>& ComponentInventory::GetItems() const {
    return items;
}

