#include "Game.h"

Game::Game(sf::RenderWindow& rw)
    :
    rw(rw)
{
    font.loadFromFile("src\\consola.ttf");
    text.setFont(font);
    text.setPosition({0,0});

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

    doPlayerMobCollision();
}

void Game::drawFrame()
{
    player.draw(rw);
    for (Mob& m : mobs)
        m.draw(rw);
    
    text.setString(std::to_string(score));
    rw.draw(text);
}

void Game::doPlayerMobCollision()
{
    auto i = mobs.begin();
    while (i != mobs.end())
    {
        if (player.getRect().intersects(i->getRect()))
        {
            score++;
            // Erase element and fix iterator.
            i = mobs.erase(i);
        }
        else
            // Advance iterator normally.
            i++;
    }
}