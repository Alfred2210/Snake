#include "Game.h"


Game::Game(const sf::Vector2u& size)
	:m_resourceManager()
	, m_input()
	,m_worldSize(size),
	m_apple(),
	m_snake(size)
{
	loadAssets();
	m_snake.setHeadTexture(m_resourceManager.getTexture(TextureID::HEAD_LEFT));
	m_apple.setTexture(m_resourceManager.getTexture(TextureID::APPLE));
	m_apple.generate_random_position(m_worldSize);
	m_snake.setTailTexture(m_resourceManager.getTexture(TextureID::TAIL_LEFT));
}

void Game::loadAssets()
{
	//Head textures
	m_resourceManager.loadTexture(TextureID::HEAD_UP, "assets/head_up.png");
	m_resourceManager.loadTexture(TextureID::HEAD_DOWN, "assets/head_down.png");
	m_resourceManager.loadTexture(TextureID::HEAD_LEFT, "assets/head_left.png");
	m_resourceManager.loadTexture(TextureID::HEAD_RIGHT, "assets/head_right.png");

	//Body textures
	m_resourceManager.loadTexture(TextureID::BODY_HORIZONTAL, "assets/body_horizontal.png");
	m_resourceManager.loadTexture(TextureID::BODY_VERTICAL, "assets/body_vertical.png");
	m_resourceManager.loadTexture(TextureID::BODY_TOPLEFT, "assets/body_topleft.png");
	m_resourceManager.loadTexture(TextureID::BODY_TOPRIGHT, "assets/body_topright.png");
	m_resourceManager.loadTexture(TextureID::BODY_BOTTOMLEFT, "assets/body_bottomleft.png");
	m_resourceManager.loadTexture(TextureID::BODY_BOTTOMRIGHT, "assets/body_bottomright.png");

	//Tail textures
	m_resourceManager.loadTexture(TextureID::TAIL_UP, "assets/tail_up.png");
	m_resourceManager.loadTexture(TextureID::TAIL_DOWN, "assets/tail_down.png");
	m_resourceManager.loadTexture(TextureID::TAIL_LEFT, "assets/tail_left.png");
	m_resourceManager.loadTexture(TextureID::TAIL_RIGHT, "assets/tail_right.png");

	//Apple texture
	m_resourceManager.loadTexture(TextureID::APPLE, "assets/apple.png");


}

void Game::update(float dt)
{

	if(m_isGameOver) return;


	m_snake.setDirection(m_input.handleInput());
	
	m_timeSinceLastUpdate += dt;

	if(m_timeSinceLastUpdate >= m_updateInterval)
	{ 
		m_snake.update();
		m_snake.updateSprite(m_resourceManager);
		m_snake.updateTailSprite(m_resourceManager);

		checkCollision();

		m_timeSinceLastUpdate = 0.0f;
	}
}


void Game::render(sf::RenderWindow& window)
{
	m_snake.draw(window);
	m_apple.draw(window);
}

bool Game::checkWallCollision()
{
	auto pos = m_snake.getPosition();

	return (pos.x < 0) || (pos.y < 0) || (pos.x >= m_worldSize.x) || (pos.y >= m_worldSize.y);

}
bool Game::checkAppleCollision()
{
	auto snakePos = m_snake.getPosition();
	auto applePos = m_apple.getPosition();

	return snakePos == applePos;
}

void Game::checkCollision()
{

	auto selfCollision = m_snake.checkSelfCollision();

	if (checkWallCollision() || selfCollision)
	{
		m_isGameOver = true;
	}

	if (checkAppleCollision())
	{
		m_snake.grow();
		m_apple.generate_random_position(m_worldSize);
	}
}
