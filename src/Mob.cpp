#include "Mob.h"
#include "RamWindow.h"
#include "RamMath.h"
#include <ctime>

Mob::Mob()
    :
    circle(radius)
{
    circle.setFillColor(sf::Color::Cyan);
    circle.setOrigin({radius, radius});

    srand(time(nullptr));

    // Generate random position.
    const int x = rand() % SCREEN_WIDTH;
    const int y = rand() % SCREEN_HEIGHT;
    circle.setPosition(sf::Vector2f(x, y));

    // Generate random direction.
    const float xDir = rand() / float(RAND_MAX);
    const float yDir = rand() / float(RAND_MAX);
    dir = GetNormalized(sf::Vector2f(xDir, yDir));
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