#include "Mob.h"
#include "RamWindow.h"
#include "RamMath.h"
#include <random>

Mob::Mob()
    :
    circle(radius),
    rng(std::random_device{}()),
    dirDist(0.0f, 1.0f)
{
    circle.setOrigin({radius, radius});

    // Generate random position.
    std::uniform_real_distribution<float> xDist(0.0f, SCREEN_WIDTH);
    std::uniform_real_distribution<float> yDist(0.0f, SCREEN_HEIGHT);
    circle.setPosition(sf::Vector2f(xDist(rng), yDist(rng)));

    // Set initial hostility to false.
    toggleHostility();
}

void Mob::update(const Player& player, float dt)
{
    const float targetTime = (isHostile) ? hostileTime : docileTime;
    curTime += dt;
    if (curTime >= targetTime)
    {
        toggleHostility();
        curTime = 0.0f;
    }

    if (isHostile)
        dir = GetNormalized(player.getRect().getPosition() - circle.getPosition());

    circle.move(dir * speed * dt);
    wrap();
}

void Mob::draw(sf::RenderWindow& rw)
{
    rw.draw(circle);
}

void Mob::wrap()
{
    sf::Vector2f pos = circle.getPosition();

    // If RIGHT side goes beyond left of screen.
    if (pos.x + radius < 0)
        pos.x = SCREEN_WIDTH + radius;
    // If LEFT side goes beyond right of screen.
    else if (pos.x - radius >= SCREEN_WIDTH)
        pos.x = -radius;
    // If BOTTOM goes beyond top of screen.
    if (pos.y + radius < 0)
        pos.y = SCREEN_HEIGHT + radius;
    // If TOP goes beyond bottom of screen.
    else if (pos.y - radius >= SCREEN_HEIGHT)
        pos.y = -radius;

    if (pos != circle.getPosition())
        circle.setPosition(pos);
}

void Mob::toggleHostility()
{
    // Change to docile attributes.
    if (isHostile)
    {
        circle.setFillColor(sf::Color::Cyan);
        // Generate random direction.
        dir = GetNormalized(sf::Vector2f(dirDist(rng), dirDist(rng)));
    }
    // Change to hostile attributes.
    else
        circle.setFillColor(sf::Color::Red);

    isHostile = !isHostile;
}

sf::FloatRect Mob::getRect() const
{
    return circle.getGlobalBounds();
}

bool Mob::IsHostile() const
{
    return isHostile;
}