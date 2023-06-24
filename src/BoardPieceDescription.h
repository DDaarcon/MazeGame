#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class BoardPiece;

class BoardPieceDescription {
public:
	//BoardPieceDescription(std::string name_ = "None", const int frames_ = 1, const bool solid_ = true) : blockName(name_), _currentAnimationFrame(0), solid(solid_), amountOfFrames(frames_), texture(nullptr) {
	//}
	//virtual ~BoardPieceDescription() {}

	//void draw(sf::RenderWindow&) const;

	//void setTexture(sf::Texture* texture_) {
	//	texture = texture_;
	//	// std::cout << blockName << "\'s texture\'s dimensions - " << texture->getSize().x << "x" << texture->getSize().y << '\n';
	//	reloadTexture();
	//}
	//sf::Texture* getTexture() const { return texture; }
	//// void setSpecialTexture(SpecialTextures spec_);

	//int nextFrame();
	//void setAmountOfFrames(int amount) { amountOfFrames = amount; }

	//void setSize(const sf::Vector2f& size_) { _displayable.setSize(size_); }
	//sf::Vector2f getSize() const { return _displayable.getSize(); }
	//void setAbsolutePosition(const sf::Vector2f& pos_) { _displayable.setPosition(pos_); }
	//sf::Vector2f getAbsolutePosition() const { return _displayable.getPosition(); }
	//void setSolid(const bool solid_) { solid = solid_; }
	//bool getSolid() const { return solid; }
	//void setPosAtStage(const sf::Vector2i& position_) { currentPosAtStage = position_; }
	//sf::Vector2i getPosAtStage() const { return currentPosAtStage; }

	//BoardPieceDescription& operator=(const BoardPieceDescription& block);

protected:

private:
	sf::RectangleShape _displayable;
	std::shared_ptr<sf::Texture> _texture;
	std::shared_ptr<BoardPiece> _piece;

	bool _isSolid;

	bool _isAnimated;
	int _currentAnimationFrame;
	int _amountOfAnimationFrames;


	/*void reloadTexture() {
		_displayable.setTexture(texture.get(), true);
		_displayable.setTextureRect(sf::IntRect(0, 0, texture->getSize().x / amountOfFrames, texture->getSize().y));
	}*/
};