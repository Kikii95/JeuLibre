#include "pch.h"

SystemMoney::SystemMoney() {}

void SystemMoney::Update(float dt, const std::vector<Entity*>& entities) {
}

bool SystemMoney::Pay(Entity* entity, int amount) {
    auto* money = entity->GetComponent<ComponentMoney>();
    if (!money) return false;
    return money->Spend(amount);
}

void SystemMoney::Give(Entity* entity, int amount) {
    auto* money = entity->GetComponent<ComponentMoney>();
    if (money) money->Add(amount);
}

int SystemMoney::Get(Entity* entity) const {
    auto* money = entity->GetComponent<ComponentMoney>();
    return money ? money->GetBalance() : 0;
}








void SystemMoney::Logs() {
    if (!debugMode || !logSystemMoney) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int richest = 0;
    int poorest = INT_MAX;
    int sum = 0;

    for (Entity* e : entities) {
        auto* money = e->GetComponent<ComponentMoney>();
        if (!money) continue;

        int gold = money->GetBalance();
        sum += gold;
        if (gold > richest) richest = gold;
        if (gold < poorest) poorest = gold;
        ++total;
    }

    float average = (total > 0) ? static_cast<float>(sum) / total : 0.0f;

    HEAD("sys_MONEY") << "Entites avec argent : " << (int)total
        << " | Total or : " << (int)sum
        << " | Moyenne : " << average
        << " | Min : " << (int)poorest
        << " | Max : " << (int)richest << ENDL;
}
