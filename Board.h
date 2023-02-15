#ifndef BOARD
#define BOARD

#include "Settings.h"
#include "Tile.h"
#include "TileBag.h"

#include <vector>


// Manages the display and save file storage of 
// everything to do with the board

class Board
{

private:
    const char row[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    // std::vector<std::vector<Tile*>> boardState;
public:
    int boardScore; 

    Board();
    ~Board();
    std::vector<std::vector<Tile *>> boardState;
    std::vector<std::vector<Tile *>> getBoardState();

    void printNewBoard();
    void updateBoard(char y, int x, Tile *tile);

    std::string printBoardValues();
    void printCurrentBoard();
    void loadSavedBoard();

    void setBoardScore(int x);
    int getBoardScore();
};

#endif