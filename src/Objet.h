#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


class Objet
{
public:
	Objet();
	void draw(sf::RenderWindow& window);
	void generate_random_position(sf::RenderWindow& window);
private:

std::unique_ptr<sf::Sprite> m_apple_sprite;
std::unique_ptr<sf::Texture> m_apple_texture;

};

