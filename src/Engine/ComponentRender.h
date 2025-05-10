#pragma once

enum class RenderType {
    Sprite,
    Shape,
    Hexagon,
    Circle,
};

class ComponentRender : public Component {
public:
    ComponentRender(Entity* entity);
    ~ComponentRender();

    void SetRenderType(RenderType type);
    RenderType GetRenderType() const;

    void SetColor(const sf::Color& c);
    const sf::Color& GetColor() const;

    void SetTexture(std::string path);
    bool HasTexture() const;

    sf::Sprite* GetSprite();
    sf::RectangleShape& GetShape();
    sf::CircleShape& GetCircleShape();
    sf::ConvexShape& GetHexagonShape();

    sf::Drawable* GetDrawable();
    void SetVisibility(bool visible);
    bool GetVisibility() const;

    void SetRenderLayer(int layer);
    int GetRenderLayer() const;

    void SetFixedOnScreen(bool value);
    bool IsFixedOnScreen() const;

private:
    RenderType renderType = RenderType::Shape;

    sf::Color color = sf::Color::White;
    sf::Sprite* sprite = nullptr;
    sf::Texture* texture = nullptr; //NO SURE
    std::string texturePath = "";

    sf::RectangleShape rectangleshape;
    sf::CircleShape circleShape;
    sf::ConvexShape hexagonShape;

    bool useTexture = false;
    bool visible = true;

	int renderLayer = 0; // 0 = background, 1 = player, 2 = enemy, 3 = UI, etc.
    bool fixedOnScreen = false;
};
