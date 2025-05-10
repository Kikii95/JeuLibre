#pragma once
#include "EntityManager.h"

class GameEngine;

class Scene
{
private:
public:
	GameEngine* mpGameEngine;

	Scene() = default;

	void SetGameEngine(GameEngine* pGameEngine) { mpGameEngine = pGameEngine; }
	virtual void OnInit() = 0;
	virtual void OnEvent (const std::optional<sf::Event>& event ) = 0;
	virtual void OnUpdate () = 0;
	virtual void OnExit() = 0;



};

