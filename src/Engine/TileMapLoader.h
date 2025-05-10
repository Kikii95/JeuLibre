#pragma once

class TileMapLoader {
public:
    static void LoadTilemap(GameEngine* engine, const std::string& mapPath, int spacing);
};
