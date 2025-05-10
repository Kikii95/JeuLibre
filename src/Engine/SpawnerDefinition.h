#pragma once

struct SpawnerDefinition {
    std::string id;
    sf::Vector2f center;
    float radius = 500.f;
    std::string type;          
    std::string profileId;
    std::string difficultyZone = "ZONE_EASY";
    int maxEntities = 3;
    float respawnDelay = 5.f;
	float playerDespawnMargin = 100.f;
	float mobDespawnMargin = 100.f;
};
