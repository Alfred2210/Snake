#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void add_texture_to_snake(const std::filesystem::path &filename , int index);
	void render_player(sf::RenderWindow& window);
	void center_player_on_screen(sf::RenderWindow& window);
	void user_input();
	void move_player(float &deltatime);
	void set_speed(float vx, float vy);
	void wrap_around_screen(sf::RenderWindow& window);
	float get_position_x();
	float get_position_y();
	void check_collision_aabb();
private:
	std::list< std::unique_ptr<sf::Sprite>> m_sprites_snake;
	std::vector<std::unique_ptr<sf::Texture>> m_snake_textures;

	bool m_is_moving;
	float m_x, m_y, m_vx, m_vy;
};
