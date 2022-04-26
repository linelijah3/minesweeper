#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TextureManager.h"
using std::string;
using std::vector;
class Tile
{
	bool isRevealed, isFlagged, hasMineOnIt;
	float positionX, positionY;
	int adjacentMines, row, column, hasBeenClicked, isDebugOn;
	vector<Tile*> adjacentTiles;
	vector<sf::Sprite> spriteVector;
public:
	bool isTileRevealed(), isTileFlagged(), hasBomb(), returnDebug(), Reveal();
	void setTileFlag(bool isFlagged), setBomb(), setSprites(), setSpritePosition(int index), changeDebug();
	sf::Sprite getSprite(int index);
	int getRow(), getColumn(), getAdjacentMines(), returnIfClicked();
	float getPositionX(), getPositionY();
	void setAdjacentTiles(Tile* adjacentTile), setEndColor(), setAdjacentMines(), whenClicked();
	Tile();
	Tile(int hasMineOnIt, int column, int row);
	vector<Tile*> returnTilesToReveal();
};

