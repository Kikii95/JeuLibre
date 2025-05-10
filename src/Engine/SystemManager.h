#pragma once
#include <typeindex>
#include "System.h"

class SystemManager {
private:
    std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
    std::vector<System*> activeSystems;
    std::vector<System*> renderSystems;
	std::vector<System*> reactiveSystems;
	std::vector<System*> turnBasedSystems;

public:
    ~SystemManager() = default;

    template <typename T, typename... Args>
    T* AddSystem(Args&&... args);

	template <typename T, typename... Args>
	T* RemoveSystem(Args&&... args);

    template <typename T>
    T* GetSystem();

    std::vector<System*> GetAllSystems() const;

	void Update(float dt);
    void UpdateActiveSystems(float dt);
	void UpdateReactiveSystems(float dt);
	void UpdateTurnBasedSystems(float dt);
    void UpdateRender(float dt);

	void Clear();
};

#include "SystemManager.inl"
