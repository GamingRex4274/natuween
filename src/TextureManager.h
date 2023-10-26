#include <memory>
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
public:
	static std::shared_ptr<sf::Texture> acquire(const std::string& filename);
	static void clean();
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturePtrs;
};

#endif