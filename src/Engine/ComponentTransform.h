#pragma once

class ComponentTransform : public Component {
private:
    sf::Vector2f position;
    sf::Vector2f size;
    float rotation; 

    sf::Vector2f previousPosition;


public:
	ComponentTransform(Entity* entity, sf::Vector2f startPos, sf::Vector2f sz);

    void SetPosition(const sf::Vector2f& pos);
    sf::Vector2f GetPosition() const;

    void SavePreviousPosition();
    sf::Vector2f GetPreviousPosition() const;

    void SetSize(const sf::Vector2f& sca);
    sf::Vector2f GetSize() const;

    void SetRotation(float angle);
    float GetRotation() const;

    void MoveBy(const sf::Vector2f& delta);
    void Rotate(float angle);
};
