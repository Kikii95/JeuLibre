#include "pch.h"

ComponentCollider::ComponentCollider(Entity* entity)
    : Component(entity) {
}

void ComponentCollider::SetType(ColliderType t) {
    type = t;
}

ColliderType ComponentCollider::GetColliderType() const {
    return type;
}

bool ComponentCollider::IsColliding() const {
	return isCollinding;
}

void ComponentCollider::SetIsColliding(bool colliding) {
	isCollinding = colliding;
}
