#include "SFML/Graphics.hpp"
#include "TextureLoader.h"
#include <map>
#include <string>
#include <iostream>
#include <filesystem>
#include <exception>

namespace fs = std::filesystem;


TextureLoader::TextureLoader(const std::string& baseDictionary) : _baseDictionary(baseDictionary)
{
}

std::unique_ptr<sf::Texture> TextureLoader::load(const std::string path)
{
	fs::path filePath(path);

	if (!fs::exists(filePath))
		throw std::exception(("File " + path + " not found!").c_str());

	auto texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(_baseDictionary + path))
		throw std::exception(("File " + path + " exists, but could not be loaded!").c_str());

	return texture;
}


#if false
sf::Texture* TextureLoader::getTextureAddress(const std::string& fileName, const std::string& extension) {
	try {
		return &(s_storage.at(fileName));
	}
	catch (...) {
		if (extension != "") {
			sf::Texture tempTexture;
			fs::path textureFile(_baseDictionary);
			// error may occur due to pointer - to delete if not
			if (fs::exists(textureFile) 
				&& tempTexture.loadFromFile(_baseDictionary + fileName + "." + extension)) 
			{
				sf::Texture* rtnTxt = &s_storage[fileName];
				*rtnTxt = tempTexture;
				return rtnTxt;
			}
			else {
				std::cerr << "Failed to load from file" << std::endl;
				return nullptr;
			}

		}
		else {
			std::cerr << "No extension found" << std::endl;
			return nullptr;
		}
	}
}

std::unique_ptr<sf::Texture> TextureLoader::getTextureAddressRedesign(const std::string& fileName, const std::string& extension) {
	try {
		return std::make_unique<sf::Texture>(s_storage.at(fileName));
	}
	catch (...) {
		if (extension != "") {
			sf::Texture tempTexture;
			fs::path textureFile(_baseDictionary);
			// error may occur due to pointer - to delete if not
			if (fs::exists(textureFile)
				&& tempTexture.loadFromFile(_baseDictionary + fileName + "." + extension))
			{
				sf::Texture* rtnTxt = &s_storage[fileName];
				*rtnTxt = tempTexture;
				return std::make_unique<sf::Texture>();
			}
			else {
				std::cerr << "Failed to load from file" << std::endl;
				return nullptr;
			}

		}
		else {
			std::cerr << "No extension found" << std::endl;
			return nullptr;
		}
	}
}

std::unique_ptr<sf::Texture> loadTexture(const std::string& fileName) {
	return std::make_unique<sf::Texture>();
}


void TextureLoader::loadInAdvance(const std::string& filename, const std::string& extension) {
	if (s_storage.count(filename) > 0) {
		sf::Texture tempTexture;
		if (tempTexture.loadFromFile(_baseDictionary + filename + "." + extension))
			s_storage[filename] = tempTexture;
	}
}

bool TextureLoader::isLoaded(const std::string& fileName) {
	auto valueItr = s_storage.find(fileName);
	return valueItr == s_storage.end();
}

#endif
