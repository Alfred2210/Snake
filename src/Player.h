#pragma once

#include <deque>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "Direction.h"
#include "ResourceManager.h"
#include <optional>

class Player
{
public:
	Player();
	void draw(sf::RenderWindow &windows);
	void update();
	void move();
	void setDirection(Direction direction);
	void setPosition(sf::Vector2f position);
	void setTailPosition(sf::Vector2f position);
	void setTexture(const sf::Texture& texture);
	void updateSprite(const ResourceManager& resourceManager);
	void updateTailSprite(const ResourceManager& resourceManager);
	sf::Vector2f getPosition() const;


private:
	std::deque<sf::Vector2f>  m_positions;
	Direction m_direction;
	std::optional<sf::Sprite> m_headSprite;
	std::optional<sf::Sprite> m_tailSprite;
	
};
