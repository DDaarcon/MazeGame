#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include <map>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::map<std::string, sf::Texture> TextureManager::s_storage;

const std::string TextureManager::dictionary = "images/";

sf::Texture* TextureManager::getTextureAddress(const std::string& fileName, const std::string& extension) {
	try {
		sf::Texture* rtnTxt = &(s_storage.at(fileName));
		return rtnTxt;
	}
	catch (...) {
		if (extension != "") {
			sf::Texture tempTexture;
			fs::path textureFile(dictionary);
			// error may occur due to pointer - to delete if not
			if (fs::exists(textureFile) 
				&& tempTexture.loadFromFile(dictionary + fileName + "." + extension)) 
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

std::unique_ptr<sf::Texture> loadTexture(const std::string& fileName) {
	return std::make_unique<sf::Texture>();
}

void TextureManager::load(const std::string& filename, const std::string& extension) {
	if (!s_storage.count(filename)) {
		sf::Texture tempTexture;
		if (tempTexture.loadFromFile(dictionary + filename + "." + extension))
			s_storage[filename] = tempTexture;
	}
}

bool TextureManager::isLoaded(const std::string& fileName) {
	auto valueItr = s_storage.find(fileName);
	return valueItr == s_storage.end();
}

