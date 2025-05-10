#pragma once

class Component;
class System;

class Entity {
private:
    int m_id;
    std::unordered_map<std::type_index, Component*> m_components;

    bool m_isDestroyed = false;

public:
    Entity(int id);
	~Entity() = default;

    int GetID() const;

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template <typename T>
    T* GetComponent();

    template <typename T>
	bool HasComponent();

    template <typename T>
    void RemoveComponent();

	void Destroy();
    bool IsDestroyed() const;

    void Update(float dt);

};

#include "Entity.inl"