#pragma once

#include <random>
#include <SFML/Graphics.hpp>
#include <optional>
class Apple
{
public:
	Apple();
	void draw(sf::RenderWindow& window);
	void generate_random_position(const sf::Vector2u& worldSize);
	void setTexture(const sf::Texture& texture);
	sf::Vector2f getPosition() const;

private:
	//std::random_device m_rd;
	//std::default_random_engine m_rng;
	std::optional<sf::Sprite> m_appleSprite;

};

