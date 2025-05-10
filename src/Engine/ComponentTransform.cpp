#include "pch.h"

ComponentTransform::ComponentTransform(Entity* entity, sf::Vector2f startPos, sf::Vector2f sz)
    : Component(entity), position(startPos), size(sz) {
}

void ComponentTransform::SetPosition(const sf::Vector2f& pos) {
    SavePreviousPosition();
    position = pos;
}

sf::Vector2f ComponentTransform::GetPosition() const {
    return position;
}

void ComponentTransform::SavePreviousPosition() {
    previousPosition = position;
}

sf::Vector2f ComponentTransform::GetPreviousPosition() const {
    return previousPosition;
}

void ComponentTransform::SetSize(const sf::Vector2f& sz) {
	size = sz;
}

sf::Vector2f ComponentTransform::GetSize() const {
	return size;
}

void ComponentTransform::SetRotation(float angle) {
    rotation = angle;
}

float ComponentTransform::GetRotation() const {
    return rotation;
}

void ComponentTransform::MoveBy(const sf::Vector2f& delta) {
    SavePreviousPosition();
    position += delta;
}

void ComponentTransform::Rotate(float angle) {
    rotation += angle;
}
