#include "pch.h"
#include "GameEngine.h"
#include "TestScene.h"
#include "GameplayScene.h"
#include "ExploNavalScene.h"

int main() {
    GameEngine& engine = GameEngine::GetInstance();
    engine.Init();
//    engine.Run();
    engine.LaunchScene<ExploNavalScene>();
    engine.CleanUp();
    return 0;
}

///*#include "pch.h"
//#include "GameEngine.h"
//
//int main() {
//    GameEngine& engine = GameEngine::GetInstance();
//    engine.Init();
//    engine.Run();
//    engine.CleanUp();
//    return 0;
//}*/
// 
// 
//#include <SFML/Graphics.hpp>
//#include <cmath>
//#include <vector>
//
//class Hexagon {
//public:
//    sf::ConvexShape shape;
//    float radius;
//    float width, height;
//
//    Hexagon(float r, float outlineThickness = 2.f, sf::Color fillColor = sf::Color::Green, sf::Color outlineColor = sf::Color::Black) {
//        radius = r;
//        width = 2 * radius;
//        height = std::sqrt(3) * radius;
//
//        // D�finit la forme de l'hexagone
//        shape.setPointCount(6);
//        for (int i = 0; i < 6; ++i) {
//            float angle = i * 2 * 3.14 / 6; // Divise l'hexagone en 6 parts �gales
//            shape.setPoint(i, sf::Vector2f(radius * std::cos(angle), radius * std::sin(angle)));
//        }
//
//        // Applique les couleurs
//        shape.setFillColor(fillColor);
//        shape.setOutlineThickness(outlineThickness);
//        shape.setOutlineColor(outlineColor);
//    }
//
//    // Positionne l'hexagone
//    void setPosition(float x, float y) {
//        shape.setPosition({ x, y });
//    }
//
//    // Dessine l'hexagone
//    void draw(sf::RenderWindow& window) {
//        window.draw(shape);
//    }
//};
//
//void drawHexGrid(sf::RenderWindow& window, int rows, int cols, float hexRadius) {
//    Hexagon hex(hexRadius, 3.f, sf::Color::Green, sf::Color::Black); // Bordure �paisse de 3 pixels
//
//    float dx = 3.f / 2.f * hexRadius; // D�calage horizontal
//    float dy = std::sqrt(3) * hexRadius; // D�calage vertical
//
//    for (int row = 0; row < rows; ++row) {
//        for (int col = 0; col < cols; ++col) {
//            float x = col * dx;
//            float y = row * dy;
//
//            // D�cale les lignes impaires
//            if (col % 2 != 0) {
//                y += dy / 2;
//            }
//
//            hex.setPosition(x, y);
//            hex.draw(window);
//        }
//    }
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Grille Hexagonale avec Bordures");
//
//    // Param�tres
//    float hexRadius = 30.f; // Rayon de l'hexagone
//    int rows = 10;  // Nombre de lignes
//    int cols = 10;  // Nombre de colonnes
//
//    while (window.isOpen()) {
//        while (const std::optional event = window.pollEvent())
//        {
//            if (event->is<sf::Event::Closed>())
//            {
//                window.close();
//            }
//        }
//
//        window.clear();
//
//        drawHexGrid(window, rows, cols, hexRadius);
//
//        window.display();
//    }
//
//    return 0;
//}
