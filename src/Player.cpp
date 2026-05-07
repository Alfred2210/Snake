#include "Player.h"
#include <iostream>
#include "TextureID.h"


Player::Player(const sf::Vector2u& worldSize)
	: 
	m_direction(Direction::LEFT),
	m_headSprite(std::nullopt),
	m_tailSprite(std::nullopt),
	m_shouldGrow(false)
{
	float startX = (worldSize.x / 32 / 2) * 32.0f;
	float startY = (worldSize.y / 32 / 2) * 32.0f;
	m_positions = { { startX, startY }, { startX +32.0f, startY } };
}

void Player::draw(sf::RenderWindow& window)
{
	if (m_headSprite.has_value())
	{
		window.draw(*m_headSprite);
	}

	if (m_tailSprite.has_value())
	{
		window.draw(*m_tailSprite);
	}

}

void Player::update()
{
	move();
	if (m_headSprite.has_value())
	{
		m_headSprite->setPosition(m_positions.front());
	}

	if (m_tailSprite.has_value())
	{

		m_tailSprite->setPosition(m_positions.back());
	}

}

void Player::move()
{
	if (m_positions.empty())
		return;

	auto head = m_positions.front();
	auto newHead = head;
	float speed = 32.0f;
	switch (m_direction)
	{
	case Direction::UP:
		newHead = { newHead.x, newHead.y - speed };
		break;
	case Direction::DOWN:
		newHead = { newHead.x, newHead.y + speed };
		break;
	case Direction::RIGHT:
		newHead = { newHead.x + speed , newHead.y };
		break;
	case Direction::LEFT:
		newHead = { newHead.x - speed, newHead.y };
		break;
	default:
		break;
	}


	m_positions.push_front(newHead);
	if(m_shouldGrow)
	{
		m_shouldGrow = false;
	}
	else
		m_positions.pop_back();
}

void Player::grow()
{

	m_shouldGrow = true;
}


void Player::setDirection(Direction direction)
{
	if ((direction == Direction::UP && m_direction == Direction::DOWN) || (direction == Direction::DOWN && m_direction == Direction::UP) ||
		(direction == Direction::LEFT && m_direction == Direction::RIGHT) || (direction == Direction::RIGHT && m_direction == Direction::LEFT) || direction == Direction::NONE)
	{
		return;
	}

	m_direction = direction;
}

void Player::setPosition(sf::Vector2f position)
{
	m_positions.front() = position;
}



sf::Vector2f Player::getPosition() const
{
	return m_positions.front();
}

void Player::setHeadTexture(const sf::Texture& texture)
{

	m_headSprite.emplace(texture);

}

void Player::setTailTexture(const sf::Texture& texture)
{

	m_tailSprite.emplace(texture);
}


void Player::updateSprite(const ResourceManager& resourceManager)
{
	// si le sprite de la tête n'existe pas, on ne fait rien

	if (!m_headSprite.has_value())
		return;



	switch (m_direction)
	{
	case Direction::UP:
		m_headSprite->setTexture(resourceManager.getTexture(TextureID::HEAD_UP));
		break;
	case Direction::DOWN:
		m_headSprite->setTexture(resourceManager.getTexture(TextureID::HEAD_DOWN));
		break;
	case Direction::RIGHT:
		m_headSprite->setTexture(resourceManager.getTexture(TextureID::HEAD_RIGHT));
		break;
	case Direction::LEFT:
		m_headSprite->setTexture(resourceManager.getTexture(TextureID::HEAD_LEFT));
		break;
	default:
		break;
	}


}

void Player::updateTailSprite(const ResourceManager& resourceManager)
{

	if (m_positions.size() < 2 || !m_tailSprite.has_value()) return;

	auto tail = m_positions.back();

	auto beforeTail = m_positions[m_positions.size() - 2];

	
	if (beforeTail.x < tail.x)
	{
		m_tailSprite->setTexture(resourceManager.getTexture(TextureID::TAIL_RIGHT));

	}
	else if (beforeTail.x > tail.x)
	{
		m_tailSprite->setTexture(resourceManager.getTexture(TextureID::TAIL_LEFT));
	}
	else if (beforeTail.y < tail.y)
	{
		m_tailSprite->setTexture(resourceManager.getTexture(TextureID::TAIL_DOWN));
	}
	else if (beforeTail.y > tail.y)
	{
		m_tailSprite->setTexture(resourceManager.getTexture(TextureID::TAIL_UP));

	}


}

bool Player::checkSelfCollision() const
{
	auto head = m_positions.front();
	for (size_t i = 1; i < m_positions.size(); i++)
	{
		if (head == m_positions[i] )
			return true;
	}

	return false;
}

