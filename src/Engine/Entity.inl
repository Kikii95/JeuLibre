#include "Logs.h"

template <typename T, typename... Args>
T* Entity::AddComponent(Args&&... args) {
    T* component = new T(this, std::forward<Args>(args)...);
    m_components[typeid(T)] = component;

    if (debugMode && logComponent) {
        HEAD("COMPONENT") << typeid(T).name() << " ADDED to entity " << m_id << ENDL;
    }
    return component;
}

template <typename T>
T* Entity::GetComponent() {
    auto it = m_components.find(typeid(T));
    return (it != m_components.end()) ? static_cast<T*>(it->second) : nullptr;
}

template <typename T>
bool Entity::HasComponent() {
    return m_components.find(typeid(T)) != m_components.end();
}

template <typename T>
void Entity::RemoveComponent() {
    auto it = m_components.find(typeid(T));
    if (it != m_components.end()) {
        if (debugMode && logComponent) {
            HEAD("COMPONENT") << "Component " << typeid(T).name() << " REMOVED from entity " << m_id << ENDL;
        }
        delete it->second;
        m_components.erase(it);
    }
}
