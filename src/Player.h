#include <SFML/Graphics.hpp>
#include "TextureManager.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player();
    void update(float dt);
    void activateDash();
    void draw(sf::RenderWindow& rw);
    void reset();
    sf::FloatRect getRect() const;
private:
    void translate(float dt);
    void wrap();
private:
    static constexpr int width = 23;
    static constexpr int height = 31;
    static constexpr float speed = 200;
    static constexpr float dashFactor = 3.5f;
    static constexpr float dashTime = 1.0f;
    static constexpr float dashCooldownTime = 5.0f;
    float curTime = 0.0f;
    bool isDashing = false;
    bool canDash = true;
    std::shared_ptr<sf::Texture> pTex;
    sf::Sprite sprite;
};

#endif