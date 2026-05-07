#include "Apple.h"

Apple::Apple()
	:
	m_appleSprite(std::nullopt)
{

    
}

void Apple::draw(sf::RenderWindow& window)
{
	if (m_appleSprite.has_value()) window.draw(*m_appleSprite);
}

void Apple::generate_random_position(const sf::Vector2u& worldSize)
{
	if (!m_appleSprite) return;

	static std::default_random_engine rng(std::random_device{}());


	int cols = worldSize.x / 32;
	int rows = worldSize.y / 32;

	std::uniform_int_distribution<int> distX(0, cols - 1);
	std::uniform_int_distribution<int> distY(0, rows - 1);

	sf::Vector2f applePosition(distX(rng) * 32.0f, distY(rng) * 32.0f);

	m_appleSprite->setPosition(applePosition);


}

void Apple::setTexture(const sf::Texture& texture)
{
	m_appleSprite.emplace(texture);
	
}

sf::Vector2f Apple::getPosition() const
{
	return m_appleSprite->getPosition();
}

