#pragma once

class SystemAction : public System {
public:
    SystemAction();

    SystemType GetType() const override { return SystemType::Reactive; }

    void Update(float dt, const std::vector<Entity*>& entities) override {}

	void ExecuteAction(Entity* actor, Entity* target, const ActionData* action);
	void UseItem(Entity* actor, const ItemInstance& instance);

	void Logs() override;
};
