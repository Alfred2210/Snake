#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void add_texture(std::string filename, int index);
	void draw(sf::RenderWindow& window);
private:
	std::list< std::unique_ptr<sf::Sprite>> m_sprite_snake;
	std::vector<std::unique_ptr<sf::Texture>> m_snake_texture;
};
