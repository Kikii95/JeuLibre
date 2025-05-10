#pragma once

class SystemNavire : public System {
public:
    SystemNavire();

	SystemType GetType() const override { return SystemType::Active; }
    void Update(float dt, const std::vector<Entity*>& entities) override;

	void Logs() override;

private:
    float CalculateSpeedModifier(const ComponentNavire* navire) const;
};
