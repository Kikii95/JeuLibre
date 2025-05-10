#include "pch.h"

ComponentRender::ComponentRender(Entity* entity)
    : Component(entity), sprite(nullptr), renderType(RenderType::Shape) {
    rectangleshape.setFillColor(color);
}

ComponentRender::~ComponentRender() {
    if (sprite) delete sprite;
    if (texture) delete texture;
}

void ComponentRender::SetRenderType(RenderType type) {
    renderType = type;

    if (sprite) {
        delete sprite;
        sprite = nullptr;
    }

    switch (renderType) {
    case RenderType::Sprite:
        if (!texture) texture = new sf::Texture();
        if (!texturePath.empty() && texture->loadFromFile(texturePath)) {
            sprite = new sf::Sprite(*texture);
            useTexture = true;
        }
        else {
            std::cerr << "[WARNING] No valid texture loaded in SetRenderType.\n";
        }
        break;

    case RenderType::Shape:
        rectangleshape.setFillColor(color);
        useTexture = false;
        break;

    case RenderType::Circle:
        circleShape.setRadius(10.f);
        circleShape.setFillColor(color);
        useTexture = false;
        break;

    case RenderType::Hexagon:
        hexagonShape.setPointCount(6);
        for (int i = 0; i < 6; ++i) {
            float angle = i * 2 * 3.14159f / 6.f - 3.14159f / 2.f;
            hexagonShape.setPoint(i, sf::Vector2f(std::cos(angle) * 10.f, std::sin(angle) * 10.f));
        }
        hexagonShape.setFillColor(color);
        useTexture = false;
        break;
    }
}

RenderType ComponentRender::GetRenderType() const {
    return renderType;
}

void ComponentRender::SetColor(const sf::Color& c) {
    color = c;
    rectangleshape.setFillColor(c);
    circleShape.setFillColor(c);
    hexagonShape.setFillColor(c);
}

const sf::Color& ComponentRender::GetColor() const {
    return color;
}

void ComponentRender::SetTexture(std::string path) {
    texturePath = path;

    if (!texture) texture = new sf::Texture();
    if (!texture->loadFromFile(path)) {
        std::cerr << "[ERROR] Failed to load texture from: " << path << std::endl;
        return;
    }

    if (sprite) {
        delete sprite;
        sprite = nullptr;
    }

    sprite = new sf::Sprite(*texture);
    useTexture = true;
}

bool ComponentRender::HasTexture() const {
    return useTexture && texture != nullptr;
}

sf::Sprite* ComponentRender::GetSprite() {
    return sprite;
}

sf::RectangleShape& ComponentRender::GetShape() {
    return rectangleshape;
}

sf::CircleShape& ComponentRender::GetCircleShape() {
    return circleShape;
}

sf::ConvexShape& ComponentRender::GetHexagonShape() {
    return hexagonShape;
}

sf::Drawable* ComponentRender::GetDrawable() {
    switch (renderType) {
    case RenderType::Sprite: return sprite;
    case RenderType::Shape: return &rectangleshape;
    case RenderType::Circle: return &circleShape;
    case RenderType::Hexagon: return &hexagonShape;
    }
    return nullptr;
}

void ComponentRender::SetVisibility(bool v) {
    visible = v;
}

bool ComponentRender::GetVisibility() const {
    return visible;
}

void ComponentRender::SetRenderLayer(int layer) {
    renderLayer = layer;
}

int ComponentRender::GetRenderLayer() const {
    return renderLayer;
}

void ComponentRender::SetFixedOnScreen(bool value) {
    fixedOnScreen = value;
}

bool ComponentRender::IsFixedOnScreen() const {
    return fixedOnScreen;
}
