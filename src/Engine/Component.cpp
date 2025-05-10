#include "pch.h"

Component::Component(Entity* _pEntity) : m_pEntity(_pEntity) 
{
}

Component::~Component() 
{
}

int Component::GetID() const
{
	return m_pEntity->GetID();
}

Entity* Component::GetEntity()
{
	return m_pEntity;
}

std::type_index Component::GetType() const {
	return typeid(*this);
}
