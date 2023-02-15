
#include "SaveFilesManip.h"
#include "Settings.h"
#include "Tile.h"
#include "Board.h"
#include "TileBag.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

// All methods that handle access and manipulation of save files
// should go here

// Load the characters in the file into a vector of tiles
void readBoard(std::string values, Board *board)
{

    std::vector<std::string> tilesNLocations;

    // spit out tile+location into vector

    std::string str;

    int n = 0;

    for (long unsigned int i = 0; i < values.length(); i++)
    {

        if (values[i] != ',')
        {
            str += values[i];
        }
        else
        {
            tilesNLocations.push_back(str);
            str = "";
            n++;
        }
    }

    for (int j = 0; j < n; j++)
    {

        std::string tile = tilesNLocations[j];

        Tile *temp = new Tile();

        char colour = tile[0];
        int shape = std::atoi(&tile[1]);
        char y = tile[3];
        int x = std::atoi(&tile[4]);

        temp->setColour(colour);
        temp->setShape(shape);
        board->updateBoard(y, x, temp);
    }
}

// Separates the string in the locations and the tiles
std::vector<std::string> returnVector(std::vector<std::string> vector, std::string value, int i, int *lengthPtr)
{
    // std::vector<std::string> vString;
    char separator = '0';
    int counter = 0;
    if (i == 1)
    {
        separator = ',';
    }
    else if (i == 2)
    {
        separator = '@';
    }
    int k = 0;
    // Temporary string used to split the string.
    std::string str;
    while (value[k] != '\0')
    {
        if (value[k] != separator)
        {
            // Append the char to the temp string.
            str += value[k];
            k++;
        }
        vector.push_back(str);
        ++counter;
        lengthPtr = &counter;
    }
    return vector;
}

// resets the tilebag from the file
void setTileBag(std::string value, TileBag *bag)
{

    for (long unsigned int i = 0; i < value.length(); i += 3)
    {

        Tile *tile = new Tile();
        const char c = value[i];

        tile->setColour(c);
        tile->setShape(std::atoi(&value[i + 1]));

        bag->addTileEnd(tile);
    }
    return;
}

// Saves the game to a text file
void saveGame(std::string saveName, Board *currentState, Player *player1, Player *player2, TileBag *tilebag, std::string currentPlayer)
{

    std::string path = "./save/";
    path += saveName;
    path += ".txt";

    std::ofstream outfile(path);
    outfile << playerInfo(player1);
    outfile << playerInfo(player2);
    outfile << ROWS << ", " << COLUMNS << "\n";
    outfile << currentState->printBoardValues() << "\n";
    outfile << tileBagContents(tilebag) << "\n";
    outfile << currentPlayer;
    void close();
}

// retrieves the values of the players to save in file
std::string playerInfo(Player *player)
{
    std::string pName = player->getName();
    std::string pScore = std::to_string(player->getScore());
    std::string pHand = player->getCurrentHands()->printElementChar();
    std::string newLine = "\n";
    std::string str = pName + newLine + pScore + newLine + pHand + newLine;
    return str;
}

std::string boardState(Board *currentState)
{
    std::string strValue = "";
    std::vector<std::vector<Tile *>> vector = currentState->getBoardState();
    for (int col = 0; col < COLUMNS; col++)
    {
        for (int rows = 0; rows < ROWS; rows++)
        {
            std::string str = stringSolution(col, rows, vector);
            std::string empty = "|  ";
            if (str != empty)
            {
                strValue += str + "@" + std::to_string(row[rows]) + std::to_string(COLUMNS) + ",";
            }
        }
        strValue += "\n";
    }
    return strValue;
}

// Assigns a string value to tile vector values to
std::string stringSolution(int col, int row, std::vector<std::vector<Tile *>> vector)
{
    std::string empty = "|  ";
    if (vector[col][row] == nullptr)
    {
        return empty;
    }
    else
    {
        Tile *tile = vector[col][row];
        char str[4] = {};
        str[0] = '|';
        str[1] = tile->getColour();
        str[2] = tile->getShape();
        return str;
    }
}

std::string tileBagContents(TileBag *tilebag)
{
    std::string str = (tilebag->getBagList())->printElementChar();
    return str;
}

std::string getCurrentPlayerName(Player *player1, Player *player2, std::string currentPlayer)
{
    std::string name1 = player1->getName();
    std::string name2 = player2->getName();

    if (currentPlayer == name1)
    {
        return name1;
    }
    else if (currentPlayer == name2)
    {
        return name2;
    }
    else
    {
        return currentPlayer;
    }
}