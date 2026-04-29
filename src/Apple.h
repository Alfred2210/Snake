#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


class Apple
{
public:
	Apple();
	void draw(sf::RenderWindow& window);
	void generate_random_position(sf::RenderWindow& window);
	std::unique_ptr<sf::Sprite> get_apple_sprite();
private:

sf::Sprite m_apple_sprite;
sf::Texture m_apple_texture;

};

