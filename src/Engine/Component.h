#pragma once

class Entity;

class Component {
protected:
    Entity* m_pEntity;

public:
    explicit Component(Entity* _pEntity);
    virtual ~Component();

    int GetID() const;

    Entity* GetEntity();

    virtual std::type_index GetType() const;

};
