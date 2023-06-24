#include <cmath>
#include <iostream>
#include "BlockCharacter.h"
#include "Stage.h"
#include "Other.h"
#include "TextureLoader.h"

void mouseBlockCreator(sf::Window& window_, Stage& st_, Block& block_);

/* Possible errors:
 * ładowanie zbyt dużej ilości tych samych tekstur
 * 
 * 
 * 
 */


int main(){
	int screenHeight = 550;
	int screenWidth = 700;
	sf::String windowName = "Game";
	
	sf::View mainView(sf::FloatRect(100, 100, screenWidth /1.5f, screenHeight /1.5f));
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), windowName);
	window.setView(mainView);
	
	TimeDelay timeDelay;
	sf::Time timer;
	
	//	BEGIN OF TEST OF STAGE
	Character playerOne;
	//playerOne.setTexture(TextureLoader::getTextureAddress("pionek", "png"));
	
	Block BBBlock("Wall");
	//BBBlock.setTexture(TextureLoader::getTextureAddress("black_block", "png"));

	Block someBlock("Cauldron", 4);
	//someBlock.setTexture(TextureLoader::getTextureAddress("cauldron", "png"));
	
	Stage stage(sf::Vector2i(100, 100), sf::Vector2f(32, 32), sf::Vector2f(0, 0));
	StageLoader::loadFromFile("stage_to_load.txt", stage);
	

	stage.setBlockDynamic(sf::Vector2i(1, 2), playerOne);
	stage.setBlockDynamic(sf::Vector2i(15, 3), someBlock);
	// stage.makeBorders(BBBlock);
	//	END OF TEST OF STAGE
	

	// BEGIN OF GAME LOOP
	while(window.isOpen()){
		sf::Event event;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
			break;
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
			break;
		}//closing event
		
		window.clear(sf::Color(90, 90, 90, 250));
		
		mainView.move(sf::Vector2f((playerOne.getAbsolutePosition().x - mainView.getCenter().x + playerOne.getSize().x/2) * timeDelay.getTimeDelay().asSeconds() *  3,
			(playerOne.getAbsolutePosition().y - mainView.getCenter().y + playerOne.getSize().y/2) * timeDelay.getTimeDelay().asSeconds() * 3
		));
		
		
		playerOne.keyDetect(stage);
		// playerTwo.keyDetect(stage, sf::Keyboard::Key::Left, sf::Keyboard::Key::Up, sf::Keyboard::Key::Right, sf::Keyboard::Key::Down);
		
		stage.draw(window, mainView, playerOne.getPosAtStage());
		// backgroundStage.draw(window);
		
		
		timer += timeDelay.getTimeDelay();
		
		if (timer.asMilliseconds() >= 150){
			someBlock.nextFrame();
			timer = sf::Time::Zero;
		}
		
		// last operations
		window.setView(mainView);
		window.display();
		timeDelay.setTimeDelay();
	}
	// END OF GAME LOOP
	
	std::cout << "FINISHED WITH NO ERRORS\n";
	
	return 0;
}


// void mouseBlockCreator(sf::Window& window_, Stage& st_, Block& block_){	//Bezużyteczne po wprowadzeniu sf::View
// 	sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
// 	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
// // 		Check if mouse position is for sure in stage area
// 		if (mousePos.x >= st_.getPositionAtWindow().x &&
// 			mousePos.x <= st_.getSizeOfStage().y * st_.getSizeOfBlock().x &&
// 			mousePos.y >= st_.getPositionAtWindow().y &&
// 			mousePos.y <= st_.getSizeOfStage().x * st_.getSizeOfBlock().y
// 		){
// 			sf::Vector2i blockNr(((mousePos.y - (int)st_.getPositionAtWindow().y) / (int)st_.getSizeOfBlock().y),
// 					 ((mousePos.x - (int)st_.getPositionAtWindow().x) / (int)st_.getSizeOfBlock().x));
// 			st_.setBlock(blockNr, block_);
// 		}
// 	}
// }

