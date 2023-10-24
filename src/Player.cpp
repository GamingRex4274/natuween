#include "Player.h"
#include "RamWindow.h"

Player::Player()
{
    rect.setSize({size, size});
    rect.setFillColor(sf::Color::White);
    rect.setOrigin(sf::Vector2f(size, size) / 2.0f);
    rect.setPosition(GetScreenCenter());
}

void Player::update(float dt)
{
    sf::Vector2f dir;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        dir.x = -1.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        dir.x = 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        dir.y = -1.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        dir.y = 1.0f;
    
    rect.move(dir * speed * dt);
}

void Player::draw(sf::RenderWindow& rw)
{
    rw.draw(rect);
}