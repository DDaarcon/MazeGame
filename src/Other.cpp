#include "Other.h"
#include "TextureManager.h"
#include <fstream>

// TEXTUREHANLDER CLASS BEGIN
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
		TextureManager::load(name, extension);
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
				tempBlock.setTexture(TextureManager::getTextureAddress(*name));
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

// bool StageLoader::loadFromFile(const std::string& filenameWithExtension, Stage& stage_) {
// 	std::ifstream inFile;
// 	inFile.open(filenameWithExtension);

// 	std::string line;
// 	std::getline(inFile, line);

// 	if (line == "") {
		
// 	}
// }