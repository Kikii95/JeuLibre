#include "pch.h"

ComponentTag::ComponentTag(Entity* entity, const std::string& tagName)
    : Component(entity), tag(tagName) {
}

void ComponentTag::SetTag(const std::string& newTag) {
    tag = newTag;
}

std::string ComponentTag::GetTag() const {
    return tag;
}
