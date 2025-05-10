#pragma once

enum class ColliderType {
    Solid,
    Mob,
    Object,
    Gatherable,
    Island
};

class ComponentCollider : public Component {
public:
    ComponentCollider(Entity* entity);

    void SetType(ColliderType type);
    ColliderType GetColliderType() const;

    bool IsColliding() const;
    void SetIsColliding(bool colliding);

private:
    ColliderType type = ColliderType::Solid;
	bool isCollinding = true;
};
