#pragma once

class SystemMerchant : public System {
public:
    SystemMerchant();

	SystemType GetType() const override { return SystemType::Reactive; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    bool BuyItem(Entity* buyer, Entity* merchant, const std::string& itemId, int quantity);
    bool SellItem(Entity* seller, Entity* merchant, const std::string& itemId, int quantity);

    void DisplayMerchantStock(Entity* merchant);
    void ClearMerchantDisplay();

    bool IsMerchantVisible() const;
    void SetMerchantIsVisible(bool visible);

    void SetCurrentMerchant(Entity* e);
    Entity* GetCurrentMerchant() const;

    int GetSellPrice(const std::string& itemId, Entity* merchant) const;

    void GenerateRandomMerchantStock(Entity* merchant, int itemCount);

	void Logs() override;

private:
    int GetItemPrice(const MerchantSlot& slot, float rate) const;

    bool merchantIsVisible = false;
    Entity* currentMerchant = nullptr;

};

