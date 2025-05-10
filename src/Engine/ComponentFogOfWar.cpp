#include "pch.h"

ComponentFogOfWar::ComponentFogOfWar(Entity* entity)
    : Component(entity) {
}

void ComponentFogOfWar::Reveal(const MapCoord& coord) {
    revealedTiles.insert(coord);
}

bool ComponentFogOfWar::IsRevealed(const MapCoord& coord) const {
    return revealedTiles.find(coord) != revealedTiles.end();
}

const std::set<MapCoord>& ComponentFogOfWar::GetRevealedTiles() const {
    return revealedTiles;
}

void ComponentFogOfWar::ClearFog() {
    revealedTiles.clear();
}
