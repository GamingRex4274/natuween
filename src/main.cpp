#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Abstract Data Taip");
    window.setFramerateLimit(5);

    Game game(window);
    while (window.isOpen())
        game.run();

    return 0;
}