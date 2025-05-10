#pragma once

class ComponentZoneSpawner : public Component 
{
public:
    ComponentZoneSpawner(Entity* entity, const std::string& zoneId);

    const std::string& GetZoneId();
	void SetZoneId(const std::string& id);

	void SetRecentlySpawned(bool value);
	bool IsRecentlySpawned() const;

private:
    std::string zoneId;
    bool recentlySpawned = true;
};
