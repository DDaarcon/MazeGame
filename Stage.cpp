#include "headers/Stage.h"

#include <cmath>

Stage::Stage(const sf::Vector2i& sizeOfStage_, const sf::Vector2f& sizeOfBlock_ , const sf::Vector2f& position0_) : sizeOfStage(sizeOfStage_), sizeOfOne(sizeOfBlock_), position0(position0_){
	try {
        blockArr.resize(sizeOfStage.x);
        blockContainer.resize(sizeOfStage.x);
        cellStates.resize(sizeOfStage.x);
        for (int j = 0; j < sizeOfStage.x; j++){
            blockArr[j].resize(sizeOfStage.y);
            blockContainer[j].resize(sizeOfStage.y);
            cellStates[j].resize(sizeOfStage.y, CellState::UNDEF);
        }
    } catch (std::bad_alloc& e) {
        std::cout << "Error while trying to allocate memory for stage. " << e.what() << std::endl;
    }
}
Stage::~Stage(){
	
}

void Stage::draw(sf::RenderWindow& w) const
{
	for(int j = 0; j < sizeOfStage.x; j++)
		for (int i = 0; i < sizeOfStage.y; i++) {
            if (cellStates[j][i] == STATIC)
                blockContainer[j][i].draw(w);
            else if (cellStates[j][i] == DYNAMIC)
                blockArr[j][i]->draw(w);
        }
}
void Stage::draw(sf::RenderWindow& w, sf::View& view_, const sf::Vector2i& relatedToCell) const{
    const int RENDER_HIDDEN = 2;
    int sX, fX, sY, fY, ver, horiz;
    sf::Vector2u screenSize = w.getSize();
    ver = (int)(screenSize.y / sizeOfOne.y) / 2;
    horiz = (int)(screenSize.x / sizeOfOne.x) / 2;

    sY = std::max(0, relatedToCell.y - ver - RENDER_HIDDEN);
    fY = std::min(sizeOfStage.y, relatedToCell.y + ver + RENDER_HIDDEN);
    sX = std::max(0, relatedToCell.x - horiz - RENDER_HIDDEN);
    fX = std::min(sizeOfStage.x, relatedToCell.x + horiz + RENDER_HIDDEN);

    for(int j = sX; j < fX; j++)
		for (int i = sY; i < fY; i++) {
            if (cellStates[j][i] == STATIC)
                blockContainer[j][i].draw(w);
            else if (cellStates[j][i] == DYNAMIC)
                blockArr[j][i]->draw(w);
        }

}

void Stage::setBlockStatic(const sf::Vector2i& blockNr_, Block& block_)	// used when block can be copied to blockContainer/this func is used to set default blocks
{
    cellStates[blockNr_.x][blockNr_.y] = STATIC;
    sf::Vector2f pos(blockNr_.x * sizeOfOne.x, blockNr_.y * sizeOfOne.y);
	blockContainer[blockNr_.x][blockNr_.y] = block_;
	blockContainer[blockNr_.x][blockNr_.y].setSize(sizeOfOne);
	blockContainer[blockNr_.x][blockNr_.y].setPosAtStage(sf::Vector2i(blockNr_.x, blockNr_.y));
	blockContainer[blockNr_.x][blockNr_.y].setAbsolutePosition(pos);
}
void Stage::setBlockDynamic(const sf::Vector2i& blockNr_, Block& block_){	// used only if block that is applied to blockArr exists somewhere (for example Character)
    cellStates[blockNr_.x][blockNr_.y] = DYNAMIC;
	sf::Vector2f pos(blockNr_.x * sizeOfOne.x, blockNr_.y * sizeOfOne.y);
	blockArr[blockNr_.x][blockNr_.y] = &block_;
	blockArr[blockNr_.x][blockNr_.y]->setSize(sizeOfOne);
	blockArr[blockNr_.x][blockNr_.y]->setPosAtStage(sf::Vector2i(blockNr_.x, blockNr_.y));
	blockArr[blockNr_.x][blockNr_.y]->setAbsolutePosition(pos);
}
void Stage::removeBlock(const sf::Vector2i& blockNr_) {
    if (cellStates[blockNr_.x][blockNr_.y] == DYNAMIC)
        blockArr[blockNr_.x][blockNr_.y] = nullptr;
    cellStates[blockNr_.x][blockNr_.y] = UNDEF;
}
Block* Stage::getBlock(const sf::Vector2i& blockNr_, CellState* getState){	// x - row, y - which one in row
    #define CELL cellStates[blockNr_.x][blockNr_.y]
    if (getState != nullptr) 
        *getState = CELL;
    if (CELL == DYNAMIC)
	    return blockArr[blockNr_.x][blockNr_.y];
    else if (CELL == STATIC)
        return &(blockContainer[blockNr_.x][blockNr_.y]);
    else return nullptr;
}

void Stage::makeBorders(Block& block_){
	for (int i = 0; i < getSizeOfStage().y; i++){
		setBlockStatic(sf::Vector2i(0, i), block_);
		setBlockStatic(sf::Vector2i(getSizeOfStage().x - 1, i), block_);
	}
	for (int i = 1; i < getSizeOfStage().x - 1; i++){
		setBlockStatic(sf::Vector2i(i, 0), block_);
		setBlockStatic(sf::Vector2i(i, getSizeOfStage().y - 1), block_);
	}
}

// unnecessary i think
Stage& Stage::operator=(Stage& stage_) {
    if (&stage_ != this) {
		sizeOfStage = stage_.sizeOfStage;
        sizeOfOne = stage_.sizeOfOne;
        position0 = stage_.position0;
        blockArr = stage_.blockArr;
        blockContainer = stage_.blockContainer;
        cellStates = stage_.cellStates;
	}
	return *this;
}
