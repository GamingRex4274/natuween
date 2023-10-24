#include <SFML/System.hpp>
#include <cmath>

static float GetLengthSq(const sf::Vector2f& v)
{
    return v.x * v.x + v.y * v.y;
}

static float GetLength(const sf::Vector2f& v)
{
    return sqrt(GetLengthSq(v));
}

const sf::Vector2f GetNormalized(const sf::Vector2f& v)
{
    return v / GetLength(v);
}