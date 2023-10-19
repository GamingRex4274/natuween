#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Abstract Data Taip");
    window.setFramerateLimit(5);
    sf::CircleShape shape(200.f);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Color c = sf::Color(dist(rng), dist(rng), dist(rng));
        std::cout << c.r << " " << c.g << " " << c.b << "\n";
        shape.setFillColor(c);

        window.draw(shape);
        window.display();
    }

    return 0;
}