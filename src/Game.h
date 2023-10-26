#include "Player.h"
#include "Mob.h"
#include <vector>

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
    void doPlayerMobCollision();
private:
    sf::RenderWindow& rw;
    sf::Clock clock;
    /** Game Variables **/
    Player player;
    std::vector<Mob> mobs;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText = {"GAME OVER", font, 50};
    int score = 0;
    bool gameIsOver = false;
    float curTime = 0.0f;
    static constexpr float mobSpawnTime = 5.0f;
};

#endif