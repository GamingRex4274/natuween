#include "Game.h"

Game::Game(sf::RenderWindow& rw)
    :
    rw(rw)
{
    for (int n = 0; n < 10; n++)
        mobs.emplace_back();
}

void Game::run()
{
    processEvents();
    rw.clear();
    updateEntities();
    drawFrame();
    rw.display();
}

void Game::processEvents()
{
    sf::Event event;
    while (rw.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            rw.close();
    }
}

void Game::updateEntities()
{
    float dt = clock.restart().asSeconds();
    player.update(dt);

    for (Mob& m : mobs)
        m.update(dt);
}

void Game::drawFrame()
{
    player.draw(rw);
    for (Mob& m : mobs)
        m.draw(rw);
}