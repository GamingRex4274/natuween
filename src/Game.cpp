#include "Game.h"
#include "RamWindow.h"

Game::Game(sf::RenderWindow& rw)
    :
    rw(rw)
{
    font.loadFromFile("src\\consola.ttf");
    scoreText.setFont(font);
    scoreText.setPosition({5, 5});

    gameOverText.setOrigin(gameOverText.getGlobalBounds().getSize() / 2.0f);
    gameOverText.setPosition(GetScreenCenter());

    subText.setOrigin(subText.getGlobalBounds().getSize() / 2.0f);
    subText.setPosition(GetScreenCenter().x, SCREEN_HEIGHT - 15);
    
    // Spawn first mob immediately.
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
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
                player.activateDash();
        }
    }
}

void Game::updateEntities()
{
    float dt = clock.restart().asSeconds();
    TextureManager::clean();

    if (!gameIsOver)
    {
        curTime += dt;
        if (curTime >= mobSpawnTime)
        {
            mobs.emplace_back();
            curTime = 0.0f;
        }
        
        player.update(dt);

        for (Mob& m : mobs)
            m.update(player, dt);

        doPlayerMobCollision();
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            reset();
    }
}

void Game::drawFrame()
{
    player.draw(rw);
    for (Mob& m : mobs)
        m.draw(rw);
    
    scoreText.setString("Score:\n" + std::to_string(score));
    rw.draw(scoreText);

    if (gameIsOver)
    {
        rw.draw(gameOverText);
        rw.draw(subText);
    }
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
                score += (i->HasBonus()) ? 5 : 1;
                // Erase element and fix iterator.
                i = mobs.erase(i);
            }
        }
        else
            // Advance iterator normally.
            i++;
    }
}

void Game::reset()
{
    player.reset();
    mobs.clear();
    mobs.emplace_back();
    score = 0;
    curTime = 0.0f;
    gameIsOver = false;
}