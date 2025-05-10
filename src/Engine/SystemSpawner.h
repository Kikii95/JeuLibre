#pragma once

struct SpawnZone {
    std::string id;
    sf::Vector2f center;
    float radius;
    std::string type;
    std::string profileId;
    int maxEntities;
    float respawnDelay;
    float timeSinceLastSpawn = 0.f;
    std::string difficultyZone = "ZONE_EASY";
	float playerDespawnMargin;
	float mobDespawnMargin;

};

class SystemSpawner : public System {
public:
    SystemSpawner();

    void Update(float dt, const std::vector<Entity*>& entities) override;
    void RegisterSpawnZone(const SpawnZone& zone);
    void SpawnStaticEntity(const std::string& profileId, const sf::Vector2f& center, float radius, float spacing, int count);

    sf::Vector2f GetRandomPointInZone(const SpawnZone& zone);

	SystemType GetType() const override { return SystemType::Active; }
	void Logs() override {};

	//SpawnZone& GetSpawnZone(const std::string& id) {
	//	for (auto& zone : zones) {
	//		if (zone.id == id) {
	//			return zone;
	//		}
	//	}
	//	throw std::runtime_error("SpawnZone not found");
	//}

private:
    std::vector<SpawnZone> zones;

    void TrySpawn(SpawnZone& zone);
    int CountEntitiesInZone(const SpawnZone& zone);
};
