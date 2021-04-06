#include "headers/Other.h"
#include <fstream>

// TEXTUREHANLDER CLASS BEGIN
std::map<std::string, sf::Texture> TextureHandler::textureHandling;
const std::string TextureHandler::dictionary = "images/";
sf::Texture* TextureHandler::getTextureAddress(const std::string& fileName, const std::string& extension) {
	try {
		sf::Texture* rtnTxt = &(textureHandling.at(fileName));
		return rtnTxt;
	} catch (...) {
		if (extension != "") {
			sf::Texture tempTexture;
			// error may occur due to pointer - to delete if not
			if (tempTexture.loadFromFile(dictionary + fileName + "." + extension)) {
				sf::Texture* rtnTxt = &textureHandling[fileName];
				*rtnTxt = tempTexture;
				return rtnTxt;
			} else {
				std::cout << "Failed to load from file" << std::endl;
				return nullptr;
			}
				
		}
		else {
			std::cout << "No extension found" << std::endl;
			return nullptr;
		}
	}
}

void TextureHandler::load(const std::string& filename, const std::string& extension) {
	if (!textureHandling.count(filename)) {
		sf::Texture tempTexture;
		if (tempTexture.loadFromFile(dictionary + filename + "." + extension))
			textureHandling[filename] = tempTexture;
	}
}

bool TextureHandler::isLoaded(const std::string& fileName) {
	try {
		textureHandling.at(fileName);
		return true;
	} catch (...) {
		return false;
	}
}


// TEXTUREHANDLER CLASS END

bool StageLoader::loadFromFile(const std::string& filename_, Stage& stage_) {
	std::ifstream file;
	file.open(filename_);
	std::map<char, std::string> textures;
	int amountOfTex;
	file >> amountOfTex;
	while (amountOfTex--) {
		char tempCh;
		std::string tempString;
		file >> tempCh >> tempString;
		size_t dot = tempString.find('.');
		std::string name = tempString.substr(0, dot);
		std::string extension = tempString.substr(dot + 1);
		TextureHandler::load(name, extension);
		textures[tempCh] = name;
	}
	int x, y;
	file >> x >> y;
	Stage stage(sf::Vector2i(x, y), stage_.getSizeOfBlock(), stage_.getPositionAtWindow());
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			char tempCh;
			file >> tempCh;
			if (tempCh == '0')
				continue;
			try {
				std::string* name = &textures.at(tempCh);
				Block tempBlock(*name);
				tempBlock.setTexture(TextureHandler::getTextureAddress(*name));
				stage.setBlockStatic(sf::Vector2i(j, i), tempBlock);
			} catch (...) {
				std::cout << "Unexpected character in file during stage loading: " << tempCh << std::endl;
				file.close();
				return false;
			}
		}
	}
	stage_ = stage;
	file.close();
	return true;
}