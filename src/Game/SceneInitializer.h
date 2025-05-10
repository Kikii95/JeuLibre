#pragma once

enum class MapType {
	GladeIsland,
	LakeIsland,
	MountainIsland,
	YingYangIsland,
	CressentIsland,
	WorldMap,
};

class SceneInitializer {
public:
	static void LoadCommonResources();
	static void LoadMap(GameEngine* engine, MapType type);
	static void SetupStaticEntities(GameEngine* engine);
	static void SetupSpawnerZones(GameEngine* engine);
	static void SetupUI(Entity* player);
};
