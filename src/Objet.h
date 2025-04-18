#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


class Objet
{
public:
	Objet();
	void draw(sf::RenderWindow& window);
	void generate_random_position(sf::RenderWindow& window);
	void bound_red(sf::RenderWindow& windows);
	std::unique_ptr<sf::Sprite> get_apple_sprite();
private:

std::unique_ptr<sf::Sprite> m_apple_sprite;
std::unique_ptr<sf::Texture> m_apple_texture;

};

