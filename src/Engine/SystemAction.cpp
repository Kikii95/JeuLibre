#include "pch.h"

SystemAction::SystemAction() {}

void SystemAction::ExecuteAction(Entity* actor, Entity* target, const ActionData* action) {
    if (!actor || !action) return;

    std::cout << "[Action] Execution action : " << action->id << "\n";

    Entity* recipient = (target != nullptr) ? target : actor;

    switch (action->actionType) {
    case ActionType::Use: {
        const EffectDefinition* effect = EffectDatabase::Get().GetEffect(action->effectId);
        if (effect) {
            auto* buff = recipient->GetComponent<ComponentBuffDebuff>();
            if (buff) {
                buff->AddEffect(effect, "SOURCE_DIRECT", false); 
                std::cout << "[Action] Effet applique : " << effect->id << " sur " << recipient->GetID() << "\n";
            }
        }

        if (action->consumeItem && !action->itemId.empty()) {
            auto* inv = actor->GetComponent<ComponentInventory>();
            if (inv) {
                inv->RemoveItem(action->itemId, 1);
                std::cout << "[Action] Objet consomme : " << action->itemId << "\n";
            }
        }
        break;
    }

    case ActionType::Gather:
        std::cout << "[Action] Recolte en cours...\n";
        break;

    case ActionType::Inspect:
        std::cout << "[Action] Debut du dialogue...\n";
        break;

    case ActionType::Interact: {
        if (!target) return;

        if (target->HasComponent<ComponentMerchant>()) {
            auto* invSys = GameEngine::GetInstance().GetSystem<SystemInventory>();
            auto* merchSys = GameEngine::GetInstance().GetSystem<SystemMerchant>();

            if (merchSys->IsMerchantVisible() && merchSys->GetCurrentMerchant() == target) {
                invSys->ClearInventoryDisplay();
                merchSys->ClearMerchantDisplay();
                invSys->SetInventoryIsVisible(false);
                merchSys->SetMerchantIsVisible(false);
                merchSys->SetCurrentMerchant(nullptr);
				GameEngine::GetInstance().GetTimer().Start();
                std::cout << "[Action] Fermeture du menu marchand\n";
                return;
            }

            invSys->ClearInventoryDisplay();
            merchSys->ClearMerchantDisplay();

            merchSys->SetCurrentMerchant(target);
            merchSys->SetMerchantIsVisible(true);
            invSys->SetInventoryIsVisible(true);

            GameEngine::GetInstance().GetTimer().Stop();

            invSys->DisplayInventory(actor);
            merchSys->DisplayMerchantStock(target);

            return;
        }


        else if (target->HasComponent<ComponentHealth>()) {
            GameEngine::GetInstance().GetSystem<SystemCombat>()->ExecuteAttack(actor, target);
        }
        break;
    }


    default:
        std::cout << "[Action] Type d’action inconnu ou non implemente.\n";
        break;
    }
}



void SystemAction::Logs() {
	if (!debugMode || !logSystemAction) return;
}

void SystemAction::UseItem(Entity* actor, const ItemInstance& instance) {
    const ItemDefinition* def = ItemDatabase::Get().GetItem(instance.itemId);
    if (!def) return;

    auto* equipSys = GameEngine::GetInstance().GetSystemManager().GetSystem<SystemEquipment>();
    if (!equipSys) return;

    if (def->type == ItemType::Weapon || def->type == ItemType::Armor || def->type == ItemType::Accessory) {
        if (instance.isEquipped) {
            equipSys->UnequipSlot(actor, def->equipmentSlot);
            std::cout << "[Action] Objet déjà équipé, on le déséquipe.\n";
        }
        else {
            std::cout << "[Action] Tentative d'équipement de l'objet : " << def->id << "\n";
            equipSys->EquipItemByInstance(actor, instance);
            std::cout << "[Action] Objet équipé : " << def->id << "\n";
        }
    }
    else if (!def->effectId.empty()) {
        ActionData action;
        action.id = "use_" + def->id;
        action.name = "Utiliser " + def->name;
        action.effectId = def->effectId;
        action.consumeItem = true;
        action.itemId = def->id;
        action.actionType = ActionType::Use;

        ExecuteAction(actor, nullptr, &action);
    }
}


