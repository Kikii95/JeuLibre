#pragma once

class ComponentDecay : public Component {
public:
    ComponentDecay(Entity* entity, float lifetimeSeconds);

    void Update(float dt);
    bool IsExpired() const;
    float GetRemaining() const;
private:
    float lifetime;
    float elapsed;
};
