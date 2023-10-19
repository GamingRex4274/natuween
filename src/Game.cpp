#include "Game.h"
#include <iostream>

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
    std::uniform_int_distribution<int> dist(0, 255);
    sf::Color c = sf::Color(dist(rng), dist(rng), dist(rng));
    std::cout << c.r << " " << c.g << " " << c.b << "\n";
    circle.setFillColor(c);
}

void Game::drawFrame()
{
    rw.draw(circle);
}