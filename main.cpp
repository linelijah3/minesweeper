#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
#include "Digits.h"
using namespace std;
Board getBoard(string fileName);
Board getTestBoards(string fileName);
void setBoard(Board& firstBoard);
void setFlagCounter(int numberOfBombs, int numberOfFlags, Digits& sign, Digits& hundreds, Digits& tens, Digits& ones);
int main()
{
    Board firstBoard = getBoard("boards/config.cfg");
    sf::RenderWindow window(sf::VideoMode(firstBoard.getColumns() * 32, (firstBoard.getRows() * 32 + 100)), "initial board!");
    TextureManager::GetTexture("debug");
    TextureManager::GetTexture("digits");
    TextureManager::GetTexture("face_happy");
    TextureManager::GetTexture("face_lose");
    TextureManager::GetTexture("face_win");
    TextureManager::GetTexture("flag");
    TextureManager::GetTexture("mine");
    TextureManager::GetTexture("tile_hidden");
    TextureManager::GetTexture("tile_revealed");
    for (int i = 1; i <= 8; i++) {
        TextureManager::GetTexture("number_" + to_string(i));
        if (i <=3) {
            TextureManager::GetTexture("test_" + to_string(i));
        }
    }
    sf::Sprite smileSprite(TextureManager::GetTexture("face_happy"));
    sf::Sprite frownSprite(TextureManager::GetTexture("face_lose"));
    sf::Sprite winSprite(TextureManager::GetTexture("face_win"));
    sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
    sf::Sprite example1Sprite(TextureManager::GetTexture("test_1"));
    sf::Sprite example2Sprite(TextureManager::GetTexture("test_2"));
    sf::Sprite example3Sprite(TextureManager::GetTexture("test_3"));
    sf::Sprite hiddenTileSprite(TextureManager::GetTexture("tile_hidden"));
    Digits signSprite;
    Digits hundredsDigitSprite;
    Digits tensDigitSprite;
    Digits onesDigitSprite;
    sf::Sprite sign(signSprite.getSprite());
    sf::Sprite hundreds(hundredsDigitSprite.getSprite());
    sf::Sprite tens(tensDigitSprite.getSprite());
    sf::Sprite ones(onesDigitSprite.getSprite());
    signSprite.setTexture();
    hundredsDigitSprite.setTexture();
    tensDigitSprite.setTexture();
    onesDigitSprite.setTexture();
    int numberOfFlags=0;
    setBoard(firstBoard);
    while (window.isOpen())
    {
        if (firstBoard.returnWinOrLose() == "") {
            setFlagCounter(firstBoard.getNumberOfBombs(), numberOfFlags, signSprite, hundredsDigitSprite, tensDigitSprite, onesDigitSprite);
        }
            smileSprite.setOrigin(smileSprite.getGlobalBounds().width / 2, smileSprite.getGlobalBounds().height / 2);
            smileSprite.setPosition(16.0 * firstBoard.getColumns(), 32.0 * (firstBoard.getRows() + 1));
            window.draw(smileSprite);
            debugSprite.setOrigin(debugSprite.getGlobalBounds().width / 2, debugSprite.getGlobalBounds().height / 2);
            debugSprite.setPosition(16.0 * (firstBoard.getColumns() + 8), 32.0 * (firstBoard.getRows() + 1));
            window.draw(debugSprite);
            example1Sprite.setOrigin(example1Sprite.getGlobalBounds().width / 2, example1Sprite.getGlobalBounds().height / 2);
            example1Sprite.setPosition(16.0 * (firstBoard.getColumns() + 12), 32.0 * (firstBoard.getRows() + 1));
            window.draw(example1Sprite);
            example2Sprite.setOrigin(example2Sprite.getGlobalBounds().width / 2, example2Sprite.getGlobalBounds().height / 2);
            example2Sprite.setPosition(16.0 * (firstBoard.getColumns() + 16), 32.0 * (firstBoard.getRows() + 1));
            window.draw(example2Sprite);
            example3Sprite.setOrigin(example3Sprite.getGlobalBounds().width / 2, example3Sprite.getGlobalBounds().height / 2);
            example3Sprite.setPosition(16.0 * (firstBoard.getColumns() + 20), 32.0 * (firstBoard.getRows() + 1));
            window.draw(example3Sprite);
        frownSprite.setOrigin(frownSprite.getGlobalBounds().width / 2, frownSprite.getGlobalBounds().height / 2);
        frownSprite.setPosition(16.0 * firstBoard.getColumns(), 32.0 * (firstBoard.getRows() + 1));
        winSprite.setOrigin(winSprite.getGlobalBounds().width / 2, winSprite.getGlobalBounds().height / 2);
        winSprite.setPosition(16.0 * firstBoard.getColumns(), 32.0 * (firstBoard.getRows() + 1));
        signSprite.setPosition(0, 32 * (firstBoard.getRows()));
        hundredsDigitSprite.setPosition(21, 32 * (firstBoard.getRows()));
        tensDigitSprite.setPosition(42, 32 * (firstBoard.getRows()));
        onesDigitSprite.setPosition(63, 32 * (firstBoard.getRows()));
        for (int i = 0; i < firstBoard.getColumns(); i++) {
            for (int j = 0; j < firstBoard.getRows(); j++) {
                if (firstBoard.getNumberOfBombs() - numberOfFlags < 0) {
                    window.draw(signSprite.getSprite());
                }
                window.draw(hundredsDigitSprite.getSprite());
                window.draw(tensDigitSprite.getSprite());
                window.draw(onesDigitSprite.getSprite());
                if (firstBoard.returnWinOrLose()=="" && firstBoard.getRevealed() == firstBoard.getTileCount() - firstBoard.getNumberOfBombs()) {
                    firstBoard.endGame();
                    firstBoard.setWin();
                    setFlagCounter(firstBoard.getNumberOfBombs(), firstBoard.getNumberOfBombs(), signSprite, hundredsDigitSprite, tensDigitSprite, onesDigitSprite);
                }
                if ((firstBoard.getTileVector()[i][j].isTileRevealed() == false && firstBoard.getTileVector()[i][j].returnIfClicked() == 0) && firstBoard.getTileVector()[i][j].isTileFlagged() == false) {
                    window.draw(firstBoard.getTileVector()[i][j].getSprite(0));
                }
                else if (firstBoard.getTileVector()[i][j].isTileFlagged()) {
                    window.draw(firstBoard.getTileVector()[i][j].getSprite(0));
                    window.draw(firstBoard.getTileVector()[i][j].getSprite(2));
                }
                else if (firstBoard.getTileVector()[i][j].isTileRevealed() == true) {
                    if (firstBoard.getTileVector()[i][j].hasBomb()) {
                        //cout << "clicked mine at " << i + 1 << ", " << j + 1 << endl;
                        firstBoard.getTileVector()[i][j].setEndColor();
                        window.draw(firstBoard.getTileVector()[i][j].getSprite(1));
                        window.draw(firstBoard.getTileVector()[i][j].getSprite(3));
                    }
                    if (firstBoard.getTileVector()[i][j].getAdjacentMines() == 0 && !firstBoard.getTileVector()[i][j].hasBomb()) {
                        //cout << "should be empty" << endl;
                        window.draw(firstBoard.getTileVector()[i][j].getSprite(1));
                    }
                    if (firstBoard.getTileVector()[i][j].getAdjacentMines() != 0 && !firstBoard.getTileVector()[i][j].hasBomb()) {
                        window.draw(firstBoard.getTileVector()[i][j].getSprite(1));
                        window.draw(firstBoard.getTileVector()[i][j].getSprite(3 + firstBoard.getTileVector()[i][j].getAdjacentMines()));
                    }

                }
                if (firstBoard.returnIsGameOver() % 2 == 1) {
                    if (firstBoard.returnWinOrLose()== "lose") {
                        if (firstBoard.getTileVector()[i][j].hasBomb()) {
                            window.draw(firstBoard.getTileVector()[i][j].getSprite(3));
                        }
                        window.draw(frownSprite);
                    }
                    if (firstBoard.returnWinOrLose() == "win") {
                        if (firstBoard.getTileVector()[i][j].hasBomb()) {
                            window.draw(firstBoard.getTileVector()[i][j].getSprite(2));
                        }
                        window.draw(winSprite);
                    }
                }
                if (firstBoard.returnDebug() % 2 == 1) {
                    if (firstBoard.getTileVector()[i][j].hasBomb()) {
                        window.draw(firstBoard.getTileVector()[i][j].getSprite(3));
                    }
                }
            }
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (firstBoard.returnWinOrLose() == "" &&firstBoard.returnIsGameOver() % 2 == 0 && event.type == event.MouseButtonPressed && debugSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    cout << "clicked debug" << endl;
                    firstBoard.enableDebug();
                }
                int isDebugOn = firstBoard.returnDebug();
                if (event.type == event.MouseButtonPressed && example1Sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    firstBoard = getTestBoards("boards/testboard1.brd");
                    window.setSize(sf::Vector2u(firstBoard.getColumns() * 32, (firstBoard.getRows() * 32 + 100)));
                    cout << "clicked 1st board" << endl;
                    numberOfFlags = 0;
                    for (int i = 0; i < isDebugOn; i++) {
                        firstBoard.enableDebug();
                    }
                }
                if (event.type == event.MouseButtonPressed && example2Sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    firstBoard = getTestBoards("boards/testboard2.brd");
                    window.setSize(sf::Vector2u(firstBoard.getColumns() * 32, (firstBoard.getRows() * 32 + 100)));
                    cout << "clicked 2nd board" << endl;
                    numberOfFlags = 0;
                    for (int i = 0; i < isDebugOn; i++) {
                        firstBoard.enableDebug();
                    }
                }
                if (event.type == event.MouseButtonPressed && example3Sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    firstBoard = getTestBoards("boards/testboard3.brd");
                    window.setSize(sf::Vector2u(firstBoard.getColumns() * 32, (firstBoard.getRows() * 32 + 100)));
                    cout << "clicked 3rd board" << endl;
                    numberOfFlags = 0;
                    for (int i = 0; i < isDebugOn; i++) {
                        firstBoard.enableDebug();
                    }
                }
                if (event.type == event.MouseButtonPressed && smileSprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    firstBoard = getBoard("boards/config.cfg");
                    setBoard(firstBoard);
                    window.setSize(sf::Vector2u(firstBoard.getColumns() * 32, (firstBoard.getRows() * 32 + 100)));
                    cout << "clicked face" << endl;
                    numberOfFlags = 0;
                    for (int i = 0; i < isDebugOn; i++) {
                        firstBoard.enableDebug();
                    }
                }
            }
            for (int i = 0; i < firstBoard.getColumns(); i++) {
                for (int j = 0; j < firstBoard.getRows(); j++) {
                    if (firstBoard.returnWinOrLose() == "" &&firstBoard.returnIsGameOver() % 2 == 0) {
                        if (firstBoard.getTileVector()[i][j].isTileRevealed() == false && firstBoard.getTileVector()[i][j].isTileFlagged() == false && event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && firstBoard.getTileVector()[i][j].getSprite(0).getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            cout << "clicked column " << (i + 1) << " row " << (j + 1) << " tile with left" << endl;
                            firstBoard.getTileVector()[i][j].Reveal();
                            if (firstBoard.getTileVector()[i][j].hasBomb()) {
                                firstBoard.endGame();
                                firstBoard.setLose();
                            }
                            else {
                                firstBoard.addRevealed();
                                cout << firstBoard.getRevealed() << endl;
                                cout << firstBoard.getTileCount()-firstBoard.getNumberOfBombs() << endl;
                            }
                        }
                        if (firstBoard.returnWinOrLose()=="" && firstBoard.getTileVector()[i][j].isTileRevealed() == false && event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && firstBoard.getTileVector()[i][j].getSprite(0).getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            if (firstBoard.getTileVector()[i][j].isTileFlagged() == false) {
                                cout << "tile clicked column " << (i + 1) << " row " << (j + 1) << " tile with right" << endl;
                                firstBoard.getTileVector()[i][j].setTileFlag(true);
                                numberOfFlags++;
                                setFlagCounter(firstBoard.getNumberOfBombs(), numberOfFlags, signSprite, hundredsDigitSprite, tensDigitSprite, onesDigitSprite);
                            }
                            else if (firstBoard.getTileVector()[i][j].isTileFlagged() == true) {
                                cout << "flag clicked column " << (i + 1) << " row " << (j + 1) << " tile with right" << endl;
                                firstBoard.getTileVector()[i][j].setTileFlag(false);
                                numberOfFlags--;
                                setFlagCounter(firstBoard.getNumberOfBombs(), numberOfFlags, signSprite, hundredsDigitSprite, tensDigitSprite, onesDigitSprite);
                            }
                        }
                    }                        
                }
            }
        }
        window.display();
        window.clear(sf::Color(255,255,255,255));
    }
    TextureManager::Clear();
    return 0;
}
void setFlagCounter(int numberOfBombs, int numberOfFlags, Digits& sign, Digits& hundreds, Digits& tens, Digits& ones) {
    int digitsToBeConverted = numberOfBombs - numberOfFlags;
    if (numberOfBombs-numberOfFlags < 0) {
        sign.getDigit(10);
        digitsToBeConverted *= -1;
    }
    else {
        sign.getDigit(-1);
    }
    hundreds.getDigit(digitsToBeConverted/100);
    tens.getDigit((digitsToBeConverted % 100)/10);
    ones.getDigit((digitsToBeConverted%10));
}
Board getBoard(string fileName) {
    ifstream board(fileName);
    if (board.is_open()) {
        int columns, rows, numberOfBombs;
        string tempStore;
        getline(board, tempStore);
        columns = stoi(tempStore);
        getline(board, tempStore);
        rows = stoi(tempStore);
        getline(board, tempStore);
        numberOfBombs = stoi(tempStore);
        Board initialBoard = Board(columns, rows, numberOfBombs);
        return initialBoard;
    }
    return Board();
}
void setBoard(Board& firstBoard) {
    int numberOfBombs = 0, numberOfFlags = 0, placedBombs = 0;
    for (int i = 0; i < firstBoard.getColumns(); i++) {
        vector<Tile> tileVector;
        firstBoard.getTileVector().push_back(tileVector);
        for (int j = 0; j < firstBoard.getRows(); j++) {
            firstBoard.getTileVector()[i].push_back(Tile(0, i, j));
            firstBoard.getTileVector()[i][j].setSprites();
            for (int k = 0; k < 12; k++) {
                firstBoard.getTileVector()[i][j].setSpritePosition(k);
            }
        }
    }
    for (int i = 0; i < firstBoard.getColumns(); i++) {
        for (int j = 0; j < firstBoard.getRows(); j++) {
            while (placedBombs < firstBoard.getNumberOfBombs()) {
                int mineColumn = Random::Int(0, firstBoard.getColumns() - 1), mineRow = Random::Int(0, firstBoard.getRows() - 1);
                if (firstBoard.getTileVector()[mineColumn][mineRow].hasBomb() == false) {
                    firstBoard.getTileVector()[mineColumn][mineRow].setBomb();
                    placedBombs++;
                }
            }
        }
    }
    for (int i = 0; i < firstBoard.getColumns(); i++) {
        for (int j = 0; j < firstBoard.getRows(); j++) {
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    int column = i + k, row = j + l;
                    if ((column) >= 0 && (column) < firstBoard.getColumns() && (row) >= 0 && (row) < firstBoard.getRows()) {
                        firstBoard.getTileVector()[i][j].setAdjacentTiles(&firstBoard.getTileVector()[column][row]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < firstBoard.getColumns(); i++) {
        for (int j = 0; j < firstBoard.getRows(); j++) {
            firstBoard.getTileVector()[i][j].setAdjacentMines();
        }
    }
}
Board getTestBoards(string fileName) {
    ifstream board(fileName);
    Board initialBoard = Board();
    if (board.is_open()) {
        int columns, rows, numberOfBombs, numberOfLines;
        vector<string> tempVector;
        string tempStore;
        while (getline(board, tempStore)) {
            tempVector.push_back(tempStore);
            columns = tempStore.length();
            for (int i = 0; i < columns; i++) {
                vector<Tile> tileVector;
                initialBoard.getTileVector().push_back(tileVector);
            }
        }
        initialBoard.setColumns(columns);
        initialBoard.setRows(tempVector.size());
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < tempVector.size(); j++) {
                initialBoard.getTileVector()[i].push_back(Tile(0, i, j));
                initialBoard.getTileVector()[i][j].setSprites();
                for (int k = 0; k < 12; k++) {
                    initialBoard.getTileVector()[i][j].setSpritePosition(k);
                }
            }
        }
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < tempVector.size(); j++) {
                if (tempVector[j].at(i)=='1') {
                    initialBoard.getTileVector()[i][j].setBomb();
                }
            }
        }
        int bombCount = 0;
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < tempVector.size(); j++) {
                if (initialBoard.getTileVector()[i][j].hasBomb()) {
                    bombCount++;
                }
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        int column = i + k, row = j + l;
                        if ((column) >= 0 && (column) < columns && (row) >= 0 && (row) < tempVector.size()) {
                            initialBoard.getTileVector()[i][j].setAdjacentTiles(&initialBoard.getTileVector()[column][row]);
                        }
                    }
                }
            }
        }
        initialBoard.setTileCount(columns*tempVector.size());
        initialBoard.setNumberOfBombs(bombCount);
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < tempVector.size(); j++) {
                initialBoard.getTileVector()[i][j].setAdjacentMines();
            }
        }
        return initialBoard;
    }
    return Board();
}