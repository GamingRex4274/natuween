#include <SFML/Graphics.hpp>

#ifndef MOB_H
#define MOB_H

class Mob
{
public:
    Mob();
    void update(float dt);
    void draw(sf::RenderWindow& rw);
    sf::FloatRect getRect() const;
private:
    void wrap();
private:
    static constexpr float speed = 200;
    static constexpr int radius = 15;
    sf::CircleShape circle;
    sf::Color color;
    sf::Vector2f dir;
};

#endif