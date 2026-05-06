#pragma once

#include <SFML/Graphics.hpp>
class Apple
{
public:
	Apple();
	void draw(sf::RenderWindow& window);
	void generate_random_position(sf::RenderWindow& window);
	void setTexture(const sf::Texture& texture);

private:

std::optional<sf::Sprite> m_appleSprite;

};

