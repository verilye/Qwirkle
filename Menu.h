#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H
#include "Player.h"
#include "SaveFilesManip.h"
#include <iostream>

// The Menu Class is all functionality that can be accessed when first
// opening qwirkle. Originally was a series of methods in a file
// but we found it to be more readable to create a class out of it. 

// Functions
void mainMenu();
void creditDisplay();
void newGameMenu(Player *player1, Player *player2, Player* player3, Player* player4, TileBag *bag, Board *board);
void addNewPlayer(int number,Player* player, TileBag* bag );
bool loadGameMenu(Player *player1, Player *player2,Player* player3,Player* player4, TileBag *bag, Board *board);
bool nameCheck(std::string name);
bool numberCheck(int number);

#endif