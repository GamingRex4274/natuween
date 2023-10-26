#include "Player.h"
#include "RamWindow.h"
#include "RamMath.h"

Player::Player()
{
    rect.setSize({size, size});
    rect.setFillColor(sf::Color::White);
    rect.setOrigin(sf::Vector2f(size, size) / 2.0f);
    reset();
}

void Player::update(float dt)
{
    translate(dt);
    wrap();
}

void Player::draw(sf::RenderWindow& rw)
{
    rw.draw(rect);
}

void Player::reset()
{
    rect.setPosition(GetScreenCenter());
}

sf::FloatRect Player::getRect() const
{
    return rect.getGlobalBounds();
}

void Player::translate(float dt)
{
    sf::Vector2f dir = {0.0f, 0.0f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        dir.x = -1.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        dir.x = 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        dir.y = -1.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        dir.y = 1.0f;
    
    dir = GetNormalized(dir);
    rect.move(dir * speed * dt);
}

void Player::wrap()
{
    sf::Vector2f pos = rect.getPosition();

    // If RIGHT side goes beyond left of screen.
    if (pos.x + size < 0)
        pos.x = SCREEN_WIDTH + size;
    // If LEFT side goes beyond right of screen.
    else if (pos.x - size >= SCREEN_WIDTH)
        pos.x = -size;
    // If BOTTOM goes beyond top of screen.
    if (pos.y + size < 0)
        pos.y = SCREEN_HEIGHT + size;
    // If TOP goes beyond bottom of screen.
    else if (pos.y - size >= SCREEN_HEIGHT)
        pos.y = -size;

    if (pos != rect.getPosition())
        rect.setPosition(pos);
}