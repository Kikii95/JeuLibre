#include "pch.h"

ToolBoxVisual& ToolBoxVisual::GetInstance() {
	static ToolBoxVisual instance;
	return instance;
}

void ToolBoxVisual::ApplyVisualConfig(Entity* entity) {
    auto* render = entity->GetComponent<ComponentRender>();
    auto* collider = entity->GetComponent<ComponentCollider>();
    auto* font = entity->GetComponent<ComponentFont>();
    auto* health = entity->GetComponent<ComponentHealth>();
    auto* stats = entity->GetComponent<ComponentStats>();
    auto* tag = entity->GetComponent<ComponentTag>();

    if (render && collider) {
        render->SetRenderLayer(1);
        collider->SetType(ColliderType::Mob);
    }

    if (health && stats) {
        std::string id = stats->GetDefinitionId();
		if (tag->GetTag() == "PLAYER") {
            font->SetDeferredText(id);			
        }
        else {
            font->SetDeferredText(id + " HP: " + std::to_string(health->GetHealth()));
        }
    }

    if (font) {
        font->SetFontByName("testFont");
        font->SetFillColor(sf::Color::Red);
    }
}

void ToolBoxVisual::ApplyUIStyle(Entity* entity, const std::string& text, const sf::Vector2f& pos, const sf::Color& color) {
    auto* transform = entity->GetComponent<ComponentTransform>();
    auto* font = entity->GetComponent<ComponentFont>();

    if (!transform) {
        transform = entity->AddComponent<ComponentTransform>(pos, sf::Vector2f());
    } else {
        transform->SetPosition(pos);
    }

    if (!font) font = entity->AddComponent<ComponentFont>();

    if (font) {
        font->SetFontByName("testFont");
        font->SetText(text, true);
        font->SetFillColor(color);
        font->SetFixedOnScreen(true);
    }
}

bool ToolBoxVisual::IsOutsideView(const sf::Vector2f& pos, float margin) {
    sf::View view = GameEngine::GetInstance().GetWindow().getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float left = center.x - size.x / 2.f - margin;
    float right = center.x + size.x / 2.f + margin;
    float top = center.y - size.y / 2.f - margin;
    float bottom = center.y + size.y / 2.f + margin;

    return (pos.x < left || pos.x > right || pos.y < top || pos.y > bottom);
}

void ToolBoxVisual::CenterTextAbove(Entity* target, ComponentFont* font, float textSize, float padding) {
    if (!target || !font) return;

    auto* transform = target->GetComponent<ComponentTransform>();
    if (!transform) return;

    font->SetCharacterSize(static_cast<unsigned int>(textSize));

    float textWidth = GetTextWidth(font);
    float textHeight = GetTextHeight(font);

    sf::Vector2f offset;

    if (textWidth > 0.f && textHeight > 0.f) {
        offset.x = -textWidth / 2.f;
        offset.y = -(transform->GetSize().y / 2.f + textHeight + padding);
    }
    else {
        sf::Vector2f objectSize = transform->GetSize();
        offset.x = -objectSize.x / 2.f;
        offset.y = -(objectSize.y / 3.f + textSize / 2.f + padding);
    }

    font->SetManualOffset(offset);
}

void ToolBoxVisual::CenterText(Entity* target, ComponentFont* font, float textSize) {
    if (!target || !font) return;

    auto* transform = target->GetComponent<ComponentTransform>();
    if (!transform) return;

    font->SetCharacterSize(static_cast<unsigned int>(textSize));

    float textWidth = GetTextWidth(font);
    float textHeight = GetTextHeight(font);

    sf::Vector2f offset;

    if (textWidth > 0.f && textHeight > 0.f) {
        offset.x = -textWidth / 2.f;
        offset.y = -textHeight / 2.f;
    }
    else {
        sf::Vector2f objectSize = transform->GetSize();
        offset.x = -objectSize.x / 2.f;
        offset.y = (objectSize.y / 2.f) - (textSize / 1.5f);
    }

    font->SetManualOffset(offset);
}

float ToolBoxVisual::GetTextWidth(ComponentFont* font) {
    if (!font) return 0.f;
	return font->GetText().getLocalBounds().size.x;
}

float ToolBoxVisual::GetTextHeight(ComponentFont* font) {
    if (!font) return 0.f;
    return font->GetText().getLocalBounds().size.y;
}
