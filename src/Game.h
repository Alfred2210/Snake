#pragma once

#include "ResourceManager.h"
#include "Player.h"
#include "Apple.h"
#include "Input.h"

class Game
{
public:

	Game(const sf::Vector2u& size);
	void loadAssets();
	void update(float dt);
	void render(sf::RenderWindow& window);
	bool checkWallCollision();
private:
	ResourceManager m_resourceManager;
	Input m_input;
	Apple m_apple;
	Player m_snake;
	float m_timeSinceLastUpdate = 0.0f;
	float m_updateInterval = 0.2f;
	sf::Vector2u m_worldSize;
	bool m_isGameOver = false;
};

