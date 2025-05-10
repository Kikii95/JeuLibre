#include "pch.h"

ComponentClickable::ComponentClickable(Entity* entity) : Component(entity) {}

void ComponentClickable::SetOnLeftClick(std::function<void()> callback) {
    onLeftClick = std::move(callback);
}

void ComponentClickable::SetOnRightClick(std::function<void()> callback) {
    onRightClick = std::move(callback);
}

void ComponentClickable::OnLeftClick() {
    if (onLeftClick) onLeftClick();
}

void ComponentClickable::OnRightClick() {
    if (onRightClick) onRightClick();
}
