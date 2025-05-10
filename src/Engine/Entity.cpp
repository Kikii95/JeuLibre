#include "pch.h"

Entity::Entity(int id) : m_id(id) {}



int Entity::GetID() const {
	return m_id;
}

void Entity::Update(float dt) {}

void Entity::Destroy() {
    if (m_isDestroyed) return; 
    m_isDestroyed = true;

    for (auto& [type, comp] : m_components) {
        delete comp;
    }
    m_components.clear();

    //std::cout << "[Entity] Composants de l'entite " << m_id << " detruits.\n";
}

bool Entity::IsDestroyed() const {
    return m_isDestroyed;
}
