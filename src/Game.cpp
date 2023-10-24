#include "Game.h"

Game::Game(sf::RenderWindow& rw)
    :
    rw(rw)
{
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
    mob.update(dt);
}

void Game::drawFrame()
{
    player.draw(rw);
    mob.draw(rw);
}