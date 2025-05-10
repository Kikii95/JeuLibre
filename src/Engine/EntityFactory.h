#pragma once

class Entity;

namespace EntityFactory {
    Entity* CreatePlayer(const sf::Vector2f& position);
    Entity* CreateMerchant(const std::string& profileId, const sf::Vector2f& position);
    Entity* CreateEnemy(const std::string& id, const std::string& profileId, const std::string& difficultyZone, const sf::Vector2f& position);
}