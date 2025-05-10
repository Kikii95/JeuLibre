#pragma once
#include "ComponentFont.h"

class ToolBoxVisual : public ToolBox {
public:
	static ToolBoxVisual& GetInstance();

    static void ApplyVisualConfig(Entity* entity);
    static void ApplyUIStyle(Entity* entity, const std::string& text, const sf::Vector2f& pos, const sf::Color& color = sf::Color::Red);

    bool IsOutsideView(const sf::Vector2f& pos, float margin = 0.f);
    void CenterTextAbove(Entity* target, ComponentFont* font, float padding, float textSize);
	void CenterText(Entity* target, ComponentFont* font, float padding);

    float GetTextWidth(ComponentFont* font);
    float GetTextHeight(ComponentFont* font);

};
