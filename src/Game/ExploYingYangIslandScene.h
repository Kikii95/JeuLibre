#pragma once

#include "Scene.h"
#include "SceneInitializer.h"

class ExploYingYangIslandScene : public Scene
{
public:
	void OnInit() override;
	void OnEvent(const std::optional<sf::Event>& event) override;
	void OnUpdate() override;
	void OnExit() override;

};

