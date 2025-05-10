#pragma once
#include "Scene.h"

class OptionScene : public Scene
{
private :
	sf::Font* mfont;
public:
	void OnInit() override;
	void OnEvent(const std::optional<sf::Event>& event) override;
	void OnUpdate() override;
};

