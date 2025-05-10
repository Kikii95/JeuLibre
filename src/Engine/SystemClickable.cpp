#include "pch.h"
#include "SystemClickable.h"

SystemClickable::SystemClickable()
{
}

SystemClickable::~SystemClickable()
{
}

void SystemClickable::Update(float dt, const std::vector<Entity*>& entities)
{
    sf::RenderWindow& window = GameEngine::GetInstance().GetWindow();
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    bool paused = GameEngine::GetInstance().GetTimer().IsPaused();

    sf::Vector2f mousePos = paused
        ? sf::Vector2f(static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y))
        : window.mapPixelToCoords(pixelPos);

    auto& em = GameEngine::GetInstance().GetEntityManager();
    bool anyHoverDetected = false;

    for (const auto& entity : entities)
    {
        auto* clickable = entity->GetComponent<ComponentClickable>();
        auto* transform = entity->GetComponent<ComponentTransform>();
        auto* tag = entity->GetComponent<ComponentTag>();

        if (!clickable || !transform || !tag) continue;

        sf::Vector2f entityPos = transform->GetPosition();
        sf::Vector2f entitySize = transform->GetSize();
        std::string tagName = tag->GetTag();

        bool hovered = false;

        if (tagName == "HEXAGON") {
            // On utilise la taille de l�hexagone comme diam�tre (approx) et on teste un rayon circulaire
            sf::Vector2f center = entityPos;
            float radius = std::min(entitySize.x, entitySize.y) * 0.5f;

            float dx = mousePos.x - center.x;
            float dy = mousePos.y - center.y;
            hovered = (dx * dx + dy * dy <= radius * radius);
        }
        else {
            hovered = mousePos.x >= entityPos.x && mousePos.x <= entityPos.x + entitySize.x &&
                mousePos.y >= entityPos.y && mousePos.y <= entityPos.y + entitySize.y;
        }

        if (!hovered) continue;

        anyHoverDetected = true;

		//std::cout << "[SystemClickable] Hover detected on entity: " << entity->GetID() << std::endl;


        if (tagName == "INVENTORY_ITEM" || tagName == "MERCHANT_ITEM" || tagName == "DROPPED_ITEM") {
            auto* itemComp = entity->GetComponent<ComponentItem>();
            if (!itemComp) continue;

            const ItemInstance& instance = itemComp->instance;
            const ItemDefinition* def = ItemDatabase::Get().GetItem(instance.itemId);
            if (!def) continue;

            for (Entity* e : em.GetEntitiesByTag("INVENTORY_HOVER_TMP")) {
                em.DestroyEntity(e);
            }

            CreateInventoryHover(def, tagName);
        }

        if (leftClickDetected) clickable->OnLeftClick();
        if (rightClickDetected) clickable->OnRightClick();
    }

    if (!anyHoverDetected) {
        for (Entity* e : em.GetEntitiesByTag("INVENTORY_HOVER_TMP")) {
            em.DestroyEntity(e);
        }
    }

    leftClickDetected = false;
    rightClickDetected = false;
}







sf::Vector2f SystemClickable::GetMousePosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameEngine::GetInstance().GetWindow());
    return sf::Vector2f(mousePos);
}

void SystemClickable::SetLeftClickDetected(bool detected)
{
    leftClickDetected = detected;
}

bool SystemClickable::IsLeftClickDetected() const
{
    return leftClickDetected;
}

void SystemClickable::SetRightClickDetected(bool detected)
{
    rightClickDetected = detected;
}

bool SystemClickable::IsRightClickDetected() const
{
    return rightClickDetected;
}

void SystemClickable::ClearRightClickCallbacksForTag(const std::string& tag)
{
    auto& em = GameEngine::GetInstance().GetEntityManager();
    for (Entity* e : em.GetEntitiesByTag(tag)) {
        auto* clickable = e->GetComponent<ComponentClickable>();
        if (clickable) {
            clickable->SetOnRightClick([]() {
                });
        }
    }
}

void SystemClickable::ClearLeftClickCallbacksForTag(const std::string& tag)
{
	auto& em = GameEngine::GetInstance().GetEntityManager();
	for (Entity* e : em.GetEntitiesByTag(tag)) {
		auto* clickable = e->GetComponent<ComponentClickable>();
		if (clickable) {
			clickable->SetOnLeftClick([]() {
				});
		}
	}
}

Entity* SystemClickable::CreateInventoryHover(const ItemDefinition* def, const std::string& tagName)
{
    if (!def) return nullptr;
    ClearInventoryHover();

    std::stringstream ss;
    ss << def->name;

    if (!def->description.empty())
        ss << "\n" << def->description;

    if (def->weight > 0.f)
        ss << "\nPoids : " << std::fixed << std::setprecision(1) << def->weight << " kg";

    if (def->damage > 0)
        ss << "\nD�g�ts : " << def->damage;

    if (!def->effectId.empty())
        ss << "\nEffet : " << def->effectId;

    std::string content = ss.str();

    size_t numLines = std::count(content.begin(), content.end(), '\n') + 1;
     float lineHeight = 37.5f;
    sf::Vector2f hoverSize(750.f, numLines * lineHeight);

    sf::Vector2f winSize = GameEngine::GetInstance().GetWindowSize();
    sf::Vector2f hoverPos;

    if (tagName == "INVENTORY_ITEM") {
        hoverPos = sf::Vector2f(50.f, winSize.y - hoverSize.y - 20.f);
    }
    else if (tagName == "MERCHANT_ITEM") {
        hoverPos = sf::Vector2f(winSize.x - hoverSize.x - 50.f, winSize.y - hoverSize.y - 20.f);
	}
	else if (tagName == "DROPPED_ITEM") {
        hoverSize = { hoverSize.x / 2 , hoverSize.y / 1.5f };
        hoverPos = sf::Vector2f((winSize.x - hoverSize.x) / 2, 20.f);
	}
	else {
		return nullptr;
	}

    Entity* hover = GameEngine::GetInstance().GetEntityManager().CreateEntity();
    hover->AddComponent<ComponentTransform>(hoverPos, hoverSize);
    hover->AddComponent<ComponentRender>();
    hover->AddComponent<ComponentFont>();
    hover->AddComponent<ComponentTag>("INVENTORY_HOVER_TMP");

    hover->GetComponent<ComponentRender>()->SetRenderType(RenderType::Shape);
    hover->GetComponent<ComponentRender>()->SetRenderLayer(4);
    hover->GetComponent<ComponentRender>()->SetFixedOnScreen(true);
    hover->GetComponent<ComponentRender>()->SetColor(sf::Color(30, 30, 30, 200));

    auto* font = hover->GetComponent<ComponentFont>();
    font->SetFontByName("testFont");
    font->SetText(content, false);
    font->SetFillColor(sf::Color::White);
    font->SetFixedOnScreen(true);
    if (tagName == "DROPPED_ITEM") {
        font->SetCharacterSize(20);
    }

    return hover;

}


void SystemClickable::ClearInventoryHover() {
	for (Entity* e : GameEngine::GetInstance().GetEntityManager().GetEntitiesByTag("INVENTORY_HOVER_TMP")) {
		GameEngine::GetInstance().GetEntityManager().DestroyEntity(e);
	}
}






void SystemClickable::Logs()
{

}