#include <SFML/Graphics.hpp>
#include "Player.h"

#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800,400}), "Snake Game !");
    Player snake;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        snake.draw(window);
        window.display();
    }
}