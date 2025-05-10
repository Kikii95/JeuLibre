#pragma once
#include <functional>
#include "ItemDefinition.h"
#include "HexDirection.h"



class EntityManager {
private:
    std::unordered_map<int, std::unique_ptr<Entity>> entities;
	std::unordered_map<int, std::unique_ptr<Entity>> mapentities;
	std::unordered_map<int, std::unique_ptr<Entity>> hexgridentities;

	std::unordered_set<Entity*> m_entitiesToDelete; 
    int nextEntityID = 0;  
	int nextMapEntityID = 0;

public:
    ~EntityManager() = default; 

    Entity* CreateEntity();
	Entity* CreateMapEntity();
	Entity* CreateHexGridEntity();

    Entity* GetEntity(int id);

    std::vector<Entity*> GetAllEntities();/*
    std::vector<Entity*> GetAllEntitiesInZone(const SpawnZone& zone);*/
    std::vector<Entity*> GetAllMapEntities();
	std::vector<Entity*> GetAllHexGridEntities();
    std::vector<Entity*> GetEntitiesByTag(const std::string& tag);
    std::vector<Entity*> GetEntitiesInArea(const sf::Vector2i& center, AreaType type, int size, HexDirection direction, std::function<bool(Entity*)> filter);
    
    void DestroyEntity(Entity* entity);

    void MarkForDeletion(Entity* entity);
    void Cleanup();

    void Clear();
};
