#include "Player.h"
#include <random>

#ifndef MOB_H
#define MOB_H

class Mob
{
public:
    Mob();
    void update(const Player& player, float dt);
    void draw(sf::RenderWindow& rw);
    sf::FloatRect getRect() const;
    bool IsHostile() const;
    bool HasBonus() const;
private:
    void wrap();
    void toggleHostility();
private:
    static constexpr float speed = 200;
    static constexpr int radius = 15;
    float hostileTime;
    float docileTime;
    float curTime = 0.0f;
    bool isHostile = true;
    bool hasBonus = false;
    sf::CircleShape circle;
    sf::Vector2f dir;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dirDist;
};

#endif