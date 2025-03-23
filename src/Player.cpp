#include "Player.h"
#include <iostream>
#include <filesystem>


Player::Player()
	:m_vx(0.00), m_vy(0.00),m_x(0.00),m_y(0.00)
{
	
	add_texture("../../../../assets/head_left.png", 0);
	

}

Player::~Player()
{
}

void Player::add_texture(std::filesystem::path filename, int index)
{
	m_snake_texture.push_back((std::make_unique<sf::Texture>()));

	if (!m_snake_texture.back()->loadFromFile(filename))
	{
		// Handle the error, for example, by throwing an exception
		m_snake_texture.pop_back();
		throw std::runtime_error("Failed to load texture from file: ");
	}
	auto sprite = std::make_unique<sf::Sprite>(*m_snake_texture[index]);
	m_sprite_snake.push_back(std::move(sprite));

}

void Player::draw(sf::RenderWindow& window)
{
    for (auto& sprite : m_sprite_snake)
    {
		window.draw(*sprite);
    }
}

void Player::center_player(sf::RenderWindow& window)
{
    sf::Vector2u windows_size = window.getSize();
    for (auto& sprite : m_sprite_snake)
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
        set_speed(-200.0f, 0.0f);
        ismoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        set_speed(200.0, 0.0f);
        ismoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        set_speed(0.0f, -200.0f);
        ismoving = true;

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        set_speed(0.0f, 200.0f);
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
   /* m_vx += m_ax * deltatime;
	m_vy += m_ay * deltatime;*/

    m_x = m_x + m_vx * deltatime;
    m_y = m_y + m_vy * deltatime;

    //float offset = 0.0f;
    for (auto& sprite : m_sprite_snake)
    {
        //auto sprite_size = sprite->getTexture().getSize();
        sprite.get()->setPosition({m_x,m_y});
        //offset = sprite_size.x;
    }

    std::cout << "Player position: (" << m_x << ", " << m_y << ")" << std::endl;

}

void Player::set_speed(float vx, float vy)
{
    m_vx = vx;
    m_vy = vy;

}


