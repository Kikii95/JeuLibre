#pragma once
#include "ItemInstance.h"

struct MerchantSlot {
    ItemInstance item;
    int overridePrice = 0;

    MerchantSlot() = default;
    MerchantSlot(const ItemInstance& instance, int price = 0)
        : item(instance), overridePrice(price) {
    }
};

class ComponentMerchant : public Component {
public:
    ComponentMerchant(Entity* entity, float buyRate = 1.0f, float sellRate = 1.0f);

    void AddItem(const MerchantSlot& slot);
    void RemoveItem(const std::string& itemId);

    std::vector<MerchantSlot>& GetStock(); 
    const std::vector<MerchantSlot>& GetStock() const; 

    void ClearStock();

    float GetBuyRate() const;
    float GetSellRate() const;

    void SetTradeRate(float rate);

    int GetSelectedIndex() const;
    void SetSelectedIndex(int index);


private:
    std::vector<MerchantSlot> stock;
	float buyRate; // 1.0f = 100% of base price
	float sellRate; // 1.0f = 100% of buyRate

    int selectedIndex = 0;
};
