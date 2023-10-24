#include "Game.h"
#include "RamWindow.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Natuween");
    window.setFramerateLimit(60);

    Game game(window);
    while (window.isOpen())
        game.run();

    return 0;
}