#include "pch.h"

void SystemText::Update(float dt, const std::vector<Entity*>& entities) {
    EntityManager& entityManager = GameEngine::GetInstance().GetEntityManager();

    Entity* player = nullptr;
    auto players = entityManager.GetEntitiesByTag("PLAYER");
    if (!players.empty()) {
        player = players[0];
    }

    for (Entity* entity : entities) {
        auto* font = entity->GetComponent<ComponentFont>();
        if (!font) continue;

        auto* tagComp = entity->GetComponent<ComponentTag>();
        std::string tag = tagComp ? tagComp->GetTag() : "";

        if (font->IsFixedOnScreen() && player) {
            if (tag == "UI_MONEY") {
                auto* money = player->GetComponent<ComponentMoney>();
                if (money) {
                    font->SetText("Money: " + std::to_string(money->GetBalance()), false);
                }
            }
            else if (tag == "UI_HP") {
                auto* hp = player->GetComponent<ComponentHealth>();
                if (hp) {
                    int currentHP = hp->GetHealth();
                    font->SetText("HP: " + std::to_string(currentHP), false);

                    if (currentHP < 30)      font->SetFillColor(sf::Color::Red);
                    else if (currentHP < 70) font->SetFillColor(sf::Color::Yellow);
                    else                     font->SetFillColor(sf::Color::Green);
                }
            }
        }


		if (tag == "PLAYER" || tag == "MERCHANT") {
			auto* stats = entity->GetComponent<ComponentStats>();
			if (stats) {
				std::string statId = stats->GetDefinitionId();
                if (font->GetText().getString() != statId)
                    font->SetText(statId, true);

			}
		}

        if (tag == "ENEMY") {
            auto* hp = entity->GetComponent<ComponentHealth>();
            auto* stats = entity->GetComponent<ComponentStats>();

            if (hp && stats) {
                std::string statId = stats->GetDefinitionId(); 
                std::string newText = statId + " HP: " + std::to_string(hp->GetHealth());
                if (font->GetText().getString() != newText)
                    font->SetText(newText, false);

            }
        }



        if (font->GetDeferredText().has_value()) {
            font->SetText(font->GetDeferredText().value(), font->IsAutoFitText());
            font->ClearDeferredText(); 
        }

    }
}

void SystemText::Logs() {
    if (!debugMode || !logSystemText) return;

    EntityManager& em = GameEngine::GetInstance().GetEntityManager();
    const auto& entities = em.GetAllEntities();

    int textCount = 0;
    int fixedCount = 0;

    for (Entity* e : entities) {
        auto* font = e->GetComponent<ComponentFont>();
        if (!font) continue;

        ++textCount;
        if (font->IsFixedOnScreen()) ++fixedCount;
    }

    HEAD("sys_TEXT") << "Textes affiches : " << (int)textCount
        << " | Textes UI fixes : " << (int)fixedCount << ENDL;

    for (Entity* e : entities) {
        auto* font = e->GetComponent<ComponentFont>();
        if (!font) continue;

        auto* tag = e->GetComponent<ComponentTag>();
        std::string tagName = tag ? tag->GetTag() : "none";

        HEAD("sys_TEXT") << "- Entity " << e->GetID()
            << " | Tag : " << (char*)tagName.c_str()
            << " | Fixe : " << (font->IsFixedOnScreen() ? "oui" : "non")
            << ENDL;
    }
}