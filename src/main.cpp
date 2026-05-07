#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800,400}), "Snake Game !");
    Game game(window.getSize());
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        game.update(dt);
        window.clear();
		game.render(window);
        window.display();
    }
}