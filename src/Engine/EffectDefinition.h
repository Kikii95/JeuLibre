#pragma once

#pragma once

enum class EffectType {
    None,
    DamageOverTime,
    HealOverTime,
    StatBoost,
    Cleanse,
    Custom
};

inline const char* ToString(EffectType type);

struct EffectDefinition {
    std::string id;
    std::string name;                 
    std::string description;          
    EffectType type = EffectType::None;  
    bool isBuff = false;              

    int duration = -1;               
    float tickInterval = 1.0f;

    int maxStacks = 1;                
    int tickDamage = 0;
    int tickHeal = 0;
    int healAmount = 0;

    std::unordered_map<std::string, int> statModifiers;

    std::vector<std::string> removeEffectTags;
    std::string tag;                  

    std::string icon;
    std::string animation;

    bool hidden = false;
    bool persistent = false;
};

inline const char* ToString(EffectType type) {
    switch (type) {
    case EffectType::DamageOverTime: return "DamageOverTime";
    case EffectType::HealOverTime:   return "HealOverTime";
    case EffectType::StatBoost:      return "StatBoost";
    case EffectType::Cleanse:        return "Cleanse";
    case EffectType::Custom:         return "Custom";
    default:                         return "None";
    }
}
