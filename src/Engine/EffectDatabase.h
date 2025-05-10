#pragma once
#include "EffectDefinition.h"
class EffectDatabase {
public:
    static EffectDatabase& Get();

    bool LoadFromFile(const std::string& file);
    const EffectDefinition* GetEffect(const std::string& id) const;

private:
    std::unordered_map<std::string, EffectDefinition> effects;
};
