#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player();
    void update(float dt);
    void draw(sf::RenderWindow& rw);
private:
    static constexpr int size = 32;
    static constexpr float speed = 200;
    sf::RectangleShape rect;
};

#endif