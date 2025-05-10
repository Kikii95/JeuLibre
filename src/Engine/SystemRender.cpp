#include "pch.h"

SystemRender::SystemRender() {}

void SystemRender::DrawWorld(sf::RenderWindow& window, const std::vector<Entity*>& entities) {
    std::vector<Entity*> sorted = entities;
    std::sort(sorted.begin(), sorted.end(), [](Entity* a, Entity* b) {
        auto* ra = a->GetComponent<ComponentRender>();
        auto* rb = b->GetComponent<ComponentRender>();
        if (!ra || !rb) return false;
        return ra->GetRenderLayer() < rb->GetRenderLayer();
        });

    for (Entity* entity : sorted) {
        auto* transform = entity->GetComponent<ComponentTransform>();
        auto* render = entity->GetComponent<ComponentRender>();
        auto* font = entity->GetComponent<ComponentFont>();

        if (!transform || !render || !render->GetVisibility() || render->IsFixedOnScreen()) continue;

        sf::Vector2f pos = transform->GetPosition();
        sf::Vector2f size = transform->GetSize();

        // === RenderType::Shape =================================================
        if (render->GetRenderType() == RenderType::Shape) {
            auto& shape = render->GetShape();
            shape.setSize(size);
            shape.setPosition(pos);
            shape.setFillColor(render->GetColor());
            window.draw(shape);
        }
        // === RenderType::Hexagon ==============================================
        else if (render->GetRenderType() == RenderType::Hexagon) {
            auto& hexagon = render->GetHexagonShape();
            float radius = size.x / 2.f;
            hexagon.setPointCount(6);
            for (int i = 0; i < 6; ++i) {
                float angle = i * 2 * 3.14159f / 6.f - 3.14159f / 2.f;
                hexagon.setPoint(i, sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius));
            }
            hexagon.setPosition(pos);
            hexagon.setFillColor(sf::Color::Transparent);
            hexagon.setOutlineThickness(2.f);
            window.draw(hexagon);
        }
        // === Drawable auto (fallback pour sprites / shapes divers) ============
        else if (sf::Drawable* drawable = render->GetDrawable()) {
            if (auto* sprite = dynamic_cast<sf::Sprite*>(drawable)) {
                const sf::Texture* tex = &sprite->getTexture();
                if (tex && tex->getSize().x > 0 && tex->getSize().y > 0) {
                    sf::Vector2f scale(
                        size.x / static_cast<float>(tex->getSize().x),
                        size.y / static_cast<float>(tex->getSize().y)
                    );
                    sprite->setScale(scale);
                }
                sprite->setPosition(pos);
            }
            else if (auto* rect = dynamic_cast<sf::RectangleShape*>(drawable)) {
                rect->setSize(size);
                rect->setPosition(pos);
                rect->setFillColor(render->GetColor());
            }
            else if (auto* circle = dynamic_cast<sf::CircleShape*>(drawable)) {
                circle->setRadius(size.x / 2);
                circle->setOrigin({ size.x / 2, size.x / 2 });
                circle->setPosition(pos);
                circle->setFillColor(render->GetColor());
            }
            else if (auto* hex = dynamic_cast<sf::ConvexShape*>(drawable)) {
                float radius = size.x / 2;
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159f / 6.f - 3.14159f / 2.f;
                    hex->setPoint(i, sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius));
                }
                hex->setPosition(pos);
                hex->setFillColor(render->GetColor());
            }

            window.draw(*drawable);
        }

        // === Font ============================================================
        if (font && !font->IsFixedOnScreen()) {
            sf::Vector2f fontPos = pos;
            if (font->IsOffsetManually()) {
                fontPos += font->GetManualOffset();
            }
            font->SetPosition(fontPos);
            window.draw(font->GetText());
        }
    }
}


void SystemRender::DrawMap(sf::RenderWindow& window, const std::vector<Entity*>& entities) {
    for (Entity* entity : entities) {
        auto* transform = entity->GetComponent<ComponentTransform>();
        auto* render = entity->GetComponent<ComponentRender>();
        auto* font = entity->GetComponent<ComponentFont>();

        if (!transform || !render || !render->GetVisibility() || render->IsFixedOnScreen()) continue;

        sf::Drawable* drawable = render->GetDrawable();
        if (drawable) {
            sf::Vector2f pos = transform->GetPosition();
            sf::Vector2f size = transform->GetSize();

            if (auto* sprite = dynamic_cast<sf::Sprite*>(drawable)) {
                const sf::Texture* tex = &sprite->getTexture();
                if (tex && tex->getSize().x > 0 && tex->getSize().y > 0) {
                    sf::Vector2f scale(
                        size.x / static_cast<float>(tex->getSize().x),
                        size.y / static_cast<float>(tex->getSize().y)
                    );
                    sprite->setScale(scale);
                }
                sprite->setPosition(pos);
            }
            else if (auto* rect = dynamic_cast<sf::RectangleShape*>(drawable)) {
                rect->setSize(size);
                rect->setPosition(pos);
                rect->setFillColor(render->GetColor());
            }
            else if (auto* circle = dynamic_cast<sf::CircleShape*>(drawable)) {
                circle->setRadius(size.x / 2);
                circle->setOrigin({size.x / 2, size.y / 2});
                circle->setPosition(pos);
                circle->setFillColor(render->GetColor());
            }
            else if (auto* hex = dynamic_cast<sf::ConvexShape*>(drawable)) {
                float radius = size.x / 2;
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159f / 6.f - 3.14159f / 2.f;
                    hex->setPoint(i, sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius));
                }
                hex->setPosition(pos);
                hex->setFillColor(render->GetColor());
            }

            window.draw(*drawable);
        }
    }
}
void SystemRender::DrawUI(sf::RenderWindow& window, const std::vector<Entity*>& entities) {
    for (Entity* entity : entities) {
        auto* transform = entity->GetComponent<ComponentTransform>();
        auto* render = entity->GetComponent<ComponentRender>();
        auto* font = entity->GetComponent<ComponentFont>();

        if (render && render->GetVisibility() && render->IsFixedOnScreen() && transform) {
            sf::Drawable* drawable = render->GetDrawable();
            sf::Vector2f pos = transform->GetPosition();
            sf::Vector2f size = transform->GetSize();

            if (auto* sprite = dynamic_cast<sf::Sprite*>(drawable)) {
                const sf::Texture* tex = &sprite->getTexture();
                if (tex && tex->getSize().x > 0 && tex->getSize().y > 0) {
                    sf::Vector2f scale(
                        size.x / static_cast<float>(tex->getSize().x),
                        size.y / static_cast<float>(tex->getSize().y)
                    );
                    sprite->setScale(scale);
                }
                sprite->setPosition(pos);
                window.draw(*sprite);
            }
            else if (auto* rect = dynamic_cast<sf::RectangleShape*>(drawable)) {
                rect->setSize(size);
                rect->setPosition(pos);
                rect->setFillColor(render->GetColor());
                window.draw(*rect);
            }
            else if (auto* circle = dynamic_cast<sf::CircleShape*>(drawable)) {
                circle->setRadius(size.x / 2);
                circle->setOrigin({ size.x / 2, size.x / 2 });
                circle->setPosition(pos);
                circle->setFillColor(render->GetColor());
                window.draw(*circle);
            }
            else if (auto* hex = dynamic_cast<sf::ConvexShape*>(drawable)) {
                float radius = size.x / 2;
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159f / 6.f - 3.14159f / 2.f;
                    hex->setPoint(i, sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius));
                }
                hex->setPosition(pos);
                hex->setFillColor(render->GetColor());
                window.draw(*hex);
            }
        }

        if (font && transform && font->IsFixedOnScreen()) {
            font->SetPosition(transform->GetPosition());
            window.draw(font->GetText());
        }
    }
}

void SystemRender::Update(float dt, const std::vector<Entity*>& entities) {
    sf::RenderWindow& window = GameEngine::GetInstance().GetWindow();

    window.setView(window.getView());
    DrawMap(window, GameEngine::GetInstance().GetEntityManager().GetAllMapEntities());
    DrawWorld(window, entities);

    window.setView(window.getDefaultView());
    DrawUI(window, entities);
}

void SystemRender::Logs() {
    if (!debugMode || !logSystemRender) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int total = 0;
    int sprites = 0;
    int shapes = 0;
    int texts = 0;
    int fixedTexts = 0;

    for (Entity* e : entities) {
        auto* render = e->GetComponent<ComponentRender>();
        auto* font = e->GetComponent<ComponentFont>();

        if (render) {
            ++total;
            if (render->HasTexture()) ++sprites;
            else ++shapes;
        }

        if (font) {
            ++texts;
            if (font->IsFixedOnScreen()) ++fixedTexts;
        }
    }

    HEAD("sys_RENDER") << "Entites rendues : " << (int)total
        << " | Sprites : " << (int)sprites
        << " | Shapes : " << (int)shapes << ENDL;

    HEAD("sys_RENDER") << "Textes : " << (int)texts
        << " | UI fixes : " << (int)fixedTexts
        << " | Dynamiques : " << (int)(texts - fixedTexts) << ENDL;
}
