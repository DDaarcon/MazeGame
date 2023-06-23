#pragma once
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class TextureManager {
public:
	
	static sf::Texture* getTextureAddress(const std::string& fileName, const std::string& extension = "");

	static void load(const std::string& fileName, const std::string& extension);

	static bool isLoaded(const std::string& name);

private:
	static std::map<std::string, sf::Texture> s_storage;
	const static std::string dictionary;
};