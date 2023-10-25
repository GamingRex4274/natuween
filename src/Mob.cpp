#include "Mob.h"
#include "RamWindow.h"
#include "RamMath.h"
#include <random>

Mob::Mob()
    :
    circle(radius)
{
    circle.setFillColor(sf::Color::Cyan);
    circle.setOrigin({radius, radius});

    std::mt19937 rng(std::random_device{}());

    // Generate random position.
    std::uniform_real_distribution<float> xDist(0.0f, SCREEN_WIDTH);
    std::uniform_real_distribution<float> yDist(0.0f, SCREEN_HEIGHT);
    circle.setPosition(sf::Vector2f(xDist(rng), yDist(rng)));

    // Generate random direction.
    std::uniform_real_distribution<float> dirDist(0.0f, 1.0f);
    dir = GetNormalized(sf::Vector2f(dirDist(rng), dirDist(rng)));
}

void Mob::update(float dt)
{
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

sf::FloatRect Mob::getRect() const
{
    return circle.getGlobalBounds();
}