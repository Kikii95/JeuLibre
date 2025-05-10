#include "pch.h"

SystemItem::SystemItem() {}

void SystemItem::Update(float dt, const std::vector<Entity*>& entities) {
    for (Entity* entity : entities) {
        auto* decay = entity->GetComponent<ComponentDecay>();
        if (!decay) continue;

        decay->Update(dt);
        if (decay->IsExpired()) {
            GameEngine::GetInstance().GetEntityManager().DestroyEntity(entity);/*
            std::cout << "[SystemItem] Suppression auto : " << entity->GetID() << std::endl;*/
        }

		auto* entityTag = entity->GetComponent<ComponentTag>();

		if (!entityTag || entity->IsDestroyed()) continue;
        if (entityTag->GetTag() != "DROPPED_ITEM") continue;

        auto* clickable = entity->GetComponent<ComponentClickable>();
        if (!clickable) continue;

        clickable->SetOnLeftClick([this, entity]() {
            auto* player = GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("PLAYER")[0];
            if (player) {
                PickupItem(player, entity);
            }
            });
    }
}

void SystemItem::PickupItem(Entity* picker, Entity* itemEntity) {
    auto* inv = picker->GetComponent<ComponentInventory>();
    auto* itemComp = itemEntity->GetComponent<ComponentItem>();
    if (!inv || !itemComp) return;

    const ItemInstance& instance = itemComp->instance;
    if (inv->AddItem(instance)) {
        std::cout << "[SystemItem] Objet ramassé : " << instance.itemId << " x" << instance.quantity << std::endl;
        GameEngine::GetInstance().GetEntityManager().DestroyEntity(itemEntity);

        GameEngine::GetInstance().GetSystem<SystemInventory>()->UpdateInventory(picker);
    }
    else {
        std::cout << "[SystemItem] Inventaire plein, impossible de ramasser " << instance.itemId << std::endl;
    }
}

void SystemItem::DropItem(const ItemInstance& instance, const sf::Vector2f& basePos) {
    const ItemDefinition* def = ItemDatabase::Get().GetItem(instance.itemId);
    if (!def) return;

    sf::Vector2f offset(
        static_cast<float>(rand() % 121 - 60),
        static_cast<float>(rand() % 121 - 60)
    );
    sf::Vector2f dropPos = basePos + offset;

    Entity* drop = GameEngine::GetInstance().GetEntityManager().CreateEntity();

    drop->AddComponent<ComponentTransform>(dropPos, sf::Vector2f(40.f, 40.f));
    drop->AddComponent<ComponentItem>(instance);
    drop->AddComponent<ComponentClickable>();
    drop->AddComponent<ComponentTag>("DROPPED_ITEM");
    drop->AddComponent<ComponentDecay>(itemLifetime);

    auto* render = drop->AddComponent<ComponentRender>();
    render->SetRenderLayer(1);
    render->SetColor(sf::Color(150, 75, 0));

    auto* font = drop->AddComponent<ComponentFont>();
    font->SetFontByName("testFont");
    font->SetDeferredText(def->name);
    font->SetFixedOnScreen(false);

    ToolBoxVisual::GetInstance().CenterTextAbove(drop, font, 20.f, 0.f);

}
