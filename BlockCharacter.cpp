#include "headers/BlockCharacter.h"
								// BLOCK CLASS BEGIN

// void Block::setSpecialTexture(Block::SpecialTextures spec_){
// 	switch (spec_){
// 		case SpecialTextures::Bordered:
// 			texture->loadFromFile("blank_bordered.png");
// 			reloadTexture();
// 			break;
// 		case SpecialTextures::NonBordered:
// 			texture->loadFromFile("blank.png");
// 			reloadTexture();
// 			break;
// 	}
// }
								
void Block::draw(sf::RenderWindow& w) const
{
	w.draw(block);
}

int Block::nextFrame(){
	if (amountOfFrames > 1){
		
		int sizeOfFrameX = texture->getSize().x / amountOfFrames;
		block.setTextureRect(sf::IntRect(sizeOfFrameX * (currentFrame), 0, sizeOfFrameX, texture->getSize().y));
		
		if (currentFrame++ >= amountOfFrames - 1)
			currentFrame = 0;
		
	}
	
	return currentFrame;
}

Block& Block::operator=(const Block& block_) {
	if (&block_ != this) {
		block =  block_.block;
		texture = block_.texture;
		
		blockName = block_.blockName;
		currentFrame = block_.currentFrame;
		currentPosAtStage = block_.currentPosAtStage;
		solid = block_.solid;
		amountOfFrames = block_.amountOfFrames;
	}
	return *this;
}
// BLOCK CLASS END
								// CHARACTER CLASS BEGIN
bool Character::move(Character::Direction dir_, Stage& stage_){
	if (dir_ == Direction::Bottom){
		if (currentPosAtStage.y < stage_.getSizeOfStage().y - 1) {
			if (stage_.getBlock(sf::Vector2i(currentPosAtStage.x, currentPosAtStage.y + 1)) == nullptr || 
				!stage_.getBlock(sf::Vector2i(currentPosAtStage.x, currentPosAtStage.y + 1))->getSolid()){
				stage_.removeBlock(currentPosAtStage);
				if (previousBlock != nullptr) {
					stage_.setBlockStatic(currentPosAtStage, previousBlockRow);
				}
				stage_.setBlockDynamic(sf::Vector2i(currentPosAtStage.x, currentPosAtStage.y + 1), *this);
				return true;
			} else
				std::cout << "Solid at " << currentPosAtStage.x << ", " << currentPosAtStage.y + 1 << "!\n";
		} else 
			std::cout << "Behind the stage at " << currentPosAtStage.x << ", " << currentPosAtStage.y + 1 << "!\n";
	} else if (dir_ == Direction::Right){
		if (currentPosAtStage.x < stage_.getSizeOfStage().x - 1) {
			if (stage_.getBlock(sf::Vector2i(currentPosAtStage.x + 1, currentPosAtStage.y)) == nullptr || 
				!stage_.getBlock(sf::Vector2i(currentPosAtStage.x + 1, currentPosAtStage.y))->getSolid()){
				stage_.removeBlock(currentPosAtStage);
				if (previousBlock != nullptr) {
					stage_.setBlockStatic(currentPosAtStage, previousBlockRow);
				}
				stage_.setBlockDynamic(sf::Vector2i(currentPosAtStage.x + 1, currentPosAtStage.y), *this);
				return true;
			} else
				std::cout << "Solid at " << currentPosAtStage.x + 1 << ", " << currentPosAtStage.y << "!\n";
		} else 
			std::cout << "Behind the stage at " << currentPosAtStage.x + 1 << ", " << currentPosAtStage.y << "!\n";
	} else if (dir_ == Direction::Left){
		if (currentPosAtStage.x > 0) {
			if (stage_.getBlock(sf::Vector2i(currentPosAtStage.x - 1, currentPosAtStage.y)) == nullptr || 
				!stage_.getBlock(sf::Vector2i(currentPosAtStage.x - 1, currentPosAtStage.y))->getSolid()){
				stage_.removeBlock(currentPosAtStage);
				if (previousBlock != nullptr) {
					stage_.setBlockStatic(currentPosAtStage, previousBlockRow);
				}
				stage_.setBlockDynamic(sf::Vector2i(currentPosAtStage.x - 1, currentPosAtStage.y), *this);
				return true;
			} else
				std::cout << "Solid at " << currentPosAtStage.x - 1 << ", " << currentPosAtStage.y << "!\n";
		} else 
			std::cout << "Behind the stage at " << currentPosAtStage.x - 1 << ", " << currentPosAtStage.y << "!\n";
	}
	if (dir_ == Direction::Top){
		if (currentPosAtStage.y > 0) {
			if (stage_.getBlock(sf::Vector2i(currentPosAtStage.x, currentPosAtStage.y - 1)) == nullptr || 
				!stage_.getBlock(sf::Vector2i(currentPosAtStage.x, currentPosAtStage.y - 1))->getSolid()){
				stage_.removeBlock(currentPosAtStage);
				if (previousBlock != nullptr) {
					stage_.setBlockStatic(currentPosAtStage, previousBlockRow);
				}
				stage_.setBlockDynamic(sf::Vector2i(currentPosAtStage.x, currentPosAtStage.y - 1), *this);
				return true;
			} else
				std::cout << "Solid at " << currentPosAtStage.x << ", " << currentPosAtStage.y - 1 << "!\n";
		} else 
			std::cout << "Behind the stage at " << currentPosAtStage.x << ", " << currentPosAtStage.y - 1 << "!\n";
	}
	return false;
}

void Character::keyDetect(Stage& st_, sf::Keyboard::Key left_, sf::Keyboard::Key top_, sf::Keyboard::Key right_, sf::Keyboard::Key bottom_){
	if(sf::Keyboard::isKeyPressed(top_) && !moveDirections[0]){	//UP
		move(Character::Direction::Top, st_);
		moveDirections[0] = true;
	} else if (!sf::Keyboard::isKeyPressed(top_) && moveDirections[0])
		moveDirections[0] = false;
	
	if(sf::Keyboard::isKeyPressed(left_) && !moveDirections[1]){	//LEFT
		move(Character::Direction::Left, st_);
		moveDirections[1] = true;
	} else if (!sf::Keyboard::isKeyPressed(left_) && moveDirections[1])
		moveDirections[1] = false;
	
	if(sf::Keyboard::isKeyPressed(bottom_) && !moveDirections[2]){	//DOWN
		move(Character::Direction::Bottom, st_);
		moveDirections[2] = true;
	} else if (!sf::Keyboard::isKeyPressed(bottom_) && moveDirections[2])
		moveDirections[2] = false;
	
	if(sf::Keyboard::isKeyPressed(right_) && !moveDirections[3]){	//RIGHT
		move(Character::Direction::Right, st_);
		moveDirections[3] = true;
	} else if (!sf::Keyboard::isKeyPressed(right_) && moveDirections[3])
		moveDirections[3] = false;
}

void Character::setPreviousBlock(Block* block_) {
	if (block_ != nullptr) {
		previousBlockRow = *block_;
		previousBlock = &previousBlockRow;
	} else {
		previousBlock = nullptr;
	}
}
Block* Character::getPreviousBlock() const {
	return previousBlock;
}
void Character::removePreviousBlock() {
	previousBlock = nullptr;
}
// CHARACTER CLASS END


