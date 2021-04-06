#pragma once

#include <vector>

#include "BlockCharacter.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Block;

class Stage {
	/**
	 * Brak błędów
	 * 
	**/
private:
	sf::Vector2i sizeOfStage;	// x - table height (first []), y - table width (second [])
	sf::Vector2f sizeOfOne;	// size of one block in px (x and y normal)
	sf::Vector2f position0;	// absolute position of whole stage (x and y normal)
	enum CellState{
		STATIC,
		DYNAMIC,
		UNDEF
	};
	
protected:
	std::vector<std::vector<Block*>> blockArr;	// dynamic
	std::vector<std::vector<Block>> blockContainer;	// static
	std::vector<std::vector<CellState>> cellStates;

	
public:
	Stage(const sf::Vector2i& sizeOfStage_, const sf::Vector2f& sizeOfBlock_ , const sf::Vector2f& position0_ = sf::Vector2f(0, 0));
	~Stage();
	
	void makeBorders(Block& block_);
	
	void draw(sf::RenderWindow& w) const; // func sending command draw to every block in stage
	void draw(sf::RenderWindow& w, sf::View& view, const sf::Vector2i& relatedToCell) const;	// render only cell seen in window (performance +1000000 xd)
	void setBlockStatic(const sf::Vector2i& blockNr_, Block& block_);	// or bool as returning type	// first row, then which one in that row ([y][x])
	void setBlockDynamic(const sf::Vector2i& blockNr_, Block& block_);
	void removeBlock(const sf::Vector2i& blockNr_);
	Block* getBlock(const sf::Vector2i& blockNr_, CellState* getState = nullptr);
	sf::Vector2i getSizeOfStage() const {return sizeOfStage;}
	sf::Vector2f getSizeOfBlock() const {return sizeOfOne;}
	sf::Vector2f getPositionAtWindow() const {return position0;}

	Stage& operator=(Stage& stage_);
};