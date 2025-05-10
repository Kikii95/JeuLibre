#include "pch.h"

void SystemEquipment::Update(float, const std::vector<Entity*>&) {}

void SystemEquipment::EquipItem(Entity* entity, const std::string& itemId) {
    auto* inv = entity->GetComponent<ComponentInventory>();
    if (!inv) return;

    auto it = std::find_if(inv->GetItems().begin(), inv->GetItems().end(), [&](const ItemInstance& i) {
        return i.itemId == itemId && !i.isEquipped;
        });

    if (it == inv->GetItems().end()) {
        std::cout << "[Equip] Aucun item disponible à équiper : " << itemId << "\n";
        return;
    }

    EquipItemByInstance(entity, *it);
}

void SystemEquipment::EquipItemByInstance(Entity* entity, const ItemInstance& item) {
    const ItemDefinition* def = ItemDatabase::Get().GetItem(item.itemId);
    if (!def || def->equipmentSlot == EquipmentSlot::None) return;

    auto* equip = entity->GetComponent<ComponentEquipment>();
    auto* inv = entity->GetComponent<ComponentInventory>();
    auto* weapon = entity->GetComponent<ComponentWeapon>();
    if (!equip || !inv) return;

    EquipmentSlot slot = def->equipmentSlot;

    auto* buff = entity->GetComponent<ComponentBuffDebuff>();
    auto* stats = entity->GetComponent<ComponentStats>();

    if (buff && stats) {
        std::string sourceUID = "EQUIP_SLOT_" + std::to_string(static_cast<int>(slot));
        buff->RemoveEffectBySource(sourceUID);
        stats->RemoveModifierGroup(sourceUID, true);
    }

    if (equip->IsEquipped(slot)) {
        UnequipSlot(entity, slot);
    }

    equip->Equip(slot, item.uid, item.itemId);

    for (auto& i : inv->GetItems()) {
        const ItemDefinition* iDef = ItemDatabase::Get().GetItem(i.itemId);
        if (!iDef) continue;

        if (i.uid == item.uid) {
            i.isEquipped = true;
        }
        else if (iDef->equipmentSlot == slot) {
            i.isEquipped = false;
        }
    }


    if (weapon && slot == EquipmentSlot::Weapon) {
        weapon->Equip(item.itemId);
    }

    if (def->type != ItemType::Weapon) {
        if (buff && stats) {
            std::string sourceUID = "EQUIP_SLOT_" + std::to_string(static_cast<int>(slot));
            buff->RemoveEffectBySource(sourceUID);
            stats->RemoveModifierGroup(sourceUID, true);
        }

        ApplyEquipmentEffects(entity);
    }

    std::cout << "[Equip] Equipé via UID : " << item.itemId << " (" << item.uid << ")\n";

    inv->RemoveItemByUID(item.uid);

}

void SystemEquipment::UnequipSlot(Entity* entity, EquipmentSlot slot) {
    auto* equip = entity->GetComponent<ComponentEquipment>();
    auto* inv = entity->GetComponent<ComponentInventory>();
    if (!equip || !inv || !equip->IsEquipped(slot)) return;

    std::string uid = equip->GetEquippedUID(slot);
    std::string itemId = equip->GetEquippedItemID(slot);

    RemoveEquipmentEffects(entity, slot);

    auto* weapon = entity->GetComponent<ComponentWeapon>();
    if (weapon) weapon->Unequip();

    equip->Unequip(slot);

    auto& items = inv->GetItems();
    auto it = std::find_if(items.begin(), items.end(), [&](ItemInstance& i) {
        return i.uid == uid;
        });

    if (it != items.end()) {
        it->isEquipped = false;
    }
    else {
        ItemInstance restored(itemId);
        restored.uid = uid;
        restored.isEquipped = false;
        inv->AddItem(restored);
    }

    std::cout << "[Equip] Désequipé UID : " << uid << " (slot " << static_cast<int>(slot) << ")\n";
}

void SystemEquipment::ApplyEquipmentEffects(Entity* entity) {
    auto* equip = entity->GetComponent<ComponentEquipment>();
    auto* stats = entity->GetComponent<ComponentStats>();
    auto* buff = entity->GetComponent<ComponentBuffDebuff>();
    if (!equip || !stats || !buff) return;

    for (const auto& [slot, _] : equip->GetAll()) {
        std::string sourceUID = "EQUIP_SLOT_" + std::to_string(static_cast<int>(slot));
        buff->RemoveEffectBySource(sourceUID);
        stats->RemoveModifierGroup(sourceUID, true);
    }

    for (const auto& [slot, pair] : equip->GetAll()) {
        const std::string& itemId = pair.second;
        const ItemDefinition* item = ItemDatabase::Get().GetItem(itemId);
        if (!item) continue;
        if (item->type == ItemType::Weapon) continue;

        // Effet principal
        if (!item->effectId.empty()) {
            const EffectDefinition* effect = EffectDatabase::Get().GetEffect(item->effectId);
            if (effect) {
                std::cout << "[ApplyEffects] Application de l'effet " << effect->id << " via item " << item->id
                    << " sur slot " << static_cast<int>(slot) << "\n";

                buff->AddEffect(effect, "EQUIP_SLOT_" + std::to_string(static_cast<int>(slot)), true);
                std::cout << "[Equipment] Effet principal appliqué : " << item->effectId << "\n";
            }
            else {
                std::cout << "[Equipment] Effet introuvable : " << item->effectId << "\n";
            }
        }

        // Effets multiples
        for (const std::string& eid : item->effects) {
            const EffectDefinition* effect = EffectDatabase::Get().GetEffect(eid);
            if (effect) {
                std::cout << "[ApplyEffects] Application de l'effet " << effect->id << " via item " << item->id
                    << " sur slot " << static_cast<int>(slot) << "\n";

                buff->AddEffect(effect, "EQUIP_SLOT_" + std::to_string(static_cast<int>(slot)), true);
                std::cout << "[Equipment] Effet secondaire appliqué : " << eid << "\n";
            }
            else {
                std::cout << "[Equipment] Effet secondaire introuvable : " << eid << "\n";
            }
        }
    }

    std::cout << "[Equipment] Tous les effets d’équipement ont été appliqués.\n";
}


void SystemEquipment::RemoveEquipmentEffects(Entity* entity, EquipmentSlot onlySlot) {
    auto* equip = entity->GetComponent<ComponentEquipment>();
    auto* stats = entity->GetComponent<ComponentStats>();
    auto* buff = entity->GetComponent<ComponentBuffDebuff>();
    if (!equip || !stats || !buff) return;

    auto it = equip->GetAll().find(onlySlot);
    if (it == equip->GetAll().end()) return;

    const std::string& itemId = it->second.second;
    const ItemDefinition* item = ItemDatabase::Get().GetItem(itemId);
    if (!item || item->type == ItemType::Weapon) return;

    std::string sourceUID = "EQUIP_SLOT_" + std::to_string(static_cast<int>(onlySlot));

    std::cout << "[RemoveEffects] Slot: " << static_cast<int>(onlySlot) << " | itemId: " << itemId << "\n";
    std::cout << "[RemoveEffects] Type d'objet : " << static_cast<int>(item->type) << "\n";

    buff->RemoveEffectBySource(sourceUID);
    stats->RemoveModifierGroup(sourceUID, true);
}



void SystemEquipment::Logs() {
    if (!debugMode || !logSystemWeapon) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int armedCount = 0;
    std::unordered_map<std::string, int> weaponUsageCount;

    for (Entity* entity : entities) {
        auto* weapon = entity->GetComponent<ComponentWeapon>();
        if (!weapon) continue;

        const std::string& weaponId = weapon->GetWeaponId();
        ++armedCount;
        ++weaponUsageCount[weaponId];
    }

    HEAD("sys_WEAPON") << "Entités avec arme équipée : " << armedCount << ENDL;

    for (const auto& [weaponId, count] : weaponUsageCount) {
        const auto* def = ItemDatabase::Get().GetItem(weaponId);
        std::string name = def ? def->name : "Inconnu";

        HEAD("sys_WEAPON") << "- " << (char*)name.c_str()
            << " (" << (char*)weaponId.c_str() << ") : "
            << count << " entité(s)" << ENDL;
    }
}
