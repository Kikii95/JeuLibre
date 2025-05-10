#pragma once

class SystemDifficulty : public System {
public:
    SystemDifficulty();

    SystemType GetType() const override { return SystemType::Active; }

    void Update(float dt, const std::vector<Entity*>& entities) override;

    void ApplyToEntity(Entity* entity, float modifier);

    void SetCurrentTimeModifier(float modifier);
    float GetCurrentTimeModifier();

	void Logs() override;

private:
    float ComputeTimeModifier(float timeSeconds) const;

	float diffChangeTimer = 1.f; // 2 minutes
	float currentTimeModifier = 0.f;
};
