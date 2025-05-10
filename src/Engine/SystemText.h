#pragma once
#include "System.h"

class SystemText : public System {
public:
    void Update(float dt, const std::vector<Entity*>& entities) override;
	SystemType GetType() const override { return SystemType::UI; }

	void Logs() override;
};
