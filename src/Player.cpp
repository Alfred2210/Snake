#include "Player.h"
#include <iostream>
#include <filesystem>


Player::Player()
{

	add_texture_to_snake("../../../../assets/head_left.png", 0);
	add_texture_to_snake("../../../../assets/tail_right.png", 1);
	//add_texture_to_snake("../../../../assets/body_horizontal.png", 2);
	change_texture("../../../../assets/head_right.png", 0);
	change_texture("../../../../assets/head_down.png", 1);
	change_texture("../../../../assets/head_up.png", 2);
	change_texture("../../../../assets/tail_left.png", 3);
	change_texture("../../../../assets/tail_down.png", 4);
	change_texture("../../../../assets/tail_up.png", 5);

}

Player::~Player()
{
}

void Player::add_texture_to_snake(const std::filesystem::path& filename, int index)
{
	m_snake_textures.push_back((std::make_unique<sf::Texture>()));

	if (!m_snake_textures.back()->loadFromFile(filename))
	{

		m_snake_textures.pop_back();
		throw std::runtime_error("Failed to load texture from file: ");
	}
	auto sprite = std::make_unique<sf::Sprite>(*m_snake_textures[index]);
	m_sprites_snake.push_back(std::move(sprite));

}

void Player::change_texture(const std::filesystem::path& filename, int index)
{
	m_snake_textures_change.push_back((std::make_unique<sf::Texture>()));

	if (!m_snake_textures_change.back()->loadFromFile(filename))
	{

		m_snake_textures_change.pop_back();
		throw std::runtime_error("Failed to load texture from file: ");
	}

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
	float x = (windows_size.x - m_sprites_snake.begin()->get()->getLocalBounds().size.x) / 2.0f;
	float y = (windows_size.y - m_sprites_snake.begin()->get()->getLocalBounds().size.y) / 2.0f;
	m_sprites_snake.begin()->get()->setPosition(sf::Vector2f(x, y));

	float sprite_width = m_sprites_snake.front()->getLocalBounds().size.x;
	float sprite_height = m_sprites_snake.front()->getLocalBounds().size.y;

	float temp_x = x;
	float temp_y = y;

	for (auto& sprite : m_sprites_snake)
	{
		sprite->setPosition(sf::Vector2f(temp_x, temp_y));
		temp_x += sprite_width;
	}
	m_x = x;
	m_y = y;


}

void Player::handle_user_input()
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

void Player::update_snake_movement(float& deltatime)
{
	handle_user_input();
	float newposition_x = m_x + m_vx * deltatime;
	float newposition_y = m_y + m_vy * deltatime;

	auto temp = m_sprites_snake.front()->getPosition();
	m_sprites_snake.front()->setPosition({ newposition_x, newposition_y });

	float sprite_width = m_sprites_snake.front()->getLocalBounds().size.x;
	float sprite_height = m_sprites_snake.front()->getLocalBounds().size.y;

	

	for (auto it = std::next(m_sprites_snake.begin()); it != m_sprites_snake.end(); it++)
	{
		auto current_pos = (*it)->getPosition();
		if (m_vx > 0)
		{
			m_sprites_snake.front()->setTexture(*m_snake_textures_change[0]);
			m_sprites_snake.back()->setTexture(*m_snake_textures_change[3]);
		
			(*it)->setPosition(sf::Vector2f(temp.x - sprite_width, temp.y));
		}
		else if (m_vx < 0)
		{
			m_sprites_snake.front()->setTexture(*m_snake_textures[0]);
			m_sprites_snake.back()->setTexture(*m_snake_textures[1]);
			(*it)->setPosition(sf::Vector2f(temp.x + sprite_width, temp.y));
		}
		else if (m_vy > 0)
		{
			m_sprites_snake.front()->setTexture(*m_snake_textures_change[1]);
			m_sprites_snake.back()->setTexture(*m_snake_textures_change[5]);
			(*it)->setPosition(sf::Vector2f(temp.x, temp.y - sprite_width));
		}
		else if (m_vy < 0)
		{
			m_sprites_snake.front()->setTexture(*m_snake_textures_change[2]);
			m_sprites_snake.back()->setTexture(*m_snake_textures_change[4]);
			(*it)->setPosition(sf::Vector2f(temp.x, temp.y + sprite_width));
		}

		temp = current_pos;
	}

	m_x = newposition_x;
	m_y = newposition_y;

	std::cout << "Position x : " << m_sprites_snake.front()->getPosition().x << " " << "Position y : " << m_sprites_snake.front()->getPosition().y << std::endl;

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
		m_sprites_snake.begin()->get()->setPosition({ 0.0f,get_position_y() });
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

void Player::check_collision_with_apple(Objet& apple, sf::RenderWindow& window)
{

	sf::FloatRect bounding_box_snake = m_sprites_snake.begin()->get()->getGlobalBounds();
	sf::FloatRect boundingBox_box_apple = apple.get_apple_sprite()->getGlobalBounds();


	if (bounding_box_snake.findIntersection(boundingBox_box_apple))
	{
		apple.generate_random_position(window);
	}

}



