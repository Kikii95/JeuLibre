#include "pch.h"
#include "OptionScene.h"

void OptionScene::OnInit()
{
	Entity* bouton = mpGameEngine->GetEntityManager().CreateEntity();
	bouton->AddComponent<ComponentTransform>(sf::Vector2f(400, 400), sf::Vector2f(NULL, NULL));
	bouton->AddComponent<ComponentRender>();
	bouton->AddComponent<ComponentFont>();
    ComponentFont* font = bouton->GetComponent<ComponentFont>();
    font->SetFontByName("testFont");
    font->SetText("Hello World", true);
    font->SetFillColor(sf::Color::Red);
    font->SetPosition(bouton->GetComponent<ComponentTransform>()->GetPosition());
}

void OptionScene::OnEvent(const std::optional<sf::Event>& event)
{
}

void OptionScene::OnUpdate()
{
}
