#include "pch.h"

ComponentCamera::ComponentCamera(Entity* entity)
    : Component(entity) {
    view.setSize(GameEngine::GetInstance().GetWindowSize());
    view.setCenter(sf::Vector2f(0, 0));
}

void ComponentCamera::SetPosition(const sf::Vector2f& position) {
    view.setCenter(position);
}

sf::Vector2f ComponentCamera::GetPosition() const {
    return view.getCenter();
}

void ComponentCamera::SetZoom(float factor) {
    view.zoom(factor);
}

float ComponentCamera::GetZoom() const {
    return view.getSize().x / GameEngine::GetInstance().GetWindowSize().x;
}

sf::View& ComponentCamera::GetView() {
    return view;
}
