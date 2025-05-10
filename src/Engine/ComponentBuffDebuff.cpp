#include "pch.h"

ComponentBuffDebuff::ComponentBuffDebuff(Entity* entity)
    : Component(entity) {
}

std::vector<EffectInstance>& ComponentBuffDebuff::GetActiveEffects() {
    return activeEffects;
}

void ComponentBuffDebuff::AddEffect(const EffectDefinition* def, const std::string& sourceUID, bool fromEquipment) {
    if (!def) return;

    RemoveEffectBySource(sourceUID);

    EffectInstance instance(def->id, sourceUID, fromEquipment, fromEquipment ? -1 : def->duration);
    instance.lastTickTime = GameEngine::GetInstance().GetTimer().TotalTime();
    activeEffects.push_back(instance);

    std::cout << "[BuffDebuff] Effet ajouté : " << def->id << " [" << sourceUID << "]\n";
}



void ComponentBuffDebuff::RemoveEffect(const std::string& effectId, bool onlyIfFromEquipment) {
    activeEffects.erase(
        std::remove_if(activeEffects.begin(), activeEffects.end(),
            [&](const EffectInstance& inst) {
                return inst.effectId == effectId && (!onlyIfFromEquipment || inst.fromEquip);
            }),
        activeEffects.end()
    );
}

void ComponentBuffDebuff::RemoveEffectBySource(const std::string& sourceUID) {
    activeEffects.erase(
        std::remove_if(activeEffects.begin(), activeEffects.end(),
            [&](const EffectInstance& inst) {
                return inst.sourceItemUID == sourceUID && inst.fromEquip;
            }),
        activeEffects.end()
    );
}

