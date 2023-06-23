#pragma once

#include <string>
#include <map>
#include "Stage.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Stage;
// TEXTUREHANDLER CLASS BEGIN

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