#include "pch.h"

GameTimer::GameTimer()
    : stopped(false) {
    previousTime = clock.getElapsedTime();
    deltaTime = sf::Time::Zero;
}

float GameTimer::TotalTime() const {
    return clock.getElapsedTime().asSeconds();
}

float GameTimer::DeltaTime() const {
    return deltaTime.asSeconds();
}

bool GameTimer::IsPaused() const {
	return stopped;
}

void GameTimer::Reset() {
    clock.restart();
    previousTime = sf::Time::Zero;
    deltaTime = sf::Time::Zero;
    stopped = false;
}

void GameTimer::Start() {
    if (stopped) {
        clock.restart();
        previousTime = sf::Time::Zero;
        stopped = false;
    }
}

void GameTimer::Stop() {
    stopped = true;
}

void GameTimer::Tick() {
    if (stopped) {
        deltaTime = sf::Time::Zero;
        return;
    }

    sf::Time currentTime = clock.getElapsedTime();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}
