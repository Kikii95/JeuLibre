#include "pch.h"

ToolBox& ToolBox::GetInstance() {
	static ToolBox instance;
	return instance;
}

int ToolBox::StrLength(const char* _str) const {
    int count = 0;
    while (_str[count] != '\0') {
        count++;
    }
    return count;
}

float ToolBox::Pow(float _x, int _exp) const {
    if (_exp == 0) return 1;
    if (_exp == 1) return _x;

    float halfPow = Pow(_x, _exp / 2);
    return (_exp % 2 == 1) ? halfPow * halfPow * _x : halfPow * halfPow;
}

float ToolBox::RandomFloat(float _min, float _max) const {
    return _min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (_max - _min)));
}

float ToolBox::Distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

sf::Vector2f ToolBox::RandomOffsetInCircle(float minDist, float maxDist) {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * 3.14159f;
    float radius = minDist + static_cast<float>(rand()) / RAND_MAX * (maxDist - minDist);
    return sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius);
}

float ToolBox::RandomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}


std::size_t ToolBox::Vector2iHasher::operator()(const sf::Vector2i& v) const {
    std::size_t h1 = std::hash<int>()(v.x);
    std::size_t h2 = std::hash<int>()(v.y);
    return h1 ^ (h2 << 1);
}

bool ToolBox::Vector2iEqual::operator()(const sf::Vector2i& a, const sf::Vector2i& b) const {
    return a.x == b.x && a.y == b.y;
}

std::size_t ToolBox::Vector2fHasher::operator()(const sf::Vector2f& v) const {
    std::size_t h1 = std::hash<float>()(v.x);
    std::size_t h2 = std::hash<float>()(v.y);
    return h1 ^ (h2 << 1);
}

bool ToolBox::Vector2fEqual::operator()(const sf::Vector2f& a, const sf::Vector2f& b) const {
    const float epsilon = 0.001f;
    return std::abs(a.x - b.x) < epsilon && std::abs(a.y - b.y) < epsilon;
}
