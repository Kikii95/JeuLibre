#pragma once

class ComponentHealth : public Component {
private:
    int health = 1;
    int maxHealth = 1000;
    int damage;

public:
    ComponentHealth(Entity* entity);

    void SetHealth(int hp);
    int GetHealth() const;

    void SetMaxHealth(int hp);
    int GetMaxHealth() const;
};
