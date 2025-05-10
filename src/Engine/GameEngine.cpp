#include "pch.h"

GameEngine& GameEngine::GetInstance() {
    static GameEngine instance;
    return instance;
}

EntityManager& GameEngine::GetEntityManager() {
    return entityManager;
}

SystemManager& GameEngine::GetSystemManager() {
    return systemManager;
}

sf::RenderWindow& GameEngine::GetWindow() {
    return window;
}

GameTimer& GameEngine::GetTimer() {
    return gameTimer;
}

void GameEngine::Init() {
    sf::Vector2u screenSize(static_cast<unsigned int>(windowSize.x), static_cast<unsigned int>(windowSize.y));
    sf::VideoMode mode(screenSize);  

    window.create(mode, "SFML Game Engine");



    systemManager.AddSystem<SystemRender>();
    systemManager.AddSystem<SystemCamera>();
	systemManager.AddSystem<SystemInput>();
	systemManager.AddSystem<SystemText>();

	systemManager.AddSystem<SystemClickable>();
    systemManager.AddSystem<SystemPhysics>();
	systemManager.AddSystem<SystemCollision>();


    systemManager.AddSystem<SystemAI>();
    systemManager.AddSystem<SystemEvent>();
    systemManager.AddSystem<SystemAction>();


    systemManager.AddSystem<SystemNavire>();
    systemManager.AddSystem<SystemDifficulty>();

    systemManager.AddSystem<SystemFaction>();
    systemManager.AddSystem<SystemCrewManagement>();
    systemManager.AddSystem<SystemReputation>();

	systemManager.AddSystem<SystemItem>();
    systemManager.AddSystem<SystemLoot>();
    systemManager.AddSystem<SystemMerchant>();
    systemManager.AddSystem<SystemMoney>();
    systemManager.AddSystem<SystemInventory>();

	systemManager.AddSystem<SystemEquipment>();
	systemManager.AddSystem<SystemProjectile>();
	systemManager.AddSystem<SystemHealth>();
	systemManager.AddSystem<SystemBuffDebuff>();

    systemManager.AddSystem<SystemDialogue>();
    systemManager.AddSystem<SystemQuest>();
    systemManager.AddSystem<SystemFogOfWar>();

	systemManager.AddSystem<SystemDifficulty>();
	systemManager.AddSystem<SystemSpawner>();
    systemManager.AddSystem<SystemStats>();
	systemManager.AddSystem<SystemCombat>();
	systemManager.AddSystem<SystemState>();
    systemManager.AddSystem<SystemTurnOrder>();

    systemManager.AddSystem<SystemPause>();
	systemManager.AddSystem<SystemWarmup>();


}


void GameEngine::Run() {
    GameLoop();
}

void GameEngine::GameLoop() {
    while (window.isOpen()) {
        Logs::Get()->Init();

        ApplySceneChangeIfNeeded();

        ProcessEvents();      
        Input::Update();

        gameTimer.Tick();
        float dt = gameTimer.DeltaTime();

        systemManager.Update(dt);

        window.clear(sf::Color::Black);
        systemManager.UpdateRender(dt);
        window.display();

        entityManager.Cleanup();
    }

    Logs::Get()->UnInit();
	std::cout << "[GameEngine] Fin de la boucle de jeu.\n";
}



void GameEngine::ProcessEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        Input::ProcessEvent(event);
        mpScene->OnEvent(event);
    }
}


void GameEngine::CleanUp() {
    entityManager.Clear();
}

void GameEngine::CloseGame() {
	CloseScene();
	std::cout << "[GameEngine] Fermeture du jeu.\n";
	window.close();
}

void GameEngine::CloseScene() {
    auto all = GetEntityManager().GetAllEntities();
    for (Entity* e : all) {
        GetEntityManager().DestroyEntity(e);
    }
    auto allMap = GetEntityManager().GetAllMapEntities();
    for (Entity* e : allMap) {
        GetEntityManager().DestroyEntity(e);
    }
}

void GameEngine::ApplySceneChangeIfNeeded() {
    if (pendingSceneFactory) {
        if (mpScene) {
            mpScene->OnExit();
            delete mpScene;
            mpScene = nullptr;
        }

        mpScene = pendingSceneFactory();
        mpScene->SetGameEngine(this);
        mpScene->OnInit();
        pendingSceneFactory = nullptr;
    }
}
