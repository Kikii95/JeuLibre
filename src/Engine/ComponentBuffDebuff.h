#include "EffectInstance.h"

class ComponentBuffDebuff : public Component {
public:
    ComponentBuffDebuff(Entity* entity);


    std::vector<EffectInstance>& GetActiveEffects();
    void AddEffect(const EffectDefinition* def, const std::string& sourceUID, bool fromEquipment);
    void RemoveEffect(const std::string& effectId, bool onlyIfFromEquipment);
    void RemoveEffectBySource(const std::string& sourceUID);

private:
    std::vector<EffectInstance> activeEffects;
};
