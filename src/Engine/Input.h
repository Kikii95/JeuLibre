#pragma once

class Input {
private:
    static std::map<sf::Keyboard::Key, bool> keyState;
    static std::map<sf::Keyboard::Key, bool> prevKeyState;

    static std::map<sf::Mouse::Button, bool> mouseButtonState;
    static std::map<sf::Mouse::Button, bool> prevMouseButtonState;


public:
    static void Update();

    static bool IsKeyJustPressed(sf::Keyboard::Key key);
    static bool IsKeyPressed(sf::Keyboard::Key key);
    static bool IsKeyReleased(sf::Keyboard::Key key);

    static bool IsMouseButtonJustPressed(sf::Mouse::Button button);
    static bool IsMouseButtonPressed(sf::Mouse::Button button);
    static bool IsMouseButtonReleased(sf::Mouse::Button button);

    static void ProcessEvent(const std::optional<sf::Event> event);
    static void ResetInput();
};

