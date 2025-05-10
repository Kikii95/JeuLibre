#pragma once

class ComponentProjectile : public Component {
public:
    std::string itemId;
    Entity* owner = nullptr;

    sf::Vector2i gridPos;         
    HexDirection direction;      
    int rangeLeft = 0;            
    int hitsRemaining = 1;        

    ComponentProjectile(Entity* entity);
};


