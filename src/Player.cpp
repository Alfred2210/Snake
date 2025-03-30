#include "Player.h"
#include <iostream>
#include <filesystem>


Player::Player()
{

	add_texture_to_snake("../../../../assets/head_left.png", 0);


}

Player::~Player()
{
}

void Player::add_texture_to_snake(const std::filesystem::path& filename, int index)
{
	m_snake_textures.push_back((std::make_unique<sf::Texture>()));

	if (!m_snake_textures.back()->loadFromFile(filename))
	{
		// Handle the error, for example, by throwing an exception
		m_snake_textures.pop_back();
		throw std::runtime_error("Failed to load texture from file: ");
	}
	auto sprite = std::make_unique<sf::Sprite>(*m_snake_textures[index]);
	m_sprites_snake.push_back(std::move(sprite));

}

void Player::render_player(sf::RenderWindow& window)
{
	for (auto& sprite : m_sprites_snake)
	{
		window.draw(*sprite);
	}
}

void Player::center_player_on_screen(sf::RenderWindow& window)
{
	sf::Vector2u windows_size = window.getSize();
	for (auto& sprite : m_sprites_snake)
	{
		float x = (windows_size.x - sprite->getGlobalBounds().size.x) / 2.00f;
		float y = (windows_size.y - sprite->getGlobalBounds().size.y) / 2.00f;
		sprite->setPosition(sf::Vector2f(x, y));
		m_x = x;
		m_y = y;
	}
}

void Player::user_input()
{
	bool ismoving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		set_speed(-300.0f, 0.0f);
		ismoving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		set_speed(300.0, 0.0f);
		ismoving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		set_speed(0.0f, -300.0f);
		ismoving = true;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		set_speed(0.0f, 300.0f);
		ismoving = true;
	}

	if (!ismoving)
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
	}
}

void Player::move_player(float& deltatime)
{
	user_input();

	m_x = m_x + m_vx * deltatime;
	m_y = m_y + m_vy * deltatime;

	//float offset = 0.0f;
	for (auto& sprite : m_sprites_snake)
	{
		//auto sprite_size = sprite->getTexture().getSize();
		sprite->setPosition({ m_x,m_y });
		//offset = sprite_size.x;
	}
	
}

void Player::set_speed(float vx, float vy)
{
	m_vx = vx;
	m_vy = vy;

}

void Player::wrap_around_screen(sf::RenderWindow& window)
{

	sf::Vector2u windows_size = window.getSize();
	sf::Vector2f new_position_left(window.getSize().x, 0.0f);
	sf::Vector2f new_position_top(window.getSize().y, 0.0f);


	if (m_sprites_snake.begin()->get()->getPosition().x > windows_size.x)
	{
		m_sprites_snake.begin()->get()->setPosition({ 0.0f,get_position_y()});
		m_x = 0.0f;
	}
	else if (m_sprites_snake.begin()->get()->getPosition().x < 0.0f)
	{
		m_sprites_snake.begin()->get()->setPosition(new_position_left);
		m_x = windows_size.x;
		
	}
	else if (m_sprites_snake.begin()->get()->getPosition().y < 0.0f)
	{
		m_sprites_snake.begin()->get()->setPosition(new_position_top);
		m_y = windows_size.y;

	}
	else if (m_sprites_snake.begin()->get()->getPosition().y > windows_size.y)
	{
		m_sprites_snake.begin()->get()->setPosition({ get_position_x(), 0.0f });
		m_y = 0.0f;

	}


}

float Player::get_position_x()
{
	return m_x;
}

float Player::get_position_y()
{
	return m_y;
}

void Player::check_collision_aabb()
{
}


