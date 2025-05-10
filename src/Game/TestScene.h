#pragma once
#include "Scene.h"
class TestScene : public Scene
{
public:
	void OnInit() override;
	void OnEvent(const std::optional<sf::Event>& event) override;
	void OnUpdate() override;
};

