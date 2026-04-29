#pragma once
#include <SFML/Graphics.hpp>

#include "deque"


class Player
{
public:
	Player();
	~Player();


	void handle();
	void update(float dt);
	void setVelocity(const sf::Vector2f& v);
	sf::Vector2f getPositions() const;
	

private:
	std::deque<sf::Vector2f> m_positions;
	std::vector<sf::Sprite> m_sprites;
	sf::Vector2f m_velocity;
};
