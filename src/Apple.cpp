#include "Apple.h"

Apple::Apple()
	:
	m_appleSprite(std::nullopt)
{

    
}

void Apple::draw(sf::RenderWindow& window)
{
    window.draw(*m_appleSprite);
}

void Apple::generate_random_position(sf::RenderWindow & window)
{

}

void Apple::setTexture(const sf::Texture& texture)
{
	m_appleSprite.emplace(texture);
	
}

