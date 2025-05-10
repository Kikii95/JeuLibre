#include "pch.h"
void TileMapLoader::LoadTilemap(GameEngine* engine, const std::string& mapPath, int spacing) {
    std::ifstream file(mapPath);
    if (!file.is_open()) {
        std::cerr << "[Erreur] Impossible de charger la tilemap : " << mapPath << std::endl;
        return;
    }

    nlohmann::json json;
    file >> json;

    int width = json["width"];
    int height = json["height"];
    std::vector<int> tiles = json["tiles"];

    auto& em = engine->GetEntityManager();
    TileDatabase& db = TileDatabase::Get();

    int offsetX = -(width * spacing) / 2;
    int offsetY = -(height * spacing) / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            if (index >= static_cast<int>(tiles.size())) continue;

            const TileDefinition* def = db.GetTile(tiles[index]);
            if (!def) continue;

            sf::Vector2f pos(x * spacing + offsetX, y * spacing + offsetY);

            Entity* tile = em.CreateMapEntity();
            tile->AddComponent<ComponentTransform>(pos, sf::Vector2f(spacing, spacing));
            tile->AddComponent<ComponentRender>();
            tile->GetComponent<ComponentRender>()->SetTexture(def->texturePath);
            tile->GetComponent<ComponentRender>()->SetRenderType(RenderType::Sprite);
            tile->GetComponent<ComponentRender>()->SetRenderLayer(0);
        }
    }

    std::cout << "[Tilemap] Chargée avec succès depuis " << mapPath << std::endl;
}
