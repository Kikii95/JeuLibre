#include "pch.h"

std::map<sf::Keyboard::Key, bool> Input::keyState;
std::map<sf::Keyboard::Key, bool> Input::prevKeyState;

std::map<sf::Mouse::Button, bool> Input::mouseButtonState;
std::map<sf::Mouse::Button, bool> Input::prevMouseButtonState;

void Input::Update() {
    prevKeyState = keyState;
    for (int k = 0; k < sf::Keyboard::KeyCount; ++k) {
        keyState[static_cast<sf::Keyboard::Key>(k)] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));
    }

    prevMouseButtonState = mouseButtonState;
    for (int b = 0; b < sf::Mouse::ButtonCount; ++b) {
        mouseButtonState[static_cast<sf::Mouse::Button>(b)] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(b));
    }
}

bool Input::IsKeyJustPressed(sf::Keyboard::Key key) {
    return keyState[key] && !prevKeyState[key];
}

bool Input::IsKeyPressed(sf::Keyboard::Key key) {
    return keyState[key];
}

bool Input::IsKeyReleased(sf::Keyboard::Key key) {
    return prevKeyState[key] && !keyState[key];
}

bool Input::IsMouseButtonJustPressed(sf::Mouse::Button button) {
    return mouseButtonState[button] && !prevMouseButtonState[button];
}

bool Input::IsMouseButtonPressed(sf::Mouse::Button button) {
    return mouseButtonState[button];
}

bool Input::IsMouseButtonReleased(sf::Mouse::Button button) {
    return prevMouseButtonState[button] && !mouseButtonState[button];
}

void Input::ProcessEvent(const std::optional<sf::Event> event) {
    if (event->is<sf::Event::Closed>()) {
        // Peut-être à rediriger ailleurs ?
    }
}

void Input::ResetInput() {
    keyState.clear();
    prevKeyState.clear();
    mouseButtonState.clear();
    prevMouseButtonState.clear();
}

