#pragma once
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class ITextureLoader {
public:
	virtual std::unique_ptr<sf::Texture> load(const std::string path) = 0;
};

class TextureLoader : public ITextureLoader {
public:
	TextureLoader() = delete;
	TextureLoader(const std::string& baseDictionary);

	std::unique_ptr<sf::Texture> load(const std::string path);

private:
	const std::string& _baseDictionary;
};