#include "Game.h"
#include "RamWindow.h"

Game::Game(sf::RenderWindow& rw)
    :
    rw(rw)
{
    font.loadFromFile("src\\consola.ttf");
    scoreText.setFont(font);
    scoreText.setPosition({0,0});

    gameOverText.setOrigin(gameOverText.getGlobalBounds().getSize() / 2.0f);
    gameOverText.setPosition(GetScreenCenter());

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
    if (!gameIsOver)
    {
        float dt = clock.restart().asSeconds();
        player.update(dt);

        for (Mob& m : mobs)
            m.update(player, dt);

        doPlayerMobCollision();
    }
}

void Game::drawFrame()
{
    player.draw(rw);
    for (Mob& m : mobs)
        m.draw(rw);
    
    scoreText.setString(std::to_string(score));
    rw.draw(scoreText);

    if (gameIsOver)
        rw.draw(gameOverText);
}

void Game::doPlayerMobCollision()
{
    auto i = mobs.begin();
    while (i != mobs.end())
    {
        if (player.getRect().intersects(i->getRect()))
        {
            if (i->IsHostile())
            {
                // Collided with hostile mob.
                // Break out of loop immediately and end game.
                gameIsOver = true;
                break;
            }
            else
            {
                // Collided with docile mob. Increase score.
                score++;
                // Erase element and fix iterator.
                i = mobs.erase(i);
            }
        }
        else
            // Advance iterator normally.
            i++;
    }
}