#include "Board.h"
Board::Board() {
	this->columns = 0;
	this->rows = 0;
	this->numberOfBombs = 0;
	this->tileCount = 0;
	this->gameStart = false;
	this->isDebugEnabled = 0;
	this->isGameOver = 0;
	this->revealedCount = 0;
	this->winOrLose = "";
}
void Board::setColumns(int columns) {
	this->columns = columns;
}
void Board::setNumberOfBombs(int numBombs) {
	this->numberOfBombs = numBombs;
}
void Board::setRows(int rows) {
	this->rows = rows;
}
void Board::setTileCount(int tileCount) {
	this->tileCount = tileCount;
}
bool Board::getGameStart() {
	return this->gameStart;
}
int Board::returnIsGameOver() {
	return this->isGameOver;
}
void Board::endGame() {
	this->isGameOver++;
}
string Board::returnWinOrLose() {
	return this->winOrLose;
}
void Board::setWin() {
	this->winOrLose = "win";
}
void Board::setLose() {
	this->winOrLose = "lose";
}
void Board::addRevealed() {
	int actualRevealed=0;
	for (int i = 0; i < this->columns; i++) {
		for (int j = 0; j < this->rows; j++) {
			if (this->getTileVector()[i][j].isTileRevealed()) {
				actualRevealed++;
			}
		}
	}
	this->revealedCount = actualRevealed;
}
void Board::startGame() {
	this->gameStart = true;
}
int Board::getRevealed() {
	return this->revealedCount;
}
Board::Board(int columns, int rows, int numberOfBombs) {
	this->columns = columns;
	this->rows = rows;
	this->numberOfBombs = numberOfBombs;
	this->tileCount = columns*rows;
	this->gameStart = false;
	this->isDebugEnabled = 0;
	this->isGameOver = 0;
	this->revealedCount = 0;
	this->winOrLose = "";
}
int Board::getColumns() {
	return this->columns;
}
int Board::getRows() {
	return this->rows;
}
int Board::getNumberOfBombs() {
	return this->numberOfBombs;
}
int Board::getTileCount() {
	return this->tileCount;
}
vector<vector<Tile>>& Board::getTileVector() {
	return this->tileVector;
}
Tile Board::getTile(int column, int row) {
	return (this->tileVector)[column][row];
}
int Board::returnDebug() {
	return this->isDebugEnabled;
}
void Board::enableDebug() {
	this->isDebugEnabled++;
}