#include "Player.h"
#include "RamWindow.h"
#include "RamMath.h"

Player::Player()
{
    pTex = TextureManager::acquire("src\\reaper.png");
    sprite.setTexture(*pTex);
    sprite.setTextureRect({0, 0, width, height});
    sprite.setOrigin(sf::Vector2f(width, height) / 2.0f);
    reset();
}

void Player::update(float dt)
{
    if (isDashing)
    {
        curTime += dt;
        if (curTime >= dashTime)
        {
            isDashing = false;
            curTime = 0.0f;
        }
    }
    else if (!canDash)
    {
        curTime += dt;
        if (curTime >= dashCooldownTime)
        {
            canDash = true;
            curTime = 0.0f;
        }
    }

    translate(dt);
    wrap();
}

void Player::activateDash()
{
    if (canDash)
    {
        canDash = false;
        isDashing = true;
    }
}

void Player::draw(sf::RenderWindow& rw)
{
    rw.draw(sprite);
}

void Player::reset()
{
    sprite.setPosition(GetScreenCenter());
    canDash = true;
    isDashing = false;
    curTime = 0.0f;
}

sf::FloatRect Player::getRect() const
{
    return sprite.getGlobalBounds();
}

int Player::getCountdown() const
{
    if (!isDashing && !canDash)
        return static_cast<int>(dashCooldownTime - curTime);
    else
        return 0;
}

void Player::translate(float dt)
{
    sf::Vector2f dir = {0.0f, 0.0f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        dir.x = -1.0f;
        sprite.setTextureRect({width, 0, width, height});
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        dir.x = 1.0f;
        sprite.setTextureRect({0, 0, width, height});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        dir.y = -1.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        dir.y = 1.0f;
    
    dir = GetNormalized(dir);
    
    const float speedupFactor = (isDashing) ? dashFactor : 1.0f;
    sprite.move(dir * speed * speedupFactor * dt);
}

void Player::wrap()
{
    sf::Vector2f pos = sprite.getPosition();

    // If RIGHT side goes beyond left of screen.
    if (pos.x + width / 2 < 0)
        pos.x = SCREEN_WIDTH + width / 2;
    // If LEFT side goes beyond right of screen.
    else if (pos.x - (width / 2) >= SCREEN_WIDTH)
        pos.x = -(width / 2);
    // If BOTTOM goes beyond top of screen.
    if (pos.y + height / 2 < 0)
        pos.y = SCREEN_HEIGHT + height / 2;
    // If TOP goes beyond bottom of screen.
    else if (pos.y - (height / 2) >= SCREEN_HEIGHT)
        pos.y = -(height / 2);

    if (pos != sprite.getPosition())
        sprite.setPosition(pos);
}