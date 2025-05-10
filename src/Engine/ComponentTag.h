#pragma once

class ComponentTag : public Component {
private:
    std::string tag;

public:
    ComponentTag(Entity* entity, const std::string& tagName);

    void SetTag(const std::string& newTag);
    std::string GetTag() const;
};
