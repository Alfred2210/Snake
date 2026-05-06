#include "ResourceManager.h"



void ResourceManager::loadTexture(TextureID id, const std::string& path)
{
	if (!m_textures[static_cast<size_t>(id)].loadFromFile(path))
	{
		throw std::runtime_error("Failed to load texture: " + path);
	}
}

const sf::Texture& ResourceManager::getTexture(TextureID id) const
{

	if (static_cast<size_t>(id) >= static_cast<size_t>(TextureID::COUNT))
	{
		throw std::out_of_range("Invalid out of range TextureID");
	}
	return m_textures[static_cast<size_t>(id)];
}
