#include <SFML/Graphics.hpp>
#include "Player.h"

#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800,400}), "Snake Game !");
    
    Player snake;
    snake.center_player(window);
    

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltatime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        snake.move_player(deltatime);
        window.clear();
        snake.draw(window);
        window.display();
    }
}