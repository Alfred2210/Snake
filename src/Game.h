#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"


class Game
{
public:


	void render(sf::RenderWindow& window);
	void center_player_on_screen(sf::RenderWindow& window);
private :

	Player m_player;

};

