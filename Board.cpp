#include "Board.h"
#include "TileBag.h"
// #include <bits/stdc++.h>
#include <vector>
#include <iomanip>
#include <iostream>


// Initialising the vector that is attached to the board here
// so its ready to store tiles

Board::Board()
{

    for (int i = 0; i <= ROWS; i++)
    {

        // Vector to store column elements
        std::vector<Tile *> v1;

        for (int j = 0; j <= COLUMNS; j++)
        {
            Tile *newTile = new Tile();
            v1.push_back(newTile);
        }

        // Pushing back above 1D vector
        // to create the 2D vector
        boardState.push_back(v1);
    }
    this->boardScore = 0;
}


// Add a tile to a specific location on the board
// with x/y coordinates

void Board::updateBoard(char y, int x, Tile *tile)
{

    // transform y into number from letter

    int rowLetter = 0;

    for (int i = 0; i < ROWS; i++)
    {

        if (this->row[i] == y)
        {
            rowLetter = i;
        }
    }

    this->boardState[rowLetter][x] = tile;
}

// Display function for showing off the board
// in the main game loop

void Board::printCurrentBoard()
{

    Tile* colourAccess = new Tile();

    int alphabetCounter = 0;

    int column = 0;

    std::cout << "\n";

    std::cout << " " << std::setw(2) << " |";
    for (int k = 0; k < COLUMNS; k++)
    {
        std::cout << std::setw(2) << k << " |";
    }

    std::cout << "\n";

    for (int i = 0; i < ROWS; i++)
    {

        if (column == 0)
        {
            std::cout << this->row[alphabetCounter];
            alphabetCounter = alphabetCounter + 1;
        }

        for (column = 0; column < COLUMNS; column++)
        {

            if (boardState[i][column]->getShape() == 0)
            {
                std::cout << std::setw(2) << "|" << boardState[i][column]->getColour() << " ";
            }
            else
            {
                std::cout << std::setw(2) << "|" << colourAccess->getEscapeCode(boardState[i][column]->getColour())<< boardState[i][column]->getColour() << boardState[i][column]->getShape();
                // Turn console output back to white
                std::cout << "\u001b[37m";
            }
        }

        
        std::cout << std::setw(2) << " |\n";
        column = 0;
    }

    delete colourAccess;
}

// Return all populated values that are on the board
// The board is initialised with empty tiles, 
// so it skips these and only adds player added tiles

std::string Board::printBoardValues()
{

    std::string str = "";

    for (int i = 0; i < COLUMNS; i++)
    {

        for (int j = 0; j < ROWS; j++)
        {

            if (this->boardState[i][j]->getShape() != 0)
            {

                char a = this->boardState[i][j]->getColour();
                std::string b = std::to_string(this->boardState[i][j]->getShape());
                char c = row[i];
                std::string d = std::to_string(j);

                // add tile @ coord with a , separator
                str += a;
                str += b;
                str += '@';
                str += c;
                str += d;
                str += ',';
            }
        }
    }

    return str;
}

//Return the vector that is stored on the board object

std::vector<std::vector<Tile *>> Board::getBoardState()
{

    return this->boardState;
}

int Board::getBoardScore() {
    return this->boardScore;
}

void Board::setBoardScore(int x) {
    this->boardScore += x;
}