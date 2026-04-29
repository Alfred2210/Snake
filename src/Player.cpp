#include "Player.h"



Player::Player()
{


}

Player::~Player()
{
}



void Player::render(sf::RenderWindow& window)
{
	for (auto& sprite : m_sprites)
	{
		window.draw(sprite);
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

void Player::handle()
{
	bool ismoving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		setVelocity(-300.0f, 0.0f);
		//ismoving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		set_speed(300.0, 0.0f);
		//ismoving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		set_speed(0.0f, -300.0f);
		//ismoving = true;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		set_speed(0.0f, 300.0f);
		//ismoving = true;
	}

	if (ismoving)
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
	}


}

void Player::update(float dt)
{
	handle();
	m_x +=  m_vx * deltaTime;
	m_y += m_vy * deltaTime;

}

void Player::setVelocity(const sf::Vector2f& v)
{

}

sf::Vector2f Player::getPositions() const
{
	return sf::Vector2f();
}


void setVelocity(const sf::Vector2f& v) 
{

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


void Player::check_collision_with_apple(Objet& apple, sf::RenderWindow& window)
{

	sf::FloatRect bounding_box_snake = m_sprites_snake.begin()->get()->getGlobalBounds();
	sf::FloatRect boundingBox_box_apple = apple.get_apple_sprite()->getGlobalBounds();


	if (bounding_box_snake.findIntersection(boundingBox_box_apple))
	{
		apple.generate_random_position(window);
	}

}



