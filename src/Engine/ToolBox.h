#pragma once

#define minimum(a, b) ((a) < (b) ? (a) : (b))
#define maximum(a, b) ((a) > (b) ? (a) : (b))
#define clamp(v, a, b) ((v) < (a) ? (a) : ((v) > (b) ? (b) : (v)))
#define clamp01(v) clamp(v, 0, 1)
#define lerp(a, b, t) ((a) * (1 - (t)) + (b) * (t))

class ToolBox {
public:
    static ToolBox& GetInstance();

    virtual ~ToolBox() = default;

    virtual int StrLength(const char* _str) const;
    virtual float Pow(float _x, int _exp) const;
    virtual float RandomFloat(float _min, float _max) const;

    virtual float Distance(const sf::Vector2f& a, const sf::Vector2f& b);

    virtual sf::Vector2f RandomOffsetInCircle(float minDist, float maxDist);

    virtual float RandomFloat(float min, float max);

    struct Vector2iHasher {
        std::size_t operator()(const sf::Vector2i& v) const;
    };

    struct Vector2iEqual {
        bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const;
    };

    struct Vector2fHasher {
        std::size_t operator()(const sf::Vector2f& v) const;
    };

    struct Vector2fEqual {
        bool operator()(const sf::Vector2f& a, const sf::Vector2f& b) const;
    };
};