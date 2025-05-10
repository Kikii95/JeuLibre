#pragma once
#include "SystemManager.h"
#include "EntityManager.h"
#include "GameTimer.h"
#include "Scene.h"

class GameEngine {
public:
    static GameEngine& GetInstance();
    EntityManager& GetEntityManager();
    SystemManager& GetSystemManager();

    template<typename T>
    T* GetSystem();

    sf::RenderWindow& GetWindow();
	sf::Vector2f GetWindowSize() const { return windowSize; }

    GameTimer& GetTimer();

    void Init();
    void Run();
    void CleanUp();

	void CloseGame();
	void CloseScene();
    
    template<typename T>
    void LaunchScene();

	template<typename T>
	void QueueSceneChange();

    void ApplySceneChangeIfNeeded();



private:
    GameEngine() = default; 
    ~GameEngine() = default;

	sf::Vector2f windowSize = { 3840.f, 2160.f };

    sf::RenderWindow window; 
    SystemManager systemManager;
    EntityManager entityManager;
    GameTimer gameTimer;
    Scene* mpScene;
    bool isRunning = true;

    void ProcessEvents();
    void GameLoop();

    std::function<Scene* ()> pendingSceneFactory = nullptr;

};

template<typename T>
void GameEngine::LaunchScene()
{
    static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
    _ASSERT(mpScene == nullptr);

    T* newScene = new T();
    mpScene = newScene;

    mpScene->SetGameEngine(this);
    mpScene->OnInit();

    Run();
}

template<typename T>
T* GameEngine::GetSystem() {
    return systemManager.GetSystem<T>();
}


template<typename T>
void GameEngine::QueueSceneChange() {
    static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
    pendingSceneFactory = []() -> Scene* { return new T(); };
}
