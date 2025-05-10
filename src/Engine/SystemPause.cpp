#include "pch.h"
#include "SystemPause.h"

SystemPause::SystemPause()
{
}

void SystemPause::Update(float dt, const std::vector<Entity*>& entities)
{

}

void SystemPause::DisplayPauseMenu(Entity* entity) {
	GameEngine::GetInstance().GetTimer().Stop();

	// === RESUME ===
	Entity* ResumeBouton = GameEngine::GetInstance().GetEntityManager().CreateEntity();
	ResumeBouton->AddComponent<ComponentTransform>(sf::Vector2f(50, 100), sf::Vector2f(200, 50));
	ResumeBouton->AddComponent<ComponentFont>();
	ResumeBouton->AddComponent<ComponentTag>("PAUSEMENU_UI");
	ResumeBouton->AddComponent<ComponentClickable>();

	ResumeBouton->GetComponent<ComponentClickable>()->SetOnLeftClick([this, entity]() {
		SetPauseMenuVisible(false);
		ClearPauseMenu();
		GameEngine::GetInstance().GetTimer().Start();
		});

	auto* font = ResumeBouton->GetComponent<ComponentFont>();
	font->SetFontByName("testFont");
	font->SetText("Resume", false); 
	font->SetFillColor(sf::Color::White);
	font->SetFixedOnScreen(true);

	Entity* OptionBouton = GameEngine::GetInstance().GetEntityManager().CreateEntity();
	OptionBouton->AddComponent<ComponentTransform>(sf::Vector2f(50, 200), sf::Vector2f(200, 50));
	OptionBouton->AddComponent<ComponentFont>();
	OptionBouton->AddComponent<ComponentTag>("PAUSEMENU_UI");
	OptionBouton->AddComponent<ComponentClickable>();
	auto* optionFont = OptionBouton->GetComponent<ComponentFont>();
	optionFont->SetFontByName("testFont");
	optionFont->SetText("Option", false);
	optionFont->SetFillColor(sf::Color::White);
	optionFont->SetFixedOnScreen(true);

	Entity* QuitBouton = GameEngine::GetInstance().GetEntityManager().CreateEntity();
	QuitBouton->AddComponent<ComponentTransform>(sf::Vector2f(50, 300), sf::Vector2f(200, 50));
	QuitBouton->AddComponent<ComponentFont>();
	QuitBouton->AddComponent<ComponentTag>("PAUSEMENU_UI");
	QuitBouton->AddComponent<ComponentClickable>();

	QuitBouton->GetComponent<ComponentClickable>()->SetOnLeftClick([this, entity]() {
		SetPauseMenuVisible(false);
		ClearPauseMenu();
		GameEngine::GetInstance().CloseGame();
		});

	auto* quitFont = QuitBouton->GetComponent<ComponentFont>();
	quitFont->SetFontByName("testFont");
	quitFont->SetText("Quit", false);
	quitFont->SetFillColor(sf::Color::White);
	quitFont->SetFixedOnScreen(true);
}


void SystemPause::ClearPauseMenu()
{
	GameEngine::GetInstance().GetTimer().Start();
	auto& em = GameEngine::GetInstance().GetEntityManager();
	auto invEntities = em.GetEntitiesByTag("PAUSEMENU_UI");
	for (Entity* e : invEntities) {
		em.DestroyEntity(e);
	}
}

bool SystemPause::IsPauseMenuVisible() const
{
	return pauseMenuVisible;
}

void SystemPause::SetPauseMenuVisible(bool visible)
{
	pauseMenuVisible = visible;
}

void SystemPause::Logs()
{
}
