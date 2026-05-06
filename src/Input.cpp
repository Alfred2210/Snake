#include "Input.h"
#include <SFML/Graphics.hpp>

Direction Input::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		return Direction::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		return  Direction::RIGHT;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		return Direction::UP;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		return Direction::DOWN;
	}

	return Direction::NONE;
}
