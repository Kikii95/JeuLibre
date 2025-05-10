#pragma once
#include "TileDefinition.h"

class TileDatabase {
public:
    static TileDatabase& Get();

    bool LoadFromFile(const std::string& path);
    const TileDefinition* GetTile(int id) const;

private:
    std::unordered_map<int, TileDefinition> tiles;
};
