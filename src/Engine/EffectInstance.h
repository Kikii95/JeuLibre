#pragma once
#include <string>

struct EffectInstance {
    std::string effectId;       // ID de l'effet (ex: poison_small_v2)
    std::string sourceItemUID;  // UID de l’objet ayant applique l’effet
    bool fromEquip = false;     // vrai si ça vient d’un objet equipe
    int remainingTicks = -1;    // -1 = permanent
    bool applied = false;       // si les effets ont deja ete appliques
    float lastTickTime = 0.0f;  // pour gerer le timing entre les ticks

    EffectInstance() = default;

    EffectInstance(const std::string& id,
        const std::string& sourceUID,
        bool fromEquip,
        int durationTicks)
        : effectId(id),
        sourceItemUID(sourceUID),
        fromEquip(fromEquip),
        remainingTicks(durationTicks),
        applied(false),
        lastTickTime(0.0f) {
    }
};
