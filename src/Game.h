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
	bool checkAppleCollision();
	void checkCollision();



private:
    ResourceManager m_resourceManager;
    Input m_input;
    sf::Vector2u m_worldSize;
    Apple m_apple;
    Player m_snake;
    float m_timeSinceLastUpdate = 0.0f;
    float m_updateInterval = 0.2f;
    bool m_isGameOver = false;
};

