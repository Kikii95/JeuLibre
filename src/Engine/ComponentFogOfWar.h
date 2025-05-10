#pragma once


using MapCoord = std::pair<int, int>;

class ComponentFogOfWar : public Component {
public:
    ComponentFogOfWar(Entity* entity);

    void Reveal(const MapCoord& coord);
    bool IsRevealed(const MapCoord& coord) const;

    const std::set<MapCoord>& GetRevealedTiles() const;
    void ClearFog(); 

private:
    std::set<MapCoord> revealedTiles;
};
