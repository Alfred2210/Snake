#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void add_texture(std::filesystem::path, int index);
	void draw(sf::RenderWindow& window);
	void center_player(sf::RenderWindow& window);
	void user_input();
	void move_player(float &deltatime);
	void set_speed(float vx, float vy);
private:
	std::list< std::unique_ptr<sf::Sprite>> m_sprite_snake;
	std::vector<std::unique_ptr<sf::Texture>> m_snake_texture;

	bool is_moving;
	float m_x,m_y,m_vx,m_vy,m_ax,m_ay;
};
