#include "Objet.h"
#include <stdexcept> 
#include <iostream>
#include <random>

Objet::Objet()

{

    m_apple_texture = std::make_unique<sf::Texture>();
   
    if (!m_apple_texture->loadFromFile("../../../../assets/apple.png"))
    {
        throw std::runtime_error("Failed to load texture from file:");
    }
    std::cout << "Texture loaded successfully!" << std::endl;
    m_apple_sprite = std::make_unique<sf::Sprite>(*m_apple_texture);
    
}

void Objet::draw(sf::RenderWindow& window)
{
	window.draw(*m_apple_sprite);
}

void Objet::generate_random_position(sf::RenderWindow& window)
{
    std::random_device r;
    std::default_random_engine e1(r());

    int sprite_x = m_apple_sprite->getTexture().getSize().x;
    int sprite_y = m_apple_sprite->getTexture().getSize().y;

    std::uniform_int_distribution<int> uniform_dist_x(0, window.getSize().x-sprite_x);
    std::uniform_int_distribution<int> uniform_dist_y(0, window.getSize().y-sprite_y);
    int random_x = uniform_dist_x(e1);
    int random_y = uniform_dist_y(e1);

    m_apple_sprite->setPosition(sf::Vector2f(random_x, random_y));
   
}

void Objet::bound_red(sf::RenderWindow& window)  
{  
   sf::FloatRect boundingBox = m_apple_sprite->getGlobalBounds();  
   sf::RectangleShape rectangle(sf::Vector2f(boundingBox.size.x, boundingBox.size.y));  
   rectangle.setPosition(m_apple_sprite->getPosition());
   rectangle.setOutlineThickness(2.f); // Épaisseur de la bordure  
   rectangle.setOutlineColor(sf::Color::Red);  
   rectangle.setFillColor(sf::Color::Transparent); // Rendre l'intérieur transparent  

   window.draw(rectangle);  
}

std::unique_ptr<sf::Sprite> Objet::get_apple_sprite()
{
    return std::make_unique<sf::Sprite>(*m_apple_sprite);
}

