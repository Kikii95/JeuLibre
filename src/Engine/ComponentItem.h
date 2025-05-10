#pragma once
#include "ItemInstance.h"

class ComponentItem : public Component {
public:
    ItemInstance instance;

    ComponentItem(Entity* entity, const ItemInstance& item)
        : Component(entity), instance(item) {
    }
};
