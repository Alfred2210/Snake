#pragma once

#include <array>
#include <string>
#include "TextureID.h"
#include <SFML/Graphics/Texture.hpp>


class ResourceManager
{
public:
	void loadTexture(TextureID id, const  std::string& path);
	const sf::Texture& getTexture(TextureID id) const;
private:

	std::array<sf::Texture, static_cast<size_t>(TextureID::COUNT)> m_textures;

};