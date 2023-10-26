#include "Mob.h"
#include "RamWindow.h"
#include "RamMath.h"
#include <random>

Mob::Mob()
    :
    rng(std::random_device{}()),
    dirDist(0.0f, 1.0f)
{
    pTex = TextureManager::acquire("src\\mob.png");
    sprite.setTexture(*pTex);
    sprite.setTextureRect({0, 0, size, size});
    sprite.setOrigin(sf::Vector2f(size, size) / 2.0f);

    // Generate random position.
    std::uniform_real_distribution<float> xDist(0.0f, SCREEN_WIDTH);
    std::uniform_real_distribution<float> yDist(0.0f, SCREEN_HEIGHT);
    sprite.setPosition(sf::Vector2f(xDist(rng), yDist(rng)));

    // Generate random timers.
    std::uniform_real_distribution<float> tDist(2.0f, 8.0f);
    hostileTime = tDist(rng);
    docileTime = tDist(rng);

    // Set initial hostility to false.
    toggleHostility();
}

void Mob::update(const Player& player, float dt)
{
    const float targetTime = (isHostile) ? hostileTime : docileTime;
    curTime += dt;
    if (curTime >= targetTime)
    {
        hasBonus = false;
        toggleHostility();
        curTime = 0.0f;
    }
    else if (!isHostile && curTime >= targetTime - 1.0f)
    {
        // Warning 1 second before turning hostile.
        sprite.setTextureRect({size, 0, size, size});
        // Bonus activated.
        hasBonus = true;
    }

    if (isHostile)
        dir = GetNormalized(player.getRect().getPosition() - sprite.getPosition());

    sprite.move(dir * speed * dt);
    wrap();
}

void Mob::draw(sf::RenderWindow& rw)
{
    rw.draw(sprite);
}

void Mob::wrap()
{
    sf::Vector2f pos = sprite.getPosition();

    // If RIGHT side goes beyond left of screen.
    if (pos.x + (size / 2) < 0)
        pos.x = SCREEN_WIDTH + (size / 2);
    // If LEFT side goes beyond right of screen.
    else if (pos.x - (size / 2) >= SCREEN_WIDTH)
        pos.x = -(size / 2);
    // If BOTTOM goes beyond top of screen.
    if (pos.y + (size / 2) < 0)
        pos.y = SCREEN_HEIGHT + (size / 2);
    // If TOP goes beyond bottom of screen.
    else if (pos.y - (size / 2) >= SCREEN_HEIGHT)
        pos.y = -(size / 2);

    if (pos != sprite.getPosition())
        sprite.setPosition(pos);
}

void Mob::toggleHostility()
{
    // Change to docile attributes.
    if (isHostile)
    {
        sprite.setTextureRect({0, 0, size, size});
        // Generate random direction.
        dir = GetNormalized(sf::Vector2f(dirDist(rng), dirDist(rng)));
    }
    // Change to hostile attributes.
    else
        sprite.setTextureRect({size * 2, 0, size, size});

    isHostile = !isHostile;
}

sf::FloatRect Mob::getRect() const
{
    return sprite.getGlobalBounds();
}

bool Mob::IsHostile() const
{
    return isHostile;
}

bool Mob::HasBonus() const
{
    return hasBonus;
}