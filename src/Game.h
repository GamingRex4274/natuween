#include <SFML/Graphics.hpp>
#include <random>

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game(sf::RenderWindow& rw);
    void run();
private:
    void processEvents();
    void updateEntities();
    void drawFrame();
    /** Game Functions **/
private:
    sf::RenderWindow& rw;
    /* Game Variables **/
    sf::CircleShape circle = sf::CircleShape(200.0f);
    std::mt19937 rng = std::mt19937(std::random_device{}());
};

#endif