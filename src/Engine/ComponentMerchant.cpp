#include "pch.h"

ComponentMerchant::ComponentMerchant(Entity* entity, float buyRate, float sellRate)
    : Component(entity), buyRate(buyRate), sellRate(sellRate) {
}

void ComponentMerchant::AddItem(const MerchantSlot& slot) {
    for (auto& existing : stock) {
        if (existing.item.itemId == slot.item.itemId && slot.item.quantity > 0) {
            existing.item.quantity += slot.item.quantity;
            return;
        }
    }
    stock.push_back(slot);
}


void ComponentMerchant::RemoveItem(const std::string& itemId) {
    stock.erase(std::remove_if(stock.begin(), stock.end(),
        [&itemId](const MerchantSlot& slot) {
            return slot.item.itemId == itemId;
        }), stock.end());
}

std::vector<MerchantSlot>& ComponentMerchant::GetStock() {
    return stock;
}

const std::vector<MerchantSlot>& ComponentMerchant::GetStock() const {
    return stock;
}

void ComponentMerchant::ClearStock() {
    stock.clear();
}

float ComponentMerchant::GetBuyRate() const {
    return buyRate;
}

float ComponentMerchant::GetSellRate() const {
    return sellRate;
}

void ComponentMerchant::SetTradeRate(float rate) {
    buyRate = std::max(0.1f, rate);

    float margin = 0.4f + static_cast<float>(rand() % 41) / 100.f;
    sellRate = std::max(0.1f, buyRate * margin);
}

int ComponentMerchant::GetSelectedIndex() const {
	return selectedIndex;
}

void ComponentMerchant::SetSelectedIndex(int index) {
	selectedIndex = index;
}