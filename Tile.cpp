#include "Tile.h"
bool Tile::isTileFlagged() {
	return this->isFlagged;
}
bool Tile::isTileRevealed() {
	return this->isRevealed;
}
void Tile::setTileFlag(bool isFlagged) {
	this->isFlagged = isFlagged;
}
bool Tile::Reveal() {
	this->isRevealed = true;
	this->hasBeenClicked++;
	if (this->adjacentMines != 0) {
		return false;
	}
	for (int i = 0; i < this->adjacentTiles.size(); i++) {
		if (this->adjacentTiles[i]->isFlagged==false&&this->adjacentTiles[i]->adjacentMines == 0 && this->adjacentTiles[i]->hasBeenClicked == 0) {
			this->adjacentTiles[i]->Reveal();
		}
		else if (this->adjacentTiles[i]->isFlagged == false && this->adjacentTiles[i]->adjacentMines != 0) {
			this->adjacentTiles[i]->Reveal();
		}
	}
	return true;
}
bool Tile::hasBomb() {
	return hasMineOnIt;
}
Tile::Tile(int hasMineOnIt, int column, int row) {
	if (hasMineOnIt == 0) {
		this->hasMineOnIt = false;
	}
	else {
		this->hasMineOnIt = true;
	}
	this->isFlagged = false;
	this->isRevealed = false;
	this->column = column;
	this->row = row;
	this->positionX = 32.0 * column;
	this->positionY = 32.0 * row;
	this->adjacentMines = 0;
	this->hasBeenClicked = 0;
	this->isDebugOn = false;
}
Tile::Tile() {
	this->isDebugOn = false;
	this->hasBeenClicked = 0;
	this->isFlagged = false;
	this->isRevealed = false;
	this->hasMineOnIt = false;
	this->positionX = 0;
	this->positionY = 0;
	this->adjacentMines = 0;
	this->column = 0;
	this->row = 0;
}
void Tile::setBomb() {
	this->hasMineOnIt = true;
}
sf::Sprite Tile::getSprite(int index) {
	return this->spriteVector.at(index);
}
float Tile::getPositionX() {
	return this->positionX;
}
float Tile::getPositionY() {
	return this->positionY;
}
int Tile::getAdjacentMines() {
	return this->adjacentMines;
}
void Tile::changeDebug() {
	if (this->isDebugOn == false) {
		this->isDebugOn = true;
	}
	else {
		this->isDebugOn = false;
	}
}
bool Tile::returnDebug() {
	return this->isDebugOn;
}
void Tile::setSprites() {
	this->spriteVector.push_back(sf::Sprite(TextureManager::GetTexture("tile_hidden")));
	this->spriteVector.push_back(sf::Sprite(TextureManager::GetTexture("tile_revealed")));
	this->spriteVector.push_back(sf::Sprite(TextureManager::GetTexture("flag")));
	this->spriteVector.push_back(sf::Sprite(TextureManager::GetTexture("mine")));
	for (int i = 1; i <= 8; i++) {
		this->spriteVector.push_back(sf::Sprite(TextureManager::GetTexture("number_" + std::to_string(i))));
	}
}
void Tile::whenClicked() {
	this->hasBeenClicked++;
	this->isRevealed =true;
}
int Tile::returnIfClicked() {
	return this->hasBeenClicked;
}
void Tile::setSpritePosition(int index) {
	this->spriteVector.at(index).setPosition(positionX, positionY);
}
void Tile::setAdjacentTiles(Tile* adjacentTile) {
	if (!(adjacentTile->column != this->column && adjacentTile->row != this->row)) {
		(this->adjacentTiles).push_back(adjacentTile);
	}
	else if (adjacentTile->column == this->column-1 && adjacentTile->row == this->row-1) {
		(this->adjacentTiles).push_back(adjacentTile);
	}
	else if (adjacentTile->column == this->column - 1 && adjacentTile->row == this->row + 1) {
		(this->adjacentTiles).push_back(adjacentTile);
	}
	else if (adjacentTile->column == this->column + 1 && adjacentTile->row == this->row - 1) {
		(this->adjacentTiles).push_back(adjacentTile);
	}
	else if (adjacentTile->column == this->column + 1 && adjacentTile->row == this->row + 1) {
		(this->adjacentTiles).push_back(adjacentTile);
	}
}
int Tile::getRow() {
	return this->row;
}
int Tile::getColumn() {
	return this->column;
}
vector<Tile*> Tile::returnTilesToReveal() {
	return this->adjacentTiles;
}
void Tile::setEndColor() {
	this->spriteVector.at(1).setColor(sf::Color(255,0,0));
}
void Tile::setAdjacentMines() {
	for (int i = 0; i < this->adjacentTiles.size(); i++) {
		if (this->adjacentTiles.at(i)->hasMineOnIt) {
			this->adjacentMines++;
		}
	}
}