#pragma once

enum class HexDirection {
    TopRight,
    Right,
    BottomRight,
    BottomLeft,
    Left,
    TopLeft
};

inline sf::Vector2i HexDirectionToOffset(HexDirection dir, int parity /* 0=even, 1=odd */) {
    switch (dir) {
    case HexDirection::TopRight:    return parity ? sf::Vector2i(1, -1) : sf::Vector2i(1, 0);
    case HexDirection::Right:       return sf::Vector2i(1, 0);
    case HexDirection::BottomRight: return parity ? sf::Vector2i(1, 0) : sf::Vector2i(1, 1);
    case HexDirection::BottomLeft:  return parity ? sf::Vector2i(0, 1) : sf::Vector2i(-1, 1);
    case HexDirection::Left:        return sf::Vector2i(-1, 0);
    case HexDirection::TopLeft:     return parity ? sf::Vector2i(0, -1) : sf::Vector2i(-1, 0);
    }
    return sf::Vector2i(0, 0);
}
