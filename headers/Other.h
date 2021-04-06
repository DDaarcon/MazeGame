#pragma once

#include <string>
#include <map>
#include "Stage.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Stage;
// TEXTUREHANDLER CLASS BEGIN
class TextureHandler {
	static std::map<std::string, sf::Texture> textureHandling;
	const static std::string dictionary;

	public:
	//fileName - key and file name without file extension
	static sf::Texture* getTextureAddress(const std::string& fileName, const std::string& extension = "");

	static void load(const std::string& fileName, const std::string& extension);

	static bool isLoaded(const std::string& name);


};
// TEXTUREHANDLER CLASS END

// TIMEDELAY CLASS BEGIN
class TimeDelay {
private:
	sf::Time frameLength;
	sf::Clock counter;
	
protected:
	
	
public:
	TimeDelay() {}
	~TimeDelay() {}
	
	sf::Time setTimeDelay() {
		frameLength = counter.restart();
		return frameLength;
	}
	
	sf::Time getTimeDelay() {
		return frameLength;
	}
	
};
// TIMEDELAY CLASS END
class StageLoader {
	
	public:

	static bool loadFromFile(const std::string& filename_, Stage& stage_);
};