#include "pch.h"

namespace EntityFactory {

    Entity* CreatePlayer(const sf::Vector2f& position) {
        Entity* player = GameEngine::GetInstance().GetEntityManager().CreateEntity();

        player->AddComponent<ComponentTransform>(position, sf::Vector2f(32, 57));
        player->AddComponent<ComponentRender>();
        player->AddComponent<ComponentPhysics>();
        player->AddComponent<ComponentTag>("PLAYER");
        player->AddComponent<ComponentCollider>();
        player->AddComponent<ComponentInput>();
        player->AddComponent<ComponentWeapon>();
        player->AddComponent<ComponentHealth>();
        player->AddComponent<ComponentState>();
        player->AddComponent<ComponentCamera>();
        player->AddComponent<ComponentMoney>();
        player->AddComponent<ComponentStats>();
        player->AddComponent<ComponentInventory>();
        player->AddComponent<ComponentFont>();
        player->AddComponent<ComponentBuffDebuff>();
        player->AddComponent<ComponentPause>();
        player->AddComponent<ComponentEquipment>();

		//player->GetComponent<ComponentInventory>()->AddItem(ItemInstance("armor_outfit_leather_var4", 1));
		//player->GetComponent<ComponentInventory>()->AddItem(ItemInstance("weapon_dagger_iron", 1));
		//player->GetComponent<ComponentInventory>()->AddItem(ItemInstance("consumable_heal_potion_small_var7", 5));

        GameEngine::GetInstance().GetSystem<SystemStats>()->InitStatsFromProfile(player, "player");


        ToolBoxVisual::GetInstance().ApplyVisualConfig(player);

        auto* inv = player->GetComponent<ComponentInventory>();
        inv->SetCapacity(20);
		inv->SetMaxWeight(100.f);

        auto* render = player->GetComponent<ComponentRender>();
        render->SetTexture("../../res/Game/perso.png");
        render->SetRenderType(RenderType::Sprite);
        render->SetRenderLayer(3);

        auto* stats = player->GetComponent<ComponentStats>();
        float baseHealth = stats->GetStat("health");

        auto* health = player->GetComponent<ComponentHealth>();
        health->SetMaxHealth(baseHealth);
        health->SetHealth(baseHealth);

        auto* collider = player->GetComponent<ComponentCollider>();
        collider->SetType(ColliderType::Solid);

        sf::Vector2f originalSize(32.f, 57.f);

        sf::Vector2u windowSize = GameEngine::GetInstance().GetWindow().getSize();
        const float BASE_WIDTH = 1280.f;
        const float BASE_HEIGHT = 720.f;

        float scaleX = static_cast<float>(windowSize.x) / BASE_WIDTH;
        float scaleY = static_cast<float>(windowSize.y) / BASE_HEIGHT;

        float scaleRaw = std::min(scaleX, scaleY);
        float uniformScale = 1.f + (scaleRaw - 1.f) * 0.5f;

        sf::Vector2f scaledSize = originalSize * uniformScale;

		player->GetComponent<ComponentTransform>()->SetSize(scaledSize);



        return player;
    }

    Entity* CreateMerchant(const std::string& profileId, const sf::Vector2f& position) {
        Entity* merchant = GameEngine::GetInstance().GetEntityManager().CreateEntity();

        merchant->AddComponent<ComponentTransform>(position, sf::Vector2f(100, 100));
        merchant->AddComponent<ComponentRender>();
        merchant->AddComponent<ComponentTag>("MERCHANT");
        merchant->AddComponent<ComponentCollider>();
        merchant->AddComponent<ComponentState>();
        merchant->AddComponent<ComponentFont>();
        merchant->AddComponent<ComponentMerchant>();
        merchant->AddComponent<ComponentStats>();
        merchant->AddComponent<ComponentHealth>();

        GameEngine::GetInstance().GetSystem<SystemStats>()->InitStatsFromProfile(merchant, profileId);

        ToolBoxVisual::GetInstance().ApplyVisualConfig(merchant);

        auto* sm = GameEngine::GetInstance().GetSystem<SystemMerchant>();
        sm->GenerateRandomMerchantStock(merchant, 6);

        auto* stats = merchant->GetComponent<ComponentStats>();
        float baseHealth = stats->GetStat("health");

        auto* health = merchant->GetComponent<ComponentHealth>();
        health->SetMaxHealth(baseHealth);
        health->SetHealth(baseHealth);

        auto* render = merchant->GetComponent<ComponentRender>();
        render->SetRenderType(RenderType::Shape);
        render->SetRenderLayer(2);

        auto* collider = merchant->GetComponent<ComponentCollider>();
        collider->SetType(ColliderType::Mob);

        return merchant;
    }

    Entity* CreateEnemy(const std::string& id, const std::string& profileId, const std::string& difficultyZone, const sf::Vector2f& position) {

        Entity* mob = GameEngine::GetInstance().GetEntityManager().CreateEntity();

        mob->AddComponent<ComponentTransform>(position, sf::Vector2f(50, 50));
        mob->AddComponent<ComponentRender>();
        mob->AddComponent<ComponentTag>("ENEMY");
        mob->AddComponent<ComponentCollider>();
        mob->AddComponent<ComponentHealth>();
        mob->AddComponent<ComponentState>();
        mob->AddComponent<ComponentFont>();
        mob->AddComponent<ComponentWeapon>();
        mob->AddComponent<ComponentStats>();
        mob->AddComponent<ComponentBuffDebuff>();
        mob->AddComponent<ComponentLoot>();
        mob->AddComponent<ComponentDifficulty>();
        mob->AddComponent<ComponentZoneSpawner>(id);

        if (auto* diff = mob->GetComponent<ComponentDifficulty>()) {
            diff->SetZoneName(difficultyZone);
        }

        GameEngine::GetInstance().GetSystem<SystemStats>()->InitStatsFromProfile(mob, profileId);

        auto* stats = mob->GetComponent<ComponentStats>();
        float baseHealth = stats->GetStat("health");

        auto* health = mob->GetComponent<ComponentHealth>();
		if (baseHealth <= 0.f) {
			baseHealth = 100.f;
		}
        health->SetMaxHealth(baseHealth);
        health->SetHealth(baseHealth);

        auto* render = mob->GetComponent<ComponentRender>();


        const StatsDefinition* def = StatsDatabase::Get().GetDefinition(profileId);

        if (def) {
            if (!def->texture.empty()) {
                render->SetTexture(def->texture);
            }

            sf::Vector2f size(100.f, 100.f);

            if (!def->size.empty() && def->size.size() == 2) {
                sf::Vector2f originalSize(static_cast<float>(def->size[0]), static_cast<float>(def->size[1]));

                sf::Vector2u currentSize = GameEngine::GetInstance().GetWindow().getSize();

                const float BASE_WIDTH = 1280.f;
                const float BASE_HEIGHT = 720.f;

                float scaleX = static_cast<float>(currentSize.x) / BASE_WIDTH;
                float scaleY = static_cast<float>(currentSize.y) / BASE_HEIGHT;

                float scaleRaw = std::min(scaleX, scaleY);
                float uniformScale = 1.f + (scaleRaw - 1.f) * 0.5f; 
                size = originalSize * uniformScale;
            }

            mob->GetComponent<ComponentTransform>()->SetSize(size);
        }


        render->SetRenderType(RenderType::Sprite);
        render->SetRenderLayer(2);




        auto* collider = mob->GetComponent<ComponentCollider>();
        collider->SetType(ColliderType::Mob);


        ToolBoxVisual::GetInstance().ApplyVisualConfig(mob);

        // Applique les loots liés au profil
        auto* loot = mob->GetComponent<ComponentLoot>();
        if (loot) {
            const auto& table = LootDatabase::Get().GetLootFor(profileId);
            for (const LootSlot& slot : table) {
                loot->AddLoot(slot);
            }
        }

        return mob;
    }
}