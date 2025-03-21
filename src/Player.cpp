#include "Player.h"
#include <iostream>

Player::Player()

{
	
	add_texture("../assets/head_left.png", 0);

}

Player::~Player()
{
}

void Player::add_texture(std::string filename, int index)
{

	m_snake_texture.push_back((std::make_unique<sf::Texture>()));

	if (!m_snake_texture.back()->loadFromFile(filename))
	{
		// Handle the error, for example, by throwing an exception
		m_snake_texture.pop_back();
		throw std::runtime_error("Failed to load texture from file: ");
	}
	auto sprite = std::make_unique<sf::Sprite>();
	sprite->setTexture(*m_snake_texture[index]);
	m_sprite_snake.push_back(std::move(sprite));

}

void Player::draw(sf::RenderWindow& window)
{
    for (auto& sprite : m_sprite_snake)
    {
		window.draw(*sprite);
    }
}


