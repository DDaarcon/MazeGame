#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <exception>

#include "Stage.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

/** ERRORS:
 * +Wyciek pamięci prawdopodobnie przy destruktorze klasy Stage (lub innej) ---- błąd w funkcji setBlockStatic
 * +Funkcja poruszająca postać niewłaściwie odczytuje wielkośc tablicy obiektu Stage
 * +Każda klatka w Stage zapisywana jest z właściwością solid
 * +Obiekty Block dostają niewłaściwe współrzędne do zmiennej currentPosAtStage - ?????
 * +Przy przenoszeniu wskaznika gracza potrzebne jest zapełnienie starego pola zwykłym obiektem Block
 * +Funkcja wykrywająca naciśnięcia przycisków wymaga przebudowania
 * +Obiekty domyślnie przypisywane do tablicy blockContainter (Stage) nie posiadają domyślnej tekstury TEST wyświetlanie blockContainter zamianst blockTab
 * 	!setTabDimensions/setBlockStatic error!
 * +Kopiowanie składowej texture w obiektach Block nie jest dokładne
 * 
 * OPTYMALIZACJA:
 * +setBlock - zamiana przsyłania przez wartość na przesyłanie przez referencję
 * +sf::Vector2<> na sf::Vector2<>&
 * -Zmniejszenie liczby obiektów sf::Textures, w klasie Block przechowywany jest wskaźnik do konkretnej tekstury zamiast jej kopii
 * ?Klasa TextureManager do przetrzymywania textur, textury zapisane w map z kluczami w postaci string (nazwy plikow w razie nie posiadania wczytanej textury)
 * 
 * PLANY:
 * -zapis i wczytywanie stanu Stage z pliku
 * +tworzenie obramowania planszy wbudowane w klasę Stage
 * 
 * 
**/

class Stage;
									// BLOCK CLASS BEGIN
class Block {
	/** Komentarze:
	 * setTextureRect przy zmianie rozmiaru? możliwe niezbędne dostosowywanie tekstury do rozmiaru komórki Stage
	 * 
	**/
private:
	sf::RectangleShape block;
	sf::Texture* texture;
	
	std::string blockName;
	int currentFrame;
protected:
	sf::Vector2i currentPosAtStage;
	bool solid;
	int amountOfFrames;
	
	void reloadTexture(){
		block.setTexture(texture, true);
		block.setTextureRect(sf::IntRect(0, 0, texture->getSize().x / amountOfFrames, texture->getSize().y));
	}
public:
	enum SpecialTextures {Bordered, NonBordered};
	
	Block(std::string name_ = "None", const int frames_ = 1, const bool solid_ = true) : blockName(name_), currentFrame(0), solid(solid_), amountOfFrames(frames_), texture(nullptr) {
	}
	virtual ~Block() {}
	
	void draw(sf::RenderWindow&) const;
	
	void setTexture(sf::Texture* texture_) {
		texture = texture_;
		// std::cout << blockName << "\'s texture\'s dimensions - " << texture->getSize().x << "x" << texture->getSize().y << '\n';
		reloadTexture();
	}
	sf::Texture* getTexture() const {return texture;}
	// void setSpecialTexture(SpecialTextures spec_);
	
	int nextFrame();
	void setAmountOfFrames(int amount) {amountOfFrames = amount;}
	
	void setSize(const sf::Vector2f& size_) {block.setSize(size_);}
	sf::Vector2f getSize() const {return block.getSize();}
	void setAbsolutePosition(const sf::Vector2f& pos_) {block.setPosition(pos_);}
	sf::Vector2f getAbsolutePosition() const {return block.getPosition();}
	void setSolid(const bool solid_) {solid = solid_;}
	bool getSolid() const {return solid;}
	void setPosAtStage(const sf::Vector2i& position_) {currentPosAtStage = position_;}
	sf::Vector2i getPosAtStage() const {return currentPosAtStage;}

	Block& operator=(const Block& block);
};
// BLOCK CLASS END

									// CHARACTER CLASS BEGIN
class Character : public Block{
	/** Komentarze:
	 * Detektor naciśnięć przycisków odpowiedzialnych za ruch postaci zawarty w klasie?:
	 * plusy:	-tablica bool'i nie musiałaby być za każdym razem przenoszona do funkcji	-przynajmniej pozornie sprzyjałoby to obiektowej stylistyce
	 * 		-łatwiejsza deklaracja wielu obiektów na podstwie klasy Character
	 * 
	 * -Poprawić konstruktor klasy Character (odnośnik do klasy Block)
	**/ 
private:
	bool moveDirections[4] = {false, false, false, false};
	Block previousBlockRow;
	Block* previousBlock = nullptr;
	
	
public:
	enum Direction {Top, Left, Bottom, Right};
	Character(std::string name_ = "PlayerCharacter", const int frames_ = 1, const bool solid_ = true) : Block(name_, frames_, solid_){}
	~Character(){}
	
	void keyDetect(Stage& st_,
			   sf::Keyboard::Key left_ = sf::Keyboard::Key::A,
		    sf::Keyboard::Key top_ = sf::Keyboard::Key::W,
		    sf::Keyboard::Key right_ = sf::Keyboard::Key::D,
		    sf::Keyboard::Key bottom_ = sf::Keyboard::Key::S);

	//set, get, del previous block
	void setPreviousBlock(Block* block_);
	Block* getPreviousBlock() const;
	void removePreviousBlock();

protected:
	bool move(Direction dir_, Stage& stage_);
	
};
// CHARACTER CLASS END