
#ifndef SAVES_H
#define SAVES_H

#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include "TileCodes.h"

#include <vector>
#include <string>


// All methods that handle access and manipulation of save files
// should go here

const char row[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
void saveGame(std::string name, Board *currentState,int playerCount, Player* playerArr[], TileBag *tilebag, std::string currentPlayer);
void readBoard(std::string value, Board *board);
void setTileBag(std::string value, TileBag *bag);
std::string stringSolution(int col, int row, std::vector<std::vector<Tile *>> vector);
std::string playerInfo(Player *player);
std::string tileBagContents(TileBag *tilebag);
std::string boardState(Board *currentState);
std::string getCurrentPlayerName(Player *player1, Player *player2, std::string currentPlayer);
std::vector<std::string> returnVector(std::vector<std::string> vector, std::string value, int i, int *lengthPtr);
std::string getCurrentPlayerName(Player *player1, Player *player2, std::string currentPlayer);

#endif // SAVES_H
