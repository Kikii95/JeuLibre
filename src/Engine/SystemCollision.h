#pragma once

class SystemCollision : public System {
public:
    SystemCollision();

    SystemType GetType() const override { return SystemType::Active; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

    // Temporaire : bascule manuelle entre exploration et combat
    void SetExplorationMode(bool active);

    Entity* GetLastMobCollision(Entity* actor);
    Entity* GetCurrentMobCollision(Entity* actor);

	void Logs() override;

private:
    bool explorationMode = true;
    void ResolveCollision(Entity* a, Entity* b);

    std::unordered_map<Entity*, Entity*> lastMobCollisions;
    std::vector<std::pair<Entity*, Entity*>> mobCollisionPairs;

};
