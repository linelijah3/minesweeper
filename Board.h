#pragma once
#include "Tile.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
class Board
{
	int columns, rows, numberOfBombs, tileCount, isGameOver, isDebugEnabled, revealedCount;
	bool gameStart;
	string winOrLose;
	vector<vector<Tile>> tileVector;
public:
	Board();
	Board(int columns, int rows, int numberOfBombs);
	int getColumns(), getRows(), getNumberOfBombs(), getTileCount(), returnDebug(), returnIsGameOver(), getRevealed();
	bool getGameStart();
	void startGame(), enableDebug(), endGame(), setWin(), setLose(), addRevealed(), setColumns(int columns), setRows(int rows), setTileCount(int tileCount);
	void setNumberOfBombs(int numBombs);
	string returnWinOrLose();
	vector<vector<Tile>>& getTileVector();
	Tile getTile(int column, int row);
};

