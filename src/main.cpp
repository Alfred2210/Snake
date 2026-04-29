#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800,400}), "Snake Game !");
 
    Player snake;
    Objet apple;
    snake.center_player_on_screen(window);
    apple.generate_random_position(window);
   
   
    

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltatime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        snake.update_snake_movement(deltatime);
        snake.wrap_around_screen(window);
        window.clear();
        snake.render_player(window);
        apple.draw(window);
        apple.bound_red(window);
        snake.check_collision_with_apple(apple,window);
        window.display();
        
    }
}