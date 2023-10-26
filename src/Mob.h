#include "Player.h"
#include "TextureManager.h"
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
    static constexpr int size = 30;
    float hostileTime;
    float docileTime;
    float curTime = 0.0f;
    bool isHostile = true;
    bool hasBonus = false;
    std::shared_ptr<sf::Texture> pTex;
    sf::Sprite sprite;
    sf::Vector2f dir;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dirDist;
};

#endif